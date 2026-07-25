#define STBY 4
#define PWMA 5
#define AIN1 7
#define AIN2 8
#define PWMB 6
#define BIN1 9
#define BIN2 10

void leftMotor(int speed) {   // speed: -255 ~ 255，正負代表方向
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

void setup() {
  Serial.begin(9600);
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  digitalWrite(STBY, HIGH);   // 驅動晶片啟用，忘了接/忘了拉HIGH馬達就完全不轉

  Serial.println("=== 左馬達 正轉 ===");
  leftMotor(150);
  delay(2000);
  stopMotors();
  delay(1000);

  Serial.println("=== 左馬達 反轉 ===");
  leftMotor(-150);
  delay(2000);
  stopMotors();
  delay(1000);

  Serial.println("=== 右馬達 正轉 ===");
  rightMotor(150);
  delay(2000);
  stopMotors();
  delay(1000);

  Serial.println("=== 右馬達 反轉 ===");
  rightMotor(-150);
  delay(2000);
  stopMotors();
  delay(1000);

  Serial.println("=== 測試完成 ===");
}

void loop() {
  // 空的，setup() 裡跑完一次就結束，不會一直重複轉
}
