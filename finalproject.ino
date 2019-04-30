
int fsrAnalogPin = 0; // FSR is connected to analog 0
int LEDpin = 2;      // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int LEDbrightness;
const int trigPin = 5;
const int echoPin = 4;
const int buzzerPin = 11;//the buzzer pin attach to
int fre;//set the variable to store the frequence value
unsigned long duration;

void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(LEDpin, OUTPUT);

  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);
}

void loop(void) {
  fsrReading = analogRead(fsrAnalogPin);
  //Serial.print("Analog reading = ");
  //Serial.println(fsrReading);

  // we'll need to change the range from the analog reading (0-1023) down to the range
  // used by analogWrite (0-255) with map!
  LEDbrightness = map(fsrReading, 0, 500, 0, 255);
  // LED gets brighter the harder you press
  analogWrite(LEDpin, LEDbrightness);

  delay(100);
  long duration, inches, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

  if (inches < 9) {
    tone(buzzerPin, 500);
  }

  if (inches > 9) {
    noTone(buzzerPin);
  }



}

long microsecondsToInches(long microseconds)
{

  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{

  return microseconds / 29 / 2;


}
