
#include "main.h"
#include "adc.h"

#include <vector>

class Analog
{
private:
    ADC_HandleTypeDef* adc;
    int count_of_channels;

public:
    explicit Analog(ADC_HandleTypeDef* a,int cc);

    std::vector<uint16_t> get();
};

Analog::Analog(ADC_HandleTypeDef *a, int cc)
{
    this->count_of_channels=cc;
    this->adc=a;
}

std::vector<uint16_t> Analog::get()
{
    std::vector<uint16_t> r;

    for(int i =0;i<count_of_channels;i++)
    {
        HAL_ADC_Start(adc);
        HAL_ADC_PollForConversion(adc,0xFFFF);

        if(HAL_IS_BIT_SET(HAL_ADC_GetState(adc),HAL_ADC_STATE_REG_EOC)){
            r.push_back(HAL_ADC_GetValue(adc));
        }
    }

    return r;
}