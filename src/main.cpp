#include <Arduino.h>

#define BAUD_RATE 115200

const int count_interval = 2000;

static unsigned long count = 0; 

void setup() {
    Serial.begin(BAUD_RATE);

}

void loop() {
    count++;
    Serial.printf("Value: %lu\n",count);
    delay(count_interval);
}