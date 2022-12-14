Mixplus
=======

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