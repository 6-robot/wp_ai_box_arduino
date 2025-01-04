#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(320,480);

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(1);
  tft.setTextSize(3);
  tft.fillScreen(TFT_RED);

  pinMode(3, INPUT);
}

char text[20];
void loop() {
  int dist_adc = analogRead(3);

  sprintf(text, "dist_adc = %04d", dist_adc);
  tft.setCursor(0, 0);
  tft.print(text);
}