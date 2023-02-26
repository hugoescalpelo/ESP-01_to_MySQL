#include <SoftwareSerial.h>

// Create a software serial object with the RX and TX pins connected to pins 2 and 3, respectively.
SoftwareSerial mySerial(2, 3);

void setup() {
  // Initialize serial communication with a baud rate of 9600.
  Serial.begin(9600);
  
  // Initialize software serial communication with the same baud rate.
  mySerial.begin(9600);
}

void loop() {
  // Define the four numbers to be sent.
  int num1 = 123;
  int num2 = 456;
  int num3 = 789;
  int num4 = 1000;
  
  // Convert the numbers to strings and concatenate them with commas.
  String data = String(num1) + "," + String(num2) + "," + String(num3) + "," + String(num4);

  // Print the data to the serial monitor for debugging purposes.
  Serial.println(data);

  // Send the data via software serial.
  mySerial.println(data);

  // Wait for a short delay before sending the next data.
  delay(1000);
}
