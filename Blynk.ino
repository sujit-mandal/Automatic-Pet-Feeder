/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  App project setup:
    Time Input widget on V1.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "RTClib.h"


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f9DT6chbi_PwR_-z-JkjHRNdGfAB8psQ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "satadal";
char pass[] = "satadal1996";


int foodTime[32][25] = {0};
int Day, Hour, Amount;


//Day
  BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
//  Serial.print("V0 Day value is: ");
 // Serial.println(pinValue);
  Day = pinValue;
}
//Hour
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
 // Serial.print("V1 Hour value is: ");
//  Serial.println(pinValue);
  Hour = pinValue;
}

//Amount

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
 // Serial.print("V2 Amount value is: ");
 // Serial.println(pinValue);
  Amount = pinValue;
}



BLYNK_WRITE(V5)
{
  int buttonState = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V5 Button value is: ");
  Serial.println(buttonState);
  if (buttonState == 1) {
    // Set time into array for time set
    Serial.print("From android Day : ");
    Serial.println(Day);
     Serial.print("From android Hour : ");
     Serial.println(Hour);
      Serial.print("From android Amount: ");
      Serial.println(Amount);
    //Serial.println();
    foodTime[Day][Hour] = Amount;
  }
  
}




void setup()
{

  // Debug console
  Serial.begin(9600);


  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);


}

void loop()
{
  Blynk.run();
  //DateTime now = rtc.now();

//    Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(" (");
////    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    Serial.print(") ");
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println();
//    delay(10000);


  
}
