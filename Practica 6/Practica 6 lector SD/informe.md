# PROCESSADORS DIGITALS
##  INFORME PRACTICA 6: MEMORIA SD
___

### Introduccio
Funcionament de la lectura d'una tarjeta SD.

___

### Codi i Funcionament
```cpp
#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
 
  myFile = SD.open("archivo.txt");//abrimos  el archivo 
  if (myFile) {
    Serial.println("archivo.txt:");
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    myFile.close(); //cerramos el archivo
  } else {
    Serial.println("Error al abrir el archivo");
  }
}

void loop()
{}
```

Primer afegim les llibreries d'Arduino, SPI i SD, després creem una variable de tipo File anomenada "myFile".

A continuació, a dins el void setup inicialitzem el Serial i la SD, amb la condició de que si no es pot inicialitzar la SD es mostri un missatge d'error "No se pudo inicializar" o en cas de que sí es pugui inicialitzar, el missatge "Inicializacion exitosa". Tot seguit, assignem  a la variable myFile el arxiu que es troba dins la targeta SD que s'ha llegit anteriorment i creem un bucle per que mostri per pantalla tot el que es trobi dins d'aquest arxiu.

Finalment, el void loop queda buit.
___