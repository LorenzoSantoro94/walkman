#include <Arduino.h>
#include <BleKeyboard.h>

#include "Volume.cpp"
#include "../config.h"

/* TODO add mute */

BleKeyboard bleKeyboard;
Volume volumeManager(&bleKeyboard);

void setup() {
  Serial.begin(921600);
  Serial.println("Starting BLE work!");

  pinMode(PLAY_PAUSE_PIN, INPUT_PULLUP);
  pinMode(REW_PIN, INPUT_PULLUP);
  pinMode(FF_PIN, INPUT_PULLUP);
  pinMode(VOL_DOWN_PIN, INPUT_PULLUP);
  pinMode(VOL_UP_PIN, INPUT_PULLUP);

  bleKeyboard.begin();
}

void handleButtons() {
  if (digitalRead(PLAY_PAUSE_PIN) == LOW) {
    Serial.println("Play/Pause");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    delay(DEBOUNCE_DELAY_MS);
  } else if (digitalRead(REW_PIN) == LOW) {
    Serial.println("REW");
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
    delay(DEBOUNCE_DELAY_MS);
  } else if (digitalRead(FF_PIN) == LOW) {
    Serial.println("FF");
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
    delay(DEBOUNCE_DELAY_MS);
  } else if (digitalRead(VOL_DOWN_PIN) == LOW) {
    Serial.println("VOL_DOWN");
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
  } else if (digitalRead(VOL_UP_PIN) == LOW) {
    Serial.println("VOL_UP");
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
  } else {
    // No button pressed
    return;
  }

  delay(100);
}

void loop() {
  if (bleKeyboard.isConnected()) {
    handleButtons();
    volumeManager.updateValue();
    delay(50);
  } else {
    // Idle delay
    delay(1000);
  }
}