#ifndef CAN_HPP
# define CAN_HPP

#include <linux/can.h>
// #include <linux/can/raw.h>
#include <unistd.h>
#include <net/if.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

class CAN 
{
    private:
        int socket_fd;
        struct sockaddr_can addr;
        struct can_frame frame;
    
    public:
        CAN(const char * ifname);
        ~CAN();

        bool initSocket(const char * ifname);
        bool sendSpeed(int speed);

        struct can_frame getLastFrame() const;

};

#endif