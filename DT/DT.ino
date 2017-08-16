#include <EEPROM.h>

u32 old, cur;

void setup() {
  //Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,1);
  delay(1000);

  int val = analogRead(A0);
  old = micros();
}

void loop() {
  int val = analogRead(A0);                                              
  cur = micros();
  int dt = cur-old;
  //Serial.println(dt);
  old = cur;
  if (dt > 150) {
    while(1){digitalWrite(13,0); delay(100); digitalWrite(13,1); delay(100);};
  }

  static u16 VALS1 = 0;
  static u16 VALS2 = 0;
  VALS1 += (val>>8) ;
  VALS2 += (val&&0xFF) ;

  static u8 dts[1024];
  static int i = 0;
  dts[i++] = dt;
  
  if (i == 1024) {
    u16 VALS = 0;
    for (i=0; i<1024; i++) {
      EEPROM[i] = dts[i];
    }
    EEPROM[1023] = VALS1+VALS2;
    digitalWrite(13,0);
    while(1);
  }

  //delayMicroseconds(150);
}
