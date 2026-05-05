#include <Arduino.h>
#include "CAN.h"
#include "virtualTimer.h"
#include "../include/can.hpp"
#include "lut.h"

enum class StrainGaugePins {
    RB = 0,
    RM = 1,
    RT = 2,
    LT = 3,
    LM = 4,
    LB = 5
};

// Pin Definitions
const uint8_t DOUT_PINS[6] = {36, 34, 39, 35, 32, 33}; 
const uint8_t SCLK_PIN = 14;
const uint8_t PWDN_PIN = 25;

// Data Storage
int32_t raw_values[6] = {0};

CANInterface canInterface;


void setup() {
    canInterface.initialize();
    Serial.begin(115200);

    // Initialize Pins
    pinMode(SCLK_PIN, OUTPUT);
    pinMode(PWDN_PIN, OUTPUT);
    
    for (size_t i = 0; i < 6; i++) {
        pinMode(DOUT_PINS[i], INPUT);
    }

    // Power up the ADCs
    digitalWrite(PWDN_PIN, HIGH);
    digitalWrite(SCLK_PIN, LOW);
    
    Serial.println("ADS1231 Multi-Channel Initialized.");
}

void read_all_adcs() {
    // 1. Wait for Data Ready (DRDY goes LOW)
    // We poll DOUT_1; since they share SCLK and PWDN, they stay in sync.
    uint32_t timeout = millis();
    while (digitalRead(DOUT_PINS[0]) == HIGH) {
        if (millis() - timeout > 200) { // Safety timeout (~5Hz or 80Hz expected)
            Serial.println("Error: ADC Timeout");
            return;
        }
    }

    // Reset raw values
    for (size_t i = 0; i < 6; i++) raw_values[i] = 0;

    // 2. Shift out 24 bits
    for (size_t i = 0; i < 24; i++) {
        digitalWrite(SCLK_PIN, HIGH);
        delayMicroseconds(1); // Ensure stable pulse (min 100ns required)

        // Read all 6 pins on the rising edge
        for (size_t channel = 0; channel < 6; channel++) {
            raw_values[channel] <<= 1;
            if (digitalRead(DOUT_PINS[channel])) {
                raw_values[channel] |= 1;
            }
        }

        digitalWrite(SCLK_PIN, LOW);
        delayMicroseconds(1);
    }

    // 3. The 25th SCLK pulse to force DOUT high
    digitalWrite(SCLK_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite(SCLK_PIN, LOW);

    // 4. Sign extension (ADS1231 is 24-bit Two's Complement)
    for (size_t i = 0; i < 6; i++) {
        if (raw_values[i] & 0x800000) { // If bit 23 is set, it's negative
            raw_values[i] |= 0xFF000000;
        }
    }
}

void loop() {
    read_all_adcs();

    // Print values (Replace this with your CAN transmission logic)
    Serial.print("Data: ");
    Serial.print("Bottom Right | ");
    Serial.print(raw_values[0]);
    Serial.println();
    Serial.print("Middle Right | ");
    Serial.print(raw_values[1]);
    Serial.println();
    Serial.print("Top Right | ");
    Serial.print(raw_values[2]);
    Serial.println();
    Serial.print("Top Left | ");
    Serial.print(raw_values[3]);
    Serial.println();
    Serial.print("Middle Left | ");
    Serial.print(raw_values[4]);
    Serial.println();
    Serial.print("Bottom Left | ");
    Serial.print(raw_values[5]);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    
    
    
    
    

    canInterface.updateSignals(raw_values[0],raw_values[1], raw_values[2],raw_values[3], raw_values[4],raw_values[5]);

    // Small delay to prevent serial flood; ADCs determine actual sample rate
    delay(2000); 
}
