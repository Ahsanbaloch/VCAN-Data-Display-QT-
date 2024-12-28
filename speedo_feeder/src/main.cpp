#include "../headers/speed.hpp"
#include "../headers/can.hpp"
#include <sstream>
#include <iomanip>
// #include "utils.cpp"

// Helper function to format CAN frame as a string
std::string formatCANFrame(const struct can_frame& frame)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(3) << frame.can_id << "#";
    for (int i = 0; i < frame.can_dlc; i++)
    {
        ss << std::setw(2) << static_cast<int>(frame.data[i]);
    }
    return ss.str();
}



int main()
{

    //initializer Curses
    // initial_functions();

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    
    mvprintw(0, 0, "Instructions...");
    mvprintw(1, 0, "press 'w' for forward throttle");
    mvprintw(2, 0, "press 's' for reverse throttle");
    mvprintw(3, 0, "press 'space' for brake");
    mvprintw(4, 0, "press 'q' to quit");
    refresh();

    int input;
    Speed speed_sensor;
    CAN can_comm("vcan0");

    int last_sent_speed = 0;
    
    while (1)
    {
        input = getch();
        if (input == ' ')
            speed_sensor.bbreak();
        else if (input == 'w')
            speed_sensor.forward();
        else if (input == 's')
            speed_sensor.reverse();
        else if (input == 'q')
        {
            std::cout << "shutting down the program " << std::endl;
            break;
        }
        else
            speed_sensor.bbreak();
        int current_speed =  speed_sensor.getSpeed();
        mvprintw(6, 0, "current Speed: %d  ", current_speed);
        refresh();

        if (current_speed != last_sent_speed)
        {
            if (can_comm.sendSpeed(current_speed))
            {
                last_sent_speed = current_speed;
                struct can_frame frame = can_comm.getLastFrame();
                std::string can_msg = formatCANFrame(frame);
                mvprintw(7, 0, "Sent CAN frame: %s", can_msg.c_str());
                // mvprintw(7, 0, "sent speed: %d ", current_speed);
            }
            // else
            //     mvprintw(7, 0, 0);
        }

        //send speed over CAN
        // can_comm.sendSpeed(speed_sensor.getSpeed());
        usleep(100000);
    }
    // getch();
    endwin();
    return (0);

    //c++ *.cpp -lncurses
    //LDFLAGS += -lncurses

}

