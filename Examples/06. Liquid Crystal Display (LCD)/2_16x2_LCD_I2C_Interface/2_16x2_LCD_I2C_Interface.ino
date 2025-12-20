/************************************************
Arduino Library
- LiquidCrystal_I2C
- v2.0.0
- Authors: Martin, Frank
- Reference: https://github.com/markub3327/LiquidCrystal_I2C
************************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(I2C_ADDS, LCD_COLS, LCD_ROWS);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("hello, world!");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Demo basic print
  lcd.clear();
  lcd.print("Basic Print:");
  lcd.setCursor(0, 2);
  lcd.print("Hello, World!");
  delay(3000);

  // Demo display on/off
  lcd.clear();
  lcd.print("Display On/Off:");
  for (int x = 0; x < 3; x++) {
    lcd.noDisplay();
    delay(1000);
    lcd.display();
    delay(1000);
  }

  // Demo cursor
  lcd.clear();
  delay(1000);
  lcd.cursor();
  lcd.print("Cursor On");
  delay(3000);
  lcd.clear();
  lcd.noCursor();
  lcd.print("Cursor Off");
  delay(3000);
  lcd.clear();
  lcd.cursor();
  lcd.blink();
  lcd.print("Cursor Blink On");
  delay(3000);
  lcd.clear();
  lcd.noCursor();
  lcd.noBlink();
  lcd.print("Cursor Blink Off");
  delay(3000);

  // Demo set cursor
  lcd.clear();
  lcd.print("Set Cursor Demo");
  delay(3000);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("5,0");
  delay(3000);
  lcd.setCursor(10, 1);
  lcd.print("10,1");
  delay(3000);
  lcd.setCursor(3, 1);
  lcd.print("3,1");
  delay(3000);

  // Demo scroll left
  lcd.clear();
  lcd.print("Scroll Left Demo");
  delay(3000);
  lcd.clear();
  lcd.setCursor(9, 0);
  lcd.print("I LOVE");
  lcd.setCursor(9, 1);
  lcd.print("IOT");
  delay(1000);
  for (int x = 0; x < 16; x++) {
    lcd.scrollDisplayLeft();
    delay(250);
  }

  // Demo scroll right
  lcd.clear();
  lcd.print("Scroll Right");
  lcd.setCursor(0, 1);
  lcd.print("Demo");
  delay(3000);
  lcd.clear();
  lcd.print("I LOVE");
  lcd.setCursor(0, 1);
  lcd.print("IOT");
  delay(1000);
  for (int x = 0; x < 16; x++) {
    lcd.scrollDisplayRight();
    delay(250);
  }
}
