#include"Display.h"
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

void Display :: show(int x, int y, String text)
{
  lcd.setCursor(x,y);
  lcd.print(text);
}

void Display :: show(int x, int y, float num)
{
  lcd.setCursor(x,y);
  num *= 100;
  int ver = num;
  num = ver / 100.0;
  lcd.print(num);
}

void Display :: show(int x, int y, double num)
{
  lcd.setCursor(x,y);
  num *= 100;
  int ver = num;
  num = ver / 100.0;
  lcd.print(num);
}

void Display :: show(int x, int y, int num)
{
  lcd.setCursor(x,y);
  lcd.print(num);
}

void Display :: legend()
{
  lcd.setCursor(0,0);
  lcd.print("DustLvL         ug/L");
  lcd.setCursor(0,1);
  lcd.print("Humidity        %   ");
  lcd.setCursor(0,2);
  lcd.print("Temperature     C   ");
  lcd.setCursor(0,3);
  lcd.print("AirQuality          ");
  delay(500);
}
