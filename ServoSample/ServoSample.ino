#include <Servo.h>
 
Servo servo;
 
void setup() {
    servo.attach(D1);
    servo.write(0);
    delay(2000);
}
 
void loop() {
    servo.write(0);
    delay(3000);
    servo.write(90);
    delay(3000);
    servo.write(180);
    delay(3000);
}
