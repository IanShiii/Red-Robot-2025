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

-   `src/`: Contains the main source code files (`.cpp`).
    -   `main.cpp`: The entry point of the program, containing the primary robot loop.
    -   `drivetrain.cpp`: Implementation for the robot's drivetrain and movement functions.
    -   `controller.cpp`: Implementation for handling input from the remote controller.
    -   `autons/`: Directory containing specific autonomous routines.
-   `include/`: Contains all header files (`.hpp`).
    -   `drivetrain.hpp`: Header for the drivetrain.
    -   `controller.hpp`: Header for the controller.
    -   `auton.hpp`: Header for autonomous functions.
    -   `pins.hpp`: Defines all microcontroller pin assignments for motors, sensors, and other peripherals.
    -   `settings.hpp`: Contains global settings, constants, and tuning variables for the robot.
-   `lib/`: For local project libraries. Dependencies are primarily managed by PlatformIO in `platformio.ini`.
-   `test/`: Contains test code for individual modules.
-   `platformio.ini`: The PlatformIO project configuration file.

### Code Overview

-   **main.cpp**: This file contains the `setup()` and `loop()` functions. `setup()` is run once at the start, and `loop()` is run repeatedly. The main robot logic, which calls functions from other modules based on the robot's state (e.g., autonomous or driver-controlled), resides here.

-   **Drivetrain**: The `drivetrain.hpp` and `drivetrain.cpp` files manage the robot's mobility. This includes functions to control the motors, read encoders, and execute movements.

-   **Controller**: The `controller.hpp` and `controller.cpp` files interface with the remote control, translating joystick and button inputs into actions for the robot to perform during the driver-controlled period.

-   **Autonomous**: The `auton.hpp` header declares functions for autonomous mode, and the `.cpp` files in `src/autons/` define the specific sequences of actions for different autonomous routines.

-   **Configuration**:
    -   `pins.hpp` is used to map the physical pins of the microcontroller to their functions on the robot. This provides a single place to manage hardware wiring.
    -   `settings.hpp` stores important variables like motor speeds, sensor thresholds, and other tunable parameters.