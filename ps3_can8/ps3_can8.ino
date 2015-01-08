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

int x = 0;
int y = 0;
int i = 0;
int point = 0;
unsigned char store_data[8][3] = {0};
unsigned char send_data[8] = {0};

enum {
	start_ch = 'a',
	select_ch,
	left_x_ch,
	left_y_ch,
	right_x_ch,
	right_y_ch,
	l1_ch,l2_ch,
	r1_ch,r2_ch,
	triangle_ch,
	circle_ch,
	cross_ch,
	square_ch,
	up_ch,
	down_ch,
	right_ch,
	left_ch,
        pitch_ch,
        roll_ch,
        CError
}Mnemonic;

void Send_data(unsigned char data_value){
  point = 1;
    store_data[x][y] = data_value;
    x++;
    if(x >= 7){
      x = 0;
      y++;
    }
}

void Start(){
  static int before_start = 0;
  int now_start = 0;
  unsigned char start_value = 0;
    
    now_start = PS3.getButtonPress(START);
    
    if (before_start != now_start) {    //PS3.getButtonPress(START)変数宣言
      before_start = now_start;
      if(now_start > 0){
        start_value = 1;
      }else{
        start_value = 0;
      }
        Send_data(start_value);
    }
}

void Select(){
  static int before_select = 0;
  int now_select = 0;
  unsigned char select_value = 0;
  
  
    now_select = PS3.getButtonPress(SELECT);
    
    if (before_select != now_select) {
      before_select = now_select;
      if(now_select > 0){  
        select_value = 1;
      }else{
        select_value = 0;
      }
        Send_data(select_value);
    }
}

//左スティックx
void Left_x(){
    static int before_left_x = 0;
    int now_left_x = 0;
    unsigned char left_x_value = 0;
    
    now_left_x = PS3.getAnalogHat(LeftHatX);
    
    if (before_left_x != now_left_x) {
      before_left_x = now_left_x;
      if (now_left_x > 0){
        left_x_value = now_left_x;
      }else{
        left_x_value = 0;
      }
        Send_data(left_x_value);
    }    
}

//左スティックy
void Left_y(){
    static int before_left_y = 0;
    int now_left_y = 0;
    unsigned char left_y_value = 0;
    
    now_left_y = PS3.getAnalogHat(LeftHatY);
    
    if(before_left_y != now_left_y) {
      before_left_y = now_left_y;
      if(now_left_y > 0){
        left_y_value = now_left_y;
        //Serial.print(PS3.getAnalogHat(LeftHatY));
        //Serial.print("\n");
      }else{
        left_y_value = 0;
        //Serial.print("0\n");
      }
        Send_data(left_y_value);
    }    
}

//右スティックx
void Right_x(){
    static int before_right_x = 0;
    int now_right_x = 0;
    unsigned char right_x_value = 0;
  
    now_right_x = PS3.getAnalogHat(RightHatX);
    
    if (before_right_x != now_right_x) {
      before_right_x = now_right_x;
      if(now_right_x > 0){
        right_x_value = now_right_x;
//        Serial.print(PS3.getAnalogHat(RightHatX));
//        Serial.print("\n");
      }else{
        right_x_value = 0;
      }
        Send_data(right_x_value);
    }
}

//右スティックy
void Right_y(){
    static int before_right_y = 0;
    int now_right_y = 0;
    unsigned char right_y_value = 0;
    
    now_right_y = PS3.getAnalogHat(RightHatY);
    
    if(before_right_y != now_right_y){
      before_right_y = now_right_y;
      if(now_right_y > 0){
        right_y_value = now_right_y;
      }else{
        right_y_value = 0;
      }
        Send_data(right_y_value);
    }
}

void Left1(){
  static int before_l1 = 0;
  int now_l1 = 0;
  unsigned char l1_value = 0;
  
    now_l1 = PS3.getAnalogButton(L1);
    
    if (before_l1 != now_l1) {
      before_l1 = now_l1;
      if(now_l1 > 0){
        l1_value = now_l1;
      }else{
        l1_value = 0;
      }
        Send_data(l1_value);
    }    
}

void Left2(){
  static int before_l2 = 0;
  int now_l2 = 0;
  unsigned char l2_value = 0;
  
    now_l2 = PS3.getAnalogButton(L2);
    
    if (before_l2 != now_l2) {
     before_l2 = now_l2;
     if (now_l2 > 0){
       l2_value = now_l2;
     }else{
       l2_value = 0;
     }
        Send_data(l2_value);
    }
}

void Right1(){
  static int before_r1 = 0;
  int now_r1 = 0;
  unsigned char r1_value = 0;

    now_r1 = PS3.getAnalogButton(R1);
    
    if (before_r1 != now_r1) {
      before_r1 = now_r1;
      if(now_r1 > 0){
        r1_value = now_r1;
      }else{
        r1_value = 0;
      }   
        Send_data(r1_value);
    }
}

