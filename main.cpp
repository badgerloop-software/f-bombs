#include "mbed.h"
#include "bombs.h"
#include "candecoder.h"

//set these to the correct pins for later
#define CAN_RX PD_0
#define CAN_TX PD_1

//testing code

int main()
{
    //TODO: get printf work
    //I don't know if I need this for printf, but currently printf is not working
    BufferedSerial serial(USBTX, USBRX);
    serial.set_baud(115200);
    serial.set_blocking(false);
    

    CANDecoder can_bus(CAN_RX, CAN_TX);

    //test delta_time
    printf("im alive\n");
    Bombs bombs = Bombs();
    bombs.set_net_current(1);
    while (1) {
        
        can_bus.runQueue(1000ms);
        bombs.update_time();

        printf("my SOC: %f   orion SOC: %f\n", bombs.pack_soc(), can_bus.getData().SOC);
    }
    return 0;
}
