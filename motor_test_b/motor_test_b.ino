#define STBY 4
#define PWMA 5
#define AIN1 7
#define AIN2 8
#define PWMB 6
#define BIN1 9
#define BIN2 10

const int SPEED = 150;   // 0~255，可依實際狀況調整

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

void moveForward(int speed) {
  leftMotor(speed);
  rightMotor(speed);
}

void moveBackward(int speed) {
  leftMotor(-speed);
  rightMotor(-speed);
}

void turnLeft(int speed) {    // 原地左轉：左輪反轉、右輪正轉
  leftMotor(-speed);
  rightMotor(speed);
}

void turnRight(int speed) {   // 原地右轉：左輪正轉、右輪反轉
  leftMotor(speed);
  rightMotor(-speed);
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
  digitalWrite(STBY, HIGH);

  Serial.println("=== 前進 ===");
  moveForward(SPEED);
  delay(1500);
  stopMotors();
  delay(1000);

  Serial.println("=== 後退 ===");
  moveBackward(SPEED);
  delay(1500);
  stopMotors();
  delay(1000);

  Serial.println("=== 左轉（原地） ===");
  turnLeft(SPEED);
  delay(800);
  stopMotors();
  delay(1000);

  Serial.println("=== 右轉（原地） ===");
  turnRight(SPEED);
  delay(800);
  stopMotors();
  delay(1000);

  Serial.println("=== 測試完成 ===");
}

void loop() {
  // 空的，setup() 跑完一次就結束
}
