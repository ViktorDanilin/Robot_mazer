#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Servo.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

Servo servo;
#define echoPin 3
#define trigPin 4
#define SENSOR_LINE_PIN A0
#define buttonPin 2
#define k 13.0
#define enA 11
#define in1 9
#define in2 8
#define enB 5
#define in3 7
#define in4 6
int buttonState = 0;
int value1;

void setup() {
  servo.attach(10);
  mlx.begin(); 
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

}
void loop()

{   
    servo.write(0); //ставим вал под 0

   delay(2000); //ждем 2 секунды

    servo.write(94); //ставим вал под 180

    delay(2000); //ждем 2 секунды

    analogWrite(enA, 200);
    analogWrite(enB, 160);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

}
