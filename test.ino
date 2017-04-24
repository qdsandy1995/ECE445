#include <i2cmaster.h>
#include <Wire.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

#include <Arduino.h>  // <-- Must add to *.INO sketch.

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ADDR_0 = 7; 
int ADDR_1 = 8; 
int PSON = 2;
int SMB_Alert = 3; 
int PWOK = 4;
int SMART_ON = 5; 
int PRESENT_N = 6; 
 
// the setup routine runs once when you press reset:
void setup()
{
  // initialize the pins as input/output.
  pinMode(ADDR_0, INPUT);    //Address of the PSU
  pinMode(ADDR_1, INPUT);    //Address of the PSU
  pinMode(PSON, OUTPUT);   //Turn on/off the PSU
  pinMode(PWOK, INPUT);  //Monitor this signal
  pinMode(SMART_ON, OUTPUT); //Turn on/off smart protection
  pinMode(SMB_Alert, INPUT); //Warning signal
  // I2C Bus
  Wire.begin();
  i2c_init();
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop()
{

  delay(500);
  
  digitalWrite(ADDR_0, LOW);
  digitalWrite(ADDR_1, LOW);
  
  digitalWrite(PSON,LOW);
  

 
  

  if(digitalRead(PWOK) == LOW)
  {
    Serial.print("PSU is not OK\n");
  }
  else
  {
    Serial.print("PSU is OK\n");
  }

  if(digitalRead(SMB_Alert) == HIGH)
  {
    Serial.print("OK\n");
  }
  else
  {
    Serial.print("Alert!\n");
  }

 
 
/*
  int Address = 0x5B;
  int command = 0x96;
  Wire.beginTransmission(Address);
  Wire.write(command);
  Wire.endTransmission(false);
  Wire.requestFrom(Address, 2);
  while(Wire.available()) // loop all bytes if any are available
{
  Serial.print(Wire.read(), HEX); // print em out
  Serial.print(" ");
}
  Serial.println(" ");
   
 */ 
 /*
  int dev_addr = 0x5B<<1;
  int datalow = 0;
  int datahigh = 0;
  int pec = 0;
  i2c_start_wait(dev_addr+I2C_WRITE);
  i2c_write(0x8C);
  //i2c_write(16);
  i2c_rep_start(dev_addr+I2C_READ);
  datalow = i2c_readAck();
  datahigh = i2c_readAck();
  pec = i2c_readNak();
  i2c_stop();
  Serial.print(datalow, HEX);
  Serial.print(" ");
  Serial.print(datahigh, HEX);
  Serial.println(" ");
 */
}

