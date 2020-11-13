
//------------------ CODE FOR DUST SENSOR STARTS -----------------------------------------------------
#define USE_AVG

const int sharpLEDPin = 4;
const int sharpVoPin = A7; 

String health;
int Saqib = 0;
static float Voc = 0.6;
const float K = 0.5;
float dustDensity;
float avarageDensity = 0;
float avgDensityTotal = 0;
void printFValue() {
  Serial.print(dustDensity);
  Serial.print(" ug/m3");
  Serial.print("\n\n");
  Serial.print(avarageDensity);
  Serial.print(" ug/m3");
  Serial.print("\n\n");
  Serial.print(health);
  Serial.print("\n\n");
}

void DustSensor(){
  
  digitalWrite(sharpLEDPin, LOW);
  delayMicroseconds(280);
  int VoRaw = analogRead(sharpVoPin);
  digitalWrite(sharpLEDPin, HIGH);
  delayMicroseconds(9620);

  float Vo = VoRaw;
  Vo = Vo / 1024.0 * 5.0;
  float dV = Vo - Voc;
  if ( dV < 0 ) {
    dV = 0;
    Voc = Vo;
  }
  dustDensity = dV / K * 100.0;
  

  printFValue();
  Serial.println("");
  
}

//------------------ CODE FOR DUST SENSOR ENDS -----------------------------------------------------

//------------------ CODE FOR MODE CHANGING STARTS ---------------------------------------------------

void All_ON(){
    Fan2Start();
    Fan1Start();
    lcdlightON();
    //digitalWrite(, LOW);
}

void All_OFF(){
    Fan1Stop();
    Fan2Stop();
    lcdlightOFF();
    //digitalWrite(, HIGH);
}

int MODE = 1;

void MODE_CONTROL(){
  if(MODE == 1){
    if(avarageDensity < 5){
      All_OFF();
      //digitalWrite(, LOW);
    }
    else{
      All_ON();
    }
  }
}

//------------------ CODE FOR MODE CHANGING ENDS ---------------------------------------------------


//------------------ CODE FOR BLUETOOTH STARTS -----------------------------------------------------
char rBlu;
void Bluetooth(){
  
  rBlu = Serial.read();
  
  if(rBlu == 'A'){
    All_ON();
    MODE = 1;
  }
  if(rBlu == 'S'){
    All_OFF();
    MODE = 0;
  }
  if(rBlu == 'M'){
    All_ON();
    MODE = 0;
  }
  if(rBlu == 'Q'){
    Fan1High();
    MODE = 0;
  }
  if(rBlu == 'W'){
    Fan1Mid();
    MODE = 0;
  }
  if(rBlu == 'E'){
    Fan1Low();
    MODE = 0;
  }
  if(rBlu == 'R'){
    Fan2High();
    MODE = 0;
  }
  if(rBlu == 'T'){
    Fan2Mid();
    MODE = 0;
  }
  if(rBlu == 'Y'){
    Fan2Low();
    MODE = 0;
  }
  if(rBlu == 'U'){
    Fan1Start();
    MODE = 0;
  }
  if(rBlu == 'I'){
    Fan1Stop();
    MODE = 0;
  }
  if(rBlu == 'O'){
    Fan2Start();
    MODE = 0;
  }
  if(rBlu == 'P'){
    Fan2Stop();
    MODE = 0;
  }
  if(rBlu == 'D'){
    lcdlightON();
    MODE = 0;
  }
  if(rBlu == 'F'){
    lcdlightOFF();
    MODE = 0;
  }
}

//------------------ CODE FOR BLUETOOTH ENDS -----------------------------------------------------


//------------------ CODE FOR MOTOR DRIVER STARTS -----------------------------------------------------

int F1Speed = 5;
int F2Speed = 6;
int F1_IN1 = 12;
int F1_IN2 = 11;
int F2_IN1 = 10;
int F2_IN2 = 9;
int FanON = 255;
int FanOff = 0;
int HighSpd = 255;
int MidSpd = 230;
int LowSpd = 85;

void Fan1Start(){
  analogWrite(F1Speed,FanON);
  digitalWrite(F1_IN1, LOW);
  digitalWrite(F1_IN2, HIGH);
}

