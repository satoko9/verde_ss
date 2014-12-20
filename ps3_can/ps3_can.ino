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

#define SHARP '#'
#define ID 0x003

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

boolean printTemperature;
boolean printAngle;

MCP_CAN CAN0(4);                            // Set CS 

enum {
	start_ch = 'a',
	select_ch,
	left_x_ch,
	left_y_ch,
	right_x_ch,
	right_y_ch,
	L1_ch,L2_ch,
	R1_ch,R2_ch,
	Triangle_ch,
	Circle_ch,
	Cross_ch,
	Square_ch,
	Up_ch,
	Right_ch,
	Down_ch,
	Left_ch,
        pitch_ch,
        roll_ch
}Mnemonic;

//左スティック
void left_stick_x(){
    static int x = 0;
    int left_x = 0;
    
    unsigned char leftx[3] = {left_x_ch,left_x,SHARP};
    
    if (x != PS3.getAnalogHat(LeftHatX)) {
      x = PS3.getAnalogHat(LeftHatX);
      if (PS3.getAnalogHat(LeftHatX) > 0){
        left_x = PS3.getAnalogHat(LeftHatX);
        leftx[1] = left_x;
        CAN0.sendMsgBuf(ID, 0, 3, leftx);              
      }else{
        left_x = 0;
      }
    }    
}

void left_stick_y(){
    static int y = 0;
    int left_y = 0;
    
    unsigned char lefty[3] = {left_y_ch,left_y,SHARP};
    
    if(y != PS3.getAnalogHat(LeftHatY)) {
      y = PS3.getAnalogHat(LeftHatY);
      if(PS3.getAnalogHat(LeftHatY) > 0){
        left_y = PS3.getAnalogHat(LeftHatY);
        lefty[1] = left_y;
        CAN0.sendMsgBuf(ID, 0, 3, lefty);              
        //Serial.print(PS3.getAnalogHat(LeftHatY));
        //Serial.print("\n");
      }else{
        left_y = 0;
        //Serial.print("0\n");
      }
    }    
}

//右スティック
void right_stick_x(){
    static int x = 0;
    int right_x = 0;
    
    unsigned char rightx[3] = {right_x_ch,right_x,SHARP};    
  
    if (x != PS3.getAnalogHat(RightHatX)) {
      x = PS3.getAnalogHat(RightHatX);
      if(PS3.getAnalogHat(RightHatX) > 0){
        right_x = PS3.getAnalogHat(RightHatX);
        rightx[1] = right_x;
        CAN0.sendMsgBuf(ID, 0, 3, rightx);       
//        Serial.print(PS3.getAnalogHat(RightHatX));
//        Serial.print("\n");
      }else{
        right_x = 0;
      }
    }
}

void right_stick_y(){
    static int y = 0;
    int right_y = 0;
    
    unsigned char righty[3] = {right_y_ch,right_y,SHARP};
    
    if(y != PS3.getAnalogHat(RightHatY)){
      y = PS3.getAnalogHat(RightHatY);
      righty[1] = right_y;
      CAN0.sendMsgBuf(ID, 0, 3, righty);       
      if(PS3.getAnalogHat(RightHatY) > 0){
        right_y = PS3.getAnalogHat(RightHatY);
      }else{
        right_y = 0;
      }
    }
}


//L1,R1
void Left1(){
  static int l = 0;  
  int left1 = 0;
  
  unsigned char l1[3] = {L1_ch,left1,SHARP};   
  
    if (l != PS3.getAnalogButton(L1)) {
      l = PS3.getAnalogButton(L1);
      if(PS3.getAnalogButton(L1) > 0){
        left1 = PS3.getAnalogButton(L1);
        l1[1] = left1;     
        CAN0.sendMsgBuf(ID, 0, 3, l1);              
      }else{
        left1 = 0;
      }
    }    
}

