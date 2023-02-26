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

  // Read the incoming data from software serial
  String data = mySerial.readStringUntil('\n');
  Serial.println("Received data: " + data);

  // Split the incoming data into four numbers separated by commas
  int values[4];
  int pos = 0;
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == ',') {
      values[pos] = data.substring(i - 3, i).toInt();
      pos++;
    }
  }
  values[pos] = data.substring(data.length() - 4).toInt();

  // Update the remote MySQL database with the data
  MySQL_Cursor* cursor = new MySQL_Cursor(&conn);
  char query[100];
  sprintf(query, "UPDATE %s.%s SET value1=%d, value2=%d, value3=%d, value4=%d WHERE id=1", database_name, table_name, values[0], values[1], values[2], values[3]);
  cursor->execute(query);
  delete cursor;

  // Wait for a short delay before sending the next data
  delay(1000);
}
