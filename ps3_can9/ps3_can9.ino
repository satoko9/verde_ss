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

//#define SHARP '#'
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

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

int x = 0;
int y = 0;
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

void Send_data(unsigned char* data_value){
    point = 1;    
    for(int u = 0; u < 2; u++){
      store_data[u][y] = data_value[u];
    }
    if(x >= 7){
      x = 0;
      y++;
    }
}

void Start(){
  static unsigned char before_start = 0;
  unsigned char start_value[2] = {start_ch,0};
    
    start_value[1] = PS3.getButtonPress(START);
    
    if (before_start != start_value[1]) {
      before_start = start_value[1];
      if(start_value[1] <= 0){
        start_value[1] = 0;
      }
        Send_data(start_value);
    }
}

void Select(){
  static unsigned char before_select = 0;
  unsigned char select_value[2] = {select_ch,0};
  
    select_value[1] = PS3.getButtonPress(SELECT);
    
    if (before_select != select_value[1]) {
      before_select = select_value[1];
      if(select_value[1] <= 0){  
        select_value[1] = 0;
      }
        Send_data(select_value);
    }
}

//左スティックx
void Left_x(){
    static unsigned char before_left_x = 0;
    unsigned char left_x_value[2] = {left_x_ch,0};
    
    left_x_value[1] = PS3.getAnalogHat(LeftHatX);
    
    if (before_left_x != left_x_value[1]) {
      before_left_x = left_x_value[1];
      if (left_x_value[1] <= 0){
        left_x_value[1] = 0;
      }
        Send_data(left_x_value);
    }    
}

//左スティックy
void Left_y(){
    static unsigned char before_left_y = 0;
    unsigned char left_y_value[2] = {left_y_ch,0};
    
    left_y_value[1] = PS3.getAnalogHat(LeftHatY);
    
    if(before_left_y != left_y_value[1]) {
      before_left_y = left_y_value[1];
      if(left_y_value[1] <= 0){
        left_y_value[1] = 0;
      }
        Send_data(left_y_value);
    }    
}

//右スティックx
void Right_x(){
    static unsigned char before_right_x = 0;
    unsigned char right_x_value[2] = {right_x_ch,0};
  
    right_x_value[1] = PS3.getAnalogHat(RightHatX);
    
    if (before_right_x != right_x_value[1]) {
      before_right_x = right_x_value[1];
      if(right_x_value[1] <= 0){
        right_x_value[1] = 0;
      }
        Send_data(right_x_value);
    }
}

//右スティックy
void Right_y(){
    static unsigned char before_right_y = 0;
    unsigned char right_y_value[2] = {right_y_ch,0};
    
    right_y_value[1] = PS3.getAnalogHat(RightHatY);
    
    if(before_right_y != right_y_value[1]){
      before_right_y = right_y_value[1];
      if(right_y_value[1] <= 0){
        right_y_value[1] = 0;
      }
        Send_data(right_y_value);
    }
}

void Left1(){
  static unsigned char before_l1 = 0;
  unsigned char l1_value[2] = {l1_ch,0};
  
    l1_value[1] = PS3.getAnalogButton(L1);
    
    if (before_l1 != l1_value[1]) {
      before_l1 = l1_value[1];
      if(l1_value[1] <= 0){
        l1_value[1] = 0;
      }
        Send_data(l1_value);
    }    
}

void Left2(){
  static unsigned char before_l2 = 0;
  unsigned char l2_value[2] = {l2_ch,0};
  
    l2_value[1] = PS3.getAnalogButton(L2);
    
    if (before_l2 != l2_value[1]) {
     before_l2 = l2_value[1];
     if (l2_value[1] <= 0){
       l2_value[1] = 0;
     }
        Send_data(l2_value);
    }
}

void Right1(){
  static unsigned char before_r1 = 0;
  unsigned char r1_value[2] = {r1_ch,0};

    r1_value[1] = PS3.getAnalogButton(R1);
    
    if (before_r1 != r1_value[1]) {
      before_r1 = r1_value[1];
      if(r1_value[1] <= 0){
        r1_value[1] = 0;
      }   
        Send_data(r1_value);
    }
}

void Right2(){
  static unsigned char before_r2 = 0;
  unsigned char r2_value[2] = {r2_ch,0};
  
    r2_value[1] = PS3.getAnalogButton(R2);
    
    if (before_r2 != r2_value[1]) {
     before_r2 = r2_value[1];
     if (r2_value[1] <= 0){
       r2_value[1] = 0;
     }
        Send_data(r2_value);
    } 
}

void Triangle(){
  static unsigned char before_triangle = 0;
  unsigned char triangle_value[2] = {triangle_ch,0};
  
    triangle_value[1] = PS3.getAnalogButton(TRIANGLE);

    if (before_triangle != triangle_value[1]){
      before_triangle = triangle_value[1];
      if(triangle_value[1] <= 0){
        triangle_value[1] = 0;
      }
        Send_data(triangle_value);
    }
}

