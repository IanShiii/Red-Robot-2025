#include "subsystems/controller.hpp"

Controller::Controller() {
    radio_ = RF24(22, 1, 1000000);
    radio_packet_[0] = 127;
    radio_packet_[1] = 127;
    radio_packet_[2] = 127;
    radio_packet_[3] = 127;
    radio_packet_[4] = 0;
    radio_packet_[5] = 0;

    pinMode(RADIO_LED_PIN, OUTPUT);

    SPI.setTX(3);
    SPI.setRX(0);
    SPI.setSCK(2);
    SPI.setCS(1);
    SPI.begin();

    if(!radio_.begin(&SPI)) {
        delay(1000);
        Serial.println("Radio not responding");
    } else {
        //Serial.println("Radio connected");
    }
    radio_.setDataRate(RF24_1MBPS);
    radio_.setChannel(CHANNEL);
    radio_.setCRCLength(RF24_CRC_16);
    radio_.setPALevel(RF_POWER_LEVEL);
    radio_.openWritingPipe(TARGET_ADDRESS);
    radio_.openReadingPipe(1,LOCAL_ADDRESS);
    radio_.startListening();
}

void Controller::loop() {
  if(radio_.available()) {
    uint8_t buf[20];
    radio_.read(buf, sizeof(buf));
    //Serial.println("Recv radio packet");

    if(is_packet_valid(buf+1)) {
      memcpy(radio_packet_, buf+5, 6);
      recv_first_packet_ = true;
      radio_led_state_ = (radio_led_state_ + 1) % 16;
      digitalWrite(RADIO_LED_PIN, radio_led_state_ == 0);
      //Serial.print("Valid ");
      //Serial.println(radio_led_state_);
    } else if(is_packet_valid(buf+2)) {
      memcpy(radio_packet_, buf+6, 6);
      recv_first_packet_ = true;
      radio_led_state_ = (radio_led_state_ + 1) % 16;
      digitalWrite(RADIO_LED_PIN, radio_led_state_);
      //Serial.print("Valid ");
      //Serial.println(radio_led_state_);
    } else {
      // Invalid
      /*Serial.print("Invalid ");
      for(int i = 0; i < 20; i++) {
        Serial.print(buf[i]);
        Serial.print(" ");
      }
      Serial.println();*/
    }
  }
}

bool Controller::is_A_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_1] >> 5) & 1;
}
bool Controller::is_B_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_1] >> 6) & 1;
}
bool Controller::is_X_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_1] >> 4) & 1;
}
bool Controller::is_Y_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_1] >> 7) & 1;
}
bool Controller::is_LB_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_2] >> 0) & 1;
}
bool Controller::is_RB_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_2] >> 1) & 1;
}
bool Controller::is_BACK_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_2] >> 4) & 1;
}
bool Controller::is_START_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_2] >> 5) & 1;
}
bool Controller::is_L3_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_2] >> 6) & 1;
}
bool Controller::is_R3_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_2] >> 7) & 1;
}

float Controller::get_left_x() {
  if(!recv_first_packet_) return 0.0;
  float lx = (((float)(radio_packet_[0])) / 127.5) - 1.0;
  lx = constrain(lx, -1.0, 1.0);
  if(lx >= -0.05 && lx <= 0.05) return 0.0;
  return lx;
}

float Controller::get_left_y() {
  if(!recv_first_packet_) return 0.0;
  float ly = (((float)(radio_packet_[1])) / 127.5) - 1.0;
  ly = constrain(ly, -1.0, 1.0);
  if(ly >= -0.05 && ly <= 0.05) return 0.0;
  return ly;
}

float Controller::get_right_x() {
  if(!recv_first_packet_) return 0.0;
  float rx = (((float)(radio_packet_[2])) / 127.5) - 1.0;
  rx = constrain(rx, -1.0, 1.0);
  if(rx >= -0.05 && rx <= 0.05) return 0.0;
  return rx;
}
float Controller::get_right_y() {
  if(!recv_first_packet_) return 0.0;
  float ry = (((float)(radio_packet_[3])) / 127.5) - 1.0;
  ry = constrain(ry, -1.0, 1.0);
  if(ry >= -0.05 && ry <= 0.05) return 0.0;
  return ry;
}
  
bool Controller::is_LT_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_2] >> 2) & 1;
}

bool Controller::is_RT_pressed() {
  if(!recv_first_packet_) return 0;
  return (radio_packet_[PACKET_BUTTONS_2] >> 3) & 1;
}

/*float axisLT() {
  float lt = (((float)(radio_packet[4])) - 127.5) / 127.5;
  lt = constrain(lt, 0.0, 1.0);
  if(lt <= 0.05) return 0.0;
  return lt;
}

float axisRT() {
  float rt = (127.5 - ((float)(radio_packet[4]))) / 127.5;
  rt = constrain(rt, 0.0, 1.0);
  if(rt <= 0.05) return 0.0;
  return rt;
}*/

int Controller::get_d_pad() {
  if(!recv_first_packet_) return 8;
  return radio_packet_[PACKET_BUTTONS_1] & 0xF;
}

bool Controller::is_packet_valid(uint8_t *pkt) {
  if(pkt[0] != pkt[10]) return false;
  if(pkt[1] != pkt[11]) return false;
  if(pkt[2] != pkt[12]) return false;
  if(pkt[3] != pkt[13]) return false;
  
  uint8_t sum = 0;
  for(int i = 0; i < 14; i++) {
    sum += pkt[i];
  }
  if(sum != pkt[14]) return false;
  
  return true;
}

void Controller::log() {
    Serial.print("Left X: ");
    Serial.print(get_left_x());
    Serial.print(" Left Y: ");
    Serial.print(get_left_y());
    Serial.print(" Right X: ");
    Serial.print(get_right_x());
    Serial.print(" Right Y: ");
    Serial.println(get_right_y());
}
