# PROCESSADORS DIGITALS

## INFORME PRACTICA 4

___ 

### Introduccio

L'objectiu d'aquesta pràctica es princincialment aprendre a utilitzar les tasques, després hi ha un exercici pràctic per simular la funció d'un semàfor.

___

### Codi i Funcionament tasques

```cpp
#include <Arduino.h>
void anotherTask( void * parameter )
{
/* loop forever */
for(;;)
{
Serial.println("this is another Task");
delay(1000);
}

/* delete a task when finish,
this will never happen because this is infinity loop */
vTaskDelete( NULL );
}

void setup()
{
Serial.begin(112500);
/* we create a new task here */
xTaskCreate(
anotherTask, /* Task function. */
"another Task", /* name of task. */
10000, /* Stack size of task */
NULL, /* parameter of the task */
1, /* priority of the task */
NULL); /* Task handle to keep track of created task */
}
/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop()
{
Serial.println("this is ESP32 Task");
delay(1000);
}
```

Primer afegim la llibreria d'Arduino, després creem una funció anomenada "void AnotherTask" per crear una taska nova. En aquesta funció hi ha un bucle on es mostra el missatge "This is another task", per parar aquest bucle s'utilitza la funció vTaskDelete, que tal com ja hem comentat s'encarrega d'aturar la tasca un cop hagi finalitzat.

Seguidament, a dins del void setup creem una nova tasca utilitzant la funció void AnotherTask esmentada anteriorment, el nom d'aquesta taska serà "Another Task".

Finalment en el void loop s'imprimeix per pantalla "Ehis is ESP32 Task" amb un temps de delay de 1 segon (1000 ms).

___

### Codi i Funcionament Semàfor

```cpp
#include <Arduino.h>
long debouncing_time = 150; 
volatile unsigned long last_micros;
 
SemaphoreHandle_t interruptSemaphore;
void interruptHandler() {
  xSemaphoreGiveFromISR(interruptSemaphore, NULL);
}
 
void TaskLed(void *pvParameters)
{
  (void) pvParameters;
  pinMode(8, OUTPUT);
  for (;;) {
    if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
      digitalWrite(8, !digitalRead(8));
    }
  }
}
void TaskBlink(void *pvParameters)
{
  (void) pvParameters;
  pinMode(7, OUTPUT);
  for (;;) {
      digitalWrite(7, HIGH);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      digitalWrite(7, LOW);
      vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}
void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    interruptHandler();
    last_micros = micros();
  }
}
 
void setup() {
  pinMode(2, INPUT_PULLUP);
  xTaskCreate(TaskLed,  "Led", 128, NULL, 0, NULL );
xTaskCreate(TaskBlink,  "LedBlink", 128, NULL, 0, NULL );
  interruptSemaphore = xSemaphoreCreateBinary();
  if (interruptSemaphore != NULL) {
    attachInterrupt(digitalPinToInterrupt(2), debounceInterrupt, LOW);
  }
}
 
void loop() {}
```

Primer afegim la llibreria d'Arduino, després declarem el temps de rebot "long debouncing_time = 150", i declarem un altre paràmetre "SemaphoreHandle_t interruptSemaphore" on s'hi gurdaran les dades del semàfor.

Seguidament declarem quatre funcions:
- void interruptHandler(): on es crida a una altre funció anomenada "xSemaphoreGiveFromISR" que s'encarrega d'encendre el LED quan TaskLed li demani.
- void debounceInterrupt(): Aquesta funció s'encarrega d'implementar el ISR , es a dir, s'encarrega de que la interrupció del LED funcioni correctament.
- void TaskLed(): En aquesta funció definim un LED assignat al pin 8 amb un bucle que s'encarrega d'encendre'l i apagar-lo quan pertoqui.
- void TaskBlink(): Assignem un altre LED al pin 7 amb un bucle que fa que aquest LED s'encengui i s'apagui cada 2 segons.

Finalment en el void setup assignem al pin 2 el interruptor i creem dues tasques les quals criden a les funcions TaskLed i TaskBlink. També cridem a la funció xSemaphoreCreateBinary() per crear un semàfor. El void loop és buit, no hi ha contingut.
___