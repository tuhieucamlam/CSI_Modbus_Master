#include "Arduino_Master_IP_Serial.h"
#include "SoftwareSerial.h"

SoftwareSerial my_soft(2, 3);
Arduino_Master_IP_Serial xx;

void setup() {
  // put your setup code here, to run once:
  my_soft.begin(9600);
  xx.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  xx.IPSerialReadHoldingRegistersRequest(1, 0, 10);

  while(!xx.available());
  
  my_soft.println(xx.IPSerialGetTransactionID());
  my_soft.println(xx.IPSerialGetResposeSlaveID());
  my_soft.println(xx.IPSerialGetFunctionCode());
  my_soft.println(xx.IPSerialGetExceptionCode());

  

  delay(1000);
}
