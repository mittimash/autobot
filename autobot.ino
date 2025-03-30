// объявление пинов для компонентов
#define SERVO_PIN 11
#define HC_TRIG 12
#define HC_ECHO 10

//объявление библиотек
#include <Servo.h> 
#include <NewPing.h>

// объявление переменных компонентов машинки
Servo myservo;
NewPing sonar(HC_TRIG, HC_ECHO, 100);

// активация пинов и компонентов, преднастройки
void setup() { 
  myservo.attach(SERVO_PIN);
  Serial.begin(9600);
  Serial.println('Hello!');
} 

// главная функция робота
void loop() {
  int where = servo_move();
  Serial.println(where);
  delay(50);
} 

// функция для сбора данных справа и слева от машинки 
// поворачивает голову сервы и собирает данные о расстоянии 
// возвращает направление куда можно повернуть машинке и ехать. 
// 0 - направо, 
// 1 - налево


int servo_move() {
  myservo.write(30);
  int right = sonar.ping_cm();
  Serial.print('Right: ');
  Serial.println(right);
  delay(2000);
  myservo.write(180);
  int left = sonar.ping_cm();
  Serial.print('left: ');
  Serial.println(left);
  delay(2000);
  myservo.write(110);
  if (right > left) {
    return 0;
  }
  return 1;
}


