//
// Created by cyberxix on 21.02.16.
//

#ifndef GEARRAKE_SERIALPROTOCOL_H
#define GEARRAKE_SERIALPROTOCOL_H


#include <util.h>
#include "Message.h"
#include "constants_message.h"

#define MSG_BIN_LEN ((3 + (int)MessageField::ENUM_COUNT)*2)
#define MIN_FRAME_LEN (MSG_BIN_LEN+3) //minimal message length is message lenth + start_c + checksum_c + end_c
//TODO u_int16_t;
//TODO u_int8_t;

//TODO all int to short
class SerialProtocol {
public:


    SerialProtocol();
    ~SerialProtocol();

    void send(Message* m);
    bool readMessage(Message* m);
    void addIn(char c);
    int getOutSize();
    char getOut();

    static void serialize(Message* m, char bin_message[], int bin_msg_len);
    static bool deserialize(char binary_msg[], int bin_msg_len, Message* return_m);

    static void packetize(char binary_msg[], int bin_msg_len, CircularQueue<char>*to_buf);
    static bool depacketize(CircularQueue<char>*from_buf, char* return_msg, int return_bin_msg_len);
    static char getChecksum(char const binary_msg[], int msg_len);
private:
    char out_data[(int)SerialConf::BUF_SIZE];
    char in_data[(int)SerialConf::BUF_SIZE];
    CircularQueue<char> in_buf = CircularQueue<char>(in_data, (int)SerialConf::BUF_SIZE);
    CircularQueue<char> out_buf = CircularQueue<char>(out_data, (int)SerialConf::BUF_SIZE);

};


#endif //GEARRAKE_SERIALPROTOCOL_H
