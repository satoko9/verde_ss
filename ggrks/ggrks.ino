/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
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

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      //Serial.print(F("\r\nLeftHatX: "));
      Serial.write('a');
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.write('#');
      //Serial.print(F("\tLeftHatY: "));
      Serial.write('A');
      Serial.print(PS3.getAnalogHat(LeftHatY));
      Serial.write('#');
      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
        //Serial.print(F("\tRightHatX: "));
        Serial.write('b');
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.write('#');
        //Serial.print(F("\tRightHatY: "));
        Serial.write('B');
        Serial.print(PS3.getAnalogHat(RightHatY));
        Serial.write('#');
      }
    }else{
      Serial.print("a128#");
      Serial.print("A129#");
      Serial.print("b128#");
      Serial.print("B129#");
    }

    // Analog button values can be read from almost all buttons
    /*if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }*/
    if (PS3.getButtonClick(PS)) {
      //Serial.print(F("\r\nPS"));
      Serial.print("l1#");
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonPress(TRIANGLE)){
        //Serial.print(F("\r\nTraingle"));
        Serial.print("g1#");
      }else{
        Serial.print("g0#");
      }
      if (PS3.getButtonPress(CIRCLE)){
        //Serial.print(F("\r\nCircle"));
        Serial.print("h1#");
      }else{
        Serial.print("h0#");
      }
      if (PS3.getButtonPress(CROSS)){
        //Serial.print(F("\r\nCross"));
        Serial.print("i1#");
      }else{
        Serial.print("i0#");
      }
      if (PS3.getButtonPress(SQUARE)){
        //Serial.print(F("\r\nSquare"));
        Serial.print("j1#");
      }else{
        Serial.print("j0#");
      }

      if (PS3.getButtonPress(UP)) {
        //Serial.print(F("\r\nUp"));
        Serial.print("c1#");
        /*if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
        }*/
      }else{
        Serial.print("c0#");
      }
      if (PS3.getButtonPress(RIGHT)) {
        //Serial.print(F("\r\nRight"));
        Serial.print("d1#");
        /*if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
        }*/
      }else{
        Serial.print("d0#");
      }
      if (PS3.getButtonPress(DOWN)) {
        //Serial.print(F("\r\nDown"));
        Serial.print("e1#");
        /*if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }*/
      }else{
        Serial.print("e0#");
      }
      if (PS3.getButtonPress(LEFT)) {
        //Serial.print(F("\r\nLeft"));
        Serial.print("f1#");
        /*if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
        }*/
      }else{
        Serial.print("f0#");
      }

      /*if (PS3.getButtonClick(L1))
        Serial.print(F("\r\nL1"));
      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (PS3.getButtonClick(R1))
        Serial.print(F("\r\nR1"));
      if (PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));
*/

      if (PS3.getButtonPress(SELECT)) {
        //Serial.print(F("\r\nSelect - "));
        Serial.print("k8#");
        PS3.printStatusString();
      }
      if (PS3.getButtonPress(START)) {
        //Serial.print(F("\r\nStart"));
        Serial.print("k1#");
        //printAngle = !printAngle;
      }
    }
#if 1 // Set this to 1 in order to see the angle of the controller

      //Serial.print(F("\r\nPitch: "));
      Serial.write('m');
      Serial.print(PS3.getAngle(Pitch));
      Serial.write('#');
      //Serial.print(F("\tRoll: "));
      Serial.write('n');
      Serial.print(PS3.getAngle(Roll));
      Serial.write('#');
    
#endif
  }
#if 0 // Set this to 1 in order to enable support for the Playstation Move controller
  else if (PS3.PS3MoveConnected) {
    if (PS3.getAnalogButton(T)) {
      Serial.print(F("\r\nT: "));
      Serial.print(PS3.getAnalogButton(T));
    }
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect"));
        printTemperature = !printTemperature;
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        PS3.moveSetBulb(Red);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.moveSetBulb(Green);
      }
      if (PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS3.moveSetBulb(Blue);
      }
      if (PS3.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS3.moveSetBulb(Yellow);
      }
      if (PS3.getButtonClick(MOVE)) {
        PS3.moveSetBulb(Off);
        Serial.print(F("\r\nMove"));
        Serial.print(F(" - "));
        PS3.printStatusString();
      }
    }
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
    else if (printTemperature) {
      Serial.print(F("\r\nTemperature: "));
      Serial.print(PS3.getTemperature());
    }
  }
#endif
}
