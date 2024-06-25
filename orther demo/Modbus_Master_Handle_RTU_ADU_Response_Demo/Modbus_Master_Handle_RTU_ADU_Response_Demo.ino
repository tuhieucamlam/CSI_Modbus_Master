
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
//    uint8_t ADU[50];
//    uint8_t ADU_length = 0;
//    while(Serial.available() > 0)
//    {
//      ADU[ADU_length++] = Serial.read();
//      delay(2);
//    }

//    Serial.println(RTU_ADU_getResposeSlaveID(ADU));
//    Serial.println(RTU_ADU_getCRC(ADU, ADU_length), HEX);

//    Serial.println(RTU_ADU_getFunctionCode(ADU), HEX);

//    Serial.println(RTU_ADU_getReadHoldingRegistersByteCount(ADU), HEX);
//    Serial.println(RTU_ADU_getReadHoldingRegistersNumberOfRegister(ADU), HEX);
    


//    register_t holding_reg[20];
//    uint8_t num_of_reg = RTU_ADU_getReadHoldingRegistersNumberOfRegister(ADU);
//    RTU_ADU_getReadHoldingRegistersValue(ADU, ADU_length, holding_reg);
//    for(uint8_t i = 0; i < num_of_reg; i++)
//    {
//      Serial.println(holding_reg[i], DEC);
//    }
  }
}
