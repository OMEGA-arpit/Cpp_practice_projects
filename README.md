# C++ Practice Projects

A collection of hands-on C++ projects built to sharpen my skills in systems programming, object-oriented design, multithreading, and software engineering best practices.

Each project lives on its own branch and will be merged into `main` once complete.

---

## Projects

### 🚦 Traffic Light Simulator
**Branch:** `Traffic_light_system`

A multi-threaded console application simulating a 4-way crossroad traffic light system. A driver can query their lane at any time and get a real-time go/wait decision based on the live signal state.

**Key concepts:** `std::thread`, `std::mutex`, `condition_variable`, RAII, `unique_ptr`, SOLID principles, dependency injection, Google Test / Google Mock

---

### 🎵 Music Player
**Branch:** `Music_player`

A console-based music player supporting audio playback, playlist management, and basic playback controls.

**Key concepts:** Audio I/O (miniaudio), OOP design, CMake

---

### 🏦 Banking Application
**Branch:** `Banking_system`

A console-based banking application simulating core account operations — account creation, deposits, withdrawals, and transaction history.

**Key concepts:** OOP, file I/O, data modelling, CMake, Google Test

---

## Repository Structure

```
main                  ← this README and shared config
├── Traffic_light_system  ← Traffic Simulator project
├── Music_player          ← Music Player project
└── Banking_system        ← Banking Application project
```

Each branch is fully self-contained: source code, headers, tests, and a project-level `.gitignore` are all scoped to that branch.

---

## Tech Stack

| Area | Tools |
|---|---|
| Language | C++17 |
| Build | CMake |
| Testing | Google Test, Google Mock |
| Version Control | Git, GitHub |

---

## How to Build a Project

```bash
# Switch to the branch you want
git checkout Traffic_light_system   # or Music_player / Banking_system

# Build
mkdir build && cd build
cmake ..
make

# Run tests
./TrafficLightSimulationTests       # test binary name varies per project
```

---

*These projects are part of my continuous learning journey in modern C++.*