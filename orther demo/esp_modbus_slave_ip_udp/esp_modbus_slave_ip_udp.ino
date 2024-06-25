#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ESP8266_Slave_IP_UDP.h"

//const char ssid[] = "Phong Tro";
//const char pwd[] = "phongtro4b";
//const char ssid[] = "Autobase VN";
//const char pwd[] = "ATC@Scada";
//const char ssid[] = "Network";
//const char pwd[] = "12345678";
//const char ssid[] = "ATBScada";
//const char pwd[] = "ATS@Scada";
const char ssid[] = "Bico";
const char pwd[] = "12345678";
IPAddress ip(192, 168, 0, 69);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

unsigned int udp_local_port = 502;
ESP8266_Slave_IP_UDP mb_udp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  
  WiFi.softAPdisconnect(true);
  
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
  if(mb_udp.begin(udp_local_port))
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
  mb_udp.fullHanlde();

  static long last_time = millis();
  if(millis() - last_time > 10)
  {
    slave_analog_output_holding_register_list[0]+=1;
    slave_analog_output_holding_register_list[1]+=2;
    slave_analog_output_holding_register_list[2]+=3;
    slave_analog_output_holding_register_list[3]+=4;
    slave_analog_output_holding_register_list[4]+=5;
    slave_analog_output_holding_register_list[5]+=1;
    slave_analog_output_holding_register_list[6]+=2;
    slave_analog_output_holding_register_list[7]+=3;
    slave_analog_output_holding_register_list[8]+=4;
    slave_analog_output_holding_register_list[9]+=5;

    last_time = millis();
  }
}
