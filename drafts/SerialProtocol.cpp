//
// Created by cyberxix on 21.02.16.
//

#include "SerialProtocol.h"
#include "Message.h"
#include "constants.h"
#include "util.h"

//binary length of


SerialProtocol::SerialProtocol() {
    //out_buf = CircularQueue<char>(out_data, (int)SerialConf::BUF_SIZE);
    //in_buf = CircularQueue<char>(in_data, (int)SerialConf::BUF_SIZE);
}


void SerialProtocol::send(Message* m) {
    char binary_msg[MSG_BIN_LEN];
    SerialProtocol::serialize(m, binary_msg, MSG_BIN_LEN);
    SerialProtocol::packetize(binary_msg, MSG_BIN_LEN, &out_buf);
}

bool SerialProtocol::readMessage(Message* m) {
    if(this->in_buf.size() < MIN_FRAME_LEN){
        return false;
    }

    char binary_msg[MSG_BIN_LEN];
    if(SerialProtocol::depacketize(&in_buf, binary_msg, MSG_BIN_LEN)){
        SerialProtocol::deserialize(binary_msg, MSG_BIN_LEN, m);
        return true;
    }
    return false;
}

void SerialProtocol::addIn(char c) {
    in_buf.add(c);
}


void SerialProtocol::serialize(Message* m, char bin_message[], int bin_msg_len) {
    int bin_msg_count = 0;

    //least significant byte first
    bin_message[bin_msg_count++] = (int)m->getType() >> 8; //get first half of int into the char
    bin_message[bin_msg_count++] = (int)m->getType() ; //get second half of int into the char

    bin_message[bin_msg_count++] = (int)m->getSenderActionType() >> 8; //get first half of int into the char
    bin_message[bin_msg_count++] = (int)m->getSenderActionType(); //get second half of int into the char

    bin_message[bin_msg_count++] = (int)m->getCommunicationId() >> 8; //get first half of int into the char
    bin_message[bin_msg_count++] = (int)m->getCommunicationId(); //get second half of int into the char

    for (int i = 0; i < (int)MessageField::ENUM_COUNT ; ++i) {
        bin_message[bin_msg_count++] = (int)m->getValue((MessageField)i) >> 8; //get first half of int into the char
        bin_message[bin_msg_count++] = (int)m->getValue((MessageField)i); //get second half of int into the char
    }


}

bool SerialProtocol::deserialize(char bin_msg[], int bin_msg_len, Message* m) {
    int bin_msg_count = 0;
    //check if received int is a real messageType
    //least significant byte first -> build an integer out of 2 chars
    int type = bin_msg[bin_msg_count++] << 8 | bin_msg[bin_msg_count++];
    if(type < 0 || type >= (int)MessageType::ENUM_COUNT ){
        return false;
    }
    m->setType((MessageType)type);

    //get sender type
    int sender_action_type = bin_msg[bin_msg_count++] << 8 | bin_msg[bin_msg_count++];
    if(sender_action_type < 0 || sender_action_type >= (int)ActionType::ENUM_COUNT ){
        return false;
    }
    m->setSenderActionType((ActionType) sender_action_type);

    //get communication id next
    int communication_id = bin_msg[bin_msg_count++] << 8 | bin_msg[bin_msg_count++];
    m->setCommunicationId(communication_id);

    //add data fields
    int message_field_count = 0;
    while(bin_msg_count + 1 < bin_msg_len && message_field_count < (int)MessageField::ENUM_COUNT) {
        int field = bin_msg[bin_msg_count++] << 8 | bin_msg[bin_msg_count++];
        m->setValue((MessageField) message_field_count, field);
        message_field_count++;
    }

}

void SerialProtocol::packetize(char binary_msg[], int bin_msg_len, CircularQueue<char>*to_buf) {
    //add start character
    to_buf->add(SerialChar::START);
    //add checksum
    to_buf->add(SerialProtocol::getChecksum(binary_msg, bin_msg_len));
    //add the message data (and escape id)
    for (int i = 0; i < bin_msg_len; ++i) {
        //if special character occours in data escape it!
        if(binary_msg[i] == SerialChar::START
                || binary_msg[i] == SerialChar::END
                || binary_msg[i] == SerialChar::ESCAPE){
            to_buf->add(SerialChar::ESCAPE);
        }
        //add the data itself
        to_buf->add(binary_msg[i]);
    }
    //add end character
    to_buf->add(SerialChar::END);
}

bool SerialProtocol::depacketize(CircularQueue<char>*from_buf, char *return_msg, int return_bin_msg_len) {

    bool msg_complete = false;
    bool escaped = false;
    bool is_checksum = false;
    int i = 0;
    char bin_msg[MSG_BIN_LEN];
    int bin_msg_len;
    char checksum;

    while (!msg_complete){
        if(i >= from_buf->size()){
            return false;
        }

        int got = from_buf->look_ahead(i);

        if(is_checksum){
            //checksum itself is not escaped, and is calculated on the unescaped data
            checksum = got;
            is_checksum = false;
            escaped = false;

            //test for escape character
        } else if (got == SerialChar::ESCAPE && !escaped){
            escaped = true;

            //test for start character
        } else if (got == SerialChar::START && !escaped){
            bin_msg_len = 0; //reset message count
            is_checksum = true; //next byte is checksum byte
            escaped = false;

            //test for end message character
        } else if (got == SerialChar::END && !escaped){
            msg_complete = true; //stop read loop
            escaped = false;

            //if no special character add it to the bin_msg
        } else {
            bin_msg[bin_msg_len] = got;
            bin_msg_len++;
            escaped = false;
        }

        if (bin_msg_len > return_bin_msg_len){
            from_buf->remove(i);
            return false;
        }
        i++;
    }

    from_buf->remove(i);

    //wrong byte count -> drop message
    if(bin_msg_len != return_bin_msg_len){
        return false;
    }

    //test checksum
    if(SerialProtocol::getChecksum(bin_msg, return_bin_msg_len) != checksum){
        return false;
    }

    //all okay write message to given char array
    for (int j = 0; j < return_bin_msg_len; ++j) {
        return_msg[j] = bin_msg[j];
    }
    return true;
}


char SerialProtocol::getChecksum(char const binary_msg[], int msg_len) {
    //inverrted additive checksum calculation. source: http://www.barrgroup.com/Embedded-Systems/How-To/Additive-Checksums 99,6% security
    char  sum = 0;
    while (msg_len-- > 0)
    {
        sum += *(binary_msg++);
    }

    return (~sum);
}

SerialProtocol::~SerialProtocol() {}

int SerialProtocol::getOutSize() {
    return out_buf.size();
}

char SerialProtocol::getOut() {
    return out_buf.get();
}
