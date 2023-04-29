/////////////////////////////////////////////////////////////////
//Group Project:
#include "Button2.h" 
#include "ESPRotary.h"
#include <Servo.h>
/////////////////////////////////////////////////////////////////
#define ROTARY_PIN1	5
#define ROTARY_PIN2	4
#define BUTTON_PIN	2
#define CLICKS_PER_STEP   2   // this number depends on your rotary encoder 
/////////////////////////////////////////////////////////////////
Servo myservo;
int pos = 0;
int Timer_Value = 0;
ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);
////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("\n\nSimple Counter");
  myservo.attach(13);
  myservo.write(90);
  r.setChangedHandler(rotate);
  r.setLeftRotationHandler(showDirection);
  r.setRightRotationHandler(showDirection);
  b.setTapHandler(click);
  b.setLongClickHandler(resetPosition);
}
void loop() {
  r.loop();
  b.loop();
  Timer_Value = Read_Knob_Status(); 
  timer(Timer_Value);
}
/////////////////////////////////////////////////////////////////
void timer(int n){
    myservo.write(0);              // turn the switch ON
    Serial.println(n);
    int x =60000*n;
    delay(2000);
    myservo.write(90);
    delay(x); //1 minute
    myservo.write(0);
}
// on change
void rotate(ESPRotary& r) {
   Serial.println(r.getPosition());
}
// on left or right rotation
void showDirection(ESPRotary& r) {
  Serial.println(r.directionToString(r.getDirection()));
}
// single click
void click(Button2& btn) {
  Serial.println("Click!");
}
// long click
void resetPosition(Button2& btn) {
  r.resetPosition();
  Serial.println("Reset!");
}
int Read_Knob_Status()
{
  int i = r.getPosition();
  return i;
}
/////////////////////////////////////////////////////////////////
