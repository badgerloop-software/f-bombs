#ifndef __BOMBS_H__
#define __BOMBS_H__

#include "mbed.h"
#include <chrono>

#define NUM_BATTERIES 31

class Bombs {
public:
    //current functions
    float pack_soh();
    float pack_soc();
    int charge_current_limit();
    void update_time();

    void set_net_current(float net_current);
    void set_individual_cell_voltage(float (&voltages)[NUM_BATTERIES]);
    void set_indiviual_cell_temp(float (&temps)[NUM_BATTERIES]);

    Bombs() noexcept {

        net_current = 0;

        for (int i = 0; i < NUM_BATTERIES; i++) {
            individual_cell_voltage[i] = 0;
            individual_cell_temp[i] = 0;
        }
        
        timer.start();
        delta_time = std::chrono::milliseconds(0);

        fully_charged = false;
        prev_pack_soc = 100;

        nomial_capacity = 0;

        max_charge = 0;
    
    }

private:
    //only known inputs currently INPUTS
    float net_current;                              //amps
    float individual_cell_voltage[NUM_BATTERIES];   //volts
    float individual_cell_temp[NUM_BATTERIES];      //celsius

    //used for coulomb counting
    Timer timer;
    std::chrono::milliseconds delta_time;   

    //static variables to use
    bool fully_charged;
    float prev_pack_soc;


    //calculated using the charge curve
    float nomial_capacity; //mAh

    
    //charge when SOC was at 100%
    float max_charge;   //coulombs
};

#endif //__BOMBS_H__