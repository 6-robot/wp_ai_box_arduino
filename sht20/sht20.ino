#include <TFT_eSPI.h>
#include <Wire.h>
#include <DFRobot_SHT20.h>

TFT_eSPI tft = TFT_eSPI(320,480);

#define I2C_SDA 9  
#define I2C_SCL 10  

TwoWire I2C_0 = TwoWire(0);  
DFRobot_SHT20 sht20(&I2C_0);

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(1);
  tft.setTextSize(3);
  tft.fillScreen(TFT_RED);

  I2C_0.begin(I2C_SDA, I2C_SCL);
  sht20.initSHT20();
  delay(100);
  sht20.checkSHT20();
}

void loop() {
  tft.setCursor(0, 0);
  tft.print("Temperature : ");
  tft.print(sht20.readTemperature());
  tft.println(" C");
  tft.print("Humidity : ");
  tft.print(sht20.readHumidity());
  tft.println(" %");
}