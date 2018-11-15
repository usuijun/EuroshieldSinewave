#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=221,258
AudioMixer4              mixer1;         //xy=430,277
AudioOutputI2S           i2s1;           //xy=595,269
AudioConnection          patchCord1(sine1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, 0, i2s1, 0);
AudioConnection          patchCord3(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=234,109
// GUItool: end automatically generated code

#define ledPinCount 4
int upperPotInput = 20;
int lowerPotInput = 21;
int ledPins[ledPinCount] = { 3, 4, 5, 6 };

void setup() {
  //Serial.begin(9600);
  setupAudioShield();
  setupWaveFormSine();
  setupMixer();
  
  for (int i = 0; i < ledPinCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  //led test
  digitalWrite(ledPins[0], HIGH);
}

void loop() {
  const int lowerPotValue = analogRead(lowerPotInput);
  const int upperPotValue = analogRead(upperPotInput);

  ledMeter(lowerPotValue / 1023.0);

  AudioNoInterrupts();
  sine1.frequency(lowerPotValue);
  sine1.amplitude(upperPotValue/1024.0);
  AudioInterrupts();
}

void setupAudioShield() {
  AudioMemory(15);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);
}

void setupWaveFormSine() {
  sine1.frequency(440);
  sine1.amplitude(0.5);
}

void setupMixer() {
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0.5);
  mixer1.gain(3, 0.5);
}

void ledMeter(float normalizedValue) {
  int i = 0;
  for(; i + 0.05 < normalizedValue * 4.0; ++i) {
    digitalWrite(ledPins[i], HIGH);
  }
  for(; i < ledPinCount; ++i) {
    digitalWrite(ledPins[i], LOW);
  }
}

