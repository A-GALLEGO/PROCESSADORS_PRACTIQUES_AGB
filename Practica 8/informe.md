# PROCESSADORS DIGITALS
## INFORME PRACTICA 8 
___
### Introduccio
Generear un bucle que envii dades del terminal rxd0 a la UART2 txd2 i que la recepció de les dades s'enviin a la sortida txd0.

### Codi i Funcionament
``` cpp
#include <Arduino.h>
#define RXD2 16
#define TXD2 17

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
}

void loop()
{
  while (Serial2.available()) 
  {
    Serial.print(char(Serial2.read()));
  }
  while (Serial.available())
  {
    Serial2.print(char(Serial.read()));
  }
}
```

Primer, afegim l allibreria d'Arduino i definim els pins corresponents per poder realitzar la comunicació UART2.

A continuació es conecten els ports RXD0 amb el TXD2 i a la vegada el TXD2 al TXD0.

Finalment es llegeix el contingut de les conexions esmentades fins a arribar a la sortida TXD0.

___