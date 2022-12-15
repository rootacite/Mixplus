
#include <stdio.h>
#include <string.h>
#include "mixplus.h"
#include "Serial.hpp"
//#include "Buffer.hpp"
#include "Timer.hpp"
#include "GPIO.hpp"
#include "Exti.hpp"
#include "Analog.hpp"



Timer Timer1(&htim2);   //��ʼ����ʱ��
GPIO PB12(GPIOB, GPIO_PIN_12);  //��ʼ��IO��
Serial Serial1(&huart1);
AnalogDMA Adc1(&hadc1,4);


void setup()
{
    //Serial1 = new Serial(&huart1);
    Serial1.begin();
    Adc1.begin();
    Timer1.freq(72, 2000);
    Timer1.circle(2000);     //ÿ��2000��ʱ�����ڴ���һ��ontick
    Timer1.ontick([]()       //��Lambda ���ʽע���¼�
        {
            //�����д���ÿ1s�ᱻִ��һ��
            //Serial1->writeline("Catched.");   //�������Catched.

            PB12.toggle();        //��תPB12
        });
             //������ʱ��

    Exti::attachInterrupt(GPIO_PIN_0,[]()
    {
        Timer1.start();
    });

    Exti::attachInterrupt(GPIO_PIN_1,[]()
    {
        char buf[120];
        uint16_t f[4];
        Adc1.get(f);

        sprintf(buf,"A1:%4d,A2:%4d,A3:%4d,A4:%4d \n",f[0],f[1],f[2],f[3]);

        Serial1.write(buf,strlen(buf));
    });
}

void loop() {
    if(Serial1.available())
        Serial1.write(Serial1.read());
}