#include "drivetrain.hpp"

Drivetrain::Drivetrain() {
    pinMode(DRIVETRAIN_LEFT_ENABLE_PIN, OUTPUT);
    pinMode(DRIVETRAIN_RIGHT_ENABLE_PIN, OUTPUT);
    pinMode(DRIVETRAIN_LEFT_PHASE_PIN, OUTPUT);
    pinMode(DRIVETRAIN_RIGHT_PHASE_PIN, OUTPUT);
}

void Drivetrain::set_speed_based_on_joysticks(double left_y, double right_x) {
    double linear_speed;
    double angular_speed;

    if (abs(left_y) < DRIVER_LINEAR_DEADBAND) {
        linear_speed = 0;
    } else {
        linear_speed = (left_y >= 0) ? (left_y * left_y) : -(left_y * left_y);
    }

    if (abs(right_x) < DRIVER_ANGULAR_DEADBAND) {
        angular_speed = 0;
    } else {
        angular_speed = (right_x >= 0) ? -(right_x * right_x) : (right_x * right_x);
    }

    if (linear_speed < 0) {
        angular_speed *= -1;
    }

    set_speed(linear_speed, angular_speed);
}

void Drivetrain::set_speed(double linear_speed, double angular_speed) {
    if (abs(linear_speed) < DRIVETRAIN_LINEAR_DEADBAND) {
        linear_speed = 0;
    }
    if (abs(angular_speed) < DRIVETRAIN_ANGULAR_DEADBAND) {
        angular_speed = 0;
    }

    double left = linear_speed - angular_speed;
    double right = linear_speed + angular_speed;

    set_left_speed(left);
    set_right_speed(right);
}

void Drivetrain::set_left_speed(double speed) {
    double constrained_speed = constrain(speed, -1.0, 1.0);
    analogWrite(DRIVETRAIN_LEFT_ENABLE_PIN, int(255 * abs(constrained_speed)));
    if (constrained_speed > 0.0) {
        digitalWrite(DRIVETRAIN_LEFT_PHASE_PIN, HIGH);
    } else {
        digitalWrite(DRIVETRAIN_LEFT_PHASE_PIN, LOW);
    }
}

void Drivetrain::set_right_speed(double speed) {
    double constrained_speed = constrain(speed, -1.0, 1.0);
    analogWrite(DRIVETRAIN_RIGHT_ENABLE_PIN, int(255 * abs(constrained_speed)));
    if (constrained_speed > 0.0) {
        digitalWrite(DRIVETRAIN_RIGHT_PHASE_PIN, LOW);
    } else {
        digitalWrite(DRIVETRAIN_RIGHT_PHASE_PIN, HIGH);
    }
}
