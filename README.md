# ESP-01_to_MySQL
In this repository you can learn how to connect a ESP8266 WiFi module (ESP-01) to an Arduino UNO connected via Serial (Tx Rx) and send data to a MySQL database in a webhosting

Then I notice it was too dificult and use a nodeMCU connected via serial to an Arduino that sends 4 numbers comma separated.

The program for the Arduino that sends data is called Sender

The program for de NodeMCU still needs you to configure the Arduino IDE and the other libraries. The name of that program is Querier

I left the other two progras as an archive of the past efforts

## Arduino IDE configuration

You need to set up Arduino IDE according to the [ESP8266 documentation](https://arduino-esp8266.readthedocs.io/en/latest/installing.html) in order to use ESP8266WiFi library. You'll need Internet Connection.

- Install Arduino IDE 1.6.8 or above
- Open Arduino IDE and go to <code>File>Preferences>Additional Boards Manager</code> and paste this URL <code>https://arduino.esp8266.com/stable/package_esp8266com_index.json </code> and save changes.
- Open Boards Manager in Tools>Board menu
- Search for ESP8266
- Install esp8266 library by ESP8266 Community from the <code>Sketch>Include Library>Library Manager</code> menu. It might take a while
- Now you can add the following line to use the library 
```
#include <ESP8266WiFi.h>
```
- Install the MySQL Connector Arduino library by Dr. Charles Bell from the <code>Sketch>Include Library>Library Manager</code> menu.
- Now you can add the following line to use the library 
```
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
```
## MySQL structure

Creating a table
```
CREATE TABLE my_table (
    id INT(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    data1 VARCHAR(255),
    data2 INT(11),
    data3 TEXT,
    data4 DECIMAL(10,2)    
);
```
If you want it in one line

```
CREATE TABLE my_table (id INT(11) NOT NULL AUTO_INCREMENT PRIMARY KEY, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, data1 VARCHAR(255), data2 INT(11), data3 TEXT, data4 DECIMAL(10,2));
```

Query to insert a new row

```
INSERT INTO my_table (data1, data2, data3, data4) VALUES (6.21, 3.14, 7.96, 12.34);
```

Check table contents

```
SELECT * FROM my_table;
```

Update column's row

```
UPDATE my_table SET data1=7.21, data2=4.14, data3=8.96, data4=12.35 WHERE id=1;
```