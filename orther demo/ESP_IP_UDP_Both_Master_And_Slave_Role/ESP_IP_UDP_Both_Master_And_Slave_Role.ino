#include "ESP8266_Master_IP_UDP.h"
#include "ESP8266_Slave_IP_UDP.h"

//const char ssid[] = "Phong Tro";
//const char pwd[] = "phongtro4b";
const char ssid[] = "Autobase VN";
const char pwd[] = "ATC@Scada";
//const char ssid[] = "ATBScada";
//const char pwd[] = "ATS@Scada";
//const char ssid[] = "Network";
//const char pwd[] = "12345678";

IPAddress ip(192, 168, 1, 169);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

unsigned int master_udp_local_port = 503;
ESP8266_Master_IP_UDP master;
unsigned int slave_udp_local_port = 502;
ESP8266_Slave_IP_UDP slave;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);

  WiFi.softAPdisconnect(true);
  
  //--------------------------------------------------------------------
  Serial.printf("Connecting to %s \r\n", ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, pwd);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.printf("Connected to %s \r\n", ssid);
  Serial.printf("Static IP: %s\r\n", ip.toString().c_str());
  //--------------------------------------------------------------------
  Serial.printf("Starting Master UDP at port %d: ", master_udp_local_port);
  if(master.begin(master_udp_local_port))
  {
    Serial.println("Successful");
  }
  else
  {
    Serial.println("Failed");
  }
  //-------------------------------------------
  Serial.printf("Starting Slave UDP at port %d: ", slave_udp_local_port);
  if(slave.begin(slave_udp_local_port))
  {
    Serial.println("Successful");
  }
  else
  {
    Serial.println("Failed");
  }
  //---------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(ESP.getFreeHeap());

  //--------------------------------------------
  
  slave.fullHanlde();

  //--------------------------------------------

  #define NUM_OF_SLAVE 8 
  static IPAddress ip_list[NUM_OF_SLAVE] = {IPAddress(192, 168, 1, 170), IPAddress(192, 168, 1, 171), IPAddress(192, 168, 1, 172), IPAddress(192, 168, 1, 173), 
                                  IPAddress(192, 168, 1, 174), IPAddress(192, 168, 1, 175), IPAddress(192, 168, 1, 176), IPAddress(192, 168, 1, 177)};
  static uint16_t slave_remote_port = 502;
  static uint8_t slave_id = 1;

  for(uint8_t i = 0; i < NUM_OF_SLAVE; i++)
  {
    Serial.print("Send to: ");
    Serial.println(ip_list[i].toString());
    
    #define NUM_OF_HOLDING_REG 10
    master.IPUDPReadHoldingRegistersRequest(ip_list[i], slave_remote_port, slave_id, 0, NUM_OF_HOLDING_REG); 
    delay(10);
  }
  Serial.println();

  #define TIME_OUT 3000
  uint8_t having_response = []() -> uint8_t
    {
      for(uint16_t i = 0; i < TIME_OUT; i++)
      {
        if(master.available())
        {
          return 1;
        }
        delay(1);
      }

      Serial.println("TIME_OUT");
      return 0;
    }();   

  if(having_response)
  {
    while(master.parsePacket())
    {
      for(uint8_t i = 0; i < NUM_OF_SLAVE; i++)
      {
        if(master.remoteIP() == ip_list[i])
        {
          Serial.print("Get from: ");
          Serial.println(master.remoteIP().toString());

          register_t temp_reg[NUM_OF_HOLDING_REG];
          master.IPUDPGetReadHoldingRegistersValue(temp_reg);
          for(uint8_t j = 0; j < NUM_OF_HOLDING_REG; j++)
          {
            slave_analog_output_holding_register_list[NUM_OF_HOLDING_REG*i + j] = temp_reg[j];
          }
        }
      }
    }
    Serial.println();

    for(uint8_t index_slave = 0; index_slave < NUM_OF_SLAVE; index_slave++)
    {
      Serial.printf("Slave %d: ", index_slave);
      for(uint8_t index_reg = 0; index_reg < NUM_OF_HOLDING_REG; index_reg++)
      {
        Serial.print(slave_analog_output_holding_register_list[NUM_OF_HOLDING_REG*index_slave + index_reg]);
        Serial.print('\t');
      }
      Serial.println();
    }
    Serial.println();
  }
}
