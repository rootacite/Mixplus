# Mixplus

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