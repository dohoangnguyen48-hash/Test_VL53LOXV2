#include <Arduino.h>
#include <Wire.h>
#include "VL53L0X_Manager.h" 

VL53L0X_Manager sensorSystem;

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);

    if (!sensorSystem.init()) {
        Serial.println("Lỗi phần cứng! Dừng hệ thống.");
        while (1);
    }
    Serial.println("Hệ thống cảm biến sẵn sàng!");
}

void loop() {
    sensorSystem.printDistances();
    delay(200); 
}