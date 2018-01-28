#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define PIN_INPUT A0 // Analog sensor for detecting multiple buttons

#define SI5    988 // one of the notes
#define PIN_SPEAKER 3 // Speaker on RX pin

extern "C" {
#include "user_interface.h"
}

//WiFiServer server(2775);
WiFiUDP Udp;
int client_number = 0;
String luno_ip = "127.0.0.1";

int button_reading = 0; // 
int last_button_reading = 0; // 
int success_connect = 1;

unsigned long interval=40; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.
unsigned long currentMillis = 0;

unsigned long alarmTimeout=60000; // maximum delay before alarm goes off due to inactivity
unsigned long last_activity_time=0; // time when last button was pressed
unsigned long last_beep_time=0; // needed to produce a beep
long lastDebounceTime = 0;  // the last time the output pin was toggled
int screenOff = 0;


void setup()
{
  success_connect = 0;
  button_reading = 0;
  last_button_reading = 990;
  client_number = 0;
  
  Serial.begin(9600);

  //********************* CHANGE PIN FUNCTION **********************
  pinMode(PIN_SPEAKER, FUNCTION_3); //GPIO 1 swap the pin to a GPIO.
  //****************************************************************
  pinMode(PIN_SPEAKER, OUTPUT);
  tone(PIN_SPEAKER, SI5, 500);

  lcd.init(); // initialize the lcd 
  lcd.backlight();
  //lcd.autoscroll();
  lcd.setCursor(0,0);
  lcd.print("LunoControl v1");
  lcd.setCursor(0,1);
  lcd.print( WiFi.softAP("LunoLuno", "jamesbond") ? "AP UP" : "Please reBOOT!");

  Serial.print("\nAccess Point Starting.\nAP IP: ");
  Serial.print(WiFi.softAPIP());

  Udp.begin(4210);
  //server.begin();
  //Serial.println("TCP server started...");
  delay(2000);
  lcd.clear();
  lcd.print("Waiting for Luno");
  lcd.setCursor(0,1);
  lcd.print("to connect...");
  Serial.print("\nWaiting for Luno to connect...");
} 
 


void UDPDir (char p)
{
  /*
    WiFiClient client;
 
    if (client.connect(luno_ip.c_str(), 4210)) {
        client.print(p);
    }
  */
    Udp.beginPacket(luno_ip.c_str(), 4210);
    Udp.write(p);
    Udp.endPacket();
    Serial.println("\nSent data!");
}

 
void loop()
{

    button_reading = analogRead(PIN_INPUT); // get the analog value
    //Serial.print( "last_button_reading... ");
    //Serial.println(last_button_reading);
    //Serial.print( "button_reading... ");
    //Serial.println(button_reading);
    delay(2);
    
    currentMillis = millis();

   if (abs(button_reading-last_button_reading) > 100) {
    // reset the debouncing timer
    lastDebounceTime = currentMillis;
    Serial.print( "\nDifference between last and current button reading: ");
    Serial.print(abs(button_reading-last_button_reading));
  }

  if (WiFi.softAPgetStationNum() != client_number) {
    client_number = WiFi.softAPgetStationNum();
    Serial.print ("\nNumber of clients: ");
    Serial.print(client_number);
    if (client_number > 0) {
      lcd.clear();
      lcd.print( "Luno Connected!");
      lcd.setCursor(0,1);
      lcd.print( "Getting IP...");

      Serial.print( "\nLuno Connected! Getting IP...");

      // Get IP
      delay(5000);
      struct station_info *station_list = wifi_softap_get_station_info();
      while (station_list != NULL) {
        String station_ip = IPAddress((&station_list->ip)->addr).toString();
        Serial.print( "\nLuno IP: ");
        Serial.print(station_ip);
        Serial.print( "\n\nPress a button");
        luno_ip = station_ip;

        lcd.clear();
        lcd.print("Luno IP:");
        lcd.setCursor(0,1);
        lcd.print(luno_ip);
        station_list = STAILQ_NEXT(station_list, next);
        success_connect = 1;
        lastDebounceTime = millis();
      }
      wifi_softap_free_station_info();
      } else {
        Serial.print("\nNo clients connected...");
        luno_ip = "127.0.0.1";
        success_connect = 0;
      }
  }

    // debounce so that button is not pressed too many times
    if ((unsigned long)(millis() - lastDebounceTime) >= interval && success_connect > 0) {
      
      //button_reading = analogRead(PIN_INPUT); // get the analog value
      //Serial.printf("\nSample: %d", button_reading);
        
      if (button_reading < 990)  {
        // catch faulty button
        Serial.print("\nSomething pressed: ");
        Serial.print(button_reading);
        //lcd.clear();
        //lcd.setCursor(13,0);
        //lcd.print(button_reading);
      }

      if (button_reading >50 && button_reading<90) {
        // backward
        lcd.clear();
        lcd.print("Backward");
        last_activity_time = millis();
        Serial.printf("\nBackward: %d", button_reading);
        lcd.setCursor(13,0);
        lcd.print(button_reading);
        UDPDir('b');
        if ( screenOff == 1){
          screenOff = 0;
          lcd.backlight();
        }
      }
      else if (button_reading >310 && button_reading<350) {
        // stop
        lcd.clear();
        lcd.print("Stop");
        last_activity_time = millis();
        Serial.printf("\nStop: %d", button_reading);
        lcd.setCursor(13,0);
        lcd.print(button_reading);
        UDPDir('s');
        if ( screenOff == 1){
          screenOff = 0;
          lcd.backlight();
        }

      }
      else if (button_reading >420 && button_reading<460) {
        // right
        lcd.clear();
        lcd.print("Right");
        last_activity_time = millis();
        Serial.printf("\nRight: %d", button_reading);
        lcd.setCursor(13,0);
        lcd.print(button_reading);
        UDPDir('r');
        if ( screenOff == 1){
          screenOff = 0;
          lcd.backlight();
        }

      }
      else if (button_reading >550 && button_reading<580) {
        // forward
        lcd.clear();
        lcd.print("Forward");
        last_activity_time = millis();
        Serial.printf("\nForward: %d", button_reading);
        lcd.setCursor(13,0);
        lcd.print(button_reading);
        UDPDir('f');
        if ( screenOff == 1){
          screenOff = 0;
          lcd.backlight();
        }

      }
      else if (button_reading >680 && button_reading<720) { 
        // left
        lcd.clear();
        lcd.print("Left");
        last_activity_time = millis();
        Serial.printf("\nLeft: %d", button_reading);
        lcd.setCursor(13,0);
        lcd.print(button_reading);
        UDPDir('l');
        if ( screenOff == 1){
          screenOff = 0;
          lcd.backlight();
        }
      }

      // save the "current" time
      previousMillis = millis();
      
      last_button_reading = button_reading;  // save the reading.  Next time through the loop,
      
    }

    // beep alarm if inactive
    if ((unsigned long)(previousMillis - last_activity_time) >= alarmTimeout){
      if ((unsigned long)(previousMillis - last_beep_time) >= 1000) {
        tone(PIN_SPEAKER, SI5, 500);
        last_beep_time = previousMillis;
        if (screenOff == 0 && success_connect > 0){
          lcd.noBacklight();
          screenOff = 1;
        }
        
      }
    }
}

