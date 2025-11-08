#pragma once

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "pins.hpp"
#include "subsystem.hpp"

#define TEAM_NUMBER 2

#define CHANNEL (TEAM_NUMBER * 3) // 0-125
#define RF_POWER_LEVEL RF24_PA_HIGH

#define PACKET_LEFT_X    0
#define PACKET_LEFT_Y    1
#define PACKET_RIGHT_X   2
#define PACKET_RIGHT_Y   3
#define PACKET_BUTTONS_1 4
#define PACKET_BUTTONS_2 5

class Controller : public Subsystem {
    uint8_t TARGET_ADDRESS[5] = {0xF0,0xF0,0xF0,0xF0,0xD2};
    uint8_t LOCAL_ADDRESS[5] = {0xF0,0xF0,0xF0,0xF0,0xE1};
    
    public:
        static Controller& get_instance() {
            static Controller instance;
            return instance;
        }
        
        void loop() override;
        void log() override;

        bool is_A_pressed();
        bool is_B_pressed();
        bool is_X_pressed();
        bool is_Y_pressed();
        bool is_LB_pressed();
        bool is_LT_pressed();
        bool is_RB_pressed();
        bool is_RT_pressed();
        bool is_BACK_pressed();
        bool is_START_pressed();
        bool is_L3_pressed();
        bool is_R3_pressed();
        float get_left_x();
        float get_left_y();
        float get_right_x();
        float get_right_y();
        int get_d_pad();
    
    private:
        friend class Subsystem;
        Controller();

        RF24 radio_;
        uint8_t radio_packet_[6];
        uint8_t radio_led_state_ = 0;
        bool recv_first_packet_ = false;

        bool is_packet_valid(uint8_t *pkt);
};
