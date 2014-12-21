#include <PS3BT.h>
#include <usbhub.h>
#include <MsTimer2.h>
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
void left_stick(){
    static int x = 0;
    static int y = 0;
    
    if (x != PS3.getAnalogHat(LeftHatX)) {
      x = PS3.getAnalogHat(LeftHatX);
      if (PS3.getAnalogHat(LeftHatX) > 0){
        Serial.write('a');
        Serial.print(PS3.getAnalogHat(LeftHatX));
        Serial.write('#');
      }else{
        Serial.print("a0#");
      }
    }
    
    if(y != PS3.getAnalogHat(LeftHatY)) {
      y = PS3.getAnalogHat(LeftHatY);
      if(PS3.getAnalogHat(LeftHatY) > 0){
        Serial.write('A');
        Serial.print(PS3.getAnalogHat(LeftHatY));
        Serial.write('#');
      }else{
        Serial.print("A0#");
      }
    }
      
}

//右スティック
void right_stick(){
    static int x = 0;
    static int y = 0;
  
    if (x != PS3.getAnalogHat(RightHatX)) {
      x = PS3.getAnalogHat(RightHatX);
      if(PS3.getAnalogHat(RightHatX) > 0){
        Serial.write('b');
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.write('#');
      }else{
      Serial.print("b0#");
      }
    }
    
    if(y != PS3.getAnalogHat(RightHatY)){
      y = PS3.getAnalogHat(RightHatY);
      if(PS3.getAnalogHat(RightHatY) > 0){
        Serial.write('B');
        Serial.print(PS3.getAnalogHat(RightHatY));
        Serial.write('#');
      }else{
        Serial.print("B0#");
      }
    }
}

//L1,R1
void L1_R1(){
  static int l = 0;
  static int r = 0;
  
    if (l != PS3.getAnalogButton(L1)) {
      l = PS3.getAnalogButton(L1);
      if(PS3.getAnalogButton(L1) > 0){
        Serial.write('o');
        Serial.print(PS3.getAnalogButton(L1));
        Serial.write('#');
      }else{
        Serial.print("o0#");
      }
    }
     
    if (r != PS3.getAnalogButton(R1)) {
      r = PS3.getAnalogButton(R1);
      if(PS3.getAnalogButton(R1) > 0){
        Serial.write('p');
        Serial.print(PS3.getAnalogButton(R1));
        Serial.write('#');
      }else{
        Serial.print("p0#");
      }   
    }   
}

//L2,R2
void L2_R2(){
  static int l = 0;
  static int r = 0;
  
    if (l != PS3.getAnalogButton(L2)) {
     l = PS3.getAnalogButton(L2);
     if (PS3.getAnalogButton(L2) > 0){
       Serial.write('q');
       Serial.print(PS3.getAnalogButton(L2));
       Serial.write('#');
     }else{
       Serial.print("q0#");
    }
    }

    if (r != PS3.getAnalogButton(R2)) {
     r = PS3.getAnalogButton(R2);
     if (PS3.getAnalogButton(R2) > 0){
       Serial.write('r');
       Serial.print(PS3.getAnalogButton(R2));
       Serial.write('#');
     }else{
     Serial.print("r0#");
     }
    }    
}

void Triangle(){
  static int triangle = 0;
  
    if (triangle != PS3.getAnalogButton(TRIANGLE)){
      triangle = PS3.getAnalogButton(TRIANGLE);
      if(PS3.getAnalogButton(TRIANGLE) > 0){
        Serial.write('g');
        Serial.print(PS3.getAnalogButton(TRIANGLE));
        Serial.write('#');
      }else{
       Serial.print("g0#");
      }
    }
}

void Circle(){
  static int circle = 0;
  
    if (circle != PS3.getAnalogButton(CIRCLE)){
      circle = PS3.getAnalogButton(CIRCLE);
      if(PS3.getAnalogButton(CIRCLE) > 0){
       Serial.write('h');
       Serial.print(PS3.getAnalogButton(CIRCLE));
       Serial.write('#');
      }else{
       Serial.print("h0#");
      }
    }
}

