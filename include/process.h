#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int id);
  int Pid();                               // Done: See src/process.cpp
  std::string User();                      // Done: See src/process.cpp
  std::string Command();                   // Done: See src/process.cpp
  float CpuUtilization ()const;                  // TODO: See src/process.cpp
  std::string Ram();                       // Done: See src/process.cpp
  long int UpTime() const;                       // Done: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  bool operator>(Process const &a)const;

  // TODO: Declare any necessary private members
 private:
    int pid_;
    std::string command_;
};

#endif