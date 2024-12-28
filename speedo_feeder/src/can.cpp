#include "../headers/can.hpp"

CAN::CAN(const char* ifname) : socket_fd(-1)
{
    initSocket(ifname);
}

CAN::~CAN()
{
    if (socket_fd >= 0)
        close(socket_fd);
}

bool CAN::initSocket(const char* ifname)
{
    struct ifreq ifr;

    if ((socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
        return (perror("Error while opening socket"), false);
    
    strcpy(ifr.ifr_name, ifname);
    if (ioctl(socket_fd, SIOCGIFINDEX, &ifr) < 0)
    {
        perror("Error in ioctl");
        return false;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return (perror("Error in socket bind"), false);
    
    return true;
}

bool CAN::sendSpeed(int speed)
{
    frame.can_id = 0x100; //can id
    frame.can_dlc = 2; // Date length code for speed
    frame.data[0] = (speed >> 8) & 0xFF; // High byte
    frame.data[1] = speed & 0xFF;

    if (write(socket_fd, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
        return (perror("Error in CAN write"), false);
    
    return true;
}

struct can_frame CAN::getLastFrame() const
{
    return frame;
}

