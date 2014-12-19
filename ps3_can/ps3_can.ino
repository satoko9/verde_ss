#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include <SPI.h>
#include <PS3BT.h>
#include <usbhub.h>
#include <MsTimer2.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#define SHARP '8'
#define ID 0x0000

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

boolean printTemperature;
boolean printAngle;

MCP_CAN CAN0(4);                            // Set CS 

//左スティック
void left_stick(){
    static int x = 0;
    static int y = 0;
    int left_x = 0;
    int left_y = 0;
    
    unsigned char left[6] = {'a',left_x,SHARP,'A',left_y,SHARP};
    
    if (x != PS3.getAnalogHat(LeftHatX)) {
      x = PS3.getAnalogHat(LeftHatX);
      if (PS3.getAnalogHat(LeftHatX) > 0){
        left_x = PS3.getAnalogHat(LeftHatX);
      }else{
        left_x = 0;
      }
    }
    
    left[1] = left_x;
    
    if(y != PS3.getAnalogHat(LeftHatY)) {
      y = PS3.getAnalogHat(LeftHatY);
      if(PS3.getAnalogHat(LeftHatY) > 0){
        left_y = PS3.getAnalogHat(LeftHatY);
        //Serial.print(PS3.getAnalogHat(LeftHatY));
        //Serial.print("\n");
      }else{
        left_y = 0;
        //Serial.print("0\n");
      }
    }
    
    left[4] = left_y;
    
     CAN0.sendMsgBuf(ID, 0, 8, left);              
}

//右スティック
void right_stick(){
    static int x = 0;
    static int y = 0;
    int right_x = 0;
    int right_y = 0;
    
    unsigned char right[6] = {'b',right_x,SHARP,'B',right_y,SHARP};    
  
    if (x != PS3.getAnalogHat(RightHatX)) {
      x = PS3.getAnalogHat(RightHatX);
      if(PS3.getAnalogHat(RightHatX) > 0){
        right_x = PS3.getAnalogHat(RightHatX);
//        Serial.print(PS3.getAnalogHat(RightHatX));
//        Serial.print("\n");
      }else{
        right_x = 0;
      }
    }
    
    right[1] = right_x;
    
    if(y != PS3.getAnalogHat(RightHatY)){
      y = PS3.getAnalogHat(RightHatY);
      if(PS3.getAnalogHat(RightHatY) > 0){
        right_y = PS3.getAnalogHat(RightHatY);
      }else{
        right_y = 0;
      }
    }
    
    right[4] = right_y;
    
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.print("\n");
     CAN0.sendMsgBuf(ID, 0, 8, right);              
}

//L1,R1
void L1_R1(){
  static int l = 0;
  static int r = 0;
  
  int left1 = 0;
  int right1 = 0;
  
  unsigned char l1_r1[6] = {'o',left1,SHARP,'p',right1,SHARP};   
  
    if (l != PS3.getAnalogButton(L1)) {
      l = PS3.getAnalogButton(L1);
      if(PS3.getAnalogButton(L1) > 0){
        left1 = PS3.getAnalogButton(L1);
      }else{
        left1 = 0;
      }
    }
    
    l1_r1[1] = left1;
     
    if (r != PS3.getAnalogButton(R1)) {
      r = PS3.getAnalogButton(R1);
      if(PS3.getAnalogButton(R1) > 0){
        right1 = PS3.getAnalogButton(R1);
      }else{
        right1 = 0;
      }   
    }
 
     l1_r1[4] = right1;
        
     CAN0.sendMsgBuf(ID, 0, 8, l1_r1);              
}

