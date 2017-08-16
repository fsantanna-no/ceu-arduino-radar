#include <EEPROM.h>

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13,1);
  delay(5000);
  Serial.begin(9600);
  Serial.println("dump");
}

void loop() {
#if 1
  for (int i=0; i<1024; i++) {
    Serial.println(EEPROM[i]);
  }
#else
  for (int i=0; i<1024; i+=2) {
    u16 val = (EEPROM[i]<<8) | EEPROM[i+1];
    Serial.println(val);
  }
#endif
  while(1);
}