void Right1(){
  static int r = 0;
  int right1 = 0;

  unsigned char r1[3] = {R1_ch,right1,SHARP};   

    if (r != PS3.getAnalogButton(R1)) {
      r = PS3.getAnalogButton(R1);
      if(PS3.getAnalogButton(R1) > 0){
        right1 = PS3.getAnalogButton(R1);
        r1[1] = right1;
        CAN0.sendMsgBuf(ID, 0, 3, r1);
      }else{
        right1 = 0;
      }   
    }
}

//L2,R2
void Left2(){
  static int l = 0;
  int left2 = 0;
  
  unsigned char l2[3] = {L2_ch,left2,SHARP};   
  
    if (l != PS3.getAnalogButton(L2)) {
     l = PS3.getAnalogButton(L2);
     if (PS3.getAnalogButton(L2) > 0){
       left2 = PS3.getAnalogButton(L2);
       l2[1] = left2;
       CAN0.sendMsgBuf(ID, 0, 3, l2);              
     }else{
       left2 = 0;
     }
    }
}

void Right2(){
  static int r = 0;  
  int right2 = 0;
  
  unsigned char r2[3] = {R2_ch,right2,SHARP};   
  
    if (r != PS3.getAnalogButton(R2)) {
     r = PS3.getAnalogButton(R2);
     if (PS3.getAnalogButton(R2) > 0){
       right2 = PS3.getAnalogButton(R2);
       r2[1] = right2;
       CAN0.sendMsgBuf(ID, 0, 3, r2);              
     }else{
       right2 = 0;
     }
    } 
}

void Triangle(){
  static int t = 0;
  
  int tri = 0;
  
  unsigned char triangle[3] = {Triangle_ch,tri,SHARP};   
  
    if (t != PS3.getAnalogButton(TRIANGLE)){
      t = PS3.getAnalogButton(TRIANGLE);
      if(PS3.getAnalogButton(TRIANGLE) > 0){
        tri = PS3.getAnalogButton(TRIANGLE);
        triangle[1] = tri;    
        CAN0.sendMsgBuf(ID, 0, 3, triangle);              
      }else{
        tri = 0;
      }
    }    
}

void Circle(){
  static int c = 0;
  
  int cir = 0;
  
  unsigned char circle[3] = {Circle_ch,cir,SHARP};   
  
    if (c != PS3.getAnalogButton(CIRCLE)){
      c = PS3.getAnalogButton(CIRCLE);
      if(PS3.getAnalogButton(CIRCLE) > 0){
        cir = PS3.getAnalogButton(CIRCLE);
        circle[1] = cir;     
        CAN0.sendMsgBuf(ID, 0, 3, circle);              
      }else{
        cir = 0;
      }
    }
}

void Cross(){
  static int s = 0;
  int cro = 0;
  
  unsigned char cross[3] = {Cross_ch,cro,SHARP};   
  
    if (s != PS3.getAnalogButton(CROSS)){
      s = PS3.getAnalogButton(CROSS);
      if(PS3.getAnalogButton(CROSS) > 0){
        cro = PS3.getAnalogButton(CROSS);
        cross[1] = cro;     
        CAN0.sendMsgBuf(ID, 0, 3, cross);              
      }else{
        cro = 0;
      }
    }
}

void Square(){
  static int q = 0;
  int squ = 0;

  unsigned char square[3] = {Square_ch,squ,SHARP};   
  
    if (q != PS3.getAnalogButton(SQUARE)){
      q = PS3.getAnalogButton(SQUARE);
      if(PS3.getAnalogButton(SQUARE) > 0){
        squ = PS3.getAnalogButton(SQUARE);
        square[1] = squ;     
        CAN0.sendMsgBuf(ID, 0, 3, square);              
      }else{
        squ = 0;
      }
    }
}