void Cross(){
  static int cross = 0;
  
    if (cross != PS3.getAnalogButton(CROSS)){
      cross = PS3.getAnalogButton(CROSS);
      if(PS3.getAnalogButton(CROSS) > 0){
       Serial.write('i');
       Serial.print(PS3.getAnalogButton(CROSS));
       Serial.write('#');
      }else{
       Serial.print("i0#");
      }
    }
}

void Square(){
  static int square = 0;
    if (square != PS3.getAnalogButton(SQUARE)){
      square = PS3.getAnalogButton(SQUARE);
      if(PS3.getAnalogButton(SQUARE) > 0){
       Serial.write('j');
       Serial.print(PS3.getAnalogButton(SQUARE));
       Serial.write('#');
      }else{
       Serial.print("j0#");
      }
    }
}

void Up(){
  static int up = 0;
  
    if (up != PS3.getAnalogButton(UP)) {
      up = PS3.getAnalogButton(UP);
      if(PS3.getAnalogButton(UP) > 0){
       Serial.write('c');
       Serial.print(PS3.getAnalogButton(UP));
       Serial.write('#');
      }else{
        Serial.print("c0#");
      }
    }
}

void Right(){
  static int right = 0;
  
    if (right != PS3.getAnalogButton(RIGHT)) {
      right = PS3.getAnalogButton(RIGHT);
      if(PS3.getAnalogButton(RIGHT) > 0){
       Serial.write('d');
       Serial.print(PS3.getAnalogButton(RIGHT));
       Serial.write('#');
      }else{
        Serial.print("d0#");
      }
    }
}

void Down(){
  static int down = 0;
  
    if (down != PS3.getAnalogButton(DOWN)) {
      down = PS3.getAnalogButton(DOWN);
      if(PS3.getAnalogButton(DOWN) > 0){
       Serial.write('e');
       Serial.print(PS3.getAnalogButton(DOWN));
       Serial.write('#');
      }else{
        Serial.print("e0#");
      }
    }
}

void Left(){
  static int left = 0;
  
    if (left != PS3.getAnalogButton(LEFT)) {
      left = PS3.getAnalogButton(LEFT);
      if (PS3.getAnalogButton(LEFT) > 0){
       Serial.write('f');
       Serial.print(PS3.getAnalogButton(LEFT));
       Serial.write('#');
      }else{
        Serial.print("f0#");
      }
    }
}

void Select(){
  static int select = 0;
  
    if (select != PS3.getButtonPress(SELECT)) {
      select = PS3.getButtonPress(SELECT);
      if(PS3.getButtonPress(SELECT) > 0){  
        Serial.print("s1#");
        //PS3.printStatusString();
      }else{
        Serial.print("s0#");
      }
    }
}

void Start(){
  static int start = 0;
    if (start != PS3.getButtonPress(START)) {
      start = PS3.getButtonPress(START);
      if(PS3.getButtonPress(START)){
        Serial.print("k1#");
        //printAngle = !printAngle;
      }else{
        Serial.print("k0#");
      }
    }
}

void roll(){
  
  Serial.write('n');
  Serial.print(PS3.getAngle(Roll));
  Serial.write('#');
  
}

void pitch(){
  
  Serial.write('m');
  Serial.print(PS3.getAngle(Pitch));
  Serial.write('#');
  
}

void all_button(){
  if (PS3.PS3Connected) {  
    right_stick();
    left_stick();
    Triangle();
    Circle();
    Cross();
    Square();
    Up();
    Right();
    Down();
    Left();
    L1_R1();
    L2_R2();
    Select();
    Start();
    pitch();
    roll();
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt  
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  MsTimer2::set(10, all_button); // 500ms period
  MsTimer2::start();
  digitalWrite(13,LOW);

}
void loop() {
  Usb.Task();
  
  if (PS3.getButtonPress(PS)) {
      PS3.disconnect();
      PS3.setLedOff();
  }
}
