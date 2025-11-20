#include <BleKeyboard.h>
#include <cmath>

#include "../config.h"

class Volume {
  const int stepSize = std::ceil(4095 / VOL_STEPS);
  int value;
  BleKeyboard* keyboard;

  public:
    Volume(BleKeyboard* k): keyboard(k) {}

    void updateValue() {
      int newValue = analogRead(VOL_ANALOG_PIN);

      if (newValue == value) {
        return;
      }

      int diff = newValue - value;
      int steps = std::ceil(diff / stepSize);
      const uint8_t* key = (steps > 0) ? KEY_MEDIA_VOLUME_UP : KEY_MEDIA_VOLUME_DOWN;
      
      if (steps != 0) {
        /*
          Only update when steps are made. 
          It would otherwise lose difference in many < 1 steps.
        */
        value = newValue;
        Serial.printf("Analog read value: %d\n", newValue);
        Serial.printf("%d volume steps\n", steps);
      }

      for (int i = 0; i < std::abs(steps); i++) {
        (*keyboard).write(key);
        delay(10);
      }
    }
};
