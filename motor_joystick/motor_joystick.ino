// 电机PWM信号引脚
const int forward_pin = 45;
const int reverse_pin = 46;

// 频率15kHz，8位分辨率
const int frequency = 15000;
const int resolution = 8;
const int forward_ch = 0;
const int reverse_ch = 1;

// 摇杆X轴的ADC输入引脚
const int x_pin = 1;

void setup() 
{
  // 配置反转PWM通道：频率15kHz，8位分辨率
  ledcSetup(reverse_ch, frequency, resolution);
  ledcAttachPin(reverse_pin, reverse_ch);
  
  // 配置正转PWM通道：频率15kHz，8位分辨率
  ledcSetup(forward_ch, frequency, resolution);
  ledcAttachPin(forward_pin, forward_ch);
  
  // 设置模拟输入引脚
  pinMode(x_pin, INPUT);
}

void loop() 
{
  // 读取模拟输入值(范围0-4095)
  int x_value = analogRead(x_pin);
  
  // 将模拟输入值映射到PWM范围(0-255)
  int pos = x_value*255/4095;
  
  // 计算PWM占空比：
  // pos*2得到范围(0-510)
  // 减去255得到范围(-255到+255)
  int duty = pos*2 - 255;

  if( duty > 0 )  // 正值表示正转
  {
    ledcWrite(forward_ch, duty);    // 正转通道输出对应占空比
    ledcWrite(reverse_ch, 0);       // 反转通道停止
  }
  else if( duty < 0 )  // 负值表示反转
  {
    ledcWrite(forward_ch, 0);       // 正转通道停止
    ledcWrite(reverse_ch, -duty);   // 反转通道输出对应占空比的绝对值
  }
  else if( duty == 0 )  // 零值表示停止
  {
    ledcWrite(forward_ch, 0);       // 正转通道停止
    ledcWrite(reverse_ch, 0);       // 反转通道停止
  }
  delay(100);
}
