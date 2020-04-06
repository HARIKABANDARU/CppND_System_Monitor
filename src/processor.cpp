#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    string line;
    
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if(stream.is_open()){
        getline(stream,line);
    }
    else
    {
        return 0.0;
    }
    
    istringstream ss(line);
    //index name  0- user 1- nice 2-system 3-idle 4- iowait 5-irq 6-softirq 7-steal 8-guest 
    //9 - guest nice
    
    ss >> cpuName;
    vector<int> values{(istream_iterator<int> (ss)),(istream_iterator<int> ())};
    idletime = values[3]+values[4];
    workingtime = values[0] + values[1] + values[2] + values[5] + values[6] + values[7];
    totalTime = workingtime+idletime;
    cpuUtilization = (totalTime-idletime)/(totalTime);
    return cpuUtilization;
 }