//
// Created by cyberxix on 21.02.16.
//

#ifndef GEARRAKE_SERIALPROTOCOL_H
#define GEARRAKE_SERIALPROTOCOL_H


#include <util.h>
#include "Message.h"
#include "constants_message.h"

class SerialProtocol {
public:


    SerialProtocol();
    ~SerialProtocol();

    void send(Message* m);
    bool readMessage(Message* m);
    void add(char c);

    static void serialize(Message* m, char bin_message[], int bin_msg_len);
    static bool deserialize(char binary_msg[], int bin_msg_len, Message* return_m);

    static void packetize(char binary_msg[], int bin_msg_len, CircularQueue<char>*to_buf);
    static bool depacketize(CircularQueue<char>*from_buf, char* return_msg, int return_bin_msg_len);
    static char getChecksum(char const binary_msg[], int msg_len);
private:
    CircularQueue<char>* in_buf;
    CircularQueue<char>* out_buf;
};


#endif //GEARRAKE_SERIALPROTOCOL_H
