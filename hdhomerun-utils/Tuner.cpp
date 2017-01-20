#include "Tuner.h"
Tuner::Tuner(const std::string& deviceID) :
deviceID_{deviceID} { 
  device_ = hdhomerun_device_create_from_str(deviceID_.data(), NULL);
}

Tuner::Tuner(const std::string& deviceID,
    const std::vector<char>& channels) : 
    channels_{channels},
    deviceID_{deviceID} {
  setChannelsList(channels_);
  device_ = hdhomerun_device_create_from_str(deviceID_.data(), NULL);
}

Tuner::~Tuner() {
  hdhomerun_device_destroy(device_);
  for(auto status_t_pointer : status_) {
    delete status_t_pointer; 
  }
}

void Tuner::setChannelsList(const std::vector<char>& channels) {
  channels_ = std::vector<char>(channels);
  status_ = std::vector<hdhomerun_tuner_status_t*>();
  for(size_t i = 0; i < channels.size(); ++i) {
    channels_[i] = channels[i];
    status_.push_back(new hdhomerun_tuner_status_t);
  }
}

std::vector<char> Tuner::getChannelsList() const {
  return channels_;
}

void Tuner::updateStatusOfChannel(const size_t channelIndex) {
  std::string channel = std::to_string(channels_[channelIndex]);
  hdhomerun_device_set_tuner_channel(device_, channel.data());
  hdhomerun_device_get_tuner_status(device_,NULL,
      status_[channelIndex]);
}

void Tuner::updateStatusOfAllChannels() {
  for(size_t i = 0; i < channels_.size(); ++i) {
    updateStatusOfChannel(i);
  }
}

size_t Tuner::getSignalStrengthOfChannel(const size_t channelIndex) {
  updateStatusOfChannel(channelIndex);
  return status_[channelIndex]->signal_strength; 
}

std::vector<size_t> Tuner::getSignalStrengthOfAllChannels() {
  updateStatusOfAllChannels();
  std::vector<size_t> signalStrengths;
  for(auto status_p : status_) {
    signalStrengths.push_back(status_p->signal_strength);
  }
  return signalStrengths;
}

size_t Tuner::getSNQOfChannel(const size_t channelIndex) {
  updateStatusOfChannel(channelIndex);
  return status_[channelIndex]->signal_to_noise_quality;
}

std::vector<size_t> Tuner::getSNQOfAllChannels() {
  updateStatusOfAllChannels();
  std::vector<size_t> SNQs; 
  for(auto status_p : status_) {
    SNQs.push_back(status_p->signal_to_noise_quality);
  }
  return SNQs;
}


int testfn() {
  const std::string deviceID = "1034F75C-0";
  const std::vector<char> channels = {7, 11, 36, 43};
  Tuner tuner = Tuner(deviceID, channels);
  tuner.updateStatusOfAllChannels();
  std::cout << "individual channel tests" << std::endl;
  for(size_t i = 0; i < channels.size(); ++i) {
    std::cout << std::to_string(channels[i]) << '\t';
    std::cout << tuner.getSignalStrengthOfChannel(i) << '\t';
    std::cout << tuner.getSNQOfChannel(i) << std::endl;
  }
  std::vector<char> channelsList = tuner.getChannelsList();
  std::vector<size_t> sigStrengths =
    tuner.getSignalStrengthOfAllChannels();
  std::vector<size_t> SNQs = tuner.getSNQOfAllChannels(); 
  std::cout << std::endl << "all channels test" << std::endl;
  for(size_t i = 0; i < channelsList.size(); ++i) {
    std::cout << std::to_string(channelsList[i]) << '\t';
    std::cout << sigStrengths[i] << '\t';
    std::cout << SNQs[i] << std::endl;
  }
  return 0;
}






