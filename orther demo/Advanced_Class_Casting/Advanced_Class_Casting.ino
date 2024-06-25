#include "ESP8266_Master_IP_UDP.h"

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

unsigned int udp_local_port = 502;
ESP8266_Master_IP_UDP xx;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);

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
  
  Serial.printf("Starting UDP at port %d: ", udp_local_port);
  if(xx.begin(udp_local_port))
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
  if(xx.parsePacket())
  {
    WiFiUDP* cc = (WiFiUDP*)(&xx);
    cc->beginPacket(cc->remoteIP(), cc->remotePort());
    for(uint8_t i = 0; i < xx.response_ADU_buffer_length; i++)
    {
      cc->write(xx.response_ADU_buffer[i]);
    }
    cc->endPacket();
  }

}
