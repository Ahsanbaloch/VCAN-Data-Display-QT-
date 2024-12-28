#include "../headers/speed.hpp"


Speed::Speed() :  _speed(0)
{
}

Speed::~Speed() {}

int Speed::getInput()
{
    return _input;
}

void Speed::forward()
{
    // std::cout << "forward speed " << std::endl;
    if (_speed < 300)
        _speed += 10;
}

void Speed::reverse()
{
    // std::cout << "reverse speed " << std::endl;
    if (_speed > -300)
        _speed -= 10;
}

void Speed::bbreak()
{
    if (_speed != 0)
    {
        if (_speed > 0 )
            _speed -= 10;
        else if (_speed < 0)
            _speed += 10;
    }
}

int Speed::getSpeed()
{
    return _speed;
}

// convert the value in CAN bitrate format

/* t_can Speed::convSpedCAN() const
{
    t_can   can;
    can.id = 0x100; // id for CAN to send the data
    can.data_length = 2; // Data length

    // Convert speed to a 16-bit value
    uint16_t speed_value = static_cast<uint16_t>(_speed + 32768); // offset to handle negative values

    can.data[0] = (speed_value >> 8) & 0xFF; //High byte
    can.data[1] = speed_value & 0xFF; // low byte

    return can;

} */