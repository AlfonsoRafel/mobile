//=====[Libraries]=============================================================

#include "mobile.h"
#include "arm_book_lib.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    mobileSystemInit();
    while (true) {
       mobileSystemUpdate();
       delay(SYSTEM_TIME_INCREMENT_MS);
    }
}