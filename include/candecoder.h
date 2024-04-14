#ifndef __CAN_DECODE_H__
#define __CAN_DECODE_H__

#include "canmanager.h"

#define BOARD_ID_MASK 0x700

typedef struct OrionBMSData {
    //x101 signals
    float SOC;
    float SOH;
    float pack_current;
    float pack_open_voltage;
    float pack_power;
    int pack_resistance;

    //x102 signals
    float pack_amphours;
} OrionBMSData;

class CANDecoder : public CANManager {
    public:
        CANDecoder(PinName rd, PinName td, int frequency = DEFAULT_CAN_FREQ) : CANManager(rd, td, frequency) {};
        
        void readHandler(int messageID, SharedPtr<unsigned char> data, int length);

        OrionBMSData getData();

    private:
        //used to compare with my implementation of SOC and SOH
    
        OrionBMSData data;

        int getValueFrom2Bytes(unsigned char bigByte, unsigned char smallByte);
        void setCellVoltage(int index, float value);

        // Helper functions for compacted messages
        void decode101(unsigned char *data);
        void decode102(unsigned char *data);
        
        // Helper functions to process data from each board
        void decodeBMS(int messageID, SharedPtr<unsigned char> data, int length);

};

#endif