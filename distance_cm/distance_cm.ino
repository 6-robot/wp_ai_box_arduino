#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(320,480);

// 初始化函数
void setup() {
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(1);
  tft.setTextSize(3);
  tft.fillScreen(TFT_RED);

  pinMode(3, INPUT);
}

// 传感器的 ADC 数值与距离的关系
float getDistance(int adc) {
  float v = (float)adc * 3.3f / 4095.0f;
  
  if (v >= 1.58f) return 6.0f;
  if (v >= 1.15f) return 6.0f + (1.58f - v) * (10.0f - 6.0f) / (1.58f - 1.15f);
  if (v >= 0.65f) return 10.0f + (1.15f - v) * (20.0f - 10.0f) / (1.15f - 0.65f);
  if (v >= 0.46f) return 20.0f + (0.65f - v) * (30.0f - 20.0f) / (0.65f - 0.46f);
  if (v >= 0.37f) return 30.0f + (0.46f - v) * (40.0f - 30.0f) / (0.46f - 0.37f);
  if (v >= 0.30f) return 40.0f + (0.37f - v) * (50.0f - 40.0f) / (0.37f - 0.30f);
  if (v >= 0.25f) return 50.0f + (0.30f - v) * (60.0f - 50.0f) / (0.30f - 0.25f);
  if (v >= 0.22f) return 60.0f + (0.25f - v) * (70.0f - 60.0f) / (0.25f - 0.22f);
  if (v >= 0.20f) return 70.0f + (0.22f - v) * (80.0f - 70.0f) / (0.22f - 0.20f);
  return 80.0f;
}

char text[20];
// 循环函数
void loop() {
  int dist_adc = analogRead(3);

  // 测距传感器的 ADC 数值
  sprintf(text, "dist_adc = %04d", dist_adc);
  tft.setCursor(0, 0);
  tft.print(text);

  // 测距传感器的电压测量值
  float voltage = (float)dist_adc * 3.3f / 4095.0f;
  sprintf(text, "voltage = %03.2f v", voltage);
  tft.setCursor(0, 30);
  tft.print(text);

  // 测距传感器的距离值
  float dist = getDistance(dist_adc);
  sprintf(text, "dist = %03.2f cm", dist);
  tft.setCursor(0, 60);
  tft.print(text);

  delay(100);
}