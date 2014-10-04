#define LED_RED 13
#define LED_GREEN 12

void setup(){
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  Serial.begin(115200);
}

void loop(){
  int signal;
  
  signal = Serial.read();
  
  if(signal != -1){
    
    switch(signal){
      case 'r':
        Serial.print("red\n");
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN,LOW);
        break;
      case 'g':
        Serial.print("green\n");
        digitalWrite(LED_RED,LOW);
        digitalWrite(LED_GREEN,HIGH);
        break;
      case 'd':
        Serial.print("red & green");
        digitalWrite(LED_GREEN,HIGH);
        digitalWrite(LED_RED,HIGH);
        break;
      case 'o':
        Serial.print("OFF");
        digitalWrite(LED_GREEN,LOW);
        digitalWrite(LED_RED,LOW);
        break;
    }
  }else{
  } 
}  
