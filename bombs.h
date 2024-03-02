#ifndef __BOMBS_H__
#define __BOMBS_H__

#include "mbed.h"
//

//TODO: will be set to values later
#define RATED_CAPACITY_OF_BATTERY
#define MAX_CHARGE //probably won't need to hardcode this but just putting it here

class Bombs {
public:
    //current functions
    uint8_t pack_soh();
    uint8_t pack_soc();
    uint8_t charge_current_limit();

private:
    //only known inputs currently
    float net_current;
    float individual_cell_voltage;
    float individual_cell_temp;

    //
};

Bombs::Bombs() noexcept {
    
};

#endif //__BOMBS_H__