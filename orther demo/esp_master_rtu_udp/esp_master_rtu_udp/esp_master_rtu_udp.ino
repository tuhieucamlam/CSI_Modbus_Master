#include "ESP8266_Master_RTU_UDP.h"

//const char ssid[] = "Phong Tro";
//const char pwd[] = "phongtro4b";
//const char ssid[] = "Autobase VN";
//const char pwd[] = "ATC@Scada";
//const char ssid[] = "ATBScada";
//const char pwd[] = "ATS@Scada";
//const char ssid[] = "Network";
//const char pwd[] = "12345678";
const char ssid[] = "Bico";
const char pwd[] = "12345678";

unsigned int master_udp_local_port = 503;
ESP8266_Master_RTU_UDP master;

IPAddress ip(192, 168, 0, 69);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

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
}

void loop() {
  // put your main code here, to run repeatedly:
  master.RTUUDPReadHoldingRegistersRequest(IPAddress(192, 168, 0, 2), 502, 1, 0, 10);

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
      Serial.print("Get from: ");
      Serial.println(master.remoteIP().toString());
  
      register_t temp_reg[10];
      master.RTUUDPGetReadHoldingRegistersValue(temp_reg);
      for(uint8_t j = 0; j < 10; j++)
      {
        Serial.println(temp_reg[j]);
      }
    }
  }
}