//L2,R2
void L2_R2(){
  static int l = 0;
  static int r = 0;
  
  int left2 = 0;
  int right2 = 0;
  
  unsigned char l2_r2[6] = {'q',left2,SHARP,'r',right2,SHARP};   
  
    if (l != PS3.getAnalogButton(L2)) {
     l = PS3.getAnalogButton(L2);
     if (PS3.getAnalogButton(L2) > 0){
       left2 = PS3.getAnalogButton(L2);
     }else{
       left2 = 0;
    }
    }

     l2_r2[1] = left2;

    if (r != PS3.getAnalogButton(R2)) {
     r = PS3.getAnalogButton(R2);
     if (PS3.getAnalogButton(R2) > 0){
       right2 = PS3.getAnalogButton(R2);
     }else{
       right2 = 0;
     }
    } 
    
     l2_r2[4] = right2;
     
     CAN0.sendMsgBuf(ID, 0, 8, l2_r2);              
}

void Triangle(){
  static int t = 0;
  
  int tri = 0;
  
  unsigned char triangle[3] = {'g',tri,SHARP};   
  
    if (t != PS3.getAnalogButton(TRIANGLE)){
      t = PS3.getAnalogButton(TRIANGLE);
      if(PS3.getAnalogButton(TRIANGLE) > 0){
        tri = PS3.getAnalogButton(TRIANGLE);
      }else{
        tri = 0;
      }
    }
    
     triangle[1] = tri;
    
     CAN0.sendMsgBuf(ID, 0, 8, triangle);              
}

void Circle(){
  static int c = 0;
  
  int cir = 0;
  
  unsigned char circle[3] = {'h',cir,SHARP};   
  
    if (c != PS3.getAnalogButton(CIRCLE)){
      c = PS3.getAnalogButton(CIRCLE);
      if(PS3.getAnalogButton(CIRCLE) > 0){
        cir = PS3.getAnalogButton(CIRCLE);
      }else{
        cir = 0;
      }
    }
    
     circle[1] = cir;
     
     CAN0.sendMsgBuf(ID, 0, 8, circle);              
}

void Cross(){
  static int s = 0;
  int cro = 0;
  
  unsigned char cross[3] = {'i',cro,SHARP};   
  
    if (s != PS3.getAnalogButton(CROSS)){
      s = PS3.getAnalogButton(CROSS);
      if(PS3.getAnalogButton(CROSS) > 0){
        cro = PS3.getAnalogButton(CROSS);
      }else{
        cro = 0;
      }
    }
    
     cross[1] = cro;
     
     CAN0.sendMsgBuf(ID, 0, 8, cross);              
}

void Square(){
  static int q = 0;
  int squ = 0;

  unsigned char square[3] = {'j',squ,SHARP};   
  
    if (q != PS3.getAnalogButton(SQUARE)){
      q = PS3.getAnalogButton(SQUARE);
      if(PS3.getAnalogButton(SQUARE) > 0){
        squ = PS3.getAnalogButton(SQUARE);
      }else{
        squ = 0;
      }
    }
    
     square[1] = squ;
     
     CAN0.sendMsgBuf(ID, 0, 8, square);              
}

void Up(){
  static int u = 0;
  int up = 0;

  unsigned char up_key[3] = {'c',up,SHARP};   
  
    if (u != PS3.getButtonPress(UP)) {
      u = PS3.getButtonPress(UP);
      if(PS3.getButtonPress(UP) > 0){
        up = PS3.getAnalogButton(UP);
      }else{
        up = 0;
      }
    }
    
     up_key[1] = up;
     
     CAN0.sendMsgBuf(ID, 0, 8, up_key);              
}

void Right(){
  static int r = 0;
  int rig = 0;
  
  unsigned char right_key[3] = {'d',rig,SHARP};   
  
    if (r != PS3.getButtonPress(RIGHT)) {
      r = PS3.getButtonPress(RIGHT);
      if(PS3.getButtonPress(RIGHT) > 0){
        rig = PS3.getAnalogButton(RIGHT);
      }else{
        rig = 0;
      }
    }
    
     right_key[1] = rig;
     
     CAN0.sendMsgBuf(ID, 0, 8, right_key);
}

