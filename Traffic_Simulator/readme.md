# Traffic Light Simulation

A C++ console application simulating a 4-way crossroad traffic light system using threads, mutexes, condition variables, and OOP / SOLID principles.

---

## Architecture

Two threads run concurrently:

| Thread | Class | Role |
|--------|-------|------|
| Controller | `TrafficController` | Cycles the green light through lanes (N→S→E→W), updating shared `TrafficState` each second |
| Input | `UserController` | Accepts driver queries, computes move type and wait time from a snapshot of `TrafficState`, displays result |

All components are constructed and owned by `TrafficLightSystemFactory` via `std::unique_ptr`. The `TrafficLightSystem` holds non-owning observer pointers and joins both threads on shutdown.

---

## Folder Structure

```
Traffic_Simulator/
├── inc/          # All header files
├── src/          # All implementation files
├── main/         # Entry point (main.cpp)
├── Test/
│   ├── inc/      # Test fixtures and mock headers
│   ├── src/      # Test implementation files
│   └── main/     # Google Test entry point
├── CMakeLists.txt
└── readme.md
```

---

## Dependencies

| Library    | Purpose       | Type           |
|------------|---------------|----------------|
| GoogleTest | Unit testing  | Shared library |
| GoogleMock | Mocking       | Shared library |

---

## Setup

Install GoogleTest and GoogleMock:

```bash
sudo apt install libgtest-dev libgmock-dev
```

---

## Build and Run

**Step 1 — Create a build directory:**
```bash
mkdir build
```

**Step 2 — Run CMake:**
```bash
cd build && cmake ..
```

**Step 3 — Build:**
```bash
make
```

**Step 4 — Run:**
```bash
./TrafficLightSimulation
```

---

## How It Works

The program models a 4-way crossroad — North, East, South, West. You play the role of a driver. Enter which lane you are in and where you want to go. The system tells you whether you can proceed or how long to wait.

Movement rules:

| Move | Permission |
|---|---|
| U-Turn | Always free — no signal needed |
| Left Turn | Always free — no signal needed |
| Right Turn | Needs green light |
| Straight | Needs green light |

The traffic light cycles automatically — `NORTH → SOUTH → EAST → WEST` — on its own thread while you interact with the system in real time.

---

## Sample Usage

```
========================================
       TRAFFIC LIGHT SIMULATION
========================================
   Semaphore-based crossroad controller
========================================

          |  N  |
          |  ^  |
          |     |
----------+     +----------
  W <                > E
----------+     +----------
          |     |
          |  v  |
          |  S  |

Which lane are you in? (N/S/E/W): N
Where do you want to go?  (N/S/E/W): S

========================================
            TRAFFIC STATUS
========================================
  From : NORTH
  To   : SOUTH
  Move : Straight

🔴  Your lane is RED — Please wait.
  Current green  : Vehicles from EAST can move (8 sec remaining)
  Your lane turns green in : 18 seconds
========================================

Another query? (Y/N): Y

Which lane are you in? (N/S/E/W): N
Where do you want to go?  (N/S/E/W): E

========================================
            TRAFFIC STATUS
========================================
  From : NORTH
  To   : EAST
  Move : Left Turn

🟢  Free move — No signal needed. You may proceed.
========================================

Another query? (Y/N): N

Thank you for using Traffic Light Simulation. Goodbye.
```

---

## Steps to Run the Tests

**Step 1 — Build tests (from the build directory):**
```bash
make TrafficLightSimulationTests
```

**Step 2 — Run all tests:**
```bash
ctest --output-on-failure
```

**Or run the test binary directly:**
```bash
./TrafficLightSimulationTests
```

**To run a specific test suite:**
```bash
./TrafficLightSimulationTests --gtest_filter=GivenUtils*
./TrafficLightSimulationTests --gtest_filter=GivenUserControllerTest*
./TrafficLightSimulationTests --gtest_filter=GivenTrafficControllerTest*
./TrafficLightSimulationTests --gtest_filter=GivenTrafficLightSystemTest*
```

---

## Test Coverage

| Suite | Tests | What Is Covered |
|---|---|---|
| `GivenUtils` | 36 | All 16 move-type cases (4 directions × 4 moves), all direction/move string conversions, invalid input handling |
| `GivenUserControllerTest` | 17 | Input validation, free moves, green/red display, time remaining, current green info, wait time calculation (1-, 2-, 3-phase and wrap-around) |
| `GivenTrafficControllerTest` | 11 | Lane initialisation order, green durations, thread shutdown, active lane validity, time remaining range |
| `GivenTrafficLightSystemTest` | 5 | System wiring, welcome/road display, thread spawning, clean shutdown |
| **Total** | **69** | |
