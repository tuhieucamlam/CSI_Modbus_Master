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
  analog_output_holding_register_list[0] = 15;
  analog_output_holding_register_list[1] = 21;
  analog_output_holding_register_list[2] = 3;
  analog_output_holding_register_list[3] = 44;
  analog_output_holding_register_list[4] = 98;
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

    // update value to holding register memory --------------------------
    analog_output_holding_register_list[0]++;
    analog_output_holding_register_list[1]++;
    analog_output_holding_register_list[2]++;
    analog_output_holding_register_list[3]++;
    analog_output_holding_register_list[4]++;
    // update value to holding register memory --------------------------
    
    delay(10);
  }
}
