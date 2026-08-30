#include "VL53L0X_Manager.h" 

VL53L0X_Manager::VL53L0X_Manager() 
    : XSHUT_PINS{13, 14, 27}, 
      ADDRESSES{0x30, 0x31, 0x29} 
{

}
void VL53L0X_Manager::hardReset() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(XSHUT_PINS[i], OUTPUT);
        digitalWrite(XSHUT_PINS[i], LOW);
    }
    delay(100);
}

bool VL53L0X_Manager::scanI2C(uint8_t targetAddress) {
    Wire.beginTransmission(targetAddress);
    return (Wire.endTransmission() == 0);
}

bool VL53L0X_Manager::init() {
    hardReset();
    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(XSHUT_PINS[i], INPUT_PULLUP);
        delay(150);

        if (!scanI2C(0x29)) return false; 

        bool initSuccess = (ADDRESSES[i] == 0x29) ? sensors[i].begin() : sensors[i].begin(ADDRESSES[i]);
        if (!initSuccess || !scanI2C(ADDRESSES[i])) return false;
    }
    return true;
}

void VL53L0X_Manager::printDistances() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        VL53L0X_RangingMeasurementData_t measure;
        sensors[i].rangingTest(&measure, false); 

        Serial.print("CB"); Serial.print(i + 1); Serial.print(": ");
        if (measure.RangeStatus != 4) {
            Serial.print(measure.RangeMilliMeter); Serial.print("mm\t");
        } else {
            Serial.print("Out\t"); 
        }
    }
    Serial.println();
}