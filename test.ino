#include <EEPROM.h>

#include <i2cmaster.h>
#include <Wire.h>
#include <Arduino.h>  // <-- Must add to *.INO sketch.

#define P_out 0x96
#define I_out 0x8C
#define T_out 0x8E

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

float linear_data_format(int datalow, int datahigh)
{
  int y = ((datahigh & 7) << 8) + datalow;
  int n = datahigh >> 3;
  if((n >> 4) == 1)
  {
      n = n^31;
      n += 1;
      n = -n;
  }
  
  return y*pow(2,n); 
}
void read_data_wire(int command, int byte_num)
{
  int addr;
    switch(command)
  {
    case P_out: 
      addr = 0;
      break;
    case I_out: 
      addr = 2;
      break;
    case T_out: 
      addr = 4;
      break;
    default: addr = 0;
  }
  int Address = 0x5B;
  Wire.beginTransmission(Address);
  Wire.write(command);
  Wire.endTransmission(false);
  Wire.requestFrom(Address, byte_num);
  while(Wire.available()) // loop all bytes if any are available
{
  int a = Wire.read();
  //Serial.print(a, HEX); // print em out
  EEPROM.write(addr,a);
  addr++;
  //Serial.print(" ");
}
  //Serial.println(" ");
}

void read_data_i2c(int command, int byte_num)
{
  int dev_addr = 0x5B<<1;
  int datalow = 0;
  int datahigh = 0;
  int pec = 0;
  i2c_start_wait(dev_addr+I2C_WRITE);
  i2c_write(command);
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
}

void test_signals()
{
  if(digitalRead(PWOK) == LOW)
  {
    Serial.print("PSU is not OK\n");
  }
  else
  {
    Serial.print("PSU is OK\n");
  }
/*
  if(digitalRead(SMB_Alert) == HIGH)
  {
    Serial.print("OK\n");
  }
  else
  {
    Serial.print("Alert!\n");
  }
  */
}
// the loop routine runs over and over again forever:
void loop()
{
  delay(500);
  
  digitalWrite(ADDR_0, LOW);
  delay(100);
  digitalWrite(ADDR_1, LOW);
  delay(100);
  digitalWrite(PSON,LOW );
  delay(100);
  digitalWrite(SMART_ON, LOW);
  
  //read_data_wire(0x19,1);
  //Serial.println(EEPROM.read(0),HEX);
  //
  //test_signals(); 
  read_data_wire(P_out,2);
  float power = linear_data_format(EEPROM.read(0),EEPROM.read(1));
  read_data_wire(I_out, 2);
  float current = linear_data_format(EEPROM.read(2),EEPROM.read(3));
  float voltage = power/current;
  read_data_wire(T_out,2);
  float temperature = linear_data_format(EEPROM.read(4),EEPROM.read(5));
  Serial.print("Current: ");
  Serial.print(current);
  Serial.print(" /Voltage: ");
  Serial.print(voltage);
  Serial.print(" /Power: ");
  Serial.print(power);
  Serial.print(" /Temperature: ");
  Serial.println(temperature);
}
