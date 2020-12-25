/*
   F = Forward
   B = Backward
   L = Left
   R = Right
   S = Stop
   N = Parking
   Q = Parking
   U = U-turn
   V = U-turn
   P = Parking Mode
   M = Normal Mode
   J = Elevated Mode
   E = Normal Mode
   O = Door Open
   C = Door Close
*/
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#define sensor A0
LiquidCrystal_I2C lcd(0x27, 20, 4);
char t;
#define enA 8
#define enB 9
#define enC 11
#define enD 12
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo servod1;
Servo servod2;

int pos = 0;
int Echo1 = A8; //Left Distance
int Trig1 = A9;
int Echo2 = A2;// Middle distance
int Trig2 = A3;
int Echo3 = A4;// Right distance
int Trig3 = A5;
int Echo4 = A6;// Back distance
int Trig4 = A7;
int Left_Distance = 0, Right_Distance = 0, Middle_Distance = 0, Back_Distance = 0 ;
int s_front = 0;
int s_back = 0;
int s_left = 0;
int s_right = 0;

void _mForward()
{

  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
  digitalWrite(28, HIGH);
  digitalWrite(29, LOW);
  Serial.println(F("Robot Moving Forward"));

}
void _mBack()
{
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
  digitalWrite(28, LOW);
  digitalWrite(29, HIGH);
  Serial.println(F("Robot Moving Backward"));
}
void _mLeft()
{
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
  analogWrite(enA, 150);
  analogWrite(enB, 250);
  analogWrite(enC, 150);
  analogWrite(enD, 250);
  Serial.println(F("Robot Moving Left"));
}
void _mRight()
{
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, HIGH);
  digitalWrite(29, LOW);
  analogWrite(enA, 150);
  analogWrite(enB, 250);
  analogWrite(enC, 150);
  analogWrite(enD, 250);
  Serial.println(F("Robot Moving Right"));
}
void _mStop()
{
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
  Serial.println(F("Robot STOP"));
}

void _nPar() {

  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, HIGH);

}

void _qPar() {

  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(29, LOW);

}


int Left_Distance_fun()
{
  digitalWrite(Trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig1, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig1, LOW);
  float Fdistance = pulseIn(Echo1, HIGH);
  delay(10);

  Fdistance = Fdistance / 29 / 2;
  return (int)Fdistance;
}

int Middle_Distance_fun()
{
  digitalWrite(Trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig2, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig2, LOW);

  float Fdistance = pulseIn(Echo2, HIGH);
  delay(10);
  Fdistance = Fdistance / 29 / 2;
  return (int)Fdistance;
}

int Right_Distance_fun() {
  digitalWrite(Trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig3, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig3, LOW);
  float Fdistance = pulseIn(Echo3, HIGH);
  delay(10);
  Fdistance = Fdistance / 29 / 2;
  return (int)Fdistance;
}

int Back_Distance_fun()
{
  digitalWrite(Trig4, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig4, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig4, LOW);
  float Fdistance = pulseIn(Echo4, HIGH);
  delay(10);
  Fdistance = Fdistance / 29 / 2;
  return (int)Fdistance;
}

