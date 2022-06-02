# PROCESSADORS DIGITALS

## INFORME PRACTICA 1
___
### Introducció
L’objectiu d’aquesta primera pràctica consisteix en encendre i apagar un llum LED en un interval de temps de 500ms.
___

### Components
-	Processador ESP32
-	Llum LED
-	Extensió de Visual Studio Code, Platformmio.
___

### Funcionament i Codi
S’implementa el codi següent que s’encarrega d’encendre i apagar un llum LED:


  
 ```cpp
	#include <Arduino.h>
	

	int led = 1;
	

	void setup() {
	  // put your setup code here, to run once:
	  Serial.begin(9600);
	  pinMode(led, OUTPUT);
	}
	

	void loop() {
	  // put your main code here, to run repeatedly:
	  digitalWrite(led, HIGH);      // Turn the LED on (HIGH is the voltage)
	  delay(500);                // Wait for a second
	  Serial.println("OFF");
	  digitalWrite(led, LOW);       // Turn the LED off by making the voltage
	  delay(500);                // Wait for a second
	  Serial.println("ON");
	}
```

Principalment s’inclou la llibreria Arduino.h, a continuació es defineix una variable anomenada led i s’iguala al número del pin al que conectarem la llum LED.

A continuació implementem la funció Serial.begin(9600) que inicia la comunicació serial a una velocitat de 9600 Bauds per segon. Després també configurem el pin al qual hi anirà conectada la llum LED amb la funció pinMode.

Finalment comença el bucle que permet encendre i apagar la llum LED reiteradament.
Amb la funció digitalWrite establim si la llum LED s’encén(HIGH) o s’apaga (LOW), amb la funció delay(500) indiquem que entre l’acció d’encendre i apagar ha de transcurrir un interval de 500 ms. Per acabar, sempre que s’executi la funció Serial.println  mostrarà en el panell de control un missatge (ON/OFF), depenèn del que hi hagi escrit entre cometes.
___
