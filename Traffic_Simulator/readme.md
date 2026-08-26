# Traffic Light Simulation

A C++ console application simulating a semaphore-based crossroad traffic light system using threads, POSIX semaphores, mutexes, and OOP principles.

---

## Dependencies

| Library    | Purpose       | Type           |
|------------|---------------|----------------|
| GoogleTest | Unit testing  | Shared library |
| GoogleMock | Mocking       | Shared library |

---

## Setup

Install GoogleTest and GoogleMock via terminal:

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

The program models a 4-way crossroad with lanes — North, East, South, West. You play the role of a driver. Enter which lane you are in and where you want to go. The system tells you whether you can proceed or how long to wait.

Movement rules are based on your facing direction:

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
  Current green  : EAST (8 sec remaining)
  Your lane turns green in : 18 seconds
========================================

Another query? (y/n): y

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

Another query? (y/n): n

Thank you for using Traffic Light Simulation. Goodbye.
```

---

## Steps to Run the Tests

**Step 1 — Build tests:**
```bash
cd build && make TrafficLightSimulationTests
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
| `UtilsTest` | 36 | All 16 move type cases, string conversions |
| `UserControllerTest` | 17 | Input validation, wait calculation, free moves, green/red logic |
| `TrafficControllerTest` | 12 | Lane initialisation, phase cycling, thread shutdown |
| `TrafficLightSystemTest` | 6 | System wiring, thread spawning, shutdown |
| **Total** | **71** | |