void Right2(){
  static int before_r2 = 0;
  int now_r2 = 0;  
  unsigned char r2_value = 0;
  
    now_r2 = PS3.getAnalogButton(R2);
    
    if (before_r2 != now_r2) {
     before_r2 = now_r2;
     if (now_r2 > 0){
       r2_value = now_r2;
     }else{
       r2_value = 0;
     }
        Send_data(r2_value);
    } 
}

void Triangle(){
  static int before_triangle = 0;
  int now_triangle = 0;
  unsigned char triangle_value = 0;
  
    now_triangle = PS3.getAnalogButton(TRIANGLE);
    if (before_triangle != now_triangle){
      before_triangle = now_triangle;
      if(now_triangle > 0){
        triangle_value = now_triangle;
      }else{
        triangle_value = 0;
      }
        Send_data(triangle_value);
    }
}

void Circle(){
  static int before_circle = 0;
  int now_circle = 0;
  unsigned char circle_value = 0;
  
    now_circle = PS3.getAnalogButton(CIRCLE);
    
    if (before_circle != now_circle){
      before_circle = now_circle;
      if(now_circle > 0){
        circle_value = now_circle;
      }else{
        circle_value = 0;
      }
        Send_data(circle_value);
    }
}

void Cross(){
  static int before_cross = 0;
  int now_cross = 0;
  unsigned char cross_value = 0;
  
    now_cross = PS3.getAnalogButton(CROSS);
    
    if (before_cross != now_cross){
      before_cross = now_cross;
      if(now_cross > 0){
        cross_value = now_cross;
      }else{
        cross_value = 0;
      }
        Send_data(cross_value);
    }
}

void Square(){
  static int before_square = 0;
  int now_square = 0;
  unsigned char square_value = 0;
  
    now_square = PS3.getAnalogButton(SQUARE);
    
    if (before_square != now_square){
      before_square = now_square;
      if(now_square > 0){
        square_value = now_square;
      }else{
        square_value = 0;
      }
        Send_data(square_value);
    }
}

void Up(){
  static int before_up = 0;
  int now_up = 0;
  unsigned char up_value = 0;
  
    now_up = PS3.getAnalogButton(UP);
    
    if (before_up != now_up) {
      before_up = now_up;
      if(now_up > 0){
        up_value = now_up;
      }else{
        up_value = 0;
      }
        Send_data(up_value);
    }
}

void Down(){
  static int before_down = 0;
  int now_down = 0;
  unsigned char down_value = 0;
  
    now_down = PS3.getAnalogButton(DOWN);
    
    if (before_down != now_down) {
      before_down = now_down;
      if(now_down > 0){
        down_value = now_down;
      }else{
        down_value = 0;
      }
        Send_data(down_value);
    }     
}

void Right(){
  static int before_right = 0;
  int now_right = 0;
  unsigned char right_value = 0;
  
    now_right = PS3.getAnalogButton(RIGHT);
    
    if (before_right != now_right) {
      before_right = now_right;
      if(now_right > 0){
        right_value = now_right;
      }else{
        right_value = 0;
      }
        Send_data(right_value);
    }
}

void Left(){
  static int before_left = 0;
  int now_left = 0;
  unsigned char left_value = 0;
  
    now_left = PS3.getAnalogButton(LEFT);
    
    if (before_left != now_left) {
      before_left = now_left;
      if(now_left > 0){
        left_value = now_left;
      }else{
        left_value = 0;
      }
        Send_data(left_value);
    }
}

void pitch(){
  unsigned char pitch_value = 0;

  pitch_value = PS3.getAngle(Pitch);

  Send_data(pitch_value);
}

void roll(){
  unsigned char roll_value = 0;

  roll_value = PS3.getAngle(Roll);     
     
  Send_data(roll_value);
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

  digitalWrite(13,LOW);
}

void loop() {
  Usb.Task();
  if (PS3.PS3Connected) {
    Start();
    Select();
    Left_x();
    Left_y();
    Right_x();
    Right_y();
    Left1();
    Left2();
    Right1();
    Right2();
    Triangle();
    Circle();
    Cross();
    Square();
    Up();
    Down();
    Right();
    Left();
//    pitch();
//    roll();

  if(point == 1){
    for(i = 0; i <= y; i++){
      for(x = 0; x < 8; x++){
        send_data[x] = store_data[x][y];
      }
      CAN0.sendMsgBuf(ID, 0, 8, send_data);
    }
    x = 0, y = 0;
  }
  
  if (PS3.getButtonPress(PS)) {
      PS3.disconnect();
      PS3.setLedOff();
  }
    digitalWrite(13,HIGH);
  } else {
    digitalWrite(13,LOW);
  }
}
