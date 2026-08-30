#ifndef VL53L0X_MANAGER_H
#define VL53L0X_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

class VL53L0X_Manager {
private:
    static const int NUM_SENSORS = 3;
    const uint8_t XSHUT_PINS[NUM_SENSORS];
    const uint8_t ADDRESSES[NUM_SENSORS];
    Adafruit_VL53L0X sensors[NUM_SENSORS];
    
    void hardReset();
    bool scanI2C(uint8_t targetAddress);

public:
    VL53L0X_Manager(); 
    bool init();
    void printDistances();
};

#endif