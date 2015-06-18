#include "mailbox.h"

void MailBoxWrite(unsigned int message, unsigned char channel)
{
    MailBox *mailbox = (MailBox*)MAILBOX_BASE;

    if ((message & 0xF) != 0) return;			// pointer at message has to be 4 byte aligned
    if (channel > 9) return;

    while (mailbox->Status & 0x80000000) { }	// waits until first status bit is one

    message |= channel;							// appends channel number to message

    mailbox->Write = message;					// writes message to mailbox
}

int MailBoxRead(unsigned char channel)
{
    MailBox *mailbox = (MailBox*)MAILBOX_BASE;
    int mail;

    if (channel > 9) return -1;

    do
    {
        while (mailbox->Status & 0x40000000) { }	// waits until second status bit is one

        mail = mailbox->Read;						// reads message
    } while ((mail & 0xF) ^ channel);				// checks if read the right channel

    return (mail & 0xFFFFFFF0);						// removes channel and returns message
}

int* BuildTag(const MBMessage* MB, unsigned int *tagSize)
{
    // picks the largest size between request and response for proper allocation
    unsigned int size = MB->RequestLength > MB->ResponseLength ? MB->RequestLength : MB->ResponseLength;
    unsigned int paddedSize = 0;

    // size padded to 32 bits (4 bytes)
    if (size % sizeof(int) != 0)
        paddedSize += sizeof(int) - (size % sizeof(int));
    else
        paddedSize = size;

    paddedSize /= sizeof(int);

    // allocates the tag
    *tagSize = 3 + paddedSize;
    int *tag = (int*)malloc(*tagSize * sizeof(int));
    tag[0] = MB->Tag;
    tag[1] = size;
    tag[2] = 0x0;       // Request/Response indicator (MSB 0 for request)

    // fills with request data, if available
    memcpy(&(tag[3]), MB->Request, MB->RequestLength);
    
	return tag;
}

void ReadTag(MBMessage* MB, int* tag, unsigned int *tagSize)
{
    // picks the largest size between request and response for proper allocation
    unsigned int size = MB->RequestLength > MB->ResponseLength ? MB->RequestLength : MB->ResponseLength;
    unsigned int paddedSize = 0;

    // size padded to 32 bits (4 bytes)
    if (size % sizeof(int) != 0)
        paddedSize += sizeof(int) - (size % sizeof(int));
    else
        paddedSize = size;

    paddedSize /= sizeof(int);

    *tagSize = 3 + paddedSize;

    // reads response data, if available
    memcpy(MB->Response, &(tag[3]), MB->ResponseLength);
}

void SendMailBoxMessage(int nMessages, MBMessage *messages)
{
    const int messageHeaderSize = 12;

    int i;
    unsigned int size = 0;

	// finds out how big each message is
    for (i = 0; i < nMessages; i++)
    {
        size += messages[i].RequestLength > messages[i].ResponseLength ? messages[i].RequestLength : messages[i].ResponseLength;;
    }

    // 12 = 4 bytes for buffer size, 4 for request/response code and 4 for  end tag
	int totalSize = sizeof(char) * (size + 12 + nMessages * messageHeaderSize);	// already in bytes
    int *message = (int*)malloc(totalSize);

    message[0] = totalSize;		// buffer size
    message[1] = 0x0;			// request code

    size = 0;
    for (i = 0; i < nMessages; i++)
    {
        int *tag;
        unsigned int tagSize;
        tag = BuildTag(&(messages[i]), &tagSize);
		// copies the contents of each message to the allocated space
        memcpy(&(message[2 + size]), tag, tagSize * sizeof(int));
        size += tagSize;
        free(tag);
    }

    message[totalSize/sizeof(int) - 1] = 0x0;       // end tag at last position

    MailBoxWrite((int)message + GPU_FLUSH_OFFSET, 8);

    if (MailBoxRead(8) == 0)
    {
        return;         // error
    }

    size = 0;
    for (i = 0; i < nMessages; i++)
    {
        unsigned int tagSize;
		// copies the response back to each message
        ReadTag(&(messages[i]), &(message[2 + size]), &tagSize);
        size += tagSize;
    }

    free(message);
}
