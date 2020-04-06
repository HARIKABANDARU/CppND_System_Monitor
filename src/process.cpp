#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;
using namespace std;
Process::Process(int id):pid_(id){}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{ 
    string line; 
    std::ifstream stream(LinuxParser::kProcDirectory +to_string(pid_)+LinuxParser::kStatFilename);
    if(stream.is_open()){
        getline(stream,line);
    }
    else
    {
        return 0.0;
    }
    istringstream ss(line);
    string pid,dumy,command;
    ss >> (pid);
    ss >> command;
    ss >> dumy;
    
    vector<int> values{(istream_iterator<int> (ss)),(istream_iterator<int> ())};
    // From https://stackoverflow.com/questions/16726779  and also man page of proc
    // 10 - utime 11- stime 12 - cutime 13-cstime 18 - starttime index value in values
    float total_time = values[10]+values[11];
    total_time += values[12]+values[13];
    float seconds =  LinuxParser::UpTime()-(values[18]/sysconf(_SC_CLK_TCK));
    float cpu_usage = ((total_time/sysconf(_SC_CLK_TCK))/seconds);
    return cpu_usage;

 }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return CpuUtilization() < a.CpuUtilization(); }
bool Process::operator>(Process const &a)const{
    return CpuUtilization() > a.CpuUtilization();
}