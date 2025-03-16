#include <MD_Parola.h>
#include <MD_MAX72xx.h>

// 定义硬件连接
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CS_PIN 5  // 根据实际连接修改CS引脚
#define MAX_DEVICES 4

// 创建 MD_Parola 对象
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// 要显示的文本
const char* message = "Hello my dear , I want to say : With a will , you can achieve anything ............         ";

void setup() {
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
}

void loop() {
  // 开启字符滚动
  if (P.displayAnimate()) {
    // 更新显示
    P.displayReset();
  }
}