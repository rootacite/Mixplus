Mixplus
=======

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