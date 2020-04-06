#include "ncurses_display.h"
#include "system.h"
#include "processor.h"
#include "linux_parser.h"
#include <iostream>
using namespace std;

int main() {
  //Process p(1);
  //cout << p.UpTime()<<"\n";
  //LinuxParser::User(1);
  //cout << LinuxParser::UpTime();
  System system;
  NCursesDisplay::Display(system);
}