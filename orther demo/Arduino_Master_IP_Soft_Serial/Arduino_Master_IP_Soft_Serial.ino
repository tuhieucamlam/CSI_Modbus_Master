#include "Arduino_Master_IP_Soft_Serial.h"

Arduino_Master_IP_Soft_Serial xx(2, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xx.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xx.IPSoftSerialReadHoldingRegistersRequest(1, 0, 10);

  delay(3000);

  if(xx.available())
  {
    Serial.print(xx.IPSoftSerialGetResposeSlaveID());
    Serial.print('\t');
    Serial.println(xx.IPSoftSerialGetReadHoldingRegistersByteCount());
    uint8_t num_of_reg = xx.IPSoftSerialGetReadHoldingRegistersNumberOfRegister();
    register_t* register_value = (register_t*)malloc(num_of_reg * sizeof(register_t));
    xx.IPSoftSerialGetReadHoldingRegistersValue(register_value);
    for(uint8_t i = 0; i < num_of_reg; i++)
    {
      Serial.println(register_value[i]);
    }
    free(register_value);
    Serial.println();
  }

  delay(1000);
}