void sonar() {

  Left_Distance = Left_Distance_fun();
  Middle_Distance = Middle_Distance_fun();
  Right_Distance = Right_Distance_fun();
  Back_Distance = Back_Distance_fun();

  Serial.println(F("Left Distance\tMiddle Distance\tRight Distance\tStatus\n"));
  Serial.print(Left_Distance);
  Serial.print(F("cm\t\t"));
  Serial.print(Middle_Distance);
  Serial.print(F("cm\t\t"));
  Serial.print(Right_Distance);
  Serial.print(F("cm\t\t"));
  Serial.print(Back_Distance);
  Serial.print(F("cm\t\t"));


}
void al() {

  float adcValue = 0;
  for (int i = 0; i < 10; i++)
  {
    adcValue += analogRead(sensor);
    delay(10);
  }
  float v = (adcValue / 10) * (5.0 / 1024.0);
  float mgL = 0.67 * v;
  Serial.print(F("BAC:"));
  Serial.print(mgL);
  Serial.print(F(" mg/L"));
  lcd.setCursor(0, 0);
  lcd.print(F("BAC: "));
  lcd.print(mgL);
  lcd.print(F(" mg/L        "));
  lcd.setCursor(0, 1);
  if (mgL > 2.75)
  {
    lcd.print(F("Drunk   "));
    Serial.println(F("    Drunk"));
  }
  else
  {
    lcd.print(F("Fit for Driving"));
    Serial.println(F("    Fit For Driving"));
  }

  delay(10);

}
void setup() {

  pinMode(22, OUTPUT);  //left motors forward
  pinMode(23, OUTPUT);  //left motors reverse
  pinMode(24, OUTPUT);  //right motors forward
  pinMode(25, OUTPUT);  //right motors reverse
  pinMode(26, OUTPUT);  //left motors forward
  pinMode(27, OUTPUT);  //left motors reverse
  pinMode(28, OUTPUT);  //right motors forward
  pinMode(29, OUTPUT);  //right motors reverse
  pinMode(8, OUTPUT);  //right motors forward
  pinMode(9, OUTPUT);  //right motors reverse
  pinMode(11, OUTPUT);  //right motors forward
  pinMode(12, OUTPUT);  //right motors reverse
  pinMode(Echo1, INPUT);
  pinMode(Trig1, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo3, INPUT);
  pinMode(Trig3, OUTPUT);
  pinMode(Echo4, INPUT);
  pinMode(Trig4, OUTPUT);

  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
  myservo5.attach(46);
  myservo6.attach(10);
  myservo7.attach(6);
  myservo8.attach(7);
  servod1.attach(44);
  servod2.attach(45);
  Serial.begin(9600);
  Serial1.begin(9600);
  lcd.init();
  lcd.backlight();


  myservo1.write(90);
  myservo2.write(0);
  myservo3.write(180);
  myservo4.write(80);
  myservo5.write(180);
  myservo6.write(180);
  myservo7.write(0);
  myservo8.write(0);
  servod1.write(180);
  servod2.write(0);

  lcd.begin(16, 2);
  lcd.print(F("Emerover Health Test"));
  lcd.setCursor(3, 1);
  lcd.print(F("Driver Alcohol"));
  lcd.setCursor(25, 0);
  lcd.print(F("Detector"));
  delay(5000);
  pinMode(sensor, INPUT);
  lcd.clear();
}

