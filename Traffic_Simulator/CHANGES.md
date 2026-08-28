# Refactoring Summary — Traffic Light Simulation

Complete record of every change made during the production-quality refactor.
No runtime behaviour was modified. All 69 tests pass with zero compiler warnings
(`-Wall -Wextra -Wpedantic`).

---

## Phase 3 — Code Refactoring

### 3.1 `Constants.h`
| Before | After | Reason |
|---|---|---|
| `const int GREEN_DURATION_SECONDS = 10` | `constexpr int GREEN_DURATION_SECONDS = 10` | Enables compile-time evaluation; `constexpr` is the correct qualifier for a compile-time integer constant |

---

### 3.2 `Lane.h`
| Before | After | Reason |
|---|---|---|
| `bool operator==(const Lane& other)` | `bool operator==(const Lane& other) const` | Missing `const` prevented comparing `Lane` values on `const` objects and was a correctness bug |

---

### 3.3 All four interface headers (`IInputHandler.h`, `ILogger.h`, `ITrafficController.h`, `IUserController.h`)
| Before | After | Reason |
|---|---|---|
| `virtual ~T() {}` | `virtual ~T() = default` | `= default` is more explicit; the compiler generates an identical destructor, making the intent unambiguous |

---

### 3.4 `MoveResult.h` + `MoveResult.cpp`
| Before | After | Reason |
|---|---|---|
| Separate `MoveResult()` constructor declared in header, defined in `.cpp` | In-class member initializers on each field; no explicit constructor | Struct initialization belongs at the declaration site; eliminates a needless translation unit; default construction is now implicit and always correct |

`MoveResult.cpp` is retained (empty body) to avoid a CMake change.

---

### 3.5 `ILogger.h`, `Logger.h`, `Logger.cpp`, `UserController.cpp`, `IMockLogger.h`, test SetUp files
**Removed `printNewLine()` from the `ILogger` interface entirely.**

| Before | After | Reason |
|---|---|---|
| `virtual void printNewLine() = 0` in `ILogger` | Removed | A method that only prints `'\n'` is an implementation detail leaking into a public contract. Callers now use `printMessage("\n")`, which is identical in behaviour |
| `logger->printNewLine()` in `UserController::displayMoveResult` | `logger->printMessage(std::string(1, Constants::NEW_LINE))` | Updated to use the remaining interface method |
| `MOCK_METHOD(void, printNewLine, ...)` in `IMockLogger` | Removed | Mock tracks the interface; removed with the interface method |
| `EXPECT_CALL(logger, printNewLine()).Times(AnyNumber())` in two test `SetUp` bodies | Removed | Expectation for a removed method |

---

### 3.6 `Utils.h` + `Utils.cpp`
| Before | After | Reason |
|---|---|---|
| No `[[nodiscard]]` on any method | Added to all four static methods | Silently discarding the return value of `stringToDirection` (a bool) or `determineMoveType` is always a logic error; the attribute makes the compiler warn at the call site |
| `stringToDirection(const std::string& input, ...)` | `stringToDirection(std::string_view input, ...)` | C++17: `string_view` avoids an unnecessary heap allocation when the caller already holds a `string` or a string literal |
| Misaligned columns in `determineMoveType` lookup table | Aligned with row/column header comments | Readability only |

---

### 3.7 `TrafficState.h`
**Added `TrafficStateSnapshot` — a plain, mutex-free struct.**

| Before | After | Reason |
|---|---|---|
| `UserController::processQuery` created a full `TrafficState` (containing a `std::mutex`) as a local "snapshot" variable | Creates `TrafficStateSnapshot` instead | `TrafficState` is non-copyable because of its mutex. Constructing one just to hold two copied integers was misleading and fragile — any new field added to `TrafficState` would silently not appear in the snapshot |

`TrafficStateSnapshot` fields have in-class defaults so it is always safe to construct without explicit initialization.

---

### 3.8 `UserController.h` + `UserController.cpp`
| Before | After | Reason |
|---|---|---|
| `calculateWaitTimeInSeconds(Direction, const TrafficState&)` | `calculateWaitTimeInSeconds(Direction, const TrafficStateSnapshot&)` | Uses the new explicit, copyable snapshot type |
| `buildMoveResult(Direction, Direction, const TrafficState&)` | `buildMoveResult(Direction, Direction, const TrafficStateSnapshot&)` | Same |
| `TrafficState snapshot; { lock; copy fields }` | `TrafficStateSnapshot snapshot; { lock; copy fields }` | Same |

---

### 3.9 `TrafficController.cpp`
**Removed the implicit `-1` initialization trick.**

