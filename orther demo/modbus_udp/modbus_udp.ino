#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Modbus_Definition.h"
#include "Modbus_Master.h"
#include "Modbus_Master_RTU.h"
#include "Modbus_Master_IP.h"
#include "Modbus_Slave.h"
#include "Modbus_Slave_Handling.h"
#include "Modbus_Slave_RTU.h"
#include "Modbus_Slave_IP.h"

const char* ssid = "Phong Tro";
const char* password = "phongtro4b";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back


void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  // assign value to holding register memory ---------------------------
  analog_output_holding_register_list[0] = 15;
  analog_output_holding_register_list[1] = 21;
  analog_output_holding_register_list[2] = 3;
  analog_output_holding_register_list[3] = 44;
  analog_output_holding_register_list[4] = 98;
  // assign value to holding register memory ---------------------------
}


void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);

    if (len > 0)
    {
      // update value to holding register memory --------------------------
      analog_output_holding_register_list[0]++;
      analog_output_holding_register_list[1]++;
      analog_output_holding_register_list[2]++;
      analog_output_holding_register_list[3]++;
      analog_output_holding_register_list[4]++;
      // update value to holding register memory --------------------------
      
      IP_ADU_incomingHandling((uint8_t*)incomingPacket, len);
      
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    for(uint8_t i = 0; i < response_IP_ADU_length; i++)
    {
      Udp.write(built_response_IP_ADU[i]);
    }
    Udp.endPacket();
  }
}
