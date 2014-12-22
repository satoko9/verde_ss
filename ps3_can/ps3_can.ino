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
	up_ch,
	right_ch,
	down_ch,
	left_ch,
	triangle_ch,
	circle_ch,
	cross_ch,
	square_ch,
	l1_ch,l2_ch,
	r1_ch,r2_ch,
        pitch_ch,
        roll_ch
}Mnemonic;

//左スティックx
void Left_x(){
    static int before_left_x = 0;
    int left_x_value = 0;
    
    unsigned char left_stick_x[3] = {left_x_ch,left_x_value,SHARP};
    
    if (before_left_x != PS3.getAnalogHat(LeftHatX)) {
      before_left_x = PS3.getAnalogHat(LeftHatX);
      if (PS3.getAnalogHat(LeftHatX) > 0){
        left_x_value = PS3.getAnalogHat(LeftHatX);
        left_stick_x[1] = left_x_value;
      }else{
        left_x_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, left_stick_x);
    }    
}

//左スティックy
void Left_y(){
    static int before_left_y = 0;
    int left_y_value = 0;
    
    unsigned char left_stick_y[3] = {left_y_ch,left_y_value,SHARP};
    
    if(before_left_y != PS3.getAnalogHat(LeftHatY)) {
      before_left_y = PS3.getAnalogHat(LeftHatY);
      if(PS3.getAnalogHat(LeftHatY) > 0){
        left_y_value = PS3.getAnalogHat(LeftHatY);
        left_stick_y[1] = left_y_value;
        //Serial.print(PS3.getAnalogHat(LeftHatY));
        //Serial.print("\n");
      }else{
        left_y_value = 0;
        //Serial.print("0\n");
      }
        CAN0.sendMsgBuf(ID, 0, 3, left_stick_y);              
    }    
}

//右スティックx
void Right_x(){
    static int before_right_x = 0;
    int right_x_value = 0;
    
    unsigned char right_stick_x[3] = {right_x_ch,right_x_value,SHARP};
  
    if (before_right_x != PS3.getAnalogHat(RightHatX)) {
      before_right_x = PS3.getAnalogHat(RightHatX);
      if(PS3.getAnalogHat(RightHatX) > 0){
        right_x_value = PS3.getAnalogHat(RightHatX);
        right_stick_x[1] = right_x_value;
//        Serial.print(PS3.getAnalogHat(RightHatX));
//        Serial.print("\n");
      }else{
        right_x_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, right_stick_x);       
    }
}

//右スティックy
void Right_y(){
    static int before_right_y = 0;
    int right_y_value = 0;
    
    unsigned char right_stick_y[3] = {right_y_ch,right_y_value,SHARP};
    
    if(before_right_y != PS3.getAnalogHat(RightHatY)){
      before_right_y = PS3.getAnalogHat(RightHatY);
      if(PS3.getAnalogHat(RightHatY) > 0){
        right_y_value = PS3.getAnalogHat(RightHatY);
        right_stick_y[1] = right_y_value;
      }else{
        right_y_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, right_stick_y);       
    }
}

void Up(){
  static int before_up = 0;
  int up_value = 0;

  unsigned char up_button[3] = {up_ch,up_value,SHARP};   
  
    if (before_up != PS3.getAnalogButton(UP)) {
      before_up = PS3.getAnalogButton(UP);
      if(PS3.getAnalogButton(UP) > 0){
        up_value = PS3.getAnalogButton(UP);
        up_button[1] = up_value;     
      }else{
        up_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, up_button);              
    }
}

void Right(){
  static int before_right = 0;
  int right_value = 0;
  
  unsigned char right_button[3] = {right_ch,right_value,SHARP};   
  
    if (before_right != PS3.getAnalogButton(RIGHT)) {
      before_right = PS3.getAnalogButton(RIGHT);
      if(PS3.getAnalogButton(RIGHT) > 0){
        right_value = PS3.getAnalogButton(RIGHT);
        right_button[1] = right_value;     
      }else{
        right_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, right_button);
    }
}

void Down(){
  static int before_down = 0;
  int down_value = 0;
  
  unsigned char down_button[3] = {down_ch,down_value,SHARP};   
  
    if (before_down != PS3.getAnalogButton(DOWN)) {
      before_down = PS3.getAnalogButton(DOWN);
      if(PS3.getAnalogButton(DOWN) > 0){
        down_value = PS3.getAnalogButton(DOWN);
        down_button[1] = down_value;
      }else{
        down_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, down_button);
    }     
}

void Left(){
  static int before_left = 0;
  int left_value = 0;
  
  unsigned char left_button[3] = {left_ch,left_value,SHARP};   
  
    if (before_left != PS3.getAnalogButton(LEFT)) {
      before_left = PS3.getAnalogButton(LEFT);
      if(PS3.getAnalogButton(LEFT) > 0){
        left_value = PS3.getAnalogButton(LEFT);
        left_button[1] = left_value;     
      }else{
        left_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, left_button);
    }
}

void Triangle(){
  static int before_triangle = 0;
  int triangle_value = 0;
  
  unsigned char triangle_button[3] = {triangle_ch,triangle_value,SHARP};   
  
    if (before_triangle != PS3.getAnalogButton(TRIANGLE)){
      before_triangle = PS3.getAnalogButton(TRIANGLE);
      if(PS3.getAnalogButton(TRIANGLE) > 0){
        triangle_value = PS3.getAnalogButton(TRIANGLE);
        triangle_button[1] = triangle_value;    
      }else{
        triangle_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, triangle_button);
    }
}

