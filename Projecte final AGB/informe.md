# PROCESSADORS DIGITALS
## INFORME PROJECTE FINAL: MESURADOR DE DISTANCIES VIA ULTRASONIDO
___
### Introduccio
L'objectiu del meu projecte és crear un mesurador de distàncies, es podria utilitzar per exemple, en un ambit cotidià com pot ser a casa mateix en cas de fer mudança, obres... 

___

### Codi i Funcionament
```cpp
#include <Arduino.h>
using namespace std;

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(1000);
}
```

Primer afegim la llibreria d'Arduino, després definim un pin pel trigger i un altre per l'echo. A continuació definim la velocitat del so segons la temperatura ambient, en el meu cas he posat la velocitat a una temperatura de 20 graus. També afegim un canvi d'unitats de cm a inches.

Tot seguit inicialitzem les variables següents:
- long duration; que emmagatzema el temps que tarda la ona d'ultrasò en arribar a l'objecte i tornar.
- float distanceCm; en aquesta variable guardarem la mesura en cm.
- float distanceInch; en aquesta variable guardarem la mesura en Inches.

En el void setup inicialitzem una comunicació serial, i definirem el pin de trigger com un output i el pin de echo com a un input.

Finalment, en el void loop primer canviem l'estat en el pin de trigger a low i fem un delay de 2 microsegons, despres tornem a activar el pin de trigger per que generi una ona nova amb un delay de 10 microsegons.

La variable de duration la igualem a una funció anomenada PulseIn() que comproba si s'ha emès una ona d'ultrasò i en cas afirmatiu retorna el temps que tarda en rebre la ona en microsegons. Un cop ja tenim el temps que tarda, utilitzant les constants definides abans calculem les distancies en Cm i en Inches. 

Per acabar el void loop mostrem les distancies en les dues unitats de mesura, Cm i Inches.

___

