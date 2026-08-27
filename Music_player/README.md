# Music Player

A console-based C++ music player with playlist management, built as a learning project and refactored to production-quality code.

## Features

- **Music library** — scans a `Songs/` folder (and subfolders) for `.mp3` files at startup
- **Search** — find a song by name and play it immediately
- **Playlists** — create, open, and delete named playlists
- **Playlist operations** — add / remove songs, reorder songs (move up/down), play/pause/next/previous
- **Circular navigation** — next on the last song wraps to the first; previous on the first wraps to the last
- **Persistence** — playlists are saved to `playlists.txt` on exit and restored on the next launch
- **Auto-advance** — when a track ends naturally the next song in the active playlist plays automatically

## Folder Structure

```
Music_player/
├── inc/               # All header files (interfaces + concrete class declarations)
│   ├── I*.h           # Pure-virtual interfaces (one per component)
│   ├── Song.h         # Plain data type
│   ├── Constants.h    # Application-wide constants and enums
│   └── ...
├── src/               # Implementation files
├── main/
│   └── main.cpp       # Entry point
├── Test/
│   ├── inc/           # Test fixture headers and GoogleMock mock headers
│   ├── src/           # Test implementation files
│   └── main/
│       └── main.cpp   # Test runner entry point
├── Songs/             # Place your .mp3 files here (created at runtime)
├── CMakeLists.txt     # Build system
└── README.md          # This file
```

## Architecture

The project follows an **interface-per-dependency** design that enables full mocking in tests.

```
MusicApplicationFactory     ← composition root; wires the full object graph
  └── MusicApplication      ← main menu loop
        ├── PlayerService   ← facade: coordinates all playback/playlist ops
        │     ├── MusicLibrary        ← scans Songs/ with std::filesystem
        │     ├── MiniAudioPlayer     ← wraps the miniaudio C library
        │     ├── PersistenceManager  ← reads/writes playlists.txt
        │     └── PlaylistFactory     ← creates Playlist instances
        ├── PlaylistController ← playlist and song operation menus
        ├── Logger             ← wraps std::cout
        └── InputHandler       ← wraps std::cin with validation
```

Ownership is expressed via `std::unique_ptr`. Every component that allocates
a dependency owns it and automatically releases it on destruction.

## Prerequisites

| Dependency | Version | Notes |
|------------|---------|-------|
| CMake | ≥ 3.16 | Build system |
| GCC or Clang | C++17 support | `std::filesystem` required |
| GoogleTest | 1.11+ | Installed via `libgtest-dev` / `libgmock-dev` |
| miniaudio | any | Single-header; auto-downloaded during CMake configure (requires internet) |

### Install system dependencies (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install -y build-essential cmake libgtest-dev libgmock-dev
```

## Build Instructions

```bash
# 1. Clone / enter the project directory
cd Music_player

# 2. Configure (downloads miniaudio.h if not present)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# 3. Build everything
cmake --build build --parallel
```

This produces two binaries inside `build/`:

| Binary | Purpose |
|--------|---------|
| `MusicPlayer` | The application |
| `MusicPlayerTests` | The unit test suite |

## Running the Application

Place `.mp3` files in a `Songs/` directory next to the binary (or in subdirectories):

```
Songs/
  Aahatein.mp3
  Believer.mp3
  Favourites/
    TumHiHo.mp3
```

Then run:

```bash
cd build
./MusicPlayer
```

The application loads `playlists.txt` from the working directory on startup and saves it on exit (menu option 5).

## Running the Tests

```bash
cd build
./MusicPlayerTests
```

Or via CTest:

```bash
cd build
ctest --output-on-failure
```

Expected output: **141 tests**, all passing.

## Usage Guide

### Main Menu

```
===============OPERATIONS===============
1. My Playlists
2. Display All Songs
3. Search
4. Pause/Resume
5. Exit
========================================
```

| Option | Action |
|--------|--------|
| 1 | Open the playlist manager |
| 2 | List all songs found in the `Songs/` folder |
| 3 | Search for a song by name and optionally play it |
| 4 | Toggle pause/resume for the currently playing track |
| 5 | Save playlists and exit |

### Playlist Manager

```
===============PLAYLIST OPERATIONS===============
1. Open Playlist
2. Create Playlist
3. Delete Playlist
4. Back
```

### Inside a Playlist

```
===============SONGS OPERATIONS===============
1. Play/Pause
2. Next
3. Previous
4. Add Song
5. Remove Song
6. Move Song Upward
7. Move Song Downward
8. Back
```

The currently playing song is marked with `>>` in the song list.

### Example Session

```
Welcome to Music Player

> 2              # Display All Songs
1. Aahatein
2. Believer

> 3              # Search
Enter song name: Aahatein
Found: Aahatein
Press p to play or b to go back: p
Now playing: Aahatein

> 1              # My Playlists → Create Playlist
Enter playlist name: Chill Vibes
Playlist created successfully.

# Open "Chill Vibes" → Add Song → type "Aahatein"
# Song added successfully.

> 5              # Exit (saves playlists.txt)
Thank you for using the application!
```

## Configuration

| Constant | Location | Default | Description |
|----------|----------|---------|-------------|
| `SONGS_FOLDER_PATH` | `Constants.h` | `"Songs"` | Folder scanned for `.mp3` files |
| `PLAYLIST_FILE_PATH` | `Constants.h` | `"playlists.txt"` | Persistence file location |

Both paths are relative to the working directory from which the binary is launched.

## Known Limitations

- Only `.mp3` files are supported (miniaudio supports more formats; extending this requires changing the extension filter in `MusicLibrary::loadSongsFromFolder`).
- `checkAndAdvance()` uses a polling model — end-of-track detection happens on the next menu loop iteration, not immediately.
- No volume control or seek functionality.
- Song search is case-sensitive and requires an exact name match.
