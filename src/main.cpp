#include "ncurses_display.h"
#include "system.h"
#include "processor.h"
#include "linux_parser.h"
#include <iostream>
using namespace std;

int main() {
  System system;
  vector<Process> p = system.Processes();
  int n = p.size();
  NCursesDisplay::Display(system,n);
}