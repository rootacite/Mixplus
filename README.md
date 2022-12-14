# Mixplus

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