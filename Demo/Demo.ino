/*
:Project:Clock_Set_Date_Time
:Author: Tiziano Bianchettin
:Date: 13/01/2017
:Revision: 1
:License: Public Domain
thanks to:
  http://a...content-available-to-author-only...t.it/2012/12/orologio-con-arduino-e-il-ds1307.html
  http://w...content-available-to-author-only...i.it/
  http://w...content-available-to-author-only...i.it/
  http://w...content-available-to-author-only...i.it/
  My electronics laboratory professor "Perito Carli"  
*/
//************libraries**************//
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"
#include <Servo.h>


// HX711 circuit wiring
#define SERVO9G_PIN_SIG  16
//************************************//
LiquidCrystal_I2C lcd(0x3F,16,2); // Display  I2C 16 x 2
RTC_DS1307 RTC;
// Scale Settings
const int SCALE_DOUT_PIN = D3;
const int SCALE_SCK_PIN = D4;



// Global variables and defines
const int servo9gRestPosition   = 20;  //Starting position
const int servo9gTargetPosition = 150; //Position when event is detected
// object initialization

HX711 scale;
Servo servo9g;
//************Button*****************//
int P1=D5;
int P2=D6; // Button SET MENU'
int P3=D7; // Button +
int P4=D8; // Button -

//************Variables**************//
int hourupg ;
int minupg;
int yearupg=2019;
int monthupg;
int dayupg;
int menu =0;
//int foodAmount = 100;
bool foodTimeWithAmount[32][24][61];

//Servo servo;