void Circle(){
  static unsigned char before_circle = 0;
  unsigned char circle_value[2] = {circle_ch,0};
  
    circle_value[1] = PS3.getAnalogButton(CIRCLE);
    
    if (before_circle != circle_value[1]){
      before_circle = circle_value[1];
      if(circle_value[1] <= 0){
        circle_value[1] = 0;
      }
        Send_data(circle_value);
    }
}

void Cross(){
  static unsigned char before_cross = 0;
  unsigned char cross_value[2] = {cross_ch,0};
  
    cross_value[1] = PS3.getAnalogButton(CROSS);
    
    if (before_cross != cross_value[1]){
      before_cross = cross_value[1];
      if(cross_value[1] <= 0){
        cross_value[1] = 0;
      }
        Send_data(cross_value);
    }
}

void Square(){
  static unsigned char before_square = 0;
  unsigned char square_value[2] = {square_ch,0};
  
    square_value[1] = PS3.getAnalogButton(SQUARE);
    
    if (before_square != square_value[1]){
      before_square = square_value[1];
      if(square_value[1] <= 0){
        square_value[1] = 0;
      }
        Send_data(square_value);
    }
}

void Up(){
  static unsigned char before_up = 0;
  unsigned char up_value[2] = {up_ch,0};
  
    up_value[1] = PS3.getAnalogButton(UP);
    
    if (before_up != up_value[1]) {
      before_up = up_value[1];
      if(up_value[1] <= 0){
        up_value[1] = 0;
      }
        Send_data(up_value);
    }
}

void Down(){
  static unsigned char before_down = 0;
  unsigned char down_value[2] = {down_ch,0};
  
    down_value[1] = PS3.getAnalogButton(DOWN);
    
    if (before_down != down_value[1]) {
      before_down = down_value[1];
      if(down_value[1] <= 0){
        down_value[1] = 0;
      }
        Send_data(down_value);
    }     
}

void Right(){
  static unsigned char before_right = 0;
  unsigned char right_value[2] = {right_ch,0};
  
    right_value[1] = PS3.getAnalogButton(RIGHT);
    
    if (before_right != right_value[1]) {
      before_right = right_value[1];
      if(right_value[1] <= 0){
        right_value[1] = 0;
      }
        Send_data(right_value);
    }
}

void Left(){
  static unsigned char before_left = 0;
  unsigned char left_value[2] = {left_ch,0};
  
    left_value[1] = PS3.getAnalogButton(LEFT);
    
    if (before_left != left_value[1]) {
      before_left = left_value[1];
      if(left_value[1] <= 0){
        left_value[1] = 0;
      }
        Send_data(left_value);
    }
}

void pitch(){
  static unsigned char before_pitch = 0;
  unsigned char pitch_value[2] = {pitch_ch,0};
  
  pitch_value[1] = PS3.getAngle(Pitch);
    
    if (before_pitch != pitch_value[1]) {
      before_pitch = pitch_value[1];
      Send_data(pitch_value);
    }
}

void roll(){
  static unsigned char before_roll = 0;
  unsigned char roll_value[2] = {roll_ch,0};
  
  roll_value[1] = PS3.getAngle(Roll);     
    
    if (before_roll != roll_value[1]) {
      before_roll = roll_value[1];
      Send_data(roll_value);
    }
}

/*void get_error(){

  if(CAN0.checkError() == CAN_CTRLERROR){
    Send_data(CError);
  }

}*/

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

  pinMode(2, INPUT);                            // Setting pin 2 for /INT input

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
/*    if(!digitalRead(2))                         // If pin 2 is low, read receive buffer
    {
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      Serial.print("ID: ");
      Serial.print(rxId, HEX);
      for(int i = 0; i<len; i++)                // Print each byte of the data
      {
        switch (rxBuf[i]){
          case start_ch:     Start();     break;
          case select_ch:    Select();    break;
          case left_x_ch:    Left_x();    break;
          case left_y_ch:    Left_y();    break;
          case right_x_ch:   Right_x();   break;
          case right_y_ch:   Right_y();   break;
          case l1_ch:        Left1();     break;
          case l2_ch:        Left2();     break;
          case r1_ch:        Right1();    break;
          case r2_ch:        Right2();    break;
          case triangle_ch:  Triangle();  break;
          case circle_ch:    Circle();    break;
          case cross_ch:     Cross();     break;
          case square_ch:    Square();    break;
          case up_ch:        Up();        break;
          case down_ch:      Down();      break;
          case right_ch:     Right();     break;
          case left_ch:      Left();      break;
          //case pitch_ch:     pitch();     break;
          //case roll_ch:      roll();      break;
          //case CError:       get_error();  break;
        }
      }
    }*/
  if(point == 1){
    for(int j = 0; j <= y; j++){
      if(j < y){
        for(int s = 0; s < 8; s++){
          send_data[s] = store_data[s][j];
        }
      }else if(j >= y){
        for(int s = 0; s <= x; s++){
          send_data[s] = store_data[s][j];
        }
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
