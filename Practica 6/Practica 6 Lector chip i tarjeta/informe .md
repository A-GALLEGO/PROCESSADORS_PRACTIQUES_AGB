# PROCESSADORS DIGITALS
## PRACTICA 6: LECTOR CHIP I TARGETA

___

### Introduccio

En aquesta practica crearemmun mòdul de lectura RFID.

___

### Codi i Funcionament

```cpp
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5  // ESP32 pin GIOP5 
#define RST_PIN 27 // ESP32 pin GIOP27 

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));

      // print UID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
}
```

Primer afegim les llibreries de SPI.h i MFRC522.h, després definim els corresponents pins (5, 27) i un objecte pel dispositiu.

A continuació en el void setup iniciem la comunicació i el bus SPI, la funcio mfrc522.PCD_Init() inicia el dispositiu, finalment s'imprimeix per pantalla un missatge que informa que s'esta fent una lectura.

Per acabar, a dins el void loop es comproba si hi ha alguna tarjeta present, i en cas de que així sigui es busca de fora serial el seu UID amb un bucle for i s'imprimeix per pantalla.

___