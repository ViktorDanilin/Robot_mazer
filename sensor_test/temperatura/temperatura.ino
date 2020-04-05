#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void setup() {
  // put your setup code here, to run once:
  mlx.begin();
  Serial.begin(9600);

}
void loop() {
  // put your main code here, to run repeatedly:
  float temp = mlx.readObjectTempC();
  Serial.println(temp);
  delay (50);
}
