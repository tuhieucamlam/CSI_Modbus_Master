#include "Modbus_Definition.h"
#include "Modbus_Master.h"
#include "Modbus_Master_RTU.h"
#include "Modbus_Master_IP.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  RTU_ADU_readHoldingRegistersRequest(1, 0, 10);
  for(int i = 0; i < request_RTU_ADU_length; i++)
  {
    Serial.write(built_request_RTU_ADU[i]);
  }

  delay(1000);
}
