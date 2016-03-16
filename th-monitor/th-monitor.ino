#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "LowPower.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define pinDHT 2
#define DHTTYPE DHT22
DHT dht(pinDHT, DHTTYPE);
float h,t;
void setup(){

  Serial.begin(19200);

  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("TH Monitor");
  display.setCursor(0,17);
  display.println("DrMaker.es");
}

void loop(){
  Serial.println("Wake up!");
  checkTH();
  print(t,h);
  Serial.println("Going to sleep...");
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

}

void print(float _t, float _h){
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(_t);
  display.setCursor(70,0);
  display.print("C");
  display.setCursor(0,17);
  display.print(_h);
  display.setCursor(70,17);
  display.print("% HR");
  display.display();
}
void checkTH(){
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }else{
    Serial.print("t=");
    Serial.print(t);
    Serial.print("\t h=");
    Serial.println(h);
  }
}
