
#include <stdio.h>
#include <unistd.h>

#include "mpost.h"

void testcallback(int value, const char *str) {
    printf("received ConnectedEvent %d %s\n", value, str);
}

int main() {
    mpost_setup();
    mpost_setcallback(ConnectedEvent, testcallback);
    mpost_open("/dev/ttyUSB0");
    printf("accept bills true");
    mpost_acceptbills(1);
    sleep(10);
    mpost_return();
    sleep(2);
    mpost_close();
    return 1;
}