void Fan2Start(){
  analogWrite(F2Speed,FanON);
  digitalWrite(F2_IN1, LOW);
  digitalWrite(F2_IN2, HIGH);
}
void Fan1High(){
  analogWrite(F1Speed,HighSpd);
  digitalWrite(F1_IN1, LOW);
  digitalWrite(F1_IN2, HIGH);
}

void Fan2High(){
  analogWrite(F2Speed,HighSpd);
  digitalWrite(F2_IN1, LOW);
  digitalWrite(F2_IN2, HIGH);
}
void Fan1Mid(){
  analogWrite(F1Speed,MidSpd);
  digitalWrite(F1_IN1, LOW);
  digitalWrite(F1_IN2, HIGH);
}

void Fan2Mid(){
  analogWrite(F2Speed,MidSpd);
  digitalWrite(F2_IN1, LOW);
  digitalWrite(F2_IN2, HIGH);
}
void Fan1Low(){
  analogWrite(F1Speed,LowSpd);
  digitalWrite(F1_IN1, LOW);
  digitalWrite(F1_IN2, HIGH);
}

void Fan2Low(){
  analogWrite(F2Speed,LowSpd);
  digitalWrite(F2_IN1, LOW);
  digitalWrite(F2_IN2, HIGH);
}

void Fan1Stop(){
    analogWrite(F1Speed,0);
}

void Fan2Stop(){
    analogWrite(F2Speed,0);
}



//------------------ CODE FOR MOTOR DRIVER ENDS -----------------------------------------------------

//------------------ CODE FOR LCD STARTS -----------------------------------------------------

#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int k = 0;

void printLcdValue(String text, float value, String units, bool isLast = false) {
  lcd.print(text);
  lcd.print(value);
  lcd.print(units);
}

void welcome(){
  lcd.setCursor(0,0);
  lcd.print("---------!!---------");
  lcd.setCursor(0,1);
  lcd.print("HEY!! Greetings from");
  lcd.setCursor(0,2);
  lcd.print("    SAQIB GIZAN!    ");
  lcd.setCursor(0,3);
  lcd.print("---------!!---------");
}

void Lcd(){
    lcd.setCursor(0,0);
    printLcdValue("DustLevel ", dustDensity, "ug/m3 ", true);
    lcd.setCursor(0,1);
    printLcdValue("Avg Level ", avarageDensity, "ug/m3", true);
    lcd.setCursor(0,2);
    lcd.print("Air in this place is");
    lcd.setCursor(0,3);
    lcd.print(health);

}

void lcdlightON(){
  digitalWrite(3,2);
}
void lcdlightOFF(){
  digitalWrite(3,LOW);
}

//------------------ CODE FOR LCD ENDS -----------------------------------------------------

//------------------ CODE FOR HEALTH ISSUE ENDS -----------------------------------------------------

void Health(){
  if(avarageDensity < 10){
   health = "     Healthy :)     ";
  }
  else if(avarageDensity < 30){
    health = "     Modarate :|     ";
  }
  else if(avarageDensity < 50){
    health = "    Sensitive :(    ";
  }
  else if(avarageDensity < 145){
    health = "    Unhealthy :'(   ";
  }
  else if(avarageDensity < 245){
    health = "   Very Unhealthy   "; 
  }
  else{
    health = "    Hazardous x_x   ";
  }
}

//------------------ CODE FOR HEALTH ISSUE ENDS -----------------------------------------------------



void setup() {
  
  pinMode(sharpLEDPin, OUTPUT);
  Serial.begin(9600);
  pinMode(F1Speed,OUTPUT);
  pinMode(F2Speed,OUTPUT);
  pinMode(F1_IN1,OUTPUT);
  pinMode(F1_IN2,OUTPUT);
  pinMode(F2_IN1,OUTPUT);
  pinMode(F2_IN2,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3, OUTPUT);
  lcd.begin(20,4);
  All_ON();
  welcome();
  delay(5000);
}

void loop() {
  DustSensor();
  Health();
  Lcd();
  Bluetooth();
  MODE_CONTROL();
  delay(1000);
}