| Before | After | Reason |
|---|---|---|
| `activeLaneIndex(-1)` in the initializer list, relying on `(-1 + 1) % 4 = 0` on the first `activateNextPhase()` call | `activeLaneIndex = static_cast<int>(orderedLaneCycle.size()) - 1` set after `initializeLanes()` | The `-1` approach was a non-obvious invariant. The new code explicitly states: "start at the last index so the first wrap gives index 0 (NORTH)" |

---

### 3.10 `TrafficLightSystemFactory.h` + `TrafficLightSystemFactory.cpp` + `main/main.cpp`
**Replaced all raw `new`/`delete` with `std::unique_ptr`.**

| Before | After | Reason |
|---|---|---|
| Five raw `T*` member pointers | Five `std::unique_ptr<T>` members | Eliminates all manual memory management |
| Explicit default constructor initializing all pointers to `nullptr` | Compiler-generated default constructor | `unique_ptr` default-initializes to `nullptr`; no boilerplate needed |
| Explicit destructor with five `delete` calls in a specific order | Compiler-generated destructor | RAII destroys members in reverse-declaration order, which matches the required teardown sequence |
| `createTrafficLightSystem()` returns raw `TrafficLightSystem*` | Returns `std::unique_ptr<TrafficLightSystem>` | Ownership is now expressed in the return type |
| `main.cpp`: `TrafficLightSystem* system = ...; delete system;` | `auto system = ...;` — no manual delete | Owned by the `unique_ptr`; destroyed automatically at end of scope |

`TrafficLightSystem` itself retains raw (non-owning) observer pointers to components because the factory owns them and outlives the system.

---

### 3.11 `UserControllerTest.cpp` — Lane Order Bug Fix
**Critical correctness bug: tests used cycle order `[N, E, S, W]`; production uses `[N, S, E, W]`.**

| Test | Before | After |
|---|---|---|
| `SetUp` lane registration | `[N, E, S, W]` | `[N, S, E, W]` — matches `TrafficController::initializeLanes()` |
| `WhenMyLaneIsNextInCycle` | From EAST, to WEST (straight) — EAST was "next" only in the wrong order | From SOUTH, to NORTH (straight) — SOUTH is actually next after NORTH in production |
| `WhenMyLaneIsTwoPhasesAway` | From SOUTH, to NORTH — SOUTH was two phases away only in the wrong order | From EAST, to WEST — EAST is two phases from NORTH in production (`N→S→E`) |
| `WhenMyLaneIsThreePhasesAway` | From WEST, to EAST | Unchanged — WEST is three phases from NORTH in both orderings |

Expected numeric values (6, 14, 23) were unchanged because the arithmetic still produces the same results with the correct lane pairings.

---

## Phase 4 — Unit Test Refactoring

### New tests added to `GivenUserControllerTest`

| Test name | What it covers | Why it was missing |
|---|---|---|
| `WhenStraightAndLaneIsGreen_ThenDisplaysTimeRemaining` | `MSG_TIME_REMAINING` with the exact second count is shown when the lane is green | Existing green tests only checked `MSG_GREEN_GO`; the time-remaining line was never verified |
| `WhenLaneIsRed_ThenDisplaysCurrentGreenLaneInfo` | `MSG_CURRENT_GREEN` showing the correct active lane name and its remaining time | The red branch prints three messages; existing tests only checked the first (`MSG_RED_WAIT`) and third (`MSG_LANE_GREEN_IN`). The second was unverified |
| `WhenLaneWrapsAroundInCycle_ThenWaitIsTimeRemainingOfCurrentPhase` | Cycle wrap-around: WEST is active → NORTH is the very next lane (index `(3+1)%4 = 0`) | The three existing wait-time tests covered 1-phase, 2-phase, and 3-phase scenarios but never a wrap-around case |

---

## Phase 5 — Documentation

### Doxygen added to

| File | What was documented |
|---|---|
| `IInputHandler.h` | Class contract (purpose, threading note), `inputString` parameter and blocking behaviour |
| `ILogger.h` | Class contract, `printMessage` parameter |
| `ITrafficController.h` | Class contract (threading model), `startTrafficCycle` (blocks), `stopTrafficCycle` (unblocks) |
| `IUserController.h` | Class contract, `handleUserQueries` (blocks) |
| `Utils.h` | Class brief, all four static methods with full `@param`/`@return` and the enum-ordinal invariant note on `determineMoveType` |
| `Lane.h` | Struct brief |
| `MoveResult.h` | Struct brief, `///` inline docs on `canGoNow`, `waitSeconds`, `timeRemaining` |
| `TrafficState.h` | Both structs: `TrafficStateSnapshot` (intent and fragility note), `TrafficState` (mutex-guard requirement) |
| `TrafficController.h` | Class brief (threading, CV design, lock scope), constructor `@param`, `getOrderedLaneCycle` stability note |
| `TrafficLightSystem.h` | Class brief (thread lifecycle, ownership note), `initiateTrafficSystem` |
| `TrafficLightSystemFactory.h` | Class brief (build order, RAII teardown, lifetime constraint), `createTrafficLightSystem` |

