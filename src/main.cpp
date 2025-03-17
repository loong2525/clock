#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// 定义硬件连接
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CS_PIN 5  // 根据实际连接修改CS引脚
#define MAX_DEVICES 4

// 创建 MD_Parola 对象
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// 要显示的文本
const char* message = "Hello my dear : with a will , you can achieve anything ..........";

// NTP相关配置
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 28800, 60000); // 根据需要修改NTP服务器和偏移量

// 格式化时间字符串
char timeStr[6];

void setup() {
  // 初始化串口
  Serial.begin(115200);
  
  // 初始化WiFi
  WiFi.begin("loong的电子节点", "shijinjia"); // 修改为你的WiFi名称和密码
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // 初始化 Parola 库
  if (!P.begin()) {
    // 初始化失败，进入无限循环
    while (1);
  }

  // 设置最高亮度
  P.setIntensity(15);

  // 设置文本效果
  P.setTextEffect(PA_SCROLL_LEFT, PA_NO_EFFECT);

  // 设置文本对齐方式
  P.setTextAlignment(PA_LEFT);

  // 设置滚动速度
  P.setSpeed(200);

  // 设置暂停时间
  P.setPause(1000);

  // 显示文本
  P.displayText(message, PA_LEFT, 100, 1000, PA_SCROLL_LEFT, PA_NO_EFFECT);
  
  // 初始化NTP客户端
  timeClient.begin();
}

void loop() {
  // 开启字符滚动
  if (P.displayAnimate()) {
    // 文本动画结束，获取并显示时间
    if (timeClient.update()) {
      int hours = timeClient.getHours();
      int minutes = timeClient.getMinutes();
      sprintf(timeStr, " %02d:%02d ", hours, minutes);
      P.displayText(timeStr, PA_LEFT, 100, 1000, PA_NO_EFFECT, PA_NO_EFFECT);
      while (P.displayAnimate()); // 显示时间直到动画结束
    }
    // 更新显示
    P.displayReset();
  }
}