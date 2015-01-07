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

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

unsigned char send_value[8] = {0};

MCP_CAN CAN0(4);                            // Set CS 

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
        roll_ch
}Mnemonic;

//左スティックx
void Left_x(unsigned char* data_value){
    static int before_left_x = 0;
    int left_x_value = 0;
    
    if (before_left_x != PS3.getAnalogHat(LeftHatX)) {
      before_left_x = PS3.getAnalogHat(LeftHatX);
      if (PS3.getAnalogHat(LeftHatX) > 0){
        left_x_value = PS3.getAnalogHat(LeftHatX);
      }else{
        left_x_value = 0;
      }
        data_value[1] = left_x_value;
    }    
}

//左スティックy
void Left_y(unsigned char* data_value){
    static int before_left_y = 0;
    int left_y_value = 0;
    
    if(before_left_y != PS3.getAnalogHat(LeftHatY)) {
      before_left_y = PS3.getAnalogHat(LeftHatY);
      if(PS3.getAnalogHat(LeftHatY) > 0){
        left_y_value = PS3.getAnalogHat(LeftHatY);
        //Serial.print(PS3.getAnalogHat(LeftHatY));
        //Serial.print("\n");
      }else{
        left_y_value = 0;
        //Serial.print("0\n");
      }
        data_value[1] = left_y_value;
    }    
}

//右スティックx
void Right_x(unsigned char* data_value){
    static int before_right_x = 0;
    int right_x_value = 0;
  
    if (before_right_x != PS3.getAnalogHat(RightHatX)) {
      before_right_x = PS3.getAnalogHat(RightHatX);
      if(PS3.getAnalogHat(RightHatX) > 0){
        right_x_value = PS3.getAnalogHat(RightHatX);
//        Serial.print(PS3.getAnalogHat(RightHatX));
//        Serial.print("\n");
      }else{
        right_x_value = 0;
      }
        data_value[1] = right_x_value;
    }
}

//右スティックy
void Right_y(unsigned char* data_value){
    static int before_right_y = 0;
    int right_y_value = 0;
    
    if(before_right_y != PS3.getAnalogHat(RightHatY)){
      before_right_y = PS3.getAnalogHat(RightHatY);
      if(PS3.getAnalogHat(RightHatY) > 0){
        right_y_value = PS3.getAnalogHat(RightHatY);
      }else{
        right_y_value = 0;
      }
        data_value[1] = right_y_value;
    }
}

void Up(unsigned char* data_value){
  static int before_up = 0;
  int up_value = 0;
  
    if (before_up != PS3.getAnalogButton(UP)) {
      before_up = PS3.getAnalogButton(UP);
      if(PS3.getAnalogButton(UP) > 0){
        up_value = PS3.getAnalogButton(UP);
      }else{
        up_value = 0;
      }
        data_value[1] = up_value;     
    }
}

void Right(unsigned char* data_value){
  static int before_right = 0;
  int right_value = 0;
  
    if (before_right != PS3.getAnalogButton(RIGHT)) {
      before_right = PS3.getAnalogButton(RIGHT);
      if(PS3.getAnalogButton(RIGHT) > 0){
        right_value = PS3.getAnalogButton(RIGHT);
      }else{
        right_value = 0;
      }
        data_value[1] = right_value;     
    }
}

void Down(unsigned char* data_value){
  static int before_down = 0;
  int down_value = 0;
  
    if (before_down != PS3.getAnalogButton(DOWN)) {
      before_down = PS3.getAnalogButton(DOWN);
      if(PS3.getAnalogButton(DOWN) > 0){
        down_value = PS3.getAnalogButton(DOWN);
      }else{
        down_value = 0;
      }
        data_value[1] = down_value;
    }     
}

void Left(unsigned char* data_value){
  static int before_left = 0;
  int left_value = 0;
  
    if (before_left != PS3.getAnalogButton(LEFT)) {
      before_left = PS3.getAnalogButton(LEFT);
      if(PS3.getAnalogButton(LEFT) > 0){
        left_value = PS3.getAnalogButton(LEFT);
      }else{
        left_value = 0;
      }
        data_value[1] = left_value;     
    }
}

void Triangle(unsigned char* data_value){
  static int before_triangle = 0;
  int triangle_value = 0;
  
    if (before_triangle != PS3.getAnalogButton(TRIANGLE)){
      before_triangle = PS3.getAnalogButton(TRIANGLE);
      if(PS3.getAnalogButton(TRIANGLE) > 0){
        triangle_value = PS3.getAnalogButton(TRIANGLE);
      }else{
        triangle_value = 0;
      }
        data_value[1] = triangle_value;    
    }
}

void Circle(unsigned char* data_value){
  static int before_circle = 0;
  int circle_value = 0;
  
    if (before_circle != PS3.getAnalogButton(CIRCLE)){
      before_circle = PS3.getAnalogButton(CIRCLE);
      if(PS3.getAnalogButton(CIRCLE) > 0){
        circle_value = PS3.getAnalogButton(CIRCLE);
      }else{
        circle_value = 0;
      }
        data_value[1] = circle_value;     
    }
}

void Cross(unsigned char* data_value){
  static int before_cross = 0;
  int cross_value = 0;
  
    if (before_cross != PS3.getAnalogButton(CROSS)){
      before_cross = PS3.getAnalogButton(CROSS);
      if(PS3.getAnalogButton(CROSS) > 0){
        cross_value = PS3.getAnalogButton(CROSS);
      }else{
        cross_value = 0;
      }
        data_value[1] = cross_value;     
    }
}