void loop() {

  sonar();
  al();
  analogWrite(enA, 150);
  analogWrite(enB, 250);
  analogWrite(enC, 150);
  analogWrite(enD, 250);

  if (Serial.available()) {
    t = Serial.read();
    Serial.println(t);
  }

  if (t == 'F') {
    s_front = 1;
    s_back = 0;
    s_left = 0;
    s_right = 0;

    if (Middle_Distance <= 20) {
      _mStop();
      Serial.println(F("Obstacle forward"));
    }
    else {
      _mForward();
      Serial.println(F("Moving Forward"));
    }
  }

  else if (t == 'Q') {
    s_front = 0;
    s_back = 0;
    s_left = 1;
    s_right = 0;
    if ( Right_Distance <= 20 ) {
      _mStop();
      Serial.println(F("Obstacle Left"));
    }
    else {
      _nPar();
      Serial.println(F("Moving Left"));
    }
  }

  else if (t == 'N') {
    s_front = 0;
    s_back = 0;
    s_left = 0;
    s_right = 1;
    if (Left_Distance <= 20) {
      _mStop();
      Serial.println(F("Obstacle Right"));
    }
    else {
      _qPar();
      Serial.println(F("Moving Right"));
    }
  }

  else if (t == 'D') {
    s_front = 0;
    s_back = 1;
    s_left = 0;
    s_right = 0;

    if ( Back_Distance <= 20) {
      _mStop();
      Serial.println(F("Obstacle Behind"));
    }
    else {
      _mBack();
      Serial.println(F("Moving Behind"));
    }
  }

  else if (t == 'L') {
    s_front = 1;
    s_back = 0;
    s_left = 0;
    s_right = 0;

    if (Middle_Distance <= 20 ) {
      _mStop();
      Serial.println(F("Obstacle Left"));
    }
    else {
      _mLeft();
      Serial.println(F("Moving Left"));
    }
  }


  else if (t == 'R') {
    s_front = 1;
    s_back = 0;
    s_left = 0;
    s_right = 0;

    if (Middle_Distance <= 20 ) {
      _mStop();
      Serial.println(F("Obstacle Right"));
    }
    else {
      _mRight();
      Serial.println(F("Moving Right"));
    }
  }

  else if (t == 'S') {
    _mStop();
    Serial.println(F("Robot Stopped"));
  }

  if (t == 'U') {
    myservo2.write(90);
    myservo1.write(0);
    analogWrite(enA, 250);
    analogWrite(enB, 250);
    analogWrite(enC, 250);
    analogWrite(enD, 250);

    digitalWrite(26, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(28, LOW);
    digitalWrite(29, HIGH);
    delay (3200);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    digitalWrite(28, LOW);
    digitalWrite(29, LOW);

    if (t == 'S') {
      digitalWrite(26, LOW);
      digitalWrite(27, LOW);
      digitalWrite(28, LOW);
      digitalWrite(29, LOW);
    }

  }

  if (t == 'T') {
    myservo2.write(90);
    myservo1.write(0);
    analogWrite(enA, 250);
    analogWrite(enB, 250);
    analogWrite(enC, 250);
    analogWrite(enD, 250);


    digitalWrite(26, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(28, LOW);
    digitalWrite(29, HIGH);
    delay (1600);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    digitalWrite(28, LOW);
    digitalWrite(29, LOW);
  }

  if (t == 'V') {
    myservo2.write(90);
    myservo1.write(0);
    analogWrite(enA, 250);
    analogWrite(enB, 250);
    analogWrite(enC, 250);
    analogWrite(enD, 250);


    digitalWrite(26, LOW);
    digitalWrite(27, HIGH);
    digitalWrite(28, HIGH);
    digitalWrite(29, LOW);
    delay (1600);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    digitalWrite(28, LOW);
    digitalWrite(29, LOW);
  }

  if (t == 'G') {
    myservo2.write(90);
    myservo1.write(0);
    analogWrite(enA, 250);
    analogWrite(enB, 250);
    analogWrite(enC, 250);
    analogWrite(enD, 250);


    digitalWrite(26, LOW);
    digitalWrite(27, HIGH);
    digitalWrite(28, HIGH);
    digitalWrite(29, LOW);
    delay (3200);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    digitalWrite(28, LOW);
    digitalWrite(29, LOW);
  }

  if (t == 'P')
    for (pos = 0; pos <= 90; pos += 1) {
      myservo1.write(pos - 90);
      myservo2.write(pos);
      myservo3.write(pos);
      myservo4.write(pos + 80);
      delay(15);
    }

  else if (t == 'M')
    for (pos = 90; pos >= 0; pos -= 1) {
      myservo1.write(pos + 90);
      myservo2.write(pos);
      myservo3.write(pos + 180);
      myservo4.write(pos + 80);
      delay(15);
    }
  else if (t == 'E') {

    for (pos = 0; pos <= 180; pos += 1) {    
    myservo5.write(pos);
    myservo6.write(pos);
    myservo7.write(pos-180);
    myservo8.write(pos-180);
    delay(15);
  }
  }
  else if (t == 'J') {
  for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo5.write(pos);
    myservo6.write(pos);
    myservo7.write(pos);
    myservo8.write(pos);
    delay (15);
  }
  }
  else if (t == 'C') {
    servod1.write(180);
    servod2.write(0);
  }
  else if (t == 'O') {
    servod1.write(20);
    servod2.write(160);
  }

  sonar();

  if (Middle_Distance < 20 && s_front == 1) {
    _mStop();
    _mStop();
    _mStop();
    Serial.println(F("Blocked"));
  }

  else if (Left_Distance < 20 && s_left == 1) {
    _mStop();
    Serial.println(F("Left Parking Blocked"));
  }

  else if (Right_Distance < 20 && s_right == 1) {
    _mStop();
    Serial.println(F("Right Parking Blocked"));
  }
  else if (Back_Distance < 20 && s_back == 1) {
    _mStop();
    Serial.println(F("Back Blocked"));
  }
}
