#include <EEPROM.h>

#define US_SAMPLE 250
#define DIF_TRIGGER 50

u32 OLD, old, cur;

void setup() {
  //Serial.begin(9600);
  pinMode(13,OUTPUT);
  delay(1000);
  digitalWrite(13,1);
}

void loop() {
  static u8 vals[1024];
  static u32 OLD, old, cur;

  u16 val = analogRead(A0);
  while (1) {
    u16 tmp = analogRead(A0);
    if (tmp > val+DIF_TRIGGER) {
      vals[0] = val >> 8;
      vals[1] = val & 0xFF;
      OLD = old = micros();
      break;
    }
  }
  
  while (1) {
    val = analogRead(A0);                                                  
    cur = micros();

    int dt = cur-old;
    //Serial.println(dt);
    old = cur;
    if (dt > US_SAMPLE) {
      while(1){digitalWrite(13,0); delay(100); digitalWrite(13,1); delay(100);};
    }
  
    static int i;  
    u32 DT = cur-OLD;
    i = (DT/US_SAMPLE * 2) + 2;
    
    vals[i + 0] = val >> 8;
    vals[i + 1] = val & 0xFF;
    //Serial.println(val);
    //Serial.println((vals[i/200]<<8) | vals[i/200+1]&&0xFF);
    
    if (i == 1024) {
      digitalWrite(13,0);
      Serial.begin(9600);
      for (i=0; i<1024; i++) {
        Serial.println(vals[i]);
        EEPROM[i] = vals[i];
      }
      while(1);
    }
  }
}
