#define TOGGLE

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#define radio_read(a,b)  radio.read(a,b)
//#define radio_write(a,b) { for (int i=0; i<1; i++) { radio.write(a,b); } }
//#define radio_write_read(a,b) { radio.stopListening(); for (int i=0; i<1; i++) { radio.write(a,b); } radio.startListening(); }
const uint64_t pipe =  0xAABBCCDDEELL;
RF24 radio(8,7);

volatile bool is_detected = false;

#ifdef TOGGLE
u8 id = 1;
#else
u8 id = 0;
#endif

void setup() { 
  ADMUX &= B11011111;
  ADMUX |= B01000000;
  ADMUX &= B11110000;
  ADMUX |= 1;
  //ADMUX = 0;
  // ADMUX |= B00001000; // Binary equivalent
  ADCSRA |= B10000000;
  ADCSRA |= B00100000;
  ADCSRB &= B11111000;
  ADCSRA |= B00000111;
  ADCSRA |= B00001000;
  sei();
  ADCSRA |=B01000000;

  Serial.begin(9600);

  radio.begin();
  //radio.disableCRC();
  radio.setPayloadSize(1);
  radio.setAutoAck(false);              // true by default
  radio.setDataRate(RF24_2MBPS);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  radio.openWritingPipe(pipe);

#ifndef TOGGLE
  while (!radio.available());
  radio.read(id, 1);
  Serial.print("ID: ");
  Serial.println(id);
#endif
  radio.stopListening();

  //pinMode(13,OUTPUT);
}

void loop() {
  if (is_detected) {
    radio.write(&id, 1);
    Serial.print("id: ");  Serial.println(id);
    delay(200);   // skip continuous "mic.ok" vibration

    is_detected = false;
#ifdef TOGGLE
    id = 3-id;
#endif
  }
}

#define SIGNAL_LOW  (512 - 100)
#define SIGNAL_HIGH (512 + 100)
#define N 6

ISR (ADC_vect)
{
  if (is_detected) {
    return;
  }
  
  static int nxt = 0;
  static u32 peeks[N] = {0, 0, 0, 0, 0, 0};
  static int i = 0;

  //digitalWrite(13, !digitalRead(13));
  
  int v = ADCL | (ADCH << 8);

  bool is_peek = false;
  if (v<SIGNAL_LOW && nxt!=1) {
    is_peek = true;
    nxt = 1;
  } else if (v>SIGNAL_HIGH && nxt!=-1) {
    is_peek = true;
    nxt = -1;
  }
  
  if (is_peek) {
    //Serial.println(v);
    peeks[i] = micros();
    int ii = (i+1) % N;
    if (peeks[i]-peeks[ii] <= 3000) {
      is_detected = true;
    }
    i = ii;
  }
}

