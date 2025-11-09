# Red Robot 2025

This repository contains the C++ source code for the 2025 competition robot, "Red Robot". The project is developed using the PlatformIO IDE.

## Latest Changes: Ultrasonic Sensor Overhaul

The `UltrasonicSensor` subsystem was recently refactored to address a critical performance issue and improve overall robustness.

-   **Problem**: The previous implementation caused significant input lag. It used a blocking `pulseIn()` call on every main loop cycle, halting the microcontroller and delaying its response to driver commands.
-   **Solution**:
    -   **Non-Blocking Reads**: The sensor logic was converted to a non-blocking state machine. It now uses a `millis()` timer to trigger a sensor reading only at a fixed interval (e.g., every 50ms), which eliminates input lag.
    -   **Improved Robustness**: A specific timeout, tailored to the arena size, was added to the `pulseIn()` call to prevent it from blocking for too long when an object is out of range.
    -   **Enhanced Safety**: The `get_distance_in()` function now returns `std::optional<double>`. This makes the subsystem's state explicit, eliminating the ambiguity between a "zero distance" reading and an "out of range" or "not yet read" state, preventing a class of potential bugs in autonomous logic.

## Documentation

### Build Environment

This project is configured to be built with [PlatformIO](https://platformio.org/). All dependencies and build configurations are managed through the `platformio.ini` file.

To build the project, use the PlatformIO CLI:
```bash
pio run
```

To upload the code to the robot's microcontroller:
```bash
pio run --target upload
```

### Folder Structure

The repository is organized as follows:

-   `src/`: Contains the implementation files (`.cpp`).
    -   `main.cpp`: The entry point of the program. It initializes all subsystems and contains the main robot loop.
    -   `subsystems/`: Directory containing the implementation for each robot subsystem (e.g., `drivetrain.cpp`, `elevator.cpp`).
-   `include/`: Contains all header files (`.hpp`).
    -   `commands.hpp`: Contains high-level robot actions that combine calls to multiple subsystems.
    -   `subsystems/`: Directory containing the header files for each robot subsystem.
        -   `subsystem.hpp`: A base class that defines the common interface for all subsystems.
    -   `pins.hpp`: Defines all microcontroller pin assignments for motors, sensors, and other peripherals.
    -   `settings.hpp`: Contains global settings, constants, and tuning variables for the robot.
-   `lib/`: For local project libraries. Dependencies are primarily managed by PlatformIO in `platformio.ini`.
-   `test/`: Contains test code for individual modules.
-   `platformio.ini`: The PlatformIO project configuration file.

### Code Overview

-   **`main.cpp`**: This file contains the `setup()` and `loop()` functions. It initializes all subsystems and runs the main control loop. It is currently configured to execute the `follow_line` command for testing, with the tele-op and mode-switching logic temporarily disabled.

-   **Subsystem Architecture**: The robot's functionality is organized into modular `Subsystem` classes. Each subsystem is implemented as a **singleton**, ensuring there is only one instance controlling its specific hardware. This design keeps the code organized and prevents conflicting commands. The current subsystems include:
    -   **`Drivetrain`**: Manages the robot's mobility.
    -   **`Controller`**: Interfaces with the RF24 remote control to get driver inputs.
    -   **`Elevator`**: Controls the elevator mechanism.
    -   **`Gate`**: Controls the servo-actuated gate.
    -   **`LineSensor`**: Manages the line-following sensor array.
    -   **`UltrasonicSensor`**: Manages the ultrasonic distance sensor.

-   **`commands.hpp`**: This file defines reusable, high-level robot behaviors (e.g., `follow_line()`). These functions orchestrate actions across multiple subsystems to perform a complex task.

-   **Configuration**:
    -   `pins.hpp` is used to map the physical pins of the microcontroller to their functions on the robot. This provides a single place to manage hardware wiring.
    -   `settings.hpp` stores important variables like motor speeds, sensor thresholds, and other tunable parameters.

### Hardware Wiring Guide

To ensure the robot functions correctly, verify that all components are wired to the Raspberry Pi Pico according to the following pin assignments. The logical names (e.g., `MOTOR1`) are defined in `include/pins.hpp`.

-   **Drivetrain (Left):** `MOTOR3`
    -   Enable Pin: `GPIO 19`
    -   Phase Pin: `GPIO 18`
-   **Drivetrain (Right):** `MOTOR4`
    -   Enable Pin: `GPIO 17`
    -   Phase Pin: `GPIO 16`
-   **Elevator:** `MOTOR1`
    -   Enable Pin: `GPIO 27`
    -   Phase Pin: `GPIO 26`
-   **Ultrasonic Sensor:**
    -   Trig Pin: `GPIO 4`
    -   Echo Pin: `GPIO 5`
-   **Line Sensor Array:**
    -   Sensors 0-5: `GPIO 6` through `GPIO 11`
-   **RF24 Radio:**
    -   CE: `GPIO 22`
    -   CSN: `GPIO 1`

### Subsystem Pattern

All hardware-related code is encapsulated within a "subsystem" class that inherits from `Subsystem`. Each subsystem is a singleton, accessed via a static `get_instance()` method. This ensures that all parts of the code are interacting with the same object for a given piece of hardware.

The main loop in `main.cpp` calls the `loop()` method on each subsystem, allowing them to perform their periodic tasks.