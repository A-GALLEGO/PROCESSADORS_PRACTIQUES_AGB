# PROCESSADORS DIGITALS
## INFORME PRACTICA 3

___

### Introducció
En aquesta practica conectarem la placa per wifi i bluetooth a un altre dispositiu.

___

### Codi i Funcionament WIFI

___

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

void handle_root();
// SSID & Password
// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1> Skold el Barto Simpson. khe tu ase barto - Station Mode &#128522;</h1>\
</body>\
</html>";
const char* ssid = "Agus"; // Enter your SSID here
const char* password = "agusboom0509"; //Enter your Password here
WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)
void handle_root() {
server.send(200, "text/html", HTML);
}

void setup() {
Serial.begin(115200);
Serial.println("Try Connecting to ");
Serial.println(ssid);
// Connect to your wi-fi modem
WiFi.begin(ssid, password);
// Check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected successfully");
Serial.print("Got IP: ");
Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
server.on("/", handle_root);
server.begin();
Serial.println("HTTP server started");
delay(100);
}

void loop() {
server.handleClient();
}
```

Primer definim les llibreries d'Arduino, Wifi i WebServer per tal de poder utilitzar les funcions necessàries(poder conectar-se a internet i poder definir un servidor web).

A continuació desenvolupem la pàgina web amb el llenguatge html, i despres introduim el nom i contrasenya del nostre wifi per poder conectar-nos i crear el servidor web.

Tot seguit dins el void setup conectem la placa a la xarxa wifi, en cas de conectar-se correctament es mostrarà un missatge que ho confirmi ("Wifi connected succesfully") i una direcció IP que la introduirem en el sercador del navegador i s'obrirà la pagina web.

Finalment en el void loop només s'utilitza la funció server."handleClient()" que sencarrega de mantenir el servidor web actualitzat en cas de que algún canvi s'hagi realitzat.

___

### Codi i Funcionament Bluetooth

```cpp
#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
void setup() {
Serial.begin(115200);
SerialBT.begin("Agus"); //Bluetooth device name
Serial.println("The device started, now you can pair it with bluetooth!");
}
void loop() {
if (Serial.available()) {
SerialBT.write(Serial.read());
}
if (SerialBT.available()) {
Serial.write(SerialBT.read());
}
delay(20);
}
```

Primer afegim les llibreries d'Arduino i bluetooth per poder continuar endevat.

En el void setup es comprova que la conexió bluetooth amb el dispositiu és correcte, i en el cas de que ho sigui es mostra un missatge que ho confirma.

Finalment en el void loop es comprova si s'ha escrit algo en el dispositiu que hem conectat i en cas de que sigui així, el programa mostrarà per pantalla aquest mateix missatge.

___