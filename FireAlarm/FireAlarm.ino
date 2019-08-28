

//#include <Wire.h>  
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); 
int smoke_data=3; 
int flame_data=4;
int buzzer = 10;
int relay = 11;
int i;
int j;
void setup()
{
  lcd.begin(16,2);   // initializing the LCD
  //lcd.backlight(); // Enable or Turn On the backlight
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO "); // Start Print text to Line 1
  Serial.print("WELCOME TO ");
  lcd.setCursor(0, 1);
  lcd.print("FIRE ALARTSYSTEM"); // Start Print Test to Line 2
  Serial.print("FIRE ALART SYSTEM");
  delay(2000);
  lcd.clear();
}
void loop()
{

  int smoke_data = digitalRead(3);
  int flame_data = digitalRead(4);
  Serial.println(smoke_data);
  Serial.println(flame_data);
  //digitalWrite(buzzer, HIGH);
  
  if (smoke_data == LOW || flame_data == LOW )
  {
    Serial.print("fire detected");
    digitalWrite(buzzer, HIGH);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("FIRE ! FIRE !");
    digitalWrite(relay, 1);
    delay(1000);
  }

  else {
    digitalWrite(buzzer, 0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("...................");
    //lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("NO FIRE (:");
    delay(5000);
    digitalWrite(relay, 0);
  }
}
