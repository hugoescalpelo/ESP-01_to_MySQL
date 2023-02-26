/*
 * Autor: Hugo Escalpelo
 * Date: 23 february 2023
 * Updated: 25 february 2023
 * 
 * This program sends 4 numbers to a remote MySQL database every second 
 * using an Arduino UNO and an ESP8266 WiFi Module (ESP-01).
 * 
 * Connection Table
 * ESP8266 Module      Arduino UNO}
 * 
 * GND-----------------GND
 * 3V3-----------------3V3
 * Tx------------------Rx
 * Rx------------------Tx
 * EN------------------3V3
 * RST-----------------3V3
 * IO2-----------------Not connected
 * IO1-----------------Not Connected
 * 
 * This program was created for Anni Garza Lau: https://www.annigarzalau.com/
 * Visit https://hugoescalpelo.com/ and https://github.com/hugoescalpelo
 */

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

SoftwareSerial espSerial(2, 3); // RX, TX

char ssid[] = "your_SSID"; // your network SSID (name)
char pass[] = "your_PASSWORD"; // your network password
char server[] = "127.168.15.101"; // MySQL server IP
char user[] = "your_USERNAME"; // MySQL username
char password[] = "your_PASSWORD"; // MySQL password
char database[] = "ANNI"; // MySQL database name
int port = 3306; // MySQL server port

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("Connecting to MySQL server...");

  if (conn.connect(server, port, user, password)) {
    Serial.println("Connected to MySQL server");
  } else {
    Serial.println("MySQL connection failed");
  }
}

void loop() {
  int data1 = 123;
  int data2 = 456;
  int data3 = 789;
  int data4 = 101112;

  char query[256];
  sprintf(query, "INSERT INTO DATOS (data1, data2, data3, data4) VALUES (%d, %d, %d, %d)", data1, data2, data3, data4);

  Serial.println(query);

  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(query);
  delete cur_mem;

  delay(1000);
}
