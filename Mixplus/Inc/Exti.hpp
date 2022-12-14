
#include "main.h"
#include <map>

typedef void(*OnExtiCallBack)();

class Exti
{
private:
    friend void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
    OnExtiCallBack CallBack;
    uint16_t Pin;

public:
    Exti(uint16_t Pin,OnExtiCallBack proc);
    ~Exti();
};
std::map<uint16_t,Exti*> CallBackList;

Exti::Exti(uint16_t Pin,OnExtiCallBack proc)
{
    CallBack = proc;
    this->Pin=Pin;
    CallBackList.insert(std::make_pair(Pin,this));
}

Exti::~Exti()
{
    CallBackList.erase(Pin);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(CallBackList.count(GPIO_Pin) == 0)return;

    CallBackList[GPIO_Pin]->CallBack();
}