void setup()
{
 // servo.attach(2);
 // servo.write(0);
 int ch1[4] = {0}; 

   // memset(foodTimeWithAmount, 0, sizeof(foodTimeWithAmount));
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  pinMode(P1,INPUT);
  pinMode(P2,INPUT);
  pinMode(P3,INPUT);

  Serial.begin(115200);
  Wire.begin();
  RTC.begin();
  DateTime now = RTC.now();
  int menu=0;
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // Set the date and time at compile time
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
   //RTC.adjust(DateTime(__DATE__, __TIME__)); //removing "//" to adjust the time
    // The default display shows the date and time
  scale.begin(SCALE_DOUT_PIN, SCALE_SCK_PIN);
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();                // reset the scale to 0
  servo9g.attach(SERVO9G_PIN_SIG);
  servo9g.write(servo9gRestPosition);
  delay(100);
  servo9g.detach();
    
  
}
void DisplayDateTime ()
{
// We show the current date and time
  DateTime now = RTC.now();

  lcd.setCursor(0, 1);
  lcd.print("Time:");
  if (now.hour()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  //hourupg=now.hour();
  lcd.print(":");
  if (now.minute()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  //minupg=now.minute();
  lcd.print(":");
  if (now.second()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.second(), DEC);

  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  if (now.day()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  //dayupg=now.day();
  lcd.print("/");
  if (now.month()<=9)
  {
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  //monthupg=now.month();
  lcd.print("/");
  lcd.print(now.year(), DEC);
  //yearupg=now.year();
}
 
void loop()
{ 
  DateTime now = RTC.now();
  Servo servo9g;
  //DisplayDateTime();
  float weight = scale.get_units(1);
  Serial.println(String(weight, 2));
  if(weight>=100)
  Serial.print("Sujit");

  scale.power_down();              // put the ADC in sleep mode
  delay(500);
  scale.power_up();
// check if you press the SET button and increase the menu index
  if(digitalRead(P1))
  {
   menu=menu+1;
  }
// in which subroutine should we go?
  if (menu==0)
    {
     DisplayDateTime(); // void DisplayDateTime
    }
  if (menu==1)
    {
    DisplaySetYear();
    }
  if (menu==2)
    {
    DisplaySetMonth();
    }
  if (menu==3)
    {
    DisplaySetDay();
    }
  if (menu==4)
    {
    DisplaySetHour();
    }
  if (menu==5)
    {
    DisplaySetMinute();
    }
  if (menu==6)
    {
//    StoreAgg();
    DisplayAmount(); 
    menu=0;
    }
    delay(100);
/*
    if ( yearupg == now.year() && monthupg == now.month() && dayupg == now.day() && hourupg == now.hour() && minupg == now.minute()) {
      //ServeFood();
      }
*/
    if (foodTimeWithAmount[now.day()][now.hour()][now.minute()] > 0) {
        //ServeFood();
    }
}  



/*void ServeFood() {
  servo.write(90);
  delay(1000);
  servo.write(0);
  
}*/


void DisplaySetHour()
{
// time setting
  lcd.clear();
  DateTime now = RTC.now();
  if(digitalRead(P2)==HIGH)
  {
    if(hourupg==23)
    {
      hourupg=0;
    }
    else
    {
      hourupg=hourupg+1;
    }
  }
   if(digitalRead(P3)==HIGH)
  {
    if(hourupg==0)
    {
      hourupg=23;
    }
    else
    {
      hourupg=hourupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set time:");
  lcd.setCursor(0,1);
  lcd.print(hourupg,DEC);
  delay(200);
}

void DisplaySetMinute()
{
// Setting the minutes
  lcd.clear();
  if(digitalRead(P2)==HIGH)
  {
    if (minupg==59)
    {
      minupg=0;
    }
    else
    {
      minupg=minupg+1;
    }
  }
   if(digitalRead(P3)==HIGH)
  {
    if (minupg==0)
    {
      minupg=59;
    }
    else
    {
      minupg=minupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Minutes:");
  lcd.setCursor(0,1);
  lcd.print(minupg,DEC);
  delay(200);
}
  
void DisplaySetYear()
{
// setting the year
  lcd.clear();
  if(digitalRead(P2)==HIGH)
  {    
    yearupg=yearupg+1;
  }
   if(digitalRead(P3)==HIGH)
  {
    yearupg=yearupg-1;
  }
  lcd.setCursor(0,0);
  lcd.print("Set Year:");
  lcd.setCursor(0,1);
  lcd.print(yearupg,DEC);
  delay(200);
}

void DisplaySetMonth()
{
// Setting the month
  lcd.clear();
  if(digitalRead(P2)==HIGH)
  {
    if (monthupg==12)
    {
      monthupg=1;
    }
    else
    {
      monthupg=monthupg+1;
    }
  }
   if(digitalRead(P3)==HIGH)
  {
    if (monthupg==1)
    {
      monthupg=12;
    }
    else
    {
      monthupg=monthupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Month:");
  lcd.setCursor(0,1);
  lcd.print(monthupg,DEC);
  delay(200);
}

void DisplaySetDay()
{
// Setting the day
  lcd.clear();
  if(digitalRead(P2)==HIGH)
  {
    if (dayupg==31)
    {
      dayupg=1;
    }
    else
    {
      dayupg=dayupg+1;
    }
  }
   if(digitalRead(P3)==HIGH)
  {
    if (dayupg==1)
    {
      dayupg=31;
    }
    else
    {
      dayupg=dayupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Day:");
  lcd.setCursor(0,1);
  lcd.print(dayupg,DEC);
  delay(200);
}
void DisplayAmount()
{
// Setting the amount
    int foodAmount = foodTimeWithAmount[dayupg][hourupg][minupg];

  lcd.clear();
  if(digitalRead(P2)==HIGH)
  {
    if (foodAmount==0)
    {
      foodAmount=1;
    }
    else
    {
      foodAmount=0;
    }
  }
   if(digitalRead(P3)==HIGH)
  {
    if (foodAmount==0)
    {
      foodAmount=1;
    }
    else
    {
      foodAmount=0;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Amount:");
  lcd.setCursor(0,1);
  lcd.print(foodAmount,DEC);
  delay(5000);
  menu = 0;
  foodTimeWithAmount[dayupg][hourupg][minupg] = foodAmount;
}

/*void StoreAgg()
{
// Variable saving
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SAVING IN");
  lcd.setCursor(0,1);
  lcd.print("PROGRESS");
  //RTC.adjust(DateTime(yearupg,monthupg,dayupg,hourupg,minupg,0));
  delay(200);
}*/
