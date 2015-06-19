#ifndef MAILBOX_H
#define MAILBOX_H

#include "../memory/string.h"
#include "../memory/malloc.h"

#define MAILBOX_BASE 0x2000B880
#define GPU_FLUSH_OFFSET 0x40000000

struct MailBox_t {
    int Read;
    int reserved[3];
    int Poll;
	int Sender;
	int Status;
	int Config;
	int Write;
};

typedef volatile struct MailBox_t MailBox;

struct MBMessage_t {
    unsigned int Tag;
    unsigned int RequestLength;
    void* Request;
    unsigned int ResponseLength;
    void* Response;
};

typedef struct MBMessage_t MBMessage;

void MailBoxWrite(unsigned int value, unsigned char channel);
int MailBoxRead(unsigned char channel);

void SendMailBoxMessage(int nMessages, MBMessage *messages);
#endif
