#include <mcp_can.h>
#include <SPI.h>
#include <PS3BT.h>
#include <usbhub.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#define ID 0x003
#define Serial_PC 0

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

unsigned long printTime = 0;

MCP_CAN CAN0(4);                            // Set CS 

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];                    //受け取った値を格納する配列

int x = 0;
int y = 0;
int flag = 0;
int Send_Flag = 0;
unsigned char store_data[8][5] = {0};          //読み取った値を一時的に保管する配列。2バイトづつ格納する
unsigned char send_data[8] = {0};              //値を送るための配列。最大8バイト送れる

//どの値を読み取ったかを識別する記号。上から(a,b,c...)と続いている
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

/******************************************************************************
*	タイトル ： 読み取った値を格納する
*	  関数名 ： Send_data
*	   引数1 ： unsigned char*型 data_value  コントローラの値
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Send_data(unsigned char* data_value){
    flag = 1;                                 //値が格納されたらフラグを立てる
    for(int u = 0; u < 2; u++){
      store_data[x][y] = data_value[u];       //2バイトづつ格納する
      x++;      
      if(x >= 8){                             //x(一列)は最大8バイトなので
        x = 0;                                //0～7まで全て埋まったらxの値をリセット
        y++;                                  //次の行に進める
      }
    }
}

/******************************************************************************
*	タイトル ： STARTボタンの値
*	  関数名 ： Start
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Start(){
  static unsigned char before_start = 0;
  unsigned char start_value[2] = {start_ch,0};       //{値の識別記号、読み取った値}の順で格納する
        
    start_value[1] = PS3.getButtonPress(START);      //コントローラの値を読み取る
    
    if (before_start != start_value[1] || Send_Flag == 1) {            //前回読み取った値と違うかフラグが立ったら値を送る
      before_start = start_value[1];
      if(start_value[1] <= 0){                       //ボタンを何も押していない場合、0を送信する
        start_value[1] = 0;
      }
        Send_data(start_value);                      //値を格納する関数に飛ぶ
        if(Serial_PC == 1){
          Serial.print("  start:");
          Serial.print(start_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： SELECTボタンの値
*	  関数名 ： Select
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Select(){
  static unsigned char before_select = 0;
  unsigned char select_value[2] = {select_ch,0};
  
    select_value[1] = PS3.getButtonPress(SELECT);
    
    if (before_select != select_value[1] || Send_Flag == 1) {
      before_select = select_value[1];
      if(select_value[1] <= 0){  
        select_value[1] = 0;
      }
        Send_data(select_value);
        if(Serial_PC == 1){
          Serial.print("  select:");
          Serial.print(select_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： 左スティックの値(x軸、y軸に分かれている)
*	  関数名 ： Left_x,Left_y
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Left_x(){
    static unsigned char before_left_x = 0;
    unsigned char left_x_value[2] = {left_x_ch,0};

    left_x_value[1] = PS3.getAnalogHat(LeftHatX);
        
    if (before_left_x != left_x_value[1] || Send_Flag == 1) {
      before_left_x = left_x_value[1];
      if (left_x_value[1] <= 0){
        left_x_value[1] = 0;
      }
        Send_data(left_x_value);
    }
        if(Serial_PC == 1){
          Serial.print("  left_x:");
          Serial.print(left_x_value[1]);
          //Serial.print("\n");
        }    
}

void Left_y(){
    static unsigned char before_left_y = 0;
    unsigned char left_y_value[2] = {left_y_ch,0};

    left_y_value[1] = PS3.getAnalogHat(LeftHatY);
        
    if(before_left_y != left_y_value[1] || Send_Flag == 1) {
      before_left_y = left_y_value[1];
      if(left_y_value[1] <= 0){
        left_y_value[1] = 0;
      }
        Send_data(left_y_value);
    }    
        if(Serial_PC == 1){
          Serial.print("  left_y:");
          Serial.print(left_y_value[1]);
          //Serial.print("\n");
        }
}

/******************************************************************************
*	タイトル ： 右スティックの値(x軸、y軸に分かれている)
*	  関数名 ： Right_x,Right_ｙ
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Right_x(){
    static unsigned char before_right_x = 0;
    unsigned char right_x_value[2] = {right_x_ch,0};
  
    right_x_value[1] = PS3.getAnalogHat(RightHatX);
    
    if (before_right_x != right_x_value[1] || Send_Flag == 1) {
      before_right_x = right_x_value[1];
      if(right_x_value[1] <= 0){
        right_x_value[1] = 0;
      }
        Send_data(right_x_value);
    }
        if(Serial_PC == 1){
          Serial.print("  right_x:");
          Serial.print(right_x_value[1]);
        }
}

void Right_y(){
    static unsigned char before_right_y = 0;
    unsigned char right_y_value[2] = {right_y_ch,0};
    
    right_y_value[1] = PS3.getAnalogHat(RightHatY);
    
    if(before_right_y != right_y_value[1] || Send_Flag == 1){
      before_right_y = right_y_value[1];
      if(right_y_value[1] <= 0){
        right_y_value[1] = 0;
      }
        Send_data(right_y_value);
    }
        if(Serial_PC == 1){
          Serial.print("  right_y:");
          Serial.print(right_y_value[1]);
          Serial.print("\n");
        }
}

/******************************************************************************
*	タイトル ： L1の値
*	  関数名 ： Left1
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Left1(){
  static unsigned char before_l1 = 0;
  unsigned char l1_value[2] = {l1_ch,0};
  
    l1_value[1] = PS3.getAnalogButton(L1);
                          
    if (before_l1 != l1_value[1] || Send_Flag == 1) {
      before_l1 = l1_value[1];
      if(l1_value[1] <= 0){
        l1_value[1] = 0;
      }
        Send_data(l1_value);
        if(Serial_PC == 1){
          Serial.print("  L1:");
          Serial.print(l1_value[1]);
        }
    }    
}

/******************************************************************************
*	タイトル ： L2の値
*	  関数名 ： Left2
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Left2(){
  static unsigned char before_l2 = 0;
  unsigned char l2_value[2] = {l2_ch,0};
  
    l2_value[1] = PS3.getAnalogButton(L2);
    
    if (before_l2 != l2_value[1] || Send_Flag == 1) {
     before_l2 = l2_value[1];
     if (l2_value[1] <= 0){
       l2_value[1] = 0;
     }
        Send_data(l2_value);
        if(Serial_PC == 1){
          Serial.print("  L2:");
          Serial.print(l2_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： R1の値
*	  関数名 ： Right1
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Right1(){
  static unsigned char before_r1 = 0;
  unsigned char r1_value[2] = {r1_ch,0};

    r1_value[1] = PS3.getAnalogButton(R1);
    
    if (before_r1 != r1_value[1] || Send_Flag == 1) {
      before_r1 = r1_value[1];
      if(r1_value[1] <= 0){
        r1_value[1] = 0;
      }   
        Send_data(r1_value);
        if(Serial_PC == 1){
          Serial.print("  R1:");
          Serial.print(r1_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： R2の値
*	  関数名 ： Right2
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
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
        if(Serial_PC == 1){
          Serial.print("  R2:");
          Serial.print(r2_value[1]);
          Serial.print("\n");
        }
    } 
}

/******************************************************************************
*	タイトル ： △ボタンの値
*	  関数名 ： Triangle
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Triangle(){
  static unsigned char before_triangle = 0;
  unsigned char triangle_value[2] = {triangle_ch,0};
  
    triangle_value[1] = PS3.getAnalogButton(TRIANGLE);

    if (before_triangle != triangle_value[1] || Send_Flag == 1){
      before_triangle = triangle_value[1];
      if(triangle_value[1] <= 0){
        triangle_value[1] = 0;
      }
        Send_data(triangle_value);
        if(Serial_PC == 1){
          Serial.print("  triangle:");
          Serial.print(triangle_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： ○ボタンの値
*	  関数名 ： Circle
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Circle(){
  static unsigned char before_circle = 0;
  unsigned char circle_value[2] = {circle_ch,0};
  
    circle_value[1] = PS3.getAnalogButton(CIRCLE);
    
    if (before_circle != circle_value[1] || Send_Flag == 1){
      before_circle = circle_value[1];
      if(circle_value[1] <= 0){
        circle_value[1] = 0;
      }
        Send_data(circle_value);
        if(Serial_PC == 1){
          Serial.print("  circle:");
          Serial.print(circle_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： ×ボタンの値
*	  関数名 ： Cross
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Cross(){
  static unsigned char before_cross = 0;
  unsigned char cross_value[2] = {cross_ch,0};
  
    cross_value[1] = PS3.getAnalogButton(CROSS);
    
    if (before_cross != cross_value[1] || Send_Flag == 1){
      before_cross = cross_value[1];
      if(cross_value[1] <= 0){
        cross_value[1] = 0;
      }
        Send_data(cross_value);
        if(Serial_PC == 1){
          Serial.print("  cross:");
          Serial.print(cross_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： □ボタンの値
*	  関数名 ： Square
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Square(){
  static unsigned char before_square = 0;
  unsigned char square_value[2] = {square_ch,0};
  
    square_value[1] = PS3.getAnalogButton(SQUARE);
    
    if (before_square != square_value[1] || Send_Flag == 1){
      before_square = square_value[1];
      if(square_value[1] <= 0){
        square_value[1] = 0;
      }
        Send_data(square_value);
        if(Serial_PC == 1){
          Serial.print("  square:");
          Serial.print(square_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： 上ボタンの値
*	  関数名 ： Up
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Up(){
  static unsigned char before_up = 0;
  unsigned char up_value[2] = {up_ch,0};
  
    up_value[1] = PS3.getAnalogButton(UP);
    
    if (before_up != up_value[1] || Send_Flag == 1) {
      before_up = up_value[1];
      if(up_value[1] <= 0){
        up_value[1] = 0;
//        Serial.print(up_value[1]);
      }
        Send_data(up_value);
        if(Serial_PC == 1){
          Serial.print("  up:");
          Serial.print(up_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： 下ボタンの値
*	  関数名 ： Down
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Down(){
  static unsigned char before_down = 0;
  unsigned char down_value[2] = {down_ch,0};
  
    down_value[1] = PS3.getAnalogButton(DOWN);
    
    if (before_down != down_value[1] || Send_Flag == 1) {
      before_down = down_value[1];
      if(down_value[1] <= 0){
        down_value[1] = 0;
//        Serial.print(down_value[1]);
      }
        Send_data(down_value);
        if(Serial_PC == 1){
          Serial.print("  down:");
          Serial.print(down_value[1]);
        }
    }     
}

/******************************************************************************
*	タイトル ： 右ボタンの値
*	  関数名 ： Right
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Right(){
  static unsigned char before_right = 0;
  unsigned char right_value[2] = {right_ch,0};
  
    right_value[1] = PS3.getAnalogButton(RIGHT);
    
    if (before_right != right_value[1] || Send_Flag == 1) {
      before_right = right_value[1];
      if(right_value[1] <= 0){
        right_value[1] = 0;
//        Serial.print(right_value[1]); 
      }
        Send_data(right_value);
        if(Serial_PC == 1){
          Serial.print("  right:");
          Serial.print(right_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： 左ボタンの値
*	  関数名 ： Left
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void Left(){
  static unsigned char before_left = 0;
  unsigned char left_value[2] = {left_ch,0};
  
    left_value[1] = PS3.getAnalogButton(LEFT);
    
    if (before_left != left_value[1] || Send_Flag == 1) {
      before_left = left_value[1];
      if(left_value[1] <= 0){
        left_value[1] = 0;
//        Serial.print(left_value[1]);
      }
        Send_data(left_value);
        if(Serial_PC == 1){
          Serial.print("  left:");
          Serial.print(left_value[1]);
        }
    }
}

/******************************************************************************
*	タイトル ： コントローラの傾き(ピッチ)の値
*	  関数名 ： pitch
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void pitch(){
  static unsigned char before_pitch = 0;
  unsigned char pitch_value[2] = {pitch_ch,0};
  
  pitch_value[1] = PS3.getAngle(Pitch);
    
    if (before_pitch != pitch_value[1] || Send_Flag == 1) {
      before_pitch = pitch_value[1];
      Send_data(pitch_value);
    }
}

/******************************************************************************
*	タイトル ： コントローラの傾き(roll )の値
*	  関数名 ： roll
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void roll(){
  static unsigned char before_roll = 0;
  unsigned char roll_value[2] = {roll_ch,0};
  
  roll_value[1] = PS3.getAngle(Roll);     
    
    if (before_roll != roll_value[1] || Send_Flag == 1) {
      before_roll = roll_value[1];
      Send_data(roll_value);
    }
}

/******************************************************************************
*	タイトル ： エラー検知
*	  関数名 ： get_error
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2015/01/14
******************************************************************************/
void get_error(){

  unsigned char error[2] = {CError,0}; 
  
  if(CAN0.checkError() == CAN_CTRLERROR){
    error[1] = 1;
    Send_data(error);
  }
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
  
  Send_Flag = 0;
  if(millis()-printTime>300){
    printTime = millis();
    Send_Flag = 1;
  }
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
    pitch();
    roll();
//    get_error();
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
  if(flag == 1){                          //フラグが立ったら値を送る
    flag = 0;
    for(int v = 0; v <= y; v++){
      if(v < y){
        for(int s = 0; s <= 7; s++){
          send_data[s] = store_data[s][v];
          //Serial.print(s);
        }
        //Serial.print("\n");
        CAN0.sendMsgBuf(ID, 0, 8, send_data);
      }else if(v >= y){
        for(int s = 0; s < x; s++){
          send_data[s] = store_data[s][v];
          //Serial.print(s);
        }
        //Serial.print("\n");
        CAN0.sendMsgBuf(ID, 0, x, send_data);
        //Serial.print(send_data[1]);
      }
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
