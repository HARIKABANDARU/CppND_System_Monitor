#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
using namespace std;
class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 string cpuName;
 int idletime;
 int workingtime;
 float cpuUtilization;
 float totalTime;
};

#endif