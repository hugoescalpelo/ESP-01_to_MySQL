#include <SoftwareSerial.h>

// Declare Serial Comunication Pins of ESP-01 Module
SoftwareSerial espSerial(2, 3); // RX, TX

// Your credentials
const char* ssid = "AXTEL XTREMO-18D6"; // Wi-Fi network name
const char* password = "038C18D6"; // Wi-Fi network password

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  espSerial.begin(9600); // Dont change this one
  
  Serial.println("Start");

  delay(1000);

  // Reset the ESP-01 module
  Serial.println("Reset ESP-01");
  espSerial.println("AT+RST"); 
  delay(1000);

  // Set the ESP-01 module to client mode
  Serial.println("Set ESP-01 to client mode");
  espSerial.println("AT+CWMODE=1");
  delay(1000);

  // Send credentials
  Serial.println("Sending Credentials");
  espSerial.print("AT+CWJAP=\"");
  espSerial.print(ssid);
  espSerial.print("\",\"");
  espSerial.print(password);
  espSerial.println("\"");

  Serial.println("Connecting to Wi-Fi network");

  delay (5000);
  
 
  Serial.println("Connected to Wi-Fi network");

  espSerial.println("AT+CIFSR"); // Get the assigned IP address
  delay(1);

  while (espSerial.available()) {
    char c = espSerial.read();
    if (c != '\r') {
      Serial.print(c);
    }
    if (c == '\n') { // Wait for the end of the response before printing a new line
      break;
    }
  }
  Serial.println ("Finished");
}

void loop() {
  // Your code goes here
}
