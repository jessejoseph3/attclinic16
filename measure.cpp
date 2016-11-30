/* \file measure.cpp
 * \brief a script to implement a measurement loop, measuring when commanded to via the bluetooth link
 */
#include "hdhomerun-utils/Tuner.h"
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <csignal>

std::ofstream serialOut;
bool continue_measuring = true;

void signalHandler( int signum ) {
  std::cout << "recieved signal: " << signum << std::endl;
  std::cout << "closing" << std::endl;
  serialOut.close();
  continue_measuring = false;
}

int main() {
  std::string deviceID = "1034F75C-0";
  std::vector<char> channels = {7, 11, 36, 43};
  Tuner tuner = Tuner(deviceID, channels);
  serialOut.open("/dev/ttyO4");
  signal(SIGINT, signalHandler);


  while(continue_measuring) {
    sleep(1);
    tuner.updateStatusOfAllChannels();
    for(size_t i = 0; i < channels.size(); ++i) {
      /* replace these couts with whatever we use to write to
      the tty line.
      */
      serialOut << channels[i] << '\t';
      serialOut << tuner.getSignalStrengthOfChannel(i) << '\t';
      serialOut << tuner.getSNQOfChannel(i) << '\n';
    } 
  }
  return 0;
}
