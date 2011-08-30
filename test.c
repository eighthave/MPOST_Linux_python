
#include <stdio.h>
#include <unistd.h>

#include "mpost.h"

int main() {
    mpost_open("/dev/ttyUSB0");
    printf("accept bills true");
    mpost_acceptbills(1);
    sleep(10);
    mpost_return();
    sleep(2);
    mpost_close();
    return 1;
}
