#include "mbed.h"
#include "bombs.h"
#include "candecoder.h"

//testing code

int main()
{
    
    BufferedSerial serial(USBTX, USBRX);
    serial.set_baud(115200);
    serial.set_blocking(false);

    //test delta_time
    printf("im alive\n");
    Bombs bombs = Bombs();
    bombs.set_net_current(1);
    while (1) {

        printf("%f\n", bombs.pack_soc());
        bombs.update_time();
    }
    return 0;
}
