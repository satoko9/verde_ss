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

//左スティック
void right_stick(){
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117) {
      Serial.write('a');
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.write('#');
      Serial.write('A');
      Serial.print(PS3.getAnalogHat(LeftHatY));
      Serial.write('#');
    }else{
      Serial.print("a128#");
      Serial.print("A129#");
    }
}

//右スティック
void left_stick(){
    if (PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.write('b');
      Serial.print(PS3.getAnalogHat(RightHatX));
      Serial.write('#');
      Serial.write('B');
      Serial.print(PS3.getAnalogHat(RightHatY));
      Serial.write('#');
    }else{
      Serial.print("b128#");
      Serial.print("B129#");
    }
}

//L1,R1ボタン
void L1_R1(){
    if (PS3.getAnalogButton(L1) || PS3.getAnalogButton(R1)) {
      Serial.write('o');
      Serial.print(PS3.getAnalogButton(L1));
      Serial.write('#');
      Serial.write('p');
      Serial.print(PS3.getAnalogButton(R1));
      Serial.write('#');
     }else{
      Serial.print("o0#");
      Serial.print("p0#");
     }
}

//L2,R2ボタン
void L2_R2(){  
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
     Serial.write('q');
     Serial.print(PS3.getAnalogButton(L2));
     Serial.write('#');
     Serial.write('r');
     Serial.print(PS3.getAnalogButton(R2));
     Serial.write('#');
    }else{
     Serial.print("q0#");
     Serial.print("r0#");
    }    
}

//△ボタン
void Triangle(){
    if (PS3.getAnalogButton(TRIANGLE)){
     Serial.write('g');
     Serial.print(PS3.getAnalogButton(TRIANGLE));
     Serial.write('#');
    }else{
     Serial.print("g0#");
    }
}

//○ボタン
void Circle(){ 
    if (PS3.getAnalogButton(CIRCLE)){
     Serial.write('h');
     Serial.print(PS3.getAnalogButton(CIRCLE));
     Serial.write('#');
    }else{
     Serial.print("h0#");
    }
}

//×ボタン
void Cross(){
    if (PS3.getAnalogButton(CROSS)){
     Serial.write('i');
     Serial.print(PS3.getAnalogButton(CROSS));
     Serial.write('#');
    }else{
     Serial.print("i0#");
    }
}

//□ボタン
void Square(){
    if (PS3.getAnalogButton(SQUARE)){
     Serial.write('j');
     Serial.print(PS3.getAnalogButton(SQUARE));
     Serial.write('#');
    }else{
     Serial.print("j0#");
    }
}

//上ボタン
void Up(){
    if (PS3.getButtonPress(UP)) {
      Serial.print("c1#");
    }else{
      Serial.print("c0#");
    }
}

//右ボタン
void Right(){
    if (PS3.getButtonPress(RIGHT)) {
      Serial.print("d1#");
    }else{
      Serial.print("d0#");
    }

}

//下ボタン
void Down(){
    if (PS3.getButtonPress(DOWN)) {
      Serial.print("e1#");
    }else{
      Serial.print("e0#");
    }
}

//左ボタン
void Left(){
    if (PS3.getButtonPress(LEFT)) {
      Serial.print("f1#");
    }else{
      Serial.print("f0#");
    }
}

//セレクトボタン
void Select(){
    if (PS3.getButtonPress(SELECT)) {
      Serial.print("s1#");
      //PS3.printStatusString();
    }else{
      Serial.print("s0#");
    }
}

//スタートボタン
void Start(){
    if (PS3.getButtonPress(START)) {
      Serial.print("k1#");
      //printAngle = !printAngle;
    }else{
      Serial.print("k0#");
    }
}

//加速度1
void pitch(){
   Serial.write('m');
   Serial.print(PS3.getAngle(Pitch));
   Serial.write('#');
}

//加速度2
void roll(){
   Serial.write('n');
   Serial.print(PS3.getAngle(Roll));
   Serial.write('#');
}

void setup() {
  Serial.begin(115200);  //ボーレートの値
  while (!Serial); 
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();
  
  if (PS3.getButtonPress(PS)) {
      Serial.print("l1#");
      PS3.disconnect();
  }
  if (PS3.PS3Connected) {
    
    //以下割り込み、値がLOWの時関数を送信する
    attachInterrupt(0, right_stick, LOW);
    attachInterrupt(0, left_stick, LOW);
    attachInterrupt(0, Triangle, LOW);
    attachInterrupt(0, Circle, LOW);
    attachInterrupt(0, Cross, LOW);
    attachInterrupt(0, Square, LOW);
    attachInterrupt(0, L1_R1, LOW);
    attachInterrupt(0, L2_R2, LOW);
    attachInterrupt(0, Start, LOW);
  }
    

#if 1 // Set this to 1 in order to see the angle of the controller　＝　加速度(角度)を見るときは1、見ない時は0にする

      attachInterrupt(0, pitch, LOW);
      attachInterrupt(0, roll, LOW);

#endif
}
