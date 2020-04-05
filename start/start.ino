#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo;
int speed1 = 0;
int speed2 = 0;
#define pinX A1
#define echoPin 3
#define trigPin A2
#define SENSOR_LINE_PIN A0
#define buttonPin 2 

//REG
#define k 5.5
#define SPEED_REG 85
#define SPEED_UP 180
#define SPEED_DOWN 0
int speed_now = SPEED_REG;

#define S1 5
#define M1 4
#define S2 6
#define M2 7


int buttonState = 0;
int value1;
unsigned int x;
//char r = 0;


#define ACCEL_THRESH 11
#define ACCEL_THRESH_TIMEOUT 5
#define ACCEL_TIMEOUT 1900

#define ACCEL_DOWN_THRESH 6
#define ACCEL_DOWN_THRESH_TIMEOUT 4
#define ACCEL_DOWN_TIMEOUT 400

#define ACCEL_UP_V 260 
#define ACCEL_DOWN_V 290 
int accel_up = 0;
int accel_down = 0;

bool accel_up_b = false;
bool accel_down_b = false;

unsigned long pt_up = 0;
unsigned long pt_down = 0;

#define RASPI_TIMEOUT 3000
unsigned long pt_raspi = 0;

float readUS() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = (float)pulseIn(echoPin, HIGH);
  float cm = duration / 58.0;
  return cm;
}

#define GORKA_UP_TIMEOUT 3500
#define GORKA_DOWN_TIMEOUT 8000
unsigned long pt_gorka = 0;
//unsigned long pt_gorka2 = 0;
int gorka = 0;
//bool gorka2 = false;


void accel_calc() {
  x = analogRead(pinX);
  if (x <= ACCEL_UP_V) {
    accel_up++;
    if (accel_up == ACCEL_THRESH_TIMEOUT) {
      pt_up = millis();
    }
  }

  if ((millis() - pt_up) < ACCEL_TIMEOUT ) {
    if (accel_up >= ACCEL_THRESH) {
      accel_up = 0;
      pt_up = millis();
      accel_up_b = true;
    }
  }
  else {
    if (accel_up >= ACCEL_THRESH_TIMEOUT) {
      accel_up = 0;
      accel_up_b = false;
    }

  }

  if (x >= ACCEL_DOWN_V) {
    accel_down++;
    if (accel_down == ACCEL_DOWN_THRESH_TIMEOUT) {
      pt_down = millis();
    }
  }

  if ((millis() - pt_down) < ACCEL_DOWN_TIMEOUT ) {
    if (accel_down >= ACCEL_DOWN_THRESH) {
      accel_down = 0;
      pt_down = millis();
      accel_down_b = true;
    }
  }
  else {
    if (accel_down >= ACCEL_DOWN_THRESH_TIMEOUT) {
      accel_down = 0;
      accel_down_b = false;
    }

  }
  Serial.println(String("Accel Debug: x: ") + String(x) + " up: " + String(accel_up) + " down: " + String(accel_down) + " up: " + String(pt_up) + " down: " + String(pt_down));
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  servo.attach(11);

  mlx.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

}

