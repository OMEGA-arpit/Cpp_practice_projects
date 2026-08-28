# Music Player

A C++ console application for managing and playing music using OOP principles, interfaces, and dependency injection.

---

## Dependencies

| Library    | Purpose          | Type          |
|------------|------------------|---------------|
| miniaudio  | Audio playback   | Header-only   |
| GoogleTest | Unit testing     | Shared library|
| GoogleMock | Mocking          | Shared library|

---

## Setup

Install GoogleTest and GoogleMock via terminal:

```bash
sudo apt install libgtest-dev libgmock-dev
```

Download the following header and place it in `inc/` before building:

- **miniaudio.h** — https://github.com/mackron/miniaudio
  Place at `inc/miniaudio.h`

---

## Build and Run

**Step 1 — Create a `bin` directory:**

```bash
mkdir bin
```

**Step 2 — Compile to object files:**

```bash
cd bin && g++ -I../inc -c ../src/*.cpp && cd ..
```

**Step 3 — Create static library:**

```bash
ar rcs libmusicplayer.a bin/*.o
```

**Step 4 — Build executable:**

```bash
g++ -I./inc main/main.cpp -L. -lmusicplayer -o MusicPlayer.out
```

**Step 5 — Run:**

```bash
./MusicPlayer.out
```

---

## Songs Folder

Place your `.mp3` files in the `Songs/` folder next to the executable. Subfolders are supported:

```
Songs/
├── Bollywood/
│   ├── Aahatein.mp3
│   └── Tum Hi Ho.mp3
└── English/
    ├── Believer.mp3
    └── Shape of You.mp3
```

The library will scan all subfolders automatically on startup.

---

## Persistence

Playlists are saved to `playlists.txt` automatically when the program exits. On next startup they are loaded back into memory. No manual saving needed.

---

## Sample Usage

```
============================================
        Welcome to Music Application
============================================

===============OPERATIONS===============
1. My Playlists
2. Display All Songs
3. Search
4. Exit
========================================
Enter your choice: 2

============ MUSIC LIBRARY ============
1. Aahatein
2. Believer
3. Tum Hi Ho

===============OPERATIONS===============
Enter your choice: 3
Enter song name: Aahatein
Found: Aahatein
Press p to play or b to go back:        
Enter choice: p
Now playing: Aahatein
```

---

## Steps to Run the Tests

### Compile all tests in a single test file

```bash
cd Test && g++ -I../inc -I./inc ../src/*.cpp src/*.cpp main/main.cpp -lgtest -lgmock -lpthread -o MusicPlayerTests.out
```

### Compile a single test file

```bash
cd Test && g++ -I../inc -I./inc ../src/*.cpp src/PlaylistTest.cpp main/main.cpp -lgtest -lgmock -lpthread -o MusicPlayerTests.out
```

Replace `PlaylistTest.cpp` with any other test file to compile that file instead.

### Run the tests

```bash
./MusicPlayerTests.out
```
