# Refactor Summary

This document records all changes made during the six-phase refactor of the Music Player project. It is intended as a permanent record of design decisions, assumptions, and future work.

---

## Phase 3: Code Refactor

### Module 1 — `inc/Song.h`

| Change | Reason |
|--------|--------|
| `operator==` now compares both `name` **and** `filePath` | Bug: previously only compared `name`, so two songs with the same title but different file paths were treated as equal — breaking duplicate detection |
| Added `noexcept` to `operator<` and `operator==` | Value-type comparators must not throw |
| Replaced empty default constructor with `= default` | Idiomatic C++11 |

### Module 2 — `IPlaylistFactory` / `PlaylistFactory`

| Change | Reason |
|--------|--------|
| `create()` returns `std::unique_ptr<IPlaylist>` | Factory transfers ownership explicitly; raw pointer return was ambiguous about who owns the result |
| `PlaylistFactory::create()` uses `std::make_unique<Playlist>` | Eliminates naked `new` |

### Module 3 — `IPlaylist` / `Playlist`

| Change | Reason |
|--------|--------|
| All getters (`getName`, `getSongs`, `getState`) marked `const` | Getters that don't mutate must be const; this was blocking use through const references |
| `getSongs()` returns `const std::list<Song>&` | Returning mutable reference to internal state allowed external modification of the list structure |
| Removed `isInitialized` bool flag | Redundant state: `isInitialized` was always equal to `!songs.empty()`. Dual state requires manual synchronisation |
| `[[nodiscard]]` on `addSong`, `removeSong`, `moveSongUpward`, `moveSongDownward` | Silently discarding a bool return that signals success/failure is a common source of bugs |
| Explicit iterator loops replaced with range-based `for` and `auto` | Idiomatic C++11; less noise |

### Module 4 — `IPersistenceManager` / `PersistenceManager`

| Change | Reason |
|--------|--------|
| `savePlaylists` / `loadPlaylists` accept `std::map<std::string, std::unique_ptr<IPlaylist>>` | Ownership-correct: the map owns the playlists via unique_ptr |
| `savePlaylist` takes `const IPlaylist&` not `IPlaylist*` | Prefer references over pointers for non-nullable parameters |
| `src/PersistanceManager.cpp` renamed to `src/PersistenceManager.cpp` | Typo fix; the header was already spelled correctly |
| Iterator loops replaced with range-based `for` and structured bindings | Idiomatic C++17 |

### Module 5 — `PlayerService`

| Change | Reason |
|--------|--------|
| Four dependency members changed to `std::unique_ptr` | PlayerService owns these objects (it was deleting them manually); unique_ptr makes ownership explicit and eliminates the custom destructor |
| Playlist map changed to `std::map<std::string, std::unique_ptr<IPlaylist>>` | Same ownership argument; `erase()` now handles cleanup automatically |
| Constructor takes `std::unique_ptr` by value (move in) | Transfers ownership at the call site, making the contract clear |
| Destructor removed | unique_ptr members handle all cleanup |
| `isPlaying`, `getAllSongs`, `searchSong`, `getPlaylistNames` marked `const` | Pure queries must not mutate state |
| All explicit iterator loops replaced | Idiomatic C++11/17 |
| `createPlaylist` / `deletePlaylist` simplified | No explicit `delete`, no redundant boolean temporaries |

### Module 6 — `PlaylistController`

| Change | Reason |
|--------|--------|
| **Bug fix**: `displayLibrarySongs()` null-checked `activePlaylist` before calling `searchSong` | Crash: `getActivePlaylist()` can return `nullptr` when no playlist is open. The "[Added]" marker feature silently crashed |
| `displayAllPlaylists()` and `displayPlaylistSongs()` use range-based `for` | Idiomatic C++11 |

### Module 7 — `MusicApplication`

| Change | Reason |
|--------|--------|
| Four members changed to `std::unique_ptr` | MusicApplication owns all four (was deleting them manually) |
| Member declaration order: `logger` first, `inputHandler` second | C++ destroys members in reverse declaration order. `MiniAudioPlayer` and `PersistenceManager` hold raw pointers to `Logger`; declaring `logger` first ensures it outlives them |
| Destructor removed | unique_ptr handles cleanup |
| Constructor accepts `std::unique_ptr` parameters | Explicit ownership transfer |

