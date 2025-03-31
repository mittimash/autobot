#include <NewPing.h>
#include "Servo.h"

Servo servo;

#define PIN_TRIG 13
#define PIN_ECHO 12
#define MAX_DISTANCE 300 
NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE);

int in1 = 7;
int in2 = 6;
int in3 = 5;
int in4 = 4;
int r = 3;
int l = 9;

int mils;


void setup() {
  Serial.begin(9600);
  servo.attach(11);
  //ставим серву на 90 градусов (прямо)
  servo.write(90);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(l, OUTPUT);
}

void test() {
  Serial.println(sonar.ping_cm());
}

void backward() {
  stop();
  delay(100);
  digitalWrite(in1,HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(r, HIGH);
  digitalWrite(l, HIGH);
}

void stop() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(r, HIGH);
  digitalWrite(l, HIGH);
}

void left(int mils) {
  stop();
  delay(500);
  digitalWrite(in1,HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(r, HIGH);
  digitalWrite(l, HIGH);
  delay(mils);
  stop();
}


void right(int mils) {
  stop();
  delay(500);
  digitalWrite(in1,LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(r, HIGH);
  digitalWrite(l, HIGH);
  delay(mils);
  stop();
}

void forward() {
  stop();
  delay(500);
  digitalWrite(in1,LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(r, 70);
  digitalWrite(l, 100);
}



void loop() {
  delay(30);
  int forward_free = sonar.ping_cm();
  forward();
  while (forward_free > 30 || forward_free == 0) {
      delay(30);
      forward_free = sonar.ping_cm();
      delay(30);
    }
  stop();
  int side = servo_move();
  if (side == 1) {left(280);}
  if (side == 0) {right(280);}
 
}

int servo_move() {
  servo.write(180);
  delay(500);
  int left = sonar.ping_cm();
  delay(1000);

  servo.write(0);
  delay(500);
  int right = sonar.ping_cm();
  delay(1000);

  servo.write(90);
  delay(500);
  if (left > right || left == 0) {
    return 1;
    } 
  
  return 0;
}
