Mixplus
=======
## Timer类用于操作定时器

范例：
-----
以下代码每隔1s翻转PB12口，并从串口输出Catched.
```cpp
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
```

## PWM类用于生成PWM波

范例：
-----
以下代码在Tim3定时器的1通道点亮呼吸灯

```cpp
PWM *PWM1= nullptr;

void setup() {
    PWM1 = new PWM(&htim3);
}

void loop() {
    for(double i=0;i<0.35;i+=0.01)
    {
        PWM1->pulse(0,i);
        Timer::delay(10);
    }
    for(double i=0.35;i>0;i-=0.01)
    {
        PWM1->pulse(0,i);
        Timer::delay(10);
    }
}
```

## GPIO类用于操作通用IO口

## Analog和AnalogDMA类用于操作ADC

范例：
-----
以下代码每隔500ms，读取一次ADC1的四个通道，并从串口输出

```cpp

Serial* Serial1 = NULL;
AnalogDMA *Adc1= nullptr;

void setup()
{
    Serial1 = new Serial(&huart1);
    Adc1 = new AnalogDMA(&hadc1,4);
}

void loop() {
    HAL_Delay(500);
    auto cv=Adc1->get();

    int cp=0;
    for(uint16_t i : cv)
    {
        string cs="AD";
        cs += to_string(cp);
        cs += ":";
        cs += to_string(i);
        cp++;
        Serial1->writeline(cs);
    }
}
```

## Serial类用于读写串口
Serial(UART_HandleTypeDef *t)
------- 
用串口句柄初始化类。<br>
参数：<br>
t：串口句柄<br>
例:
```cpp
Serial Serial1 = new Serial(&huart1);
```
bool available();
------- 
判断串口是否有待读取的数据。<br>
参数：无<br>
返回值：<br>
若串口缓冲区中有数据，返回true，否则返回false。<br>

char read();
------- 
从串口读取一个字节，若当前缓冲区没有数据，则会阻塞直到读取到数据。<br>
参数：无<br>
返回值：<br>
读取到的数据<br>

std::string readline();
------- 
从串口读取一行字符串，阻塞直到读取到一行<br>
参数：无<br>
返回值：<br>
读取到的字符串<br>

std::vector<char> readbytes(int c);
------- 
从串口读取指定的字节数，阻塞直到读取到指定的字节数<br>
参数：无<br>
返回值：<br>
读取到的数据<br>

int bufferedSize();
------- 
获取缓冲区内的数据大小<br>
参数：无<br>
返回值：<br>
缓冲区大小<br>

void write(char c);
------- 
向串口写入一个字节<br>
参数：c 要写入的字节<br>
返回值：无<br>

void write(std::string s);
------- 
向串口写入一个字符串<br>
参数：s 要写入的字符串<br>
返回值：无<br>

void write(char *c,int length);
------- 
向串口写入指定数量的字节<br>
参数：c 要写入的字节串 length 字节串长度<br>
返回值：无<br>

void writeline(std::string str);
------- 
向串口写入一个字符串<br>
参数：str 要写入的字符串<br>
返回值：无<br>

范例
-----
以下代码从串口读取一行字符串后，在其头部加上“Received：”，然后输出到串口。
```cpp
Serial* Serial1 = NULL;

void setup()
{
    Serial1 = new Serial(&huart1);
}

void loop() {
    string rev = Serial1->readline();
    Serial1->writeline("Received:" + rev);
}