# 核心库 MD_MAX72XX
这是库的核心类，封装了所有与 MAX72XX 设备交互的方法和属性。通过这个类，用户可以方便地控制 LED 矩阵的显示效果。\

## 枚举类型
* moduleType_t：定义了不同类型的硬件模块，如 GENERIC_HW、FC16_HW 等。用户可以根据实际使用的硬件模块选择合适的类型。
* controlRequest_t：用于指定对设备的控制请求，如 SHUTDOWN、SCANLIMIT、INTENSITY 等。这些请求可以控制设备的各种参数。
* controlValue_t：定义了控制请求的 ON/OFF 状态，即 OFF 和 ON。
* transformType_t：用于指定对显示数据的变换类型，如 TSL（左移）、TSR（右移）、TFLR（左右翻转）等。

## 构造函数
* MD_MAX72XX(moduleType_t mod, int8_t dataPin, int8_t clkPin, int8_t csPin, uint8_t numDevices=1)：使用任意数字接口初始化对象。
* MD_MAX72XX(moduleType_t mod, int8_t csPin, uint8_t numDevices=1)：使用默认的 SPI 硬件接口初始化对象。
* MD_MAX72XX(moduleType_t mod, SPIClass &spi, int8_t csPin, uint8_t numDevices = 1)：指定 SPI 硬件接口初始化对象，适用于有多个硬件 SPI 接口的架构。

## 主要方法 (mx.)
### 控制方法
* control(uint8_t dev, controlRequest_t mode, int value)：设置指定设备的控制状态。
* control(controlRequest_t mode, int value)：设置所有设备的控制状态。
* control(uint8_t startDev, uint8_t endDev, controlRequest_t mode, int value)：设置连续子集设备的控制状态。
### 图形和位图方法
* clear()：清除所有显示设备的显示数据。
* getBuffer(uint16_t col, uint8_t size, uint8_t *pd)：从显示缓冲区读取位图数据到用户缓冲区。
* setBuffer(uint16_t col, uint8_t size, uint8_t *pd)：将用户缓冲区的位图数据加载到显示缓冲区。
* getColumn(uint16_t c)：获取指定列的 LED 状态。
* setColumn(uint16_t c, uint8_t value)：设置指定列的 LED 状态。
* getPoint(uint8_t r, uint16_t c)：获取指定像素点的 LED 状态。
* setPoint(uint8_t r, uint16_t c, bool state)：设置指定像素点的 LED 状态。
### 设备管理方法
* clear(uint8_t buf)：清除指定缓冲区的显示数据。
* getColumn(uint8_t buf, uint8_t c)：获取指定缓冲区中指定列的 LED 状态。
* getRow(uint8_t buf, uint8_t r)：获取指定缓冲区中指定行的 LED 状态。
* setColumn(uint8_t buf, uint8_t c, uint8_t value)：设置指定缓冲区中指定列的 LED 状态。
* setRow(uint8_t buf, uint8_t r, uint8_t value)：设置指定缓冲区中指定行的 LED 状态。
* transform(uint8_t buf, transformType_t ttype)：对指定设备的显示数据进行变换。
* update(uint8_t buf)：强制更新指定缓冲区的显示。
### 字体和字符方法（仅当 USE_LOCAL_FONT 为 1 时可用）
* getChar(uint16_t c, uint8_t size, uint8_t *buf)：从字体数据中加载字符到用户缓冲区。
* setChar(uint16_t col, uint16_t c)：将字符从字体表直接加载到显示的指定列。
* setFont(fontType_t *f)：设置当前字体表。
* getMaxFontWidth(void)：获取当前字体中最宽字符的宽度。
* getFontHeight(void)：获取当前字体的字符高度。
* getFont(void)：获取当前字体表的指针。
### 私有方法和属性
* spiSend(void)：执行实际的物理通信任务。
* spiClearBuffer(void)：清除 SPI 发送缓冲区。
* controlHardware(uint8_t dev, controlRequest_t mode, int value)：设置硬件控制命令。
* controlLibrary(controlRequest_t mode, int value)：设置内部控制命令。
* flushBuffer(uint8_t buf)：确定并传输一个设备需要发送的数据。
* flushBufferAll(void)：确定并传输所有设备需要发送的数据。


