
#include <stdio.h>
#include <unistd.h>
        
void mpost_open(char *portname);
void mpost_close();
/* return the bill that is currently sitting in escrow */
void mpost_return();
/* stack the bill that is currently sitting in escrow */
void mpost_stack();
void mpost_softreset();
void mpost_acceptbills(int enable);
void mpost_debug(int enable);


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