void Square(unsigned char* data_value){
  static int before_square = 0;
  int square_value = 0;
  
    if (before_square != PS3.getAnalogButton(SQUARE)){
      before_square = PS3.getAnalogButton(SQUARE);
      if(PS3.getAnalogButton(SQUARE) > 0){
        square_value = PS3.getAnalogButton(SQUARE);
      }else{
        square_value = 0;
      }
        data_value[1] = square_value;     
    }
}

//L1,R1
void Left1(unsigned char* data_value){
  static int before_l1 = 0;  
  int l1_value = 0;
  
    if (before_l1 != PS3.getAnalogButton(L1)) {
      before_l1 = PS3.getAnalogButton(L1);
      if(PS3.getAnalogButton(L1) > 0){
        l1_value = PS3.getAnalogButton(L1);
      }else{
        l1_value = 0;
      }
        data_value[1] = l1_value;     
    }    
}

void Right1(unsigned char* data_value){
  static int before_r1 = 0;
  int r1_value = 0;

    if (before_r1 != PS3.getAnalogButton(R1)) {
      before_r1 = PS3.getAnalogButton(R1);
      if(PS3.getAnalogButton(R1) > 0){
        r1_value = PS3.getAnalogButton(R1);
      }else{
        r1_value = 0;
      }   
        data_value[1] = r1_value;
    }
}

//L2,R2
void Left2(unsigned char* data_value){
  static int before_l2 = 0;
  int l2_value = 0;
  
    if (before_l2 != PS3.getAnalogButton(L2)) {
     before_l2 = PS3.getAnalogButton(L2);
     if (PS3.getAnalogButton(L2) > 0){
       l2_value = PS3.getAnalogButton(L2);
     }else{
       l2_value = 0;
     }
       data_value[1] = l2_value;
    }
}

void Right2(unsigned char* data_value){
  static int before_r2 = 0;  
  int r2_value = 0;
  
    if (before_r2 != PS3.getAnalogButton(R2)) {
     before_r2 = PS3.getAnalogButton(R2);
     if (PS3.getAnalogButton(R2) > 0){
       r2_value = PS3.getAnalogButton(R2);
     }else{
       r2_value = 0;
     }
       data_value[1] = r2_value;
    } 
}

void Select(unsigned char* data_value){
  static int before_select = 0;
  int select_value = 0;
  
    if (before_select != PS3.getButtonPress(SELECT)) {
      before_select = PS3.getButtonPress(SELECT);
      if(PS3.getButtonPress(SELECT) > 0){  
        select_value = 1;
      }else{
        select_value = 0;
      }
        data_value[1] = select_value;     
    }
}

void Start(unsigned char* data_value){
  static int before_start = 0;
  int start_value = 0;
    
    if (before_start != PS3.getButtonPress(START)) {
      before_start = PS3.getButtonPress(START);
      if(PS3.getButtonPress(START)){
        start_value = 1;
      }else{
        start_value = 0;
      }
        data_value[1] = start_value;
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
  pinMode(2, INPUT);                            // Setting pin 2 for /INT input
//  CAN0.init_Filt(0,0,0x0111);
//  CAN0.init_Filt(2,0,0x0112);

  digitalWrite(13,LOW);
}

void loop() {
  Usb.Task();
  
  int x = 0;
  int y = 0;

  unsigned char data_value[3] = {0};
  unsigned char send_data[8] = {0};
  
  data_value[2] = SHARP;
  
  if (PS3.PS3Connected) {
    if(!digitalRead(2))                         // If pin 2 is low, read receive buffer
    {
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      Serial.print("ID: ");
      Serial.print(rxId, HEX);
      Serial.print("  Data: ");
      for(int i = 0; i<len; i++)                // Print each byte of the data
      {
        switch (rxBuf[i]){
                case start_ch:     Start(data_value);     data_value[0] = start_ch;     break; 
        	case select_ch:    Select(data_value);    data_value[0] = select_ch;    break;
        	case left_x_ch:    Left_x(data_value);    data_value[0] = left_x_ch;    break;
        	case left_y_ch:    Left_y(data_value);    data_value[0] = left_y_ch;    break;
        	case right_x_ch:   Right_x(data_value);   data_value[0] = right_x_ch;   break;
        	case right_y_ch:   Right_y(data_value);   data_value[0] = right_y_ch;   break;
        	case l1_ch:        Left1(data_value);     data_value[0] = l1_ch;        break;
                case l2_ch:        Left2(data_value);     data_value[0] = l2_ch;        break;
        	case r1_ch:        Right1(data_value);    data_value[0] = r1_ch;        break;
                case r2_ch:        Right2(data_value);    data_value[0] = r2_ch;        break;
        	case triangle_ch:  Triangle(data_value);  data_value[0] = triangle_ch;  break;
        	case circle_ch:    Circle(data_value);    data_value[0] = circle_ch;    break;
        	case cross_ch:     Cross(data_value);     data_value[0] = cross_ch;     break;
        	case square_ch:    Square(data_value);    data_value[0] = square_ch;    break;
        	case up_ch:        Up(data_value);        data_value[0] = up_ch;        break;
        	case down_ch:      Down(data_value);      data_value[0] = down_ch;      break;
        	case right_ch:     Right(data_value);     data_value[0] = right_ch;     break;
        	case left_ch:      Left(data_value);      data_value[0] = left_ch;      break;        
        }
//              pitch();
//              roll();
        for(x=0; x>=2; x++){
          send_data[y] = data_value[x];
          y++;
          if(y >= 7){
            y = 0;
            CAN0.sendMsgBuf(ID, 0, 8, send_data);
          }
        }
        
      }
    if (PS3.getButtonPress(PS)) {
        PS3.disconnect();
        PS3.setLedOff();
    }
    digitalWrite(13,HIGH);
  }else {
    digitalWrite(13,LOW);
  }
  }
}
