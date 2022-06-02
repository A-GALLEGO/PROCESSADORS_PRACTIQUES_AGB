# PROCESSADORS DIGITALS
## INFORME PRACTICA 2   

___

### Components
- Processador ESP32
- Extensió de Visual Studio Code, Platformio

___

### Introducció
En aquesta pràctica 2 utilitzarem l'interrupció per GPIO i interrupció per timer.

___ 

## Codi i Funcionament GPIO


```cpp

#include <Arduino.h>

struct Button {
const uint8_t PIN;
uint32_t numberKeyPresses;
bool pressed;
};
Button button1 = {18, 0, false};
void IRAM_ATTR isr() {
button1.numberKeyPresses += 1;
button1.pressed = true;
}
void setup() {
Serial.begin(115200);
pinMode(button1.PIN, INPUT_PULLUP);
attachInterrupt(button1.PIN, isr, FALLING);
}
void loop() {
if (button1.pressed) {
Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
button1.pressed = false;
}
//Detach Interrupt after 1 Minute
static uint32_t lastMillis = 0;
if (millis() - lastMillis > 60000) {
lastMillis = millis();
detachInterrupt(button1.PIN);
Serial.println("Interrupt Detached!");
}
}
```
Primer definim la llibreria d'Arduino i despres creem un struct on definim les variables necessaries per continuar amb el programa.

Seguidament, dins el void setup definim que un cop es premi el interruptor produeixi la interrupció, aquesta es produeix canviant el estat de HIGH a LOW.


Finalment tenim el void loop on shi produiràn dues accions:
La primera consisteix en mostrar per pantalla un contador cada vegada que es prem el interruptor per a fer la interrupció. La segona acció consisteix en que si en un periode de 1 minut (60000 ms) no s'ha premut el interruptor que es detingui la interrupció i es mostri el missatge: "Interrupt Detached!".


___

### Codi i Funcionament Timer

```cpp
#include <Arduino.h>

volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
interruptCounter++;
portEXIT_CRITICAL_ISR(&timerMux);
}
void setup() {
Serial.begin(115200);
timer = timerBegin(0, 80, true);
timerAttachInterrupt(timer, &onTimer, true);
timerAlarmWrite(timer, 1000000, true);
timerAlarmEnable(timer);
}
void loop() {
if (interruptCounter > 0) {
portENTER_CRITICAL(&timerMux);
interruptCounter--;
portEXIT_CRITICAL(&timerMux);
totalInterruptCounter++;
Serial.print("An interrupt as occurred. Total number: ");
Serial.println(totalInterruptCounter);
}
}
```

Principalment es defineix altre vegada la llibreria d'Arduino i despres les variables necessàries per a duur a terme el programa.

Seguidament en el void setup es declara el Timer amb el temps corresponent que hi haurà entre interrupcions.

Finalment en el void loop es defineix un counter per a mantenir un registre de les vegades que s'ha dut a terme aquestes interrupcions i on es mostra per pantalla aquest contador.
