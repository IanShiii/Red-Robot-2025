# Red Robot 2025

This repository contains the C++ source code for the 2025 competition robot, "Red Robot". The project is developed using the PlatformIO IDE.

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
    -   `subsystems/`: Directory containing the header files for each robot subsystem.
        -   `subsystem.hpp`: A base class that defines the common interface for all subsystems.
    -   `pins.hpp`: Defines all microcontroller pin assignments for motors, sensors, and other peripherals.
    -   `settings.hpp`: Contains global settings, constants, and tuning variables for the robot.
-   `lib/`: For local project libraries. Dependencies are primarily managed by PlatformIO in `platformio.ini`.
-   `test/`: Contains test code for individual modules.
-   `platformio.ini`: The PlatformIO project configuration file.

### Code Overview

-   **`main.cpp`**: This file contains the `setup()` and `loop()` functions. It is responsible for initializing all subsystems and managing the high-level robot state (e.g., switching between autonomous and tele-operated modes).

-   **Subsystem Architecture**: The robot's functionality is organized into modular `Subsystem` classes. Each subsystem is implemented as a **singleton**, ensuring there is only one instance controlling its specific hardware. This design keeps the code organized and prevents conflicting commands. The current subsystems include:
    -   **`Drivetrain`**: Manages the robot's mobility.
    -   **`Controller`**: Interfaces with the RF24 remote control to get driver inputs.
    -   **`Elevator`**: Controls the elevator mechanism.
    -   **`Gate`**: Controls the servo-actuated gate.
    -   **`LineSensor`**: Manages the line-following sensor array.
    -   **`Sonar`**: Manages the ultrasonic distance sensor.

-   **Configuration**:
    -   `pins.hpp` is used to map the physical pins of the microcontroller to their functions on the robot. This provides a single place to manage hardware wiring.
    -   `settings.hpp` stores important variables like motor speeds, sensor thresholds, and other tunable parameters.

### Subsystem Pattern

All hardware-related code is encapsulated within a "subsystem" class that inherits from `Subsystem`. Each subsystem is a singleton, accessed via a static `get_instance()` method. This ensures that all parts of the code are interacting with the same object for a given piece of hardware.

The main loop in `main.cpp` calls the `loop()` method on each subsystem, allowing them to perform their periodic tasks.