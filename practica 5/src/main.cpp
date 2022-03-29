#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  



void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operación */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Presion oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtrado. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tiempo Standby. */
}

void loop(){
    Serial.print(F("Temperatura = "));
    float temp = bmp.readTemperature();
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Presión = "));
    float pressure = bmp.readPressure();
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Altitud = "));
    float alt = bmp.readAltitude(1013.25);
    Serial.print(bmp.readAltitude(1013.25));
    Serial.println(" m");

    Serial.println();
    delay(2000);

  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("temperatura: ");
  lcd.print(temp);
  // set cursor to first column, second row
  lcd.setCursor(0,2);
  lcd.print("pressure: ");
  lcd.print(pressure);
  // set cursor to first column, third row
  lcd.setCursor(0,4);
  lcd.print("altitude: ");
  lcd.print(alt); 
}