## 示例代码
使用 MD_MAX72XX 库控制 LED 矩阵

`#include <MD_MAX72xx.h>`

`#define HARDWARE_TYPE MD_MAX72XX::FC16_HW`//定义使用的硬件模块类型
`#define CS_PIN 10`// 定义 CS 引脚
`#define NUM_DEVICES 1`// 定义设备数量

`MD_MAX72XX mx(HARDWARE_TYPE, CS_PIN, NUM_DEVICES);`// 创建 MD_MAX72XX 对象

``` cpp
void setup() 
{
  mx.begin();// 初始化对象
  
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);// 设置显示亮度为最大值的一半

  mx.clear();// 清除显示数据
}

void loop() 
{
  mx.setColumn(0, 0xFF);// 设置第一列的所有 LED 为点亮状态 机器码为1111 1111
  delay(1000);
  
  mx.clear();// 清除显示数据
  delay(1000);
} 
```


# MD_Parola 
基于 MD_MAX72xx 库，专门用于控制由 MAX7219 或 MAX7221 驱动的 8x8 LED 点阵显示屏来显示文本和动画效果。
## 核心类
Parola 库的核心是MD_Parola类，该类可以管理一个或多个显示区域（zones），每个区域可以独立设置文本、动画效果、速度等参数。
## 构造函数
* MD_Parola(MD_MAX72XX::moduleType_t mod, uint8_t dataPin, uint8_t clkPin, uint8_t csPin, uint8_t numDevices = 1):任意输出引脚
* MD_Parola(MD_MAX72XX::moduleType_t mod, uint8_t csPin, uint8_t numDevices = 1) :默认SPI引脚
* MD_Parola(MD_MAX72XX::moduleType_t mod, SPIClass &spi, uint8_t csPin, uint8_t numDevices = 1) ：指定SPI引脚
  
## 使用
### 初始化
`bool begin(void);` // 创建一个覆盖整个显示屏的区域
`bool begin(uint8_t numZones);` // 指定区域的数量

