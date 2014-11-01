#include <PS3BT.h>
#include <usbhub.h>
#include <MsTimer2.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

boolean printTemperature;
boolean printAngle;

const int motorA = 2;
const int motorB = 3;
const int PWM_motAB = 5;
const int motorC = 7;
const int motorD = 8;
const int PWM_motCD = 6;

void right_front(){
  static int r = 0;
  
    if (r != PS3.getAnalogButton(R2)) {
      r = PS3.getAnalogButton(R2);
      if(PS3.getAnalogButton(R2) > 0){
       digitalWrite(motorA,HIGH);
       digitalWrite(motorB,LOW);
       Serial.print("R2");
       Serial.print(PS3.getAnalogButton(R2));
       Serial.print("\n");
      }
    }
}

void left_front(){
  static int l = 0;
    if (l != PS3.getAnalogButton(L2)) {
      l = PS3.getAnalogButton(L2);
      if(PS3.getAnalogButton(L2) > 0){
       digitalWrite(motorC,HIGH);
       digitalWrite(motorD,LOW);
       Serial.print("L2");
       Serial.print(PS3.getAnalogButton(L2));
       Serial.print("\n");       
      }   
    }   
}

void right_back(){
  static int r = 0;
    if (r != PS3.getAnalogButton(R1)) {
      r = PS3.getAnalogButton(R1);
      if(PS3.getAnalogButton(R1) > 0){
       digitalWrite(motorA,LOW);
       digitalWrite(motorB,HIGH);
       Serial.print("R1");
       Serial.print(PS3.getAnalogButton(R1));
       Serial.print("\n");
      }   
    }   
}

void left_back(){
  static int l = 0;
    if (l != PS3.getAnalogButton(L1)) {
      l = PS3.getAnalogButton(L1);
      if(PS3.getAnalogButton(L1) > 0){
       digitalWrite(motorC,LOW);
       digitalWrite(motorD,HIGH);
       Serial.print("L1");
       Serial.print(PS3.getAnalogButton(L1));
       Serial.print("\n");
      }
    }
}

void brake(){
  static int circle = 0;  
    if (circle != PS3.getAnalogButton(CIRCLE)){
      circle = PS3.getAnalogButton(CIRCLE);
      if(PS3.getAnalogButton(CIRCLE) > 0){
       digitalWrite(motorA,LOW);
       digitalWrite(motorB,LOW);
       digitalWrite(motorC,LOW);
       digitalWrite(motorD,LOW);
       Serial.print("stop");
       Serial.print("\n");
      }
    }
}

/*void accel_up(){
  static int up = 0;
  int accel = 90;   
    if (up != PS3.getAnalogButton(UP)){
      up = PS3.getAnalogButton(UP);
      if(PS3.getAnalogButton(UP) > 0){
       accel++;
      }
    }else if(down != PS3.getAnalogButton(DOWN)){
*/      
  

void all(){
  if (PS3.PS3Connected) {
    right_front();
    left_front();
    right_back();
    left_back();
    brake();
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(motorA,LOW);
    digitalWrite(motorB,LOW);
    digitalWrite(motorC,LOW);
    digitalWrite(motorD,LOW);
    digitalWrite(13,LOW);    
  }
}

void setup() {
  pinMode(motorA,OUTPUT); //信号用ピン
  pinMode(motorB,OUTPUT); //信号用ピン
  pinMode(motorC,OUTPUT); //信号用ピン
  pinMode(motorD,OUTPUT); //信号用ピン

  analogWrite(PWM_motAB,70);
  analogWrite(PWM_motCD,70);
  
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  MsTimer2::set(10, all); // 500ms period
  MsTimer2::start();
  digitalWrite(13,LOW);
}

void loop() {
  Usb.Task();
  
  if (PS3.getButtonPress(PS)) {
      //Serial.print("l1#");
      PS3.disconnect();
      PS3.setLedOff();
  }
  
}
  
