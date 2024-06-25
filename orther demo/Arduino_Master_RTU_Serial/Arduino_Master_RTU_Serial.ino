#include "Arduino_Master_RTU_Serial.h"

Arduino_Master_RTU_Serial xx;

void setup() {
  // put your setup code here, to run once:
  xx.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xx.RTUSerialReadHoldingRegistersRequest(1, 0, 10);

  delay(3000);

  if(xx.available())
  {
    Serial.print(xx.RTUSerialGetResposeSlaveID());
    Serial.print('\t');
    Serial.println(xx.RTUSerialGetReadHoldingRegistersByteCount());
    uint8_t num_of_reg = xx.RTUSerialGetReadHoldingRegistersNumberOfRegister();
    register_t* register_value = (register_t*)malloc(num_of_reg * sizeof(register_t));
    xx.RTUSerialGetReadHoldingRegistersValue(register_value);
    for(uint8_t i = 0; i < num_of_reg; i++)
    {
      Serial.println(register_value[i]);
    }
    free(register_value);
    Serial.println();
  }

  delay(1000);
}
