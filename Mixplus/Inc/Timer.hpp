
#include "main.h"
#include "tim.h"

typedef void(*OnTickListener)();

class Timer
{
private:
    TIM_HandleTypeDef* tim;
    OnTickListener tick;

    friend void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
public:
    explicit Timer(TIM_HandleTypeDef* t);
    explicit Timer(TIM_HandleTypeDef* t,int arr);

    static void delay(int t);
    void ontick(OnTickListener CallBack);
    void start();
    void stop();
    unsigned int getcounter();
    void reset();
    void setcounter(unsigned int c);

    void freq(int clockfreq,int f);
    void circle(int c);
};

std::map<TIM_HandleTypeDef *,Timer *> Launched_Tim;

void Timer::delay(int t) {
    HAL_Delay(t);
}

Timer::Timer(TIM_HandleTypeDef *t) {
    this->tim=t;
    Launched_Tim.insert(std::make_pair(t,this));
}

Timer::Timer(TIM_HandleTypeDef *t, int arr) {
    this->tim=t;

    this->tim->Instance->ARR = arr;
    Launched_Tim.insert(std::make_pair(t,this));
}

void Timer::ontick(OnTickListener CallBack) {
    tick = CallBack;
}

void Timer::start() {
    HAL_TIM_Base_Start_IT(tim);
}

void Timer::stop() {
    HAL_TIM_Base_Stop_IT(tim);
}

unsigned int Timer::getcounter()
{
    return __HAL_TIM_GET_COUNTER(tim);
}

void Timer::setcounter(unsigned int c)
{
    __HAL_TIM_SET_COUNTER(tim, c);
}

void Timer::reset()
{
    this->setcounter(0);
}

void Timer::freq(int clockfreq, int f)
{
    int p = (clockfreq * 1000000) / f;
    if(p>65535)return;

    tim->Instance->PSC = p - 1;
    this->setcounter(tim->Instance->ARR);
}

void Timer::circle(int c)
{
    tim->Instance->ARR = c;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    Launched_Tim[htim]->tick();
}