#include <ESP8266WiFi.h>

#include "Modbus_Definition.h"
#include "Modbus_Master.h"
#include "Modbus_Master_RTU.h"
#include "Modbus_Master_IP.h"
#include "Modbus_Slave.h"
#include "Modbus_Slave_Handling.h"
#include "Modbus_Slave_RTU.h"
#include "Modbus_Slave_IP.h"

char station_ssid[] = "Bico";
char station_pass[] = "12345678";

WiFiServer esp_server(502);

IPAddress static_ip(192,168,1,69);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  esp_server.begin();

  WiFi.config(static_ip, gateway, subnet);
  WiFi.begin(station_ssid, station_pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.println(String(station_ssid) + " has connected");
  Serial.println(WiFi.localIP());


  // assign value to input register memory ---------------------------
  analog_input_register_list[0] = 15;
  analog_input_register_list[1] = 21;
  analog_input_register_list[2] = 3;
  analog_input_register_list[3] = 44;
  analog_input_register_list[4] = 98;
  // assign value to input register memory ---------------------------
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient new_client = esp_server.available();
  if(new_client)
  {
    new_client.setTimeout(100);
    
    while(new_client.connected())
    { 
      if(new_client.available())
      {
        // declare buffer and buffer-length ---------------
        uint8_t xx[50];
        uint16_t len = 0;
        // declare buffer and buffer-length ---------------
    
        // get data from Serial to buffer -----------------
        while(new_client.available() > 0)
        {
          xx[len++] = new_client.read();
          delay(1);
        }
        // get data from Serial to buffer -----------------   

        // update value to input register memory ---------------------------
        analog_input_register_list[0]++;
        analog_input_register_list[1]++;
        analog_input_register_list[2]++;
        analog_input_register_list[3]++;
        analog_input_register_list[4]++;
        // assign value to input register memory ---------------------------
  
        // handling buffer ------------------------
        IP_ADU_incomingHandling(xx, len);  // in this step, response message is building automatically
        // handling buffer ------------------------

        // response message sending ------------------------------------
        for(uint8_t i = 0; i < response_IP_ADU_length; i++)
        {
          new_client.write(built_response_IP_ADU[i]);
        }
        // response message sending ------------------------------------

        for(uint8_t i = 0; i < response_IP_ADU_length; i++)
        {
          Serial.write(built_response_IP_ADU[i]);
        }
        // response message sending ------------------------------------
    
        while(new_client.available() > 0)
        {
          new_client.read();
        }
        delay(10);
      }
    }

    new_client.stop();
  }

}
