#include"Dispaly.h"
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Display :: Display()
{
  
}

void Display :: begin()
{
  lcd.begin(20,4);
  lcd.setCursor(0,0);
  lcd.print("Low cost AirPurifier");
  lcd.setCursor(0,1);
  lcd.print("         by         ");
  lcd.setCursor(0,2);
  lcd.print("  Md. Masrur Saqib  ");
  lcd.setCursor(0,3);
  lcd.print("       Gizan        ");
  delay(1500);
  lcd.setCursor(0,1);
  lcd.print("     guided by      ");
  lcd.setCursor(0,2);
  lcd.print(" Prof. Dr. Mir Md.  ");
  lcd.setCursor(0,3);
  lcd.print("  Jahangir Kabr Sir ");
  delay(1500);
}
