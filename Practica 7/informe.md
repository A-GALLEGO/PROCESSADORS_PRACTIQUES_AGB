# PROCESSADORS DIGITALS
## INFORME PRACTICA 7
___

### Introduccio
L'objectiu d'aquest apractica és aprendre i entendre el funcionament del bus I2S.

### Codi i Funcionament
```cpp
#include <Arduino.h>
#include <AudioGeneratorAAC.h>
#include <AudioOutputI2S.h>
#include <AudioFileSourcePROGMEM.h>
#include <sampleaac.h>

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup(){
  Serial.begin(115200);
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out -> SetGain(0.125);
  out -> SetPinout(26,25,22);
  aac->begin(in, out);
}

void loop(){
  if (aac->isRunning()) {
    aac->loop();
    } else {

      aac -> stop();
      Serial.printf("Sound Generator\n");
      delay(1000);
  }
}
```

Primer definim les llibreries necessàries i 3 punters que s'utilitzaran per: llegir el fitxer s'audio, descodificar el fitxer i per enviar de forma analògica l'audio.

En el void setup s'inicialitzen els punters esmentats anteriorment.

end el void loop primer es comprobarà si l'arxiu ha estat descodificat, un cop acabat el procés aquest s'aturarà i generarà el soroll.
___