### 核心控制方法
1. 动画显示
* displayAnimate()方法用于动画显示所有区域的文本，需要在循环中频繁调用以确保动画流畅：
`bool displayAnimate(void); `//  返回值表示是否有区域完成动画
2. 区域状态检查
* getZoneStatus()方法用于检查指定区域的动画是否完成：
`bool getZoneStatus(uint8_t z);`(检查的指定区域编号)
3. 清除和重置显示
* void displayClear(void); // 清除所有区域
* void displayClear(uint8_t z); // 清除指定区域
* void displayReset(void); // 重置所有区域的动画
* void displayReset(uint8_t z); // 重置指定区域的动画
4. 关闭和暂停显示
* void displayShutdown(bool b); // 关闭或恢复显示硬件(bool为1，关闭；bool为0，恢复)
* void displaySuspend(bool b); // 暂停或恢复显示更新
5. 区域设置
* void getZone(uint8_t z, uint8_t &moduleStart, uint8_t &moduleEnd); // 获取指定区域的模块范围
* bool setZone(uint8_t z, uint8_t moduleStart, uint8_t moduleEnd); // 设置指定区域的模块范围
### 快速启动方法
1. 滚动文本显示
* void displayScroll(const char *pText, textPosition_t align, textEffect_t effect, uint16_t speed);
align：**PA_LEFT**：左对齐，文本从显示区域的左侧开始显示。**PA_CENTER**：居中对齐，文本在显示区域中居中显示。**PA_RIGHT**：右对齐，文本从显示区域的右侧开始显示。
effect：**PA_SCROLL_LEFT**：文本从右向左滚动进入。**PA_SCROLL_RIGHT**：文本从左向右滚动进入。**PA_SCROLL_UP**：文本从下向上滚动进入。**PA_SCROLL_DOWN**：文本从上向下滚动进入。**PA_OPENING**：文本从中间向两边展开进入。
**PA_CLOSING**：文本从两边向中间收缩进入。**PA_PRINT**：文本直接显示，无动画效果进入。
1. 静态文本显示
* void displayText(const char *pText, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut = PA_NO_EFFECT);
1. 区域文本显示
*void displayZoneText(uint8_t z, const char *pText, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut = PA_NO_EFFECT);
### 显示调整方法
1. 获取和设置字符间距
* uint8_t getCharSpacing(void); // 获取单个区域的字符间距
* uint8_t getCharSpacing(uint8_t z); // 获取指定区域的字符间距
* void setCharSpacing(uint8_t cs); // 设置所有区域的字符间距
* void setCharSpacing(uint8_t z, uint8_t cs); // 设置指定区域的字符间距
1. 获取和设置显示反转
* bool getInvert(void); // 获取单个区域的显示反转状态
* bool getInvert(uint8_t z); // 获取指定区域的显示反转状态
* void setInvert(uint8_t invert); // 设置所有区域的显示反转
* void setInvert(uint8_t z, uint8_t invert); // 设置指定区域的显示反转
1. 获取和设置显示亮度
* uint8_t getIntensity(void); // 获取单个区域的显示亮度
* uint8_t getIntensity(uint8_t z); // 获取指定区域的显示亮度
* void setIntensity(uint8_t intensity); // 设置所有区域的显示亮度
* void setIntensity(uint8_t z, uint8_t intensity); // 设置指定区域的显示亮度
1. 获取和设置暂停时间
* uint16_t getPause(void); // 获取单个区域的暂停时间
* uint16_t getPause(uint8_t z); // 获取指定区域的暂停时间
* void setPause(uint16_t pause); // 设置所有区域的暂停时间
* void setPause(uint8_t z, uint16_t pause); // 设置指定区域的暂停时间
1. 获取和设置滚动间距
* uint16_t getScrollSpacing(void); // 获取单个区域的滚动间距
* void setScrollSpacing(uint16_t space); // 设置所有区域的滚动间距
1. 获取和设置动画速度
* uint16_t getSpeed(void); // 获取单个区域的动画速度
* uint16_t getSpeed(uint8_t z); // 获取指定区域的动画速度
* uint16_t getSpeedIn(uint8_t z); // 获取指定区域的进入动画速度
* uint16_t getSpeedOut(uint8_t z); // 获取指定区域的退出动画速度
* void setSpeed(uint16_t speed); // 设置所有区域的动画速度
* void setSpeedInOut(uint16_t speedIn, uint16_t speedOut); // 设置所有区域的进入和退出动画速度
* void setSpeed(uint8_t z, uint16_t speed); // 设置指定区域的动画速度
* void setSpeedInOut(uint8_t z, uint16_t speedIn, uint16_t speedOut); // 设置指定区域的进入和退出动画速度
1. 获取和设置文本对齐方式
* textPosition_t getTextAlignment(void); // 获取单个区域的文本对齐方式
* textPosition_t getTextAlignment(uint8_t z); // 获取指定区域的文本对齐方式
* void setTextAlignment(textPosition_t ta); // 设置所有区域的文本对齐方式
* void setTextAlignment(uint8_t z, textPosition_t ta); // 设置指定区域的文本对齐方式
1. 获取和设置文本缓冲区
* void setTextBuffer(const char *pb); // 设置单个区域的文本缓冲区
* void setTextBuffer(uint8_t z, const char *pb); // 设置指定区域的文本缓冲区
1. 获取和设置文本效果
* void setTextEffect(textEffect_t effectIn, textEffect_t effectOut); // 设置所有区域的进入和退出文本效果
* void setTextEffect(uint8_t z, textEffect_t effectIn, textEffect_t effectOut); // 设置指定区域的进入和退出文本效果
1.  获取和设置区域效果
* boolean getZoneEffect(uint8_t z, zoneEffect_t ze); // 获取指定区域的效果状态
* void setZoneEffect(uint8_t z, boolean b, zoneEffect_t ze); // 设置指定区域的效果状态

## 示例代码
使用 Parola 库在 LED 点阵显示屏上显示滚动文本：
```cpp
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

// 定义硬件连接
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define DATA_PIN  12
#define CLK_PIN   11
#define CS_PIN    10
#define MAX_DEVICES 4

// 创建MD_Parola对象
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  
  P.begin();// 初始化对象
  
  P.displayScroll("Hello, World!", PA_LEFT, PA_SCROLL_LEFT, 100);// 设置滚动文本
}

void loop() {

  if (P.displayAnimate()) {
    P.displayReset();// 当动画完成时，可以重置或更新文本
  }
}
```