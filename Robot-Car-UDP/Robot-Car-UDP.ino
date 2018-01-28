 //#include <pins_arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// arduino
/*
int MOTORA1 = 2;
int MOTORA2 = 3;
int MOTORB1 = 6;
int MOTORB2 = 7;
*/
// wemos
#define MOTORA1 5
#define MOTORA2 4
#define MOTORB1 0
#define MOTORB2 2

// UDP Config
WiFiUDP Udp;
unsigned int localUdpPort = 4210;
char incomingPacket[255];
char state_old_1 = 'n';
char state_old_2 = 'n';

unsigned long previousMillisLed=0; // millis() returns an unsigned long.

unsigned long alarmTimeout=60000; // maximum delay before alarm goes off due to inactivity
unsigned long last_activity_time=0; // time when last button was pressed
unsigned long last_beep_time=0; // needed to produce a beep

// 0 - stop, 1 - forward, 2 - left, 3 - right, 4 - backward, 5 - special, 6 - startup
int state = 0;

// Define speaker pin (PWM~). RX is GPIO 3
#define PIN_SPEAKER 3

// LED stip pin
#define PIN_LED 15
int ledState = 0;

// Easy to use notes (Do not modify)
#define SOL_d2 104
#define LA2    110
#define LA_d2  114
#define SI2    124
#define DO3    131
#define DO_d3  139
#define RE3    147
#define RE_d3  156
#define MI3    165
#define FA3    175
#define FA_d3  185
#define SOL3   196
#define SOL_d3 208
#define LA3    220
#define LA_d3  233
#define SI3    247
#define DO4    262
#define DO_d4  277
#define RE4    294
#define RE_d4  311
#define MI4    330
#define FA4    349
#define FA_d4  370
#define SOL4   392
#define SOL_d4 415
#define LA4    440
#define LA_d4  466
#define SI4    494
#define DO5    523
#define DO_d5  554
#define RE5    587
#define RE_d5  622
#define MI5    659
#define FA5    698
#define FA_d5  740
#define SOL5   784
#define SOL_d5 831
#define LA5    880
#define LA_d5  932
#define SI5    988
#define DO6    1046
#define DO_d6  1109
#define RE6    1175
#define RE_d6  1245
#define MI6    1319
#define FA6    1397
#define FA_d6  1480
#define SOL6   1568
#define SOL_d6 1661
#define LA6   1760
#define LA_d6  1865


void setup()
{
  last_activity_time = millis();
  //********************* CHANGE PIN FUNCTION **********************
  //pinMode(PIN_SPEAKER, FUNCTION_3); //GPIO 3 swap the pin to a GPIO. only if PIN is RX/TX
  //****************************************************************
  pinMode(PIN_SPEAKER, OUTPUT);
  //tone(PIN_SPEAKER, SI5, 500);

  pinMode(PIN_LED, OUTPUT);
  
  pinMode(MOTORA1, OUTPUT);
  pinMode(MOTORA2, OUTPUT);
  pinMode(MOTORB1, OUTPUT);
  pinMode(MOTORB2, OUTPUT);

  digitalWrite(PIN_SPEAKER, LOW);
  digitalWrite(PIN_LED, LOW);
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);

// WiFi Coonect
  Serial.begin(9600);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin("LunoLuno", "jamesbond");
  
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localUdpPort); // start UDP server
  Serial.println("UDP Server Stared");
}


void loop() {
  
  unsigned long currentMillis = millis(); // grab current time

  int packetSize = Udp.parsePacket();

  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // debounce
    if (incomingPacket[0] == state_old_1 && incomingPacket[0] == state_old_2){
      state_old_2 = state_old_1;
      state_old_1 = incomingPacket[0];
    }
    else {
      state_old_2 = state_old_1;
      state_old_1 = incomingPacket[0];
      incomingPacket[0] = 'n';
    }
     
    
    switch (incomingPacket[0]) {
        case 's':
        noTone(PIN_SPEAKER);
        digitalWrite(PIN_LED, LOW);
        state = 0;
        go_stop();
        Serial.printf("Stop\n");
        last_activity_time = millis();
        break;
       case 'f':  
        noTone(PIN_SPEAKER);
        digitalWrite(PIN_LED, LOW);
        state = 1;
        go_forward();
        Serial.printf("Forward\n");
        last_activity_time = millis();
        break;
      case 'l':
        noTone(PIN_SPEAKER);
        digitalWrite(PIN_LED, LOW);
        state = 2;
        go_left();
        Serial.printf("Left\n");
        last_activity_time = millis();
        break;
      case 'r':
        noTone(PIN_SPEAKER);
        digitalWrite(PIN_LED, LOW);
        state = 3;
        go_right();
        Serial.printf("Right\n");
        last_activity_time = millis();
        break;        
      case 'b':
        noTone(PIN_SPEAKER);
        state = 4;
        go_backward();
        tone(PIN_SPEAKER, SOL6, 500);
        Serial.printf("Backward\n");
        last_activity_time = millis();
        break;
      case 'w': 
        // special button
        noTone(PIN_SPEAKER);
        digitalWrite(PIN_LED, LOW);
        state = 5;
        tone(PIN_SPEAKER, DO3, 1000);
        Serial.printf("Special\n");
        last_activity_time = millis();
        break;
      case 'n':
      // do nothing
        Serial.printf("Do nothing\n");
        last_activity_time = millis();
        break;
    }
  }
  
  // going backward sound and LED flash
  if ((unsigned long)(currentMillis - previousMillisLed) >= 500 && state == 4) {
    if (ledState == 0){
      ledState = 1;
      tone(PIN_SPEAKER, SOL6, 500);
      digitalWrite(PIN_LED, HIGH);
    }
    else {
      ledState = 0;
      noTone(PIN_SPEAKER);
      digitalWrite(PIN_LED, LOW);
    }
    
    // save the "current" time
    previousMillisLed = millis();
  }

  // beep ALARM if inactive
  
  if ((unsigned long)(millis() - last_activity_time) >= alarmTimeout && state == 0){
    if ((unsigned long)(millis() - last_beep_time) >= 500) {
      if (ledState == 0){
        ledState = 1;
        tone(PIN_SPEAKER, SOL6, 500);
        digitalWrite(PIN_LED, HIGH);
      }
      else {
        ledState = 0;
        noTone(PIN_SPEAKER);
        digitalWrite(PIN_LED, LOW);
      }
      // save the "current" time
      last_beep_time = millis();
    }
  }

} // end loop

void go_left(){
  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);
}

void go_right(){
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);
}

void go_backward(){
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);
}
void go_forward(){
  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);
}

void go_stop(){
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);
}