### Inline algorithm comments added to

| File / Function | What was annotated |
|---|---|
| `TrafficController.cpp` — `activateNextPhase` | Why the lock scope is minimal (brief write, not the whole phase) |
| `TrafficController.cpp` — `countDownCurrentPhase` | The `condition_variable::wait_for` pattern: returns `true` (predicate satisfied) on early wakeup from `stopTrafficCycle()` |
| `UserController.cpp` — `calculateWaitTimeInSeconds` | The walk-forward algorithm, the wrap-around comment on `% totalLanes`, and the "already green = 0 wait" branch |
| `Utils.cpp` — `determineMoveType` | Row/column header comments on the 4×4 lookup table |

### `readme.md` updated

- Added **Architecture** section (thread/class/role table)
- Added **Folder Structure** section
- Corrected test counts: total 71 → 69; per-suite counts corrected
- Corrected suite names in filter examples (`UtilsTest` → `GivenUtils`, etc.)
- Fixed the sample output "current green" line to match actual code output format

---

## Phase 6 — Final Verification & Test Audit

### Trivially-passing assertions replaced

| Test | Old assertion | New assertion | Problem |
|---|---|---|---|
| `WhenStopCycleCalled_ThenThreadJoinsCleanly` | `SUCCEED()` | `EXPECT_EQ(trafficState.activeLane, Constants::Direction::NORTH)` | `SUCCEED()` is a no-op. Thread join failure causes a hang, not a test failure. The new assertion verifies `activateNextPhase()` ran and produced the expected first phase |
| `WhenCycleRuns_ThenActiveLaneIsAlwaysAValidDirection` | `EXPECT_TRUE(isValid)` where `isValid = (lane == N \|\| lane == S \|\| lane == E \|\| lane == W)` | `EXPECT_EQ(trafficState.timeRemaining, Constants::GREEN_DURATION_SECONDS)` | Since `Direction` is a scoped enum with exactly 4 members, `isValid` is structurally always `true` — equivalent to `EXPECT_TRUE(true)`. The new assertion verifies that the stop signal interrupted the countdown before any 1-second tick decremented `timeRemaining` |

---

## Final State

| Metric | Before | After |
|---|---|---|
| Compiler warnings (`-Wall -Wextra -Wpedantic`) | Not enforced | **0** |
| Test count | 66 | **69** |
| Tests passing | 66 | **69** |
| Raw `new` / `delete` calls (production code) | 7 | **0** |
| Interface methods that leaked implementation detail | 1 (`printNewLine`) | **0** |
| `[[nodiscard]]` on value-returning utility functions | 0 | **4** |
| Test assertions that were trivially true | 2 | **0** |
| Lane-order bug in test fixture | Present | **Fixed** |

---

## Assumptions

1. **Cycle order** — `[N, S, E, W]` as implemented in `TrafficController` is the authoritative order. The `UserControllerTest` fixture was treated as a bug, not an intentional alternative.
2. **`printNewLine` removal** — Treated as a pure interface smell. If a future output target requires newlines to be handled differently from other text, `ILogger` would need to be reconsidered.
3. **50 ms test timing** — The `TrafficController` thread tests sleep for 50 ms then stop. This is assumed sufficient for `activateNextPhase()` to execute on any modern machine. No clock abstraction was introduced.

---

## Suggestions for Future Improvement

These were not implemented — they are observations for the next iteration.

1. **CI/CD** — A GitHub Actions pipeline running `cmake && make && ctest --output-on-failure` on every push would catch regressions automatically.

2. **Mockable clock for `TrafficController`** — Injecting a clock abstraction would allow a test to verify that the active lane advances from NORTH → SOUTH after one full phase, without requiring a real 10-second wait.

3. **Thread-safe `TrafficState` encapsulation** — The current pattern requires every reader to remember to take `stateMutex` manually. Encapsulating `activeLane` and `timeRemaining` behind getter/setter methods that lock internally would eliminate the possibility of accidentally reading without a lock.

4. **Configurable green duration per lane** — `GREEN_DURATION_SECONDS` is a single compile-time constant applied to all lanes. Accepting a per-lane duration map in the factory would allow realistic asymmetric phasing.

5. **Case-insensitive input** — `stringToDirection` rejects lowercase ("n", "north"). An `std::toupper` transform before comparison would improve usability without changing the interface.

6. **`UserController` private method testability** — `calculateWaitTimeInSeconds` and `buildMoveResult` are private, so they are only tested indirectly through `handleUserQueries`. Extracting a `MoveCalculator` class would allow direct unit tests for the wait arithmetic without needing to set up mock input/output sequences.
