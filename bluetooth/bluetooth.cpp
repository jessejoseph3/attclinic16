/* 
 * \file bluetooth.cpp
 * \author Ramy Elminyawi
 * \brief opens, configures, reads and writes to serial port 0 of the BBB in 
 *  order to communicate to the BlueSmirf bluetooth over UART
 */

#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include "bluetooth.h"

int Bluetooth::openPort()
{	
	std::cout << "Opening Port..." << std::endl;
	//Port 0 can read/write with flags, open returns file descriptor
    serialHandle = open("/dev/ttyO0",O_RDWR|O_NOCTTY|O_NDELAY);
    
    // Error occurred
    if(serialHandle == -1)
    {
        return 0;
    }
    else
    {
        return serialHandle;
    }
}
void Bluetooth::configurePort(int hndlport)
{
	std::cout << "Configuring Port..." << std::endl;
    struct termios options;

    // Configure port reading
    fcntl(serialHandle, F_SETFL, FNDELAY);
    // Get the current options for the port
    tcgetattr(serialHandle, &options);
    // Set the baud rates to 9600
    cfsetispeed(&options, B38400);
    cfsetospeed(&options, B38400);
    // Enable the receiver and set local mode
    options.c_cflag |= (CLOCAL | CREAD);
    // Mask the character size to 8 bits, no parity    
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    //Select 8 data bits
    options.c_cflag |=  CS8;
    //Disable hardware flow control
    options.c_cflag &= ~CRTSCTS;
    //Enable data to be processed as raw input
    options.c_lflag &= ~(ICANON | ECHO | ISIG);
    //Set the new options for the port
    tcsetattr(serialHandle, TCSANOW, &options);
}

void Bluetooth::readPort()
{
    std::cout << "Reading Port..." << std::endl;
    int numBuff = 255;
    char szBuff[255];

    int numtemp;

    while (1)
    {
        numtemp = read(serialHandle, &szBuff, sizeof(szBuff));
        //cout << numtemp << endl;
        if (szBuff != 0)
        {
            std::cout << szBuff;
            szBuff[0]=0;
        }
    }

}

int main()
{
    Bluetooth uart0;
    int tempHandle;

    tempHandle = uart0.openPort();
    if(tempHandle == 0)
    {
        std::cout << "Serial Port Open - Status Fail" << std::endl;
    }
    else
    {
        std::cout << "Serial Port Open - Status Pass with handle value " << tempHandle << std::endl;
        uart0.configurePort(tempHandle);
    }

    uart0.readPort();
    return 0;
}
