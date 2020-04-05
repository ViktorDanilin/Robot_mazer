#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.print("HELLO WORLD!");
  delay(5000);
  lcd.clear();
}

void loop()
{

}
