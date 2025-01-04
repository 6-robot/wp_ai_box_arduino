#ifndef XYFUN_HELPER_H
#define XYFUN_HELPER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>
#include <base64.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

void xfyun_init();
void xfyun_iat(int16_t* record_data, int data_length, const char* appID, const char* apiSecret, const char* apiKey);
String xfyun_get_result();

void xfyun_tts(String text,const char* voiceName, const char* appID, const char* apiSecret, const char* apiKey);
void xfyun_tts_spin();

#endif // XYFUN_HELPER_H