void Up(){
  static int u = 0;
  int up = 0;

  unsigned char up_key[3] = {Up_ch,up,SHARP};   
  
    if (u != PS3.getAnalogButton(UP)) {
      u = PS3.getAnalogButton(UP);
      if(PS3.getAnalogButton(UP) > 0){
        up = PS3.getAnalogButton(UP);
        up_key[1] = up;     
        CAN0.sendMsgBuf(ID, 0, 3, up_key);              
      }else{
        up = 0;
      }
    }
}

void Right(){
  static int r = 0;
  int rig = 0;
  
  unsigned char right_key[3] = {Right_ch,rig,SHARP};   
  
    if (r != PS3.getAnalogButton(RIGHT)) {
      r = PS3.getAnalogButton(RIGHT);
      if(PS3.getAnalogButton(RIGHT) > 0){
        rig = PS3.getAnalogButton(RIGHT);
        right_key[1] = rig;     
        CAN0.sendMsgBuf(ID, 0, 3, right_key);
      }else{
        rig = 0;
      }
    }    
}

void Down(){
  static int d = 0;
  int dow = 0;
  
  unsigned char down_key[3] = {Down_ch,dow,SHARP};   
  
    if (d != PS3.getAnalogButton(DOWN)) {
      d = PS3.getAnalogButton(DOWN);
      if(PS3.getAnalogButton(DOWN) > 0){
        dow = PS3.getAnalogButton(DOWN);
        down_key[1] = dow;
        CAN0.sendMsgBuf(ID, 0, 3, down_key);
      }else{
        dow = 0;
      }
    }     
}

void Left(){
  static int l = 0;
  int lef = 0;
  
  unsigned char left_key[3] = {Left_ch,lef,SHARP};   
  
    if (l != PS3.getAnalogButton(LEFT)) {
      l = PS3.getAnalogButton(LEFT);
      if(PS3.getAnalogButton(LEFT) > 0){
        lef = PS3.getAnalogButton(LEFT);
        left_key[1] = lef;     
        CAN0.sendMsgBuf(ID, 0, 3, left_key);
      }else{
        lef = 0;
      }
    }
}

void Select(){
  static int s = 0;
  int sel = 0;
  
  unsigned char select[3] = {select_ch,sel,SHARP};   
  
    if (s != PS3.getButtonPress(SELECT)) {
      s = PS3.getButtonPress(SELECT);
      if(PS3.getButtonPress(SELECT) > 0){  
        sel = 1;
        select[1] = sel;     
        CAN0.sendMsgBuf(ID, 0, 3, select);
      }else{
        sel = 0;
      }
    }
}

void Start(){
  static int s = 0;
  int sta = 0;
  
  unsigned char start[3] = {start_ch,sta,SHARP};   
  
    if (s != PS3.getButtonPress(START)) {
      s = PS3.getButtonPress(START);
      if(PS3.getButtonPress(START)){
        sta = 1;
        start[1] = sta;
        CAN0.sendMsgBuf(ID, 0, 3, start);
      }else{
        sta = 0;
      }
    }     
}

void pitch_roll(){
  static int p = 0;
  static int r = 0;
  int pit = 0;
  int rol = 0;
  
  unsigned char pit_rol[6] = {pitch_ch,pit,SHARP,roll_ch,rol,SHARP};
    
     pit = PS3.getAngle(Pitch);
     rol = PS3.getAngle(Roll);
     
     pit_rol[1] = pit;
     pit_rol[4] = rol;
     
     CAN0.sendMsgBuf(ID, 0, 6, pit_rol);  
}

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
    right_stick_x();
    right_stick_y();
    left_stick_x();
    left_stick_y();
    Right1();
    Left1();
    Right2();
    Left2();
    Triangle();
    Circle();
    Cross();
    Square();
    Up();
    Right();
    Down();
    Left();
    Select();
    Start();
    pitch_roll();
  if (PS3.getButtonPress(PS)) {
      PS3.disconnect();
      PS3.setLedOff();
  }
    digitalWrite(13,HIGH);
  }else {
    digitalWrite(13,LOW);
  }
}
