#include <Wire.h>
#include <Auto485.h>
#include <CMRI.h>

// CMRI Settings
#define CMRI_ADDR 2 //CMRI node address in JMRI
#define DE_PIN 33

#define CMRI_INPUTS 24
#define CMRI_OUTPUTS 48

#define BAUD_RATE 19200
#define SERIAL_BAUD_RATE 19200

#define LED_PIN 21

// Setup serial communication
Auto485 bus(DE_PIN); // ESP32 pin 33 -> MAX485 DE and RE pins

// Define CMRI connection with 24 inputs and 48 outputs
CMRI cmri(CMRI_ADDR, CMRI_INPUTS, CMRI_OUTPUTS, bus);

int light_state = LOW;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  // bus.begin(BAUD_RATE, SERIAL_8N2); // May need this version (8 bit, no parity, 2 stop bits) if JMRI doesn't understand the standard single stop bit.
  bus.begin(BAUD_RATE);                // Ensure this matches the baud rate in JMRI.

  pinMode(LED_PIN, OUTPUT);

  Serial.println("start light show");
}

void loop() {
    cmri.process();
    light_state = cmri.get_bit(0);
    cmri.set_bit(0, !light_state);  //Bit 0 = address 2001 in JMRI/CMRI
    digitalWrite(LED_PIN, light_state);
}
