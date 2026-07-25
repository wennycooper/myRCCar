#include <SoftwareSerial.h>

#define STBY 4
#define PWMA 5
#define AIN1 7
#define AIN2 8
#define PWMB 6
#define BIN1 9
#define BIN2 10

SoftwareSerial BT(2, 3);   // RX, TX ← 接 HC-05 TXD/RXD

const int SPEED = 150;     // 0~255
char currentCmd = 'S';

void leftMotor(int speed) {
  digitalWrite(AIN1, speed >= 0 ? HIGH : LOW);
  digitalWrite(AIN2, speed >= 0 ? LOW  : HIGH);
  analogWrite(PWMA, abs(speed));
}

void rightMotor(int speed) {
  digitalWrite(BIN1, speed >= 0 ? HIGH : LOW);
  digitalWrite(BIN2, speed >= 0 ? LOW  : HIGH);
  analogWrite(PWMB, abs(speed));
}

void stopMotors() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

void applyCommand(char cmd) {
  switch (cmd) {
    case 'F': leftMotor(SPEED);  rightMotor(SPEED);  break;
    case 'B': leftMotor(-SPEED); rightMotor(-SPEED); break;
    case 'L': leftMotor(-SPEED); rightMotor(SPEED);  break;
    case 'R': leftMotor(SPEED);  rightMotor(-SPEED); break;
    default:  stopMotors(); break;   // 'S' 或其他未知指令一律停止
  }
}

void setup() {
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  digitalWrite(STBY, HIGH);

  BT.begin(9600);      // HC-05 出廠預設鮑率 9600
  Serial.begin(9600);  // 接電腦用，方便 debug 看收到什麼指令
}

void loop() {
  if (BT.available()) {
    char c = BT.read();
    // BT Serial App 送出文字後常常會多送 \r 或 \n，
    // 只接受看得懂的指令，其他 byte（換行、雜訊）直接忽略
    if (c == 'F' || c == 'B' || c == 'L' || c == 'R' || c == 'S') {
      currentCmd = c;
      Serial.print("收到指令: ");
      Serial.println(currentCmd);
    }
  }
  applyCommand(currentCmd);
}
