#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 4, 5, 6, 7);
 
const int currentPin = A0;
int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;
int Vin;  
float Temperature;
unsigned long previousMillis = 0;
int sensor = 10;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps=0;
float steps_old=0;
float temp=0;
float rps=0;
void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print(" Halil ");
  lcd.setCursor(0,1);
  lcd.print("  Coskuner..  ");
  delay(1000);
  pinMode(sensor,INPUT_PULLUP);
}
 
void loop()
{
ekranayazdir();
}
void akim()
{
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);

}
void sicaklik()
{
  unsigned long currentMillis = millis();
  Vin = analogRead(A2);
  
  if (currentMillis - previousMillis >= Vin) 
  {
    previousMillis = currentMillis;
 
  Temperature = (500.0 * Vin)/1023;
   
  }
  
}
void lm393()
{
  start_time=millis();
 end_time=start_time+1000;
 while(millis()<end_time)
 {
   if(digitalRead(sensor))
   {
    steps=steps+1; 
    while(digitalRead(sensor));
   }
 }
    temp=steps-steps_old;
    steps_old=steps;
    rps=(temp/20);
  
}

void ekranayazdir()
{
  akim();
  sicaklik();
  lm393();
  lcd.clear();
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("adcValue =");
  lcd.setCursor(12,0);
  lcd.print(adcValue);
 
//  Serial.print("\t Voltage(mV) = ");
//  Serial.print(adcVoltage,3);
  lcd.setCursor(0,1);
  lcd.print("V in mV =       ");
  lcd.setCursor(10,1);
  lcd.print(adcVoltage,1);
  delay(2000);
  lcd.clear();
//  Serial.print("\t Current = ");
//  Serial.println(currentValue,3);
  lcd.setCursor(0,0);
  lcd.print("Current =       ");
  lcd.setCursor(10,0);
  lcd.print(currentValue,2);
  lcd.setCursor(14,0);
  lcd.print("A");

  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(5,1);
  lcd.print(Temperature);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("rps=");
  lcd.setCursor(4,0);
  lcd.print(rps);
  
  
}



