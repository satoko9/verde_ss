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
    static int before_x = 0;   
    static int before_y = 0;
    int left_x_value = 0;
    int left_y_value = 0;
    
    left_x_value = PS3.getAnalogHat(LeftHatX);
    
    if (before_x != left_x_value) {
      before_x = left_x_value;
      if (left_x_value > 0){
        Serial.write('a');
        Serial.print(left_x_value);
        Serial.write('#');
      }else{
        Serial.print("a0#");
      }
    }
    
    left_y_value = PS3.getAnalogHat(LeftHatY);
    
    if(before_y != left_y_value) {
      before_y = left_y_value;
      if(left_y_value > 0){
        Serial.write('A');
        Serial.print(left_y_value);
        Serial.write('#');
      }else{
        Serial.print("A0#");
      }
    }
      
}

//右スティック
void right_stick(){
    static int before_x = 0;
    static int before_y = 0;
    int right_x_value = 0;
    int right_y_value = 0;
  
    right_x_value = PS3.getAnalogHat(RightHatX);
    
    if (before_x != right_x_value) {
      before_x = right_x_value;
      if(right_x_value > 0){
        Serial.write('b');
        Serial.print(right_x_value);
        Serial.write('#');
      }else{
      Serial.print("b0#");
      }
    }
    
    right_y_value = PS3.getAnalogHat(RightHatY);
    
    if(before_y != right_y_value){
      before_y = right_y_value;
      if(right_y_value > 0){
        Serial.write('B');
        Serial.print(right_y_value);
        Serial.write('#');
      }else{
        Serial.print("B0#");
      }
    }
}

//L1,R1
void L1_R1(){
  static int before_l1 = 0;
  static int before_r1 = 0;
  int l1_value = 0;
  int r1_value = 0;
  
    l1_value = PS3.getAnalogButton(L1);
    
    if (before_l1 != l1_value) {
      before_l1 = l1_value;
      if(l1_value > 0){
        Serial.write('o');
        Serial.print(l1_value);
        Serial.write('#');
      }else{
        Serial.print("o0#");
      }
    }
    
    r1_value =  PS3.getAnalogButton(R1);
    
    if (before_r1 != r1_value) {
      before_r1 = r1_value;
      if(r1_value > 0){
        Serial.write('p');
        Serial.print(r1_value);
        Serial.write('#');
      }else{
        Serial.print("p0#");
      }   
    }   
}

//L2,R2
void L2_R2(){
  static int before_l2 = 0;
  static int before_r2 = 0;
  int l2_value = 0;
  int r2_value = 0;
  
    l2_value =  PS3.getAnalogButton(L2);
    
    if (before_l2 != l2_value) {
     before_l2 = l2_value;
     if (l2_value > 0){
       Serial.write('q');
       Serial.print(l2_value);
       Serial.write('#');
     }else{
       Serial.print("q0#");
    }
    }

    r2_value = PS3.getAnalogButton(R2);
    
    if (before_r2 != r2_value) {
     before_r2 = r2_value;
     if (r2_value > 0){
       Serial.write('r');
       Serial.print(r2_value);
       Serial.write('#');
     }else{
     Serial.print("r0#");
     }
    }    
}

void Triangle(){
  static int before_triangle = 0;
  int triangle_value = 0;
  
    triangle_value = PS3.getAnalogButton(TRIANGLE);
    
    if (before_triangle != triangle_value){
      before_triangle = triangle_value;
      if(triangle_value > 0){
        Serial.write('g');
        Serial.print(triangle_value);
        Serial.write('#');
      }else{
       Serial.print("g0#");
      }
    }
}

void Circle(){
  static int before_circle = 0;
  int circle_value = 0;
  
    circle_value = PS3.getAnalogButton(CIRCLE);
    
    if (before_circle != circle_value){
      before_circle = circle_value;
      if(circle_value > 0){
       Serial.write('h');
       Serial.print(circle_value);
       Serial.write('#');
      }else{
       Serial.print("h0#");
      }
    }
}

void Cross(){
  static int before_cross = 0;
  int cross_value = 0;
  
    cross_value = PS3.getAnalogButton(CROSS);
    
    if (before_cross != cross_value){
      before_cross = cross_value;
      if(cross_value > 0){
       Serial.write('i');
       Serial.print(cross_value);
       Serial.write('#');
      }else{
       Serial.print("i0#");
      }
    }
}

void Square(){
  static int before_square = 0;
  int sqare_value = 0;
  
    sqare_value = PS3.getAnalogButton(SQUARE);
    
    if (before_square != sqare_value){
      before_square = sqare_value;
      if(sqare_value > 0){
        Serial.write('j');
        Serial.print(sqare_value);
        Serial.write('#');
      }else{
        Serial.print("j0#");
      }
    }
}

void Up(){
  static int before_up = 0;
  int up_value = 0;
  
    up_value = PS3.getAnalogButton(UP);
    
    if (before_up != up_value) {
      before_up = up_value;
      if(up_value > 0){
        Serial.write('c');
        Serial.print(up_value);
        Serial.write('#');
      }else{
        Serial.print("c0#");
      }
    }
}

void Right(){
  static int before_right = 0;
  int right_value = 0;
  
    right_value = PS3.getAnalogButton(RIGHT);
    
    if (before_right != right_value) {
      before_right = right_value;
      if(right_value > 0){
       Serial.write('d');
       Serial.print(right_value);
       Serial.write('#');
      }else{
        Serial.print("d0#");
      }
    }
}

void Down(){
  static int before_down = 0;
  int down_value = 0;
  
    down_value = PS3.getAnalogButton(DOWN);
    
    if (before_down != down_value) {
      before_down = down_value;
      if(down_value > 0){
       Serial.write('e');
       Serial.print(down_value);
       Serial.write('#');
      }else{
        Serial.print("e0#");
      }
    }
}

void Left(){
  static int before_left = 0;
  int left_value = 0;
  
    left_value = PS3.getAnalogButton(LEFT);
    
    if (before_left != left_value) {
      before_left = left_value;
      if (left_value > 0){
       Serial.write('f');
       Serial.print(left_value);
       Serial.write('#');
      }else{
        Serial.print("f0#");
      }
    }
}

void Select(){
  static int before_select = 0;
  int select_value = 0;
  
    select_value = PS3.getButtonPress(SELECT);
    
    if (before_select != select_value) {
      before_select = select_value;
      if(select_value > 0){  
        Serial.print("s1#");
        //PS3.printStatusString();
      }else{
        Serial.print("s0#");
      }
    }
}

void Start(){
  static int before_start = 0;
  int start_value = 0;
  
    start_value = PS3.getButtonPress(START);
    
    if (before_start != start_value) {
      before_start = start_value;
      if(start_value){
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
    if (PS3.getButtonPress(PS)) {
        PS3.disconnect();
        PS3.setLedOff();
    }
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
}
