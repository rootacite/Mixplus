
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
    Timer1 = new Timer(&htim2);   //��ʼ����ʱ��
    PB12 = new GPIO(GPIOB, GPIO_PIN_12);  //��ʼ��IO��

    Timer1->freq(96, 2000);   //��Ƶ������Ϊ2000Hz��96��ʱ����Ƶ96MHz������ʱ�������õ���
    Timer1->circle(2000);     //ÿ��2000��ʱ�����ڴ���һ��ontick
    Timer1->ontick([]()       //��Lambda ���ʽע���¼�
        {
            //�����д���ÿ1s�ᱻִ��һ��
            Serial1->writeline("Catched.");   //�������Catched.
            PB12->set(!PB12->get());          //��תPB12
        });
    Timer1->start();          //������ʱ��

}

void loop() {

}