//identify pins
int trigPin = 2;
int echoPin = 3;
int ltPower = 6;
int ltFwd = 7;
int ltBwd = 8;
int rtPower = 11;
int rtFwd = 12;
int rtBwd = 13;
int motorSpeedL = 255;

int motorSpeedR = 255;
boolean goingBack;
boolean doneGoingBack;
boolean first;

void setup() {
  Serial.begin(9600);
  pinMode(ltPower, OUTPUT);
  pinMode(ltFwd, OUTPUT);
  pinMode(ltBwd, OUTPUT);
  pinMode(rtPower, OUTPUT);
  pinMode(rtFwd, OUTPUT);
  pinMode(rtBwd, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  first = true;   goingBack = false;
  doneGoingBack = false;
}

void loop() {
  if (first) {
    delay(6000);
    first = false;
  }

  boolean changed = false;
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);

  // send a new pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // time for sound pulse to go and return
  distance = (duration / 2) * 0.034029; // speed of sound is 0.034029 cm per microsecond

  Serial.print(distance);

  Serial.println(" cm");
  if (!goingBack) {
    // tell the car to stop when the distance is less than 20cm     if (distance < 20) {       goingBack = true;
  }

  else {
    motorSpeedL = 255;
    motorSpeedR = 255;
    changed = true;
  }

  if (changed) {
    lftMotor(motorSpeedL);
    rgtMotor(motorSpeedR);
  }
}

else {

  if (!doneGoingBack) {
    // stop the car
    lftMotor(0);
    rgtMotor(0);
    delay(1000);

    // drive backwards
    lftMotor(-255);
    rgtMotor(-255);
    delay(500);

    // stop the car
    lftMotor(0);
    rgtMotor(0);
    delay(500);
    doneGoingBack = true;
  }
}
delay(200);
}

void rgtMotor(int power) {
  
  // set to drive forward
  if (power >= 0) { 
    digitalWrite(rtFwd, HIGH);
    digitalWrite(rtBwd, LOW);
  }   

  // set to drive in reverse
  else { 
    digitalWrite(rtFwd, LOW);
    digitalWrite(rtBwd, HIGH);
  }
  
  analogWrite(rtPower, abs(power));
}  
void lftMotor(int power)
{ 
   // set to drive forward
  if (power >= 0){ 
    digitalWrite(ltFwd, HIGH);
    digitalWrite(ltBwd, LOW);
  }   
  
  // set to drive in reverse
  else{ 
    digitalWrite(ltFwd, LOW);
    digitalWrite(ltBwd, HIGH);
  }
  analogWrite(ltPower, abs(power));
}