void Down(){
  static int d = 0;
  int dow = 0;
  
  unsigned char down_key[3] = {'e',dow,SHARP};   
  
    if (d != PS3.getButtonPress(DOWN)) {
      d = PS3.getButtonPress(DOWN);
      if(PS3.getButtonPress(DOWN) > 0){
        dow = PS3.getAnalogButton(DOWN);
      }else{
        dow = 0;
      }
    }
    
     down_key[1] = dow;
     
     CAN0.sendMsgBuf(ID, 0, 8, down_key);
}

void Left(){
  static int l = 0;
  int lef = 0;
  
  unsigned char left_key[3] = {'f',lef,SHARP};   
  
    if (l != PS3.getButtonPress(LEFT)) {
      l = PS3.getButtonPress(LEFT);
      if(PS3.getButtonPress(LEFT) > 0){
        lef = PS3.getAnalogButton(LEFT);
      }else{
        lef = 0;
      }
    }
    
     left_key[1] = lef;
     
     CAN0.sendMsgBuf(ID, 0, 8, left_key);
}

void Select(){
  static int s = 0;
  int sel = 0;
  
  unsigned char select[3] = {'s',sel,SHARP};   
  
    if (s != PS3.getButtonPress(SELECT)) {
      s = PS3.getButtonPress(SELECT);
      if(PS3.getButtonPress(SELECT) > 0){  
        sel = PS3.getAnalogButton(SELECT);
      }else{
        sel = 0;
      }
    }
    
     select[1] = sel;
     
     CAN0.sendMsgBuf(ID, 0, 8, select);
}

void Start(){
  static int s = 0;
  int sta = 0;
  
  unsigned char start[3] = {'k',sta,SHARP};   
  
    if (s != PS3.getButtonPress(START)) {
      s = PS3.getButtonPress(START);
      if(PS3.getButtonPress(START)){
        sta = PS3.getAnalogButton(START);
      }else{
        sta = 0;
      }
    }
    
     start[1] = sta;
     
     CAN0.sendMsgBuf(ID, 0, 8, start);
}

void pitch_roll(){
  static int p = 0;
  static int r = 0;
  int pit = 0;
  int rol = 0;
  
  unsigned char pit_rol[6] = {'m',pit,SHARP,'n',rol,SHARP};
    
     pit = PS3.getAngle(Pitch);
     rol = PS3.getAngle(Roll);
     
     pit_rol[1] = pit;
     pit_rol[4] = rol;
     
     CAN0.sendMsgBuf(ID, 0, 8, pit_rol);  
}

/*void PS_Botton(){
  static int ps = 0;
  int ps3 = 0;
  
  unsigned char ps_botton[3] = {'z',ps3,SHARP};   
  
    if (ps != PS3.getButtonPress(PS)) {
      ps = PS3.getButtonPress(PS);
      if(PS3.getButtonPress(PS)){
        ps3 = PS3.getAnalogButton(PS);
        PS3.disconnect();
        PS3.setLedOff();        
      }else{
        ps3 = 0;
      }
    }
    
     ps_botton[1] = ps3;
    
     CAN0.sendMsgBuf(0x0000, 0, 8, ps_botton);
}*/
  

/*void all_button(){
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
    pitch_roll();
    //PS_Botton();
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}
*/
void setup() {
  Serial.begin(115200);

  while (!Serial);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start\n"));
    while (1); //halt  
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started\n"));
  
  if(CAN0.begin(CAN_1000KBPS) == CAN_OK) {
      Serial.print("can init ok!!\r\n");
  }else {
      Serial.print("Can init fail!!\r\n");
  }

  CAN0.init_Filt(0,0,0x0111);
  CAN0.init_Filt(2,0,0x0112);

//  MsTimer2::set(10, all_button); // 500ms period
//  MsTimer2::start();
  digitalWrite(13,LOW);
}

void loop() {
  Usb.Task();
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
    pitch_roll();
  if (PS3.getButtonPress(PS)) {
      PS3.disconnect();
      PS3.setLedOff();
  }
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}
