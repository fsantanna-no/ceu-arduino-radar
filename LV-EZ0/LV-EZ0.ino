/*
 * The LV-EZ0’s range is really dependent on the size of the object – About 8ft for something the size of a finger, to over 20ft for something the size of a piece of paper. 
 * The best part is that the output is linear, so something that is 6ft way will output half that of something 12 ft away. 
 * This makes it very easy to read actual distance with it.
 * Maxbotix says the LV-EZ0 has a 1 inch resolution and a range of 0 – 254in meaning you could track something with 1in reliability over 254in of movement from the sensor. 
 * The reality is that this guy has trouble sensing distances under 1ft, and the output can be pretty shaky especially when trying to sense objects that are not perpendicular with the sensor.
 */

void setup () {
  Serial.begin(9600);
  pinMode(3, INPUT);
}

void loop () {
  int a  = analogRead(A5);
  int mV = a * 5 / 1.024;
  //int cm = 5 * v / 5/1024; // 5mm * Vread / Vref/1024
  int cm = 5 * (mV/4.883) / 10;
  //int v = pulseIn(3, HIGH);
  //int cm = v/10;

  //in = cm/2.54;

  Serial.println("-----");
  Serial.print(mV);
  Serial.println(" mV");
  Serial.print(cm);
  Serial.println(" cm");

  //Pulse Width representation with a scale factor of 147 uS per Inch.
  int pulse = pulseIn(3, HIGH);
  int inches = pulse / 147;
  cm = inches * 2.54;
  Serial.print(cm);
  Serial.println(" cm");
  
  delay(200);
} 
