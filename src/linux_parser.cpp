#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;



// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  string version;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}
long LinuxParser::HelperMemUtil(std::string line){
   std::string sName,value,type;

   std::stringstream ss(line);
   ss >> sName >> value >> type;
   return std::stol(value);
   
}
// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::string line;
  std::ifstream stream(kProcDirectory+kMeminfoFilename);
  long memTotal,memFree;
  if(stream.is_open()){
    std::getline(stream,line);
    memTotal = HelperMemUtil(line);
    std::getline(stream,line);
    memFree = HelperMemUtil(line);
    return (memTotal-memFree)/(float)memTotal;
  }
  
  return 0.0; 
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
   std::ifstream filestream(kProcDirectory+kUptimeFilename);
   std::string line;
   if(filestream.is_open()){
      std::getline(filestream,line);
   }
   std::string uptime,idletime;
   std::istringstream ss(line);
   ss >> uptime >> idletime;
   return stol(uptime);
}

// TODO: Read and return the number of jiffies for the system
/*long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }


// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {

}*/

int ProcessesHelper(string fileName,string key){
  std::string line,keyVal,value;
  std::ifstream fstream(fileName);
  if(fstream.is_open()){
    while(getline(fstream,line)){
      std::stringstream ss(line);
      while(ss >> keyVal >> value)
      if(keyVal == key)
        return std::stoi(value);
    }
  }
  return 0;
}
// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string fName = kProcDirectory+kStatFilename;
  return ProcessesHelper(fName,"processes");
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string fName = kProcDirectory+kStatFilename;
  return ProcessesHelper(fName,"procs_running");
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string command;
  std::ifstream fstream(kProcDirectory+to_string(pid)+kCmdlineFilename);
  if(fstream.is_open()){
    std::getline(fstream,command);
    return command;
  }
  return string(); 
  
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string fName =  kProcDirectory+to_string(pid)+kStatusFilename;
  int val = ProcessesHelper(fName,"VmSize:");
  return to_string(val/1024);
  
  return string(); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
   string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
  
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
    std::string line;
    std::ifstream stream(kPasswordPath);
    string uid = LinuxParser::Uid(pid);
    if(stream.is_open()){
      while(std::getline(stream,line)){
        string user,phash,uidVal;
        std::replace(line.begin(),line.end(),':',' ');
        std::stringstream ss(line);
        while(ss >> user >> phash >> uidVal){
          if(uid == uidVal)
            return user;
        }


      }
    }
  return "";
  }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 

  std::string line;
  std::ifstream stream(kProcDirectory+to_string(pid)+kStatFilename);
  string temp;
  if(stream.is_open()){
    while(std::getline(stream,line))
    {
      std::stringstream ss(line);

      for(int i = 1;i<23;i++){
          ss >> temp;
      }
    }
    return std::stol(temp)/sysconf(_SC_CLK_TCK);
  }

  
  return -1; 
}