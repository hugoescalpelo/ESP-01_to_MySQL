#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Replace with your network credentials
const char* ssid = "network_name";
const char* password = "password";

// Replace with your MySQL server IP, port, username, and password
IPAddress server(192, 168, 1, 1);
int port = 3306;
const char* username = "db_username";
const char* password_mysql = "db_pass";

// Replace with your remote database name and table name
const char* database_name = "db_name";
const char* table_name = "table_name";

// Create a software serial object with the RX and TX pins connected to pins D2 and D3, respectively
SoftwareSerial mySerial(2, 3);

// Float variables to store received messages
float value1, value2, value3, value4;

void setup() {
  // Start serial communication for debugging purposes
  Serial.begin(9600);

  // Start software serial communication with the same baud rate
  mySerial.begin(9600);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MySQL server
  WiFiClient client;
  MySQL_Connection conn(&client);
  if (conn.connect(server, port, username, password_mysql)) {
    Serial.println("Connected to MySQL server");
  } else {
    Serial.println("Connection to MySQL server failed");
  }
}

void loop() {
  // Wait for data to be available on software serial
  while (!mySerial.available()) {
    delay(100);
  }

  if (mySerial.available() > 0) {
    String data = mySerial.readStringUntil('\n'); // Read the serial data until a newline character is received
    int index1 = data.indexOf(','); // Find the first comma separator
    int index2 = data.indexOf(',', index1+1); // Find the second comma separator
    int index3 = data.indexOf(',', index2+1); // Find the third comma separator
    if (index1 > -1 && index2 > -1 && index3 > -1) { // Check if all four values are received
      value1 = data.substring(0, index1).toFloat(); // Convert the first value to a float
      value2 = data.substring(index1+1, index2).toFloat(); // Convert the second value to a float
      value3 = data.substring(index2+1, index3).toFloat(); // Convert the third value to a float
      value4 = data.substring(index3+1).toFloat(); // Convert the fourth value to a float
      Serial.print("Received: ");
      Serial.print(value1);
      Serial.print(", ");
      Serial.print(value2);
      Serial.print(", ");
      Serial.print(value3);
      Serial.print(", ");
      Serial.println(value4);
    }
  }

  // Update the remote MySQL database with the data
  MySQL_Cursor* cursor = new MySQL_Cursor(&conn);
  char query[100];
  sprintf(query, "UPDATE %s.%s SET value1=%d, value2=%d, value3=%d, value4=%d WHERE id=1", database_name, table_name, values1, values2, values3, values4);
  cursor->execute(query);
  delete cursor;

  // Wait for a short delay before sending the next data
  delay(1000);
}
