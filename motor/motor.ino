const int forward_pin = 45;
const int reverse_pin = 46;

const int frequency = 15000;
const int resolution = 8;
const int forward_ch = 0;
const int reverse_ch = 1;

void setup() 
{
  ledcSetup(reverse_ch, frequency, resolution);
  ledcAttachPin(reverse_pin, reverse_ch);
  
  ledcSetup(forward_ch, frequency, resolution);
  ledcAttachPin(forward_pin, forward_ch);
}

void loop() 
{
    ledcWrite(forward_ch, 150);
    ledcWrite(reverse_ch, 0);
    delay(3000);
    ledcWrite(forward_ch, 0);
    ledcWrite(reverse_ch, 0);
    delay(2000);
    ledcWrite(forward_ch, 0);
    ledcWrite(reverse_ch, 150);
    delay(3000);
    ledcWrite(forward_ch, 0);
    ledcWrite(reverse_ch, 0);
    delay(2000);
}