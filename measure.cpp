/* \file measure.cpp
 * \brief a script to implement a measurement loop, measuring when commanded to via the bluetooth link
 */
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <csignal>
#include <pthread.h>
#include "hdhomerun-utils/Tuner.h"
#include "serialibv1.2/serialib/serialib.h"

#define DEVICE_PORT "/dev/ttyO4"
int Ret;
serialib LS;                                                            // Object of the serialib class

void signalHandler( int signum ) {
  std::cout << "recieved signal: " << signum << std::endl;
  std::cout << "closing" << std::endl;
  LS.Close();
  Ret = 0;
}

int main() {
  signal(SIGINT,signalHandler);
  std::string deviceID = "104689B9-0";
  std::vector<char> channels = {7, 11, 36, 43};
  Tuner tuner = Tuner(deviceID, channels);

  std::string dataLine;


  // Open serial port

  Ret=LS.Open(DEVICE_PORT,9600);                                        // Open serial link at 115200 bauds
  if (Ret!=1) {                                                           // If an error occured...
      std::cout << "Error while opening port. Permission problem?" << std::endl;
      return Ret;                                                         // ... quit the application
  }
  std::cout << "Serial port opened successfully !\n" << std::endl;




  // Write the AT command on the serial port


  while(Ret==1) {
    sleep(3);
    tuner.updateStatusOfAllChannels();
    Ret=LS.WriteString("ch  ss  snq\n");
    for(size_t i = 0; i < channels.size(); ++i) {
      dataLine = std::to_string(channels[i]);
      dataLine += "  ";
      if(channels[i] == 7){
	dataLine += ' ';
      }
      dataLine += std::to_string(tuner.getSignalStrengthOfChannel(i));
      dataLine += "   "; 
      dataLine += std::to_string(tuner.getSNQOfChannel(i));
      dataLine += '\n';
      Ret = LS.WriteString(dataLine.data());
      std::cout << dataLine.data(); 
      if(Ret != 1) {
	break;
      }
    } 
    std::cout << std::endl << std::endl;
    Ret = LS.WriteString("\n\n");
  }
  return 0;
}
