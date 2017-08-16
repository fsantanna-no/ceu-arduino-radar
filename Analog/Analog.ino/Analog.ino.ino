void setup() {
  Serial.begin(9600);
}

void loop() {
  static int v0 = 0;
  int v = analogRead(A0);
  if (v>v0*1.1 || v<v0*0.9) {
    v0 = v;
    Serial.println(v);
  }
  delay(1);
}
