#include "drivetrain.hpp"

Drivetrain::Drivetrain(uint8_t left_enable_pin, uint8_t right_enable_pin, uint8_t left_phase_pin, uint8_t right_phase_pin) {
    this->left_enable_pin_ = left_enable_pin;
    this->right_enable_pin_ = right_enable_pin;
    this->left_phase_pin_ = left_phase_pin;
    this->right_phase_pin_ = right_phase_pin;

    pinMode(left_enable_pin_, OUTPUT);
    pinMode(right_enable_pin_, OUTPUT);
    pinMode(left_phase_pin_, OUTPUT);
    pinMode(right_phase_pin_, OUTPUT);
}

void Drivetrain::set_speed(double linear_speed, double angular_speed) {
    double left = linear_speed - angular_speed;
    double right = linear_speed + angular_speed;
    set_left_speed(left);
    set_right_speed(right);
}

void Drivetrain::set_left_speed(double speed) {
    double constrained_speed = constrain(speed, -1.0, 1.0);
    analogWrite(left_enable_pin_, int(255 * abs(constrained_speed)));
    if (constrained_speed > 0.0) {
        digitalWrite(left_phase_pin_, HIGH);
    } else {
        digitalWrite(left_phase_pin_, LOW);
    }
}

void Drivetrain::set_right_speed(double speed) {
    double constrained_speed = constrain(speed, -1.0, 1.0);
    analogWrite(right_enable_pin_, int(255 * abs(constrained_speed)));
    if (constrained_speed > 0.0) {
        digitalWrite(right_phase_pin_, LOW);
    } else {
        digitalWrite(right_phase_pin_, HIGH);
    }
}
