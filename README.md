Mixplus
=======
## Timer�����ڲ�����ʱ��

������
-----
���´���ÿ��1s��תPB12�ڣ����Ӵ������Catched.
```cpp
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
```

## PWM����������PWM��

������
-----
���´�����Tim3��ʱ����1ͨ������������

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

## GPIO�����ڲ���ͨ��IO��

## Analog��AnalogDMA�����ڲ���ADC

������
-----
���´���ÿ��500ms����ȡһ��ADC1���ĸ�ͨ�������Ӵ������

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

## Serial�����ڶ�д����
Serial(UART_HandleTypeDef *t)
------- 
�ô��ھ����ʼ���ࡣ<br>
������<br>
t�����ھ��<br>
��:
```cpp
Serial Serial1 = new Serial(&huart1);
```
bool available();
------- 
�жϴ����Ƿ��д���ȡ�����ݡ�<br>
��������<br>
����ֵ��<br>
�����ڻ������������ݣ�����true�����򷵻�false��<br>

char read();
------- 
�Ӵ��ڶ�ȡһ���ֽڣ�����ǰ������û�����ݣ��������ֱ����ȡ�����ݡ�<br>
��������<br>
����ֵ��<br>
��ȡ��������<br>

std::string readline();
------- 
�Ӵ��ڶ�ȡһ���ַ���������ֱ����ȡ��һ��<br>
��������<br>
����ֵ��<br>
��ȡ�����ַ���<br>

std::vector<char> readbytes(int c);
------- 
�Ӵ��ڶ�ȡָ�����ֽ���������ֱ����ȡ��ָ�����ֽ���<br>
��������<br>
����ֵ��<br>
��ȡ��������<br>

int bufferedSize();
------- 
��ȡ�������ڵ����ݴ�С<br>
��������<br>
����ֵ��<br>
��������С<br>

void write(char c);
------- 
�򴮿�д��һ���ֽ�<br>
������c Ҫд����ֽ�<br>
����ֵ����<br>

void write(std::string s);
------- 
�򴮿�д��һ���ַ���<br>
������s Ҫд����ַ���<br>
����ֵ����<br>

void write(char *c,int length);
------- 
�򴮿�д��ָ���������ֽ�<br>
������c Ҫд����ֽڴ� length �ֽڴ�����<br>
����ֵ����<br>

void writeline(std::string str);
------- 
�򴮿�д��һ���ַ���<br>
������str Ҫд����ַ���<br>
����ֵ����<br>

����
-----
���´���Ӵ��ڶ�ȡһ���ַ���������ͷ�����ϡ�Received������Ȼ����������ڡ�
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