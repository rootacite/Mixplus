
#include "mixplus.h"
#include "Serial.hpp"
#include "Timer.hpp"

#include <list>
#include <string>

using namespace std;


Timer* Timer1 = nullptr;
GPIO* PB12 = nullptr;

void setup()
{
    Timer1 = new Timer(&htim2);   //初始化定时器
    PB12 = new GPIO(GPIOB, GPIO_PIN_12);  //初始化IO口

    Timer1->freq(96, 2000);   //将频率设置为2000Hz，96是时钟主频96MHz，根据时钟树设置调整
    Timer1->circle(2000);     //每隔2000定时器周期触发一起ontick
    Timer1->ontick([]()       //用Lambda 表达式注册事件
        {
            //这两行代码每1s会被执行一次
            Serial1->writeline("Catched.");   //串口输出Catched.
            PB12->set(!PB12->get());          //翻转PB12
        });
    Timer1->start();          //开启定时器

}

void loop() {

}