void Circle(){
  static int before_circle = 0;
  int circle_value = 0;
  
  unsigned char circle_button[3] = {circle_ch,circle_value,SHARP};   
  
    if (before_circle != PS3.getAnalogButton(CIRCLE)){
      before_circle = PS3.getAnalogButton(CIRCLE);
      if(PS3.getAnalogButton(CIRCLE) > 0){
        circle_value = PS3.getAnalogButton(CIRCLE);
        circle_button[1] = circle_value;     
      }else{
        circle_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, circle_button);              
    }
}

void Cross(){
  static int before_cross = 0;
  int cross_value = 0;
  
  unsigned char cross_button[3] = {cross_ch,cross_value,SHARP};   
  
    if (before_cross != PS3.getAnalogButton(CROSS)){
      before_cross = PS3.getAnalogButton(CROSS);
      if(PS3.getAnalogButton(CROSS) > 0){
        cross_value = PS3.getAnalogButton(CROSS);
        cross_button[1] = cross_value;     
      }else{
        cross_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, cross_button);              
    }
}

void Square(){
  static int before_square = 0;
  int square_value = 0;

  unsigned char square_button[3] = {square_ch,square_value,SHARP};   
  
    if (before_square != PS3.getAnalogButton(SQUARE)){
      before_square = PS3.getAnalogButton(SQUARE);
      if(PS3.getAnalogButton(SQUARE) > 0){
        square_value = PS3.getAnalogButton(SQUARE);
        square_button[1] = square_value;     
      }else{
        square_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, square_button);              
    }
}

//L1,R1
void Left1(){
  static int before_l1 = 0;  
  int l1_value = 0;
  
  unsigned char l1_button[3] = {l1_ch,l1_value,SHARP};   
  
    if (before_l1 != PS3.getAnalogButton(L1)) {
      before_l1 = PS3.getAnalogButton(L1);
      if(PS3.getAnalogButton(L1) > 0){
        l1_value = PS3.getAnalogButton(L1);
        l1_button[1] = l1_value;     
      }else{
        l1_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, l1_button);              
    }    
}

void Right1(){
  static int before_r1 = 0;
  int r1_value = 0;

  unsigned char r1_button[3] = {r1_ch,r1_value,SHARP};   

    if (before_r1 != PS3.getAnalogButton(R1)) {
      before_r1 = PS3.getAnalogButton(R1);
      if(PS3.getAnalogButton(R1) > 0){
        r1_value = PS3.getAnalogButton(R1);
        r1_button[1] = r1_value;
      }else{
        r1_value = 0;
      }   
        CAN0.sendMsgBuf(ID, 0, 3, r1_button);
    }
}

//L2,R2
void Left2(){
  static int before_l2 = 0;
  int l2_value = 0;
  
  unsigned char l2_button[3] = {l2_ch,l2_value,SHARP};   
  
    if (before_l2 != PS3.getAnalogButton(L2)) {
     before_l2 = PS3.getAnalogButton(L2);
     if (PS3.getAnalogButton(L2) > 0){
       l2_value = PS3.getAnalogButton(L2);
       l2_button[1] = l2_value;
     }else{
       l2_value = 0;
     }
       CAN0.sendMsgBuf(ID, 0, 3, l2_button);
    }
}

void Right2(){
  static int before_r2 = 0;  
  int r2_value = 0;
  
  unsigned char r2_button[3] = {r2_ch,r2_value,SHARP};   
  
    if (before_r2 != PS3.getAnalogButton(R2)) {
     before_r2 = PS3.getAnalogButton(R2);
     if (PS3.getAnalogButton(R2) > 0){
       r2_value = PS3.getAnalogButton(R2);
       r2_button[1] = r2_value;
     }else{
       r2_value = 0;
     }
       CAN0.sendMsgBuf(ID, 0, 3, r2_button);              
    } 
}

void Select(){
  static int before_select = 0;
  int select_value = 0;
  
  unsigned char select_button[3] = {select_ch,select_value,SHARP};   
  
    if (before_select != PS3.getButtonPress(SELECT)) {
      before_select = PS3.getButtonPress(SELECT);
      if(PS3.getButtonPress(SELECT) > 0){  
        select_value = 1;
        select_button[1] = select_value;     
      }else{
        select_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, select_button);
    }
}

void Start(){
  static int before_start = 0;
  int start_value = 0;
  
  unsigned char start_button[3] = {start_ch,start_value,SHARP};   
  
    if (before_start != PS3.getButtonPress(START)) {
      before_start = PS3.getButtonPress(START);
      if(PS3.getButtonPress(START)){
        start_value = 1;
        start_button[1] = start_value;
      }else{
        start_value = 0;
      }
        CAN0.sendMsgBuf(ID, 0, 3, start_button);
    }
}

void pitch(){
  int pitch_value = 0;
  
  unsigned char pitch_angle[3] = {pitch_ch,pitch_value,SHARP};

  pitch_value = PS3.getAngle(Pitch);     
  pitch_angle[1] = pitch_value;
     
  CAN0.sendMsgBuf(ID, 0, 3, pitch_angle);  
}

void roll(){
  int roll_value = 0;
  
  unsigned char roll_angle[3] = {roll_ch,roll_value,SHARP};

  roll_value = PS3.getAngle(Roll);     
  roll_angle[1] = roll_value;
     
  CAN0.sendMsgBuf(ID, 0, 3, roll_angle);  
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
    Left_x();
    Left_y();
    Right_x();
    Right_y();
    Up();
    Right();
    Down();
    Left();
    Triangle();
    Circle();
    Cross();
    Square();
    Left1();
    Right1();
    Left2();
    Right2();
    Select();
    Start();
    pitch();
    roll();
  if (PS3.getButtonPress(PS)) {
      PS3.disconnect();
      PS3.setLedOff();
  }
    digitalWrite(13,HIGH);
  }else {
    digitalWrite(13,LOW);
  }
}
