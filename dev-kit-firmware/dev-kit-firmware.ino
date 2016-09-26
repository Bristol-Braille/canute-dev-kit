#include <Keyboard.h>
#include <SPI.h>
#include "I2C.h"

#define VERSION 1
#define N_COLUMNS 80
#define N_ROWS 9
#define I2C_ADDRESS_BUTTONS 0x020
#define INTERRUPT_BUTTONS digitalPinToInterrupt(7)

#include "Display.h"
#include "protocol.h"

void setup () {
    I2c.begin();
    Keyboard.begin();
    attachInterrupt(INTERRUPT_BUTTONS, handle_buttons, FALLING);
    Display::setup();
}

void loop () {
   ui_control();
}

static void handle_buttons () {
    static uint16_t previous = 0;
    uint16_t data = read_i2c() & 0xFFF;
    if(data != previous) {
       set_key(data, 0, '1');
       set_key(data, 1, '2');
       set_key(data, 2, '3');
       set_key(data, 3, '4');
       set_key(data, 4, '5');
       set_key(data, 5, '6');
       set_key(data, 6, '7');
       set_key(data, 7, '8');
       set_key(data, 8, '9');
       set_key(data, 9, KEY_LEFT_ARROW);
       set_key(data, 10, KEY_DOWN_ARROW);
       set_key(data, 11, KEY_RIGHT_ARROW);
    }
    previous = data;
}

void set_key(uint16_t data, uint8_t n, char key) {
   if (data & 1 << n) {
      Keyboard.press(key);
   } else {
      Keyboard.release(key);
   }
}

uint16_t read_i2c() {
    uint16_t data = 0;
    I2c.read(I2C_ADDRESS_BUTTONS, 2);
    if (I2c.available()) {
        data = I2c.receive();
    }
    if (I2c.available()) {
        data |= I2c.receive() << 8;
    }
    return ~data;
}

void ui_control () {
    if (Serial.available() >= 0){
        uint8_t cc = Serial.read();
        uint8_t cursor = 0;
        switch (cc) {
            case COMMAND_N_CHARACTERS:
                Serial.write(COMMAND_N_CHARACTERS);
                Serial.write((uint8_t)(N_COLUMNS / 2));
                break;
            case COMMAND_N_ROWS:
                Serial.write(COMMAND_N_ROWS);
                Serial.write(N_ROWS);
                break;
            case COMMAND_SEND_DATA: {
                uint8_t buffer[N_ROWS * N_COLUMNS];
                for (uint8_t i = 0; i < (N_ROWS * N_COLUMNS / 2 / 64); ++i) {
                    //chunk data into 64 byte packets and respond to each
                    for (uint8_t j = 0; j < (64 * 2);) {
                        if (Serial.available() > 0) {
                            uint8_t c = Serial.read();
                            buffer[(i * 64 * 2) + j]     = c & 0b111;
                            buffer[(i * 64 * 2) + j + 1] = (c >> 3) & 0b111;
                            j += 2;
                        }
                    }
                    Serial.write((uint8_t)0);
                }
                Display::set(buffer);
                Serial.write(COMMAND_SEND_DATA);
                Serial.write((uint8_t)0);
                break;
            }
            case COMMAND_SEND_LINE: {
                uint8_t buffer[N_COLUMNS];
                uint8_t row = Serial.read();
                for (uint8_t i = 0; i < (N_COLUMNS / 2); ++i) {
                    if (Serial.available() > 0) {
                        uint8_t c = Serial.read();
                        buffer[i * 2]       = c & 0b111;
                        buffer[(i * 2) + 1] = (c >> 3) & 0b111;
                    }
                }
                Display::set_row(row, buffer);
                Serial.write(COMMAND_SEND_LINE);
                Serial.write((uint8_t)0);
            }
            case COMMAND_VERSION:
                Serial.write((uint8_t)COMMAND_VERSION);
                Serial.write((uint16_t)VERSION);
                break;
            case COMMAND_SEND_ERROR:
                break;
            case COMMAND_SEND_OK:
                break;
            case COMMAND_TEST_MODE:
                break;
        }
    };
}


