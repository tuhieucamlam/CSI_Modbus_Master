
#include "Modbus_Definition.h"
#include "Modbus_Master.h"
#include "Modbus_Master_RTU.h"
#include "Modbus_Master_IP.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0)
  {
    uint8_t ADU[50];
    uint8_t ADU_length = 0;
    while(Serial.available() > 0)
    {
      ADU[ADU_length++] = Serial.read();
      delay(2);
    }

//    Serial.println(RTU_ADU_getResposeSlaveID(ADU));
//    Serial.println(RTU_ADU_getCRC(ADU, ADU_length), HEX);

    uint8_t PDU[50];
    uint8_t PDU_length = 0;
    RTU_ADU_getPDU(ADU, ADU_length, PDU, &PDU_length);
    
//    for(uint8_t i = 0; i < PDU_length; i++)
//    {
//      Serial.write(PDU[i]);
//    }

//    Serial.println(getFunctionCode(PDU), HEX);

//    Serial.println(getReadHoldingRegistersByteCount(PDU), HEX);
      
//    Serial.println(getReadHoldingRegistersByteCount(PDU), HEX);


    register_t holding_reg[20];
    uint8_t num_of_reg = getReadHoldingRegistersNumberOfRegister(PDU);
    getReadHoldingRegistersValue(PDU, PDU_length, holding_reg);
    for(uint8_t i = 0; i < num_of_reg; i++)
    {
      Serial.println(holding_reg[i], DEC);
    }
  }
}
