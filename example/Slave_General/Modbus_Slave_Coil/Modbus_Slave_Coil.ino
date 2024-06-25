#include "Modbus_Definition.h"
#include "Modbus_Master.h"
#include "Modbus_Master_RTU.h"
#include "Modbus_Master_IP.h"
#include "Modbus_Slave.h"
#include "Modbus_Slave_Handling.h"
#include "Modbus_Slave_RTU.h"
#include "Modbus_Slave_IP.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // assign value to holding register memory ---------------------------
  setBitToArray(discrete_output_coil_list, 5, 1);
  setBitToArray(discrete_output_coil_list, 8, 1);
  setBitToArray(discrete_output_coil_list, 10, 1);
  setBitToArray(discrete_output_coil_list, 20, 1);
  setBitToArray(discrete_output_coil_list, 25, 1);
  setBitToArray(discrete_output_coil_list, 45, 1);
  // assign value to holding register memory ---------------------------
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    // declare buffer and buffer-length ---------------
    uint8_t xx[50];
    uint16_t len = 0;
    // declare buffer and buffer-length ---------------

    // get data from Serial to buffer -----------------
    while(Serial.available() > 0)
    {
      xx[len++] = Serial.read();
      delay(1);
    }
    // get data from Serial to buffer -----------------


    // handling buffer ------------------------
    RTU_ADU_incomingHandling(xx, len);  // in this step, response message is building automatically
    // handling buffer ------------------------


    // response message sending ------------------------------------
    for(uint8_t i = 0; i < response_RTU_ADU_length; i++)
    {
      Serial.write(built_response_RTU_ADU[i]);
    }
    // response message sending ------------------------------------

    
    delay(10);
  }
}