### Module 8 — `MusicApplicationFactory` / `main.cpp`

| Change | Reason |
|--------|--------|
| `create()` returns `std::unique_ptr<MusicApplication>` | Communicates ownership at the call site |
| All `new X(...)` replaced with `std::make_unique<X>(...)` | Exception-safe; no naked `new` |
| `main.cpp` uses the returned `unique_ptr` | No manual `delete` |

### Module 9 — `CMakeLists.txt` (new file)

| Change | Reason |
|--------|--------|
| Added `CMakeLists.txt` | No build file existed; developers had to know a manual `g++` incantation |
| C++17 standard, `-Wall -Wextra -Wpedantic` | Project uses `std::filesystem`; strict warnings catch real issues |
| Three targets: `musiclib`, `MusicPlayer`, `MusicPlayerTests` | Clean separation of library, app, and test builds |
| Test target: `-Wno-unused-result` | Test Arrange blocks intentionally discard `[[nodiscard]]` return values; this suppresses only the test binary, leaving production code fully warned |

### Bonus fixes

| Change | File | Reason |
|--------|------|--------|
| Added `virtual ~IMusicLibrary() = default` | `IMusicLibrary.h` | Missing virtual destructor caused `unique_ptr<IMusicLibrary>` to not properly delete derived mock objects — GMock reported leaked mocks |
| `getSongs()` / `findSongByTitle()` made `const` | `IMusicLibrary.h`, `MusicLibrary.h/.cpp` | Consistent with the read-only nature of the library after startup |
| Member init order fixed | `MiniAudioPlayer.cpp` | Init list order differed from member declaration order; `-Wreorder` warning |
| Pre-existing test bug fixed | `MusicApplicationTest.cpp` | `playSong` mock returned `false` by default, so `MSG_NOW_PLAYING` was never triggered; fixed with `WillOnce(Return(true))` |

---

## Phase 4: Unit Test Refactor

### New tests added (132 → 141)

| File | Test name | What it validates |
|------|-----------|-------------------|
| `SongTest.cpp` | `WhenTwoSongsHaveSameNameAndSamePath_ThenTheyAreEqual` | Identical songs compare equal |
| `SongTest.cpp` | `WhenTwoSongsHaveSameNameButDifferentPath_ThenTheyAreNotEqual` | The Phase 3 `operator==` bug fix |
| `SongTest.cpp` | `WhenTwoSongsHaveDifferentName_ThenTheyAreNotEqual` | Basic inequality |
| `PlaylistTest.cpp` | `WhenPlaylistCreated_ThenNameIsCorrect` | `getName()` |
| `PlaylistTest.cpp` | `WhenNewPlaylistCreated_ThenDefaultStateIsStopped` | Default state |
| `PlaylistTest.cpp` | `WhenStateSetToPlaying_ThenGetStateReturnsPlaying` | `setState`/`getState` round-trip |
| `PlaylistTest.cpp` | `WhenStateSetToPaused_ThenGetStateReturnsPaused` | `setState`/`getState` round-trip |
| `PlaylistTest.cpp` | `WhenSongWithSamePathButDifferentNameAdded_ThenItIsRejected` | Dedup is by filePath, not name |
| `PlaylistTest.cpp` | `WhenSongWithSameNameButDifferentPathAdded_ThenBothAreStored` | Two songs with same display name but different paths are distinct |
| `PlayerServiceTest.cpp` | `WhenLoadCalled_ThenDelegatesToPersistenceManager` | `loadPlaylists()` delegation (was the only untested delegation) |

### Mock infrastructure updates (Phase 3 cascade)

All mock files were updated to match refactored interface signatures:

- `IMockPlaylistFactory` — `create()` returns `std::unique_ptr<IPlaylist>`
- `IMockPersistenceManager` — `savePlaylists`/`loadPlaylists` accept unique_ptr maps
- `IMockPlaylist` — getter methods marked `(const, override)`
- `IMockPlayerService` — `getAllSongs`, `searchSong`, `isPlaying`, `getPlaylistNames` marked `(const, override)`
- `IMockMusicLibrary` — `getSongs`, `findSongByTitle` marked `(const, override)`
- `MusicApplicationTest.h` — fixture updated to use `make_unique` + observer raw pointers
- `PlayerServiceTest.h/.cpp` — fixture updated to use `make_unique` + observer raw pointers
- `PersistenceManagerTest.cpp` — map types updated to `unique_ptr`; factory `create()` returns via lambda

---

## Phase 5: Documentation

| Added to | What |
|----------|------|
| All 9 `I*.h` interfaces | Full Doxygen: class-level description, every method (`@brief`, `@param`, `@return`) |
| `Song.h` | Doxygen on struct, fields (with `///`), and operators |
| `MusicApplicationFactory.h` | Doxygen with usage `@code` example |
| `src/PlayerService.cpp` | Comment explaining why `this` capture in on-song-end lambda is safe |
| `src/Playlist.cpp` | Comments on the `removeSong` cursor-update strategy and circular wrap logic |
| `src/MiniAudioPlayer.cpp` | Comments on `MA_SOUND_FLAG_ASYNC` rationale and `checkSongEnd` logic |
| `src/PersistenceManager.cpp` | File-format specification at the top of the file |
| `README.md` (new) | Project overview, architecture diagram, prerequisites, build/run/test instructions, menu reference, usage example, configuration table, known limitations |

---

## Assumptions Made

1. **`checkAndAdvance()` polling is intentional.** The application polls for song-end on every menu loop iteration rather than using a dedicated audio thread or OS-level callback. This design was preserved as-is; changing it would require threading work beyond the scope of a refactor.

2. **`activePlaylistName` is not cleared when the user plays a song directly from the library.** If a user is inside a playlist and then plays a song from the library via the Search menu, the `activePlaylistName` string is not reset. This means if the library song ends, `next()` fires and advances the last-opened playlist. This was the original behaviour and was preserved. It may or may not be intentional.

3. **Song search is case-sensitive.** `MusicLibrary::findSongByTitle` uses `std::set::find` which relies on `Song::operator<` (alphabetical by name). No case-folding is applied. This was the original behaviour.

4. **`Songs/` folder is relative to the working directory.** The application must be launched from the same directory as the `Songs/` folder, not from the `build/` directory. This is documented in the README but not enforced at runtime.

5. **Playlist file is read/written in the working directory.** `playlists.txt` is created next to wherever the binary is run from. No path configuration is available at runtime.

---

## Future Improvements (not implemented)

### Code quality
- **Replace the polling model** (`checkAndAdvance` called from the menu loop) with a thread-safe callback mechanism so that song-end events fire immediately without requiring a menu interaction.
- **Case-insensitive song search** — fold both search term and song name to lowercase before comparing.
- **`std::optional<std::string>` for `activePlaylistName`** — using an empty string as a sentinel for "no active playlist" is fragile; `std::optional` expresses the intent clearly.
- **Error result types** — methods like `playSong` return `bool` with no information about what went wrong. A `std::expected<void, Error>` (C++23) or a simple `Result` enum would give callers richer feedback.

### Features
- **Volume control and seek** — `miniaudio` supports both; surfacing them would require new interface methods and menu options.
- **Additional audio formats** — miniaudio supports FLAC, WAV, MP3, OGG; the extension filter in `MusicLibrary` currently only loads `.mp3`.
- **Multiple sort orders for the library** — currently always alphabetical by name; sorting by date added or most-recently-played would require additional metadata.

### Build / CI
- **CI pipeline** — a GitHub Actions workflow running `cmake --build` and `ctest` on every push would prevent regressions.
- **Code coverage** — `lcov` + `gcov` integration in CMake to track test coverage per file.
- **Static analysis** — `clang-tidy` or `cppcheck` pass in CI to catch issues the compiler warnings don't catch.
- **Address Sanitizer build** — add a CMake preset with `-fsanitize=address,undefined` to catch memory errors that tests might otherwise not detect deterministically.
- **Doxygen HTML generation** — add a CMake custom target (`make docs`) that runs Doxygen to generate browsable API docs from the existing `@brief`/`@param` comments.