void loop() {
  String rec = "";
  while (Serial.available() > 0) {
    //    char r;
    rec += String((char)Serial.read());
  }
  Serial.println(rec);
  char r = 0;
  for (int i = 0; i < rec.length(); i++) {
    if ((rec[i] == '#') && ((i + 1) < rec.length())) {
      r = rec[i + 1];
    }
  }
  accel_calc();
  // Serial.println(x);
  buttonState = !digitalRead(buttonPin);
  bool sign = digitalRead(SENSOR_LINE_PIN);
  //  Serial.println("start temp: ");
  float temp = mlx.readObjectTempC();
  float cm = readUS();
  //  Serial.print("OK");
  int type = 0;


  lcd.setCursor(1, 0);
  lcd.print((millis() - pt_raspi));
  if (buttonState == HIGH)
    type = 1;
  else if (sign == 1)
    type = 2;
  else if ((temp > 33.0)or(r == '4') && ((millis() - pt_raspi) > RASPI_TIMEOUT))
    type = 3;
  else if ((r == '1') && ((millis() - pt_raspi) > RASPI_TIMEOUT)) {
    type = 4;
    pt_raspi = millis();
    //    Serial.flush();
  }
  else if ((r == '2') && ((millis() - pt_raspi) > RASPI_TIMEOUT)) {
    type = 5;
    pt_raspi = millis();
  }
  else if ((r == '3') && ((millis() - pt_raspi) > RASPI_TIMEOUT)) {
    type = 6;
    pt_raspi = millis();
  }
  else if (accel_up_b)
    type = 7;
  else if (accel_down_b)
    type = 8;
  switch (type) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("1");
      motors(-60, -60);
      delay(100);
      motors(-120, 120);
      delay(300);
      motors(120, 120);
      delay(100);
      lcd.clear();
      type = 0;
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("2");
      motors(-90, -90);
      delay(500);
      motors(-120, 120);
      delay(500);
      lcd.clear();
      type = 0;
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("3"); 
      if (temp < 1000) {
        motors(0, 0);
        delay(2000);
        servo.write(0);
        delay(2000);
        servo.write(97);
        delay(2000);
      }
      lcd.clear();
      type = 0;
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("H");
      motors(0, 0);
      delay(2000);
      servo.write(0);
      delay(2000);
      servo.write(97);
      delay(2000);
      servo.write(0);
      delay(2000);
      servo.write(97);
      delay(2000);
      lcd.clear();
      type = 0;
      pt_raspi = millis();
      break;
    case 5:
      lcd.setCursor(0, 0);
      lcd.print("S");
      motors(0, 0);
      delay(2000);
      servo.write(0);
      delay(2000);
      servo.write(97);
      delay(2000);
      lcd.clear();
      type = 0;
      pt_raspi = millis();
      break;
    case 6:
      lcd.setCursor(0, 0);
      lcd.print("U");
      motors(0, 0);
      delay(2000);
      lcd.clear();
      type = 0;
      pt_raspi = millis();
      break;
    case 7:
      lcd.setCursor(0, 0);
      lcd.print("7");
      speed_now = SPEED_UP;
      pt_gorka = millis();
      gorka = 1;
      lcd.clear();
      type = 0;
      break;
    case 8:
      lcd.setCursor(0, 0);
      lcd.print("8");
      motors(SPEED_DOWN, SPEED_DOWN);
      speed_now = SPEED_DOWN;
      pt_gorka = millis();
      gorka = 2;
      lcd.clear();
      type = 0;
      break;
    case 0:
      if (gorka == 1) {
        if ((millis() - pt_gorka) > GORKA_UP_TIMEOUT) {
          speed_now = SPEED_REG;
          gorka = 0;
        }
      }
      else if (gorka == 2) {
        if ((millis() - pt_gorka) > GORKA_DOWN_TIMEOUT) {
          speed_now = SPEED_REG;
          gorka = 0;
        }

      }
      else {
        speed_now = SPEED_REG;
        //        gorka = 0;
      }


    default:
      lcd.setCursor(7, 0); // 1 строка
      lcd.print("Speed:");
      lcd.print(speed_now);
      lcd.setCursor(7, 1); // 3 строка
      lcd.print(" x:");
      lcd.print(x);
      float error = (cm - 5.0);
      float sr = (error * k);
      speed1 = (speed_now - sr);
      if (speed1 < 0) speed1 = 0;
      if (speed1 > 255) speed1 = 255;
      speed2 = (speed_now + sr);
      if (speed2 < 0) speed2 = 0;
      if (speed2 > 255) speed2 = 255;
      motors(speed2, speed1);
  }
  accel_up_b = false;
  accel_down_b = false;

  delay(10);
}

void motors(int Speed1, int Speed2) {
  analogWrite(S1, abs(Speed1));
  analogWrite(S2, abs(Speed2));
  digitalWrite(M1, Speed1 < 0);
  digitalWrite(M2, Speed2 < 0);
}
