
#include "mixplus.h"
#include "Serial.hpp"

#include <list>
#include <string>

using namespace std;


Serial* Serial1 = NULL;

void setup()
{
    Serial1 = new Serial(&huart1);
}

void loop() {
    string rev = Serial1->readline();
    Serial1->writeline("Received:" + rev);
}