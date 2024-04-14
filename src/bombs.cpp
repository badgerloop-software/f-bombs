
#include "bombs.h"

using namespace std::chrono;


//TODO: thinking of condensing these three into one function to set the values
//setters
void Bombs::set_net_current(float net_current)
{
    this->net_current = net_current;
}

void Bombs::set_individual_cell_voltage(float (&voltages)[NUM_BATTERIES])
{
    for (int i = 0; i < NUM_BATTERIES; i++) {
        individual_cell_voltage[i] = voltages[i];
    }
}

void Bombs::set_indiviual_cell_temp(float (&temps)[NUM_BATTERIES])
{
   for (int i = 0; i < NUM_BATTERIES; i++) {
        individual_cell_temp[i] = temps[i];
    }
}

//TODO:
/// @brief calculates pack SOC using coulomb counting method.
/// @return the state of health from 0-100%
float Bombs::pack_soc()
{
    //resets to 100% when battery is confirmed fully charged
    if (fully_charged) {
        prev_pack_soc = 100;

        max_charge = nomial_capacity * 0.36;
        return prev_pack_soc;
    }

    //TODO: do this right. this is just for testing.
    //done using Coulomb counting method
    return prev_pack_soc - (net_current / max_charge) * duration_cast<seconds>(delta_time).count();
}   

float Bombs::pack_soh()
{
    if (fully_charged) {

    }
    //TODO:
    return 0;
}

int Bombs::charge_current_limit()
{
    //TODO:
    return 0;
}


//TODO:
/// @brief calculates the delta_time for use every time for SOC 
///         should probably 
/// @return deltatime
void Bombs::update_time()
{
    //whenever called, timer 
    
    //read the timer
    delta_time = duration_cast<milliseconds>(timer.elapsed_time());
    timer.reset();
}


