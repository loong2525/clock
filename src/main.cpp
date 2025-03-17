#include <GetTime.h>
#include <AnimationText.h>

const char* ssid = "loong的电子节点";    //WIFI名称
const char* password = "shijinjia";     //WIFI密码
const char* message = "Hello my dear : with a will , you can achieve anything ..........";

AnimationText animText(message, PA_SCROLL_LEFT, PA_NO_EFFECT);//选择文本动画效果
/*      PA_SCROLL_LEFT：文本从右向左滚动进入或退出。
        PA_SCROLL_RIGHT：文本从左向右滚动进入或退出。
        PA_SCROLL_UP：文本从下向上滚动进入或退出。
        PA_SCROLL_DOWN：文本从上向下滚动进入或退出。
        PA_DISSOLVE：文本逐渐溶解显示或消失。
        PA_OPENING：文本像开门一样从中间向两边展开显示或从两边向中间闭合消失。
        PA_CLOSING：与 PA_OPENING 相反，文本从两边向中间闭合显示或从中间向两边展开消失。 
*/
GetTime timeGetter(ssid, password);

void setup() {
    animText.begin();
    timeGetter.begin();
}

void loop() {
    if (animText.loop()) 
    {
        timeGetter.showTime(animText.getDisplay());
    }
}