#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

#define AURIGARINGLEDNUM  12
#define RINGALLLEDS        0

MeRGBLed led_ring( 0, 12 );

MeEncoderOnBoard Encoder_D(SLOT1);
MeEncoderOnBoard Encoder_G(SLOT2);
int count;
int inbyte;
int serialdata = 0;
int defaultSpeed = 150;
int directionalSpeed = 10;

void setup() {  
    Serial.println("Start...");

    Serial.begin(9600);
    
    led_ring.setpin(44);
    delay(500);       
    led_ring.setColor( RINGALLLEDS, 0, 0, 1 );
    led_ring.show();
    delay(500);
    led_ring.setColor( RINGALLLEDS, 0, 1, 0 );
    led_ring.show();
}

void loop() {
    // red: 197 1121
    // green: 198 1122
    // blue: 199 1123

    // fow: 200 1124
    // bck: 201 1125
    // right: 202 1126
    // left: 203 1127
    // stop: 204 1128
  
    inbyte = Serial.read();  
    if (inbyte > 0)
    {     
      if (inbyte == 10) {
         serialdata = 0; 
      }
      if (inbyte != 10) {        
        serialdata = serialdata + inbyte;
      }
      inbyte = 0;
    }
    if (serialdata > 0){
      if (serialdata > 196) {
        Serial.println(serialdata);
        if (serialdata == 197){
          led_ring.setColor( RINGALLLEDS, 1, 0, 0 );
          led_ring.show();
        }
        if (serialdata == 198){
          led_ring.setColor( RINGALLLEDS, 0, 1, 0 );
          led_ring.show();
        }        
        if (serialdata == 199){
          led_ring.setColor( RINGALLLEDS, 0, 0, 1 );
          led_ring.show();
        }
        //forward
        if (serialdata == 200) {          
          Encoder_D.setMotorPwm(defaultSpeed);
          Encoder_G.setMotorPwm(-defaultSpeed);
        }      
        //backward
        if (serialdata == 201) {          
          Encoder_D.setMotorPwm(-defaultSpeed);
          Encoder_G.setMotorPwm(defaultSpeed);
        }
        //right
        if (serialdata == 202) {        
          Encoder_D.setMotorPwm(-((defaultSpeed / 2) * 2));
          Encoder_G.setMotorPwm(-(defaultSpeed + (defaultSpeed / 2)));
          
        }        
        //left
        if (serialdata == 203) {          
          Encoder_D.setMotorPwm(((defaultSpeed / 2) * 2));
          Encoder_G.setMotorPwm((defaultSpeed + (defaultSpeed / 2)));
        }
        //stop
        if (serialdata == 204) {          
          Encoder_D.setMotorPwm(0);
          Encoder_G.setMotorPwm(0);
        }        
        serialdata = 0;
      }
    }
}
