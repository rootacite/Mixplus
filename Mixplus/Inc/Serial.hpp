
#include "main.h"
#include "usart.h"
#include "Buffer.hpp"

class Serial : public Buffer<char>
{
private:
    UART_HandleTypeDef *uart;
    friend void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

public:
    Serial(UART_HandleTypeDef *t);

    bool available();
    void begin();

    char read();
    void read(int c,char *buf);

    void write(char c);
    void write(char *c,int length);
};

uint8_t cc_serial[1];
Serial * Launched_Dic[8] = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};
int _pos_of_uart=0;

Serial::Serial(UART_HandleTypeDef* t) : Buffer<char>(512)
{
    this->uart = t;
    Launched_Dic[_pos_of_uart] = this;
    _pos_of_uart++;
}

void Serial::begin()
{
    HAL_UART_Receive_IT(uart,cc_serial,1);
}


bool Serial::available()
{
    return this->buffered_size() > 0;
}


void Serial::read(int c,char *buf)
{
    int _p=0;

    while(_p < c)
    {
        if(this->available())
        {
            buf[_p]=this->read();
            _p++;
        }
    }
}

char Serial::read()
{
    while(!this->available()){}

    return pop();
}

void Serial::write(char c)
{
    uint8_t cc = c;
    HAL_UART_Transmit(this->uart,&cc,1,0xFFFF);
}

void Serial::write(char *c,int length)
{
    HAL_UART_Transmit(this->uart,(uint8_t*)c,length,0xFFFF);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    for(Serial* i : Launched_Dic)
    {
        if(i->uart ==  huart)
        {
            i->push(cc_serial[0]);
        }
    }

    HAL_UART_Receive_IT(huart,cc_serial,1);
}
