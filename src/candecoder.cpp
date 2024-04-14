#include "candecoder.h"

/*
    gets value from 2 bytes.
    - 
    bigByte:       the byte that is at the front/shifted
    smallByte:     the data that is at the end
    
*/
int CANDecoder::getValueFrom2Bytes(unsigned char bigByte, unsigned char smallByte) {
    return ((bigByte << 8) + smallByte);
}

/*
    decodes the data from ID = x101. 
    data: the pointer to the data byte
    
*/
void CANDecoder::decode101(unsigned char *data) {
    this->data.pack_current = getValueFrom2Bytes(data[0], data[1]) * 0.1;

    this->data.pack_open_voltage = getValueFrom2Bytes(data[2], data[3]) * 0.1;

    this->data.pack_power = this->data.pack_current * this->data.pack_open_voltage;
    
    this->data.SOC = data[4] * 0.5;

    this->data.SOH = data[5];

    this->data.pack_resistance = getValueFrom2Bytes(data[6], data[7]);
}

/*
    decodes the data from ID = x102. 
    data: the pointer to the data byte
    
*/
void CANDecoder::decode102(unsigned char *data) {

    this->data.pack_amphours = getValueFrom2Bytes(data[0], data[1]) * 0.1;
}

/*
    Decode BMS messages
*/
void CANDecoder::decodeBMS(int messageID, SharedPtr<unsigned char> data, int length) {
    switch (messageID) {
        case 0x101:      
            CANDecoder::decode101(data.get());
            break;
        case 0x102:
            CANDecoder::decode102(data.get());
            break;
        default:
            break;
    }
}

OrionBMSData CANDecoder::getData() {
    return this->data;
}

void CANDecoder::readHandler(int messageID, SharedPtr<unsigned char> data, int length) {
    // IDs are 11 bits, first 3 are used to ID the board, rest for message
    switch (messageID & BOARD_ID_MASK) {
        case 0x100:
            decodeBMS(messageID, data, length);
            break;
        default:
            break;
    }
}
