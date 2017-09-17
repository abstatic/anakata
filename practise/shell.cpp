#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using namespace std;

std::string exec(const char* cmd)
{
  char buffer[1024];
  string cmdi(cmd);
  cmdi += " 2>/dev/null";
  FILE* pipe = popen(cmdi.c_str(), "r");

  while (!feof(pipe))
  {
    fgets(buffer, 1024, pipe);
    cout << buffer;
  }
  perror("ERROR ");
  return "DONE";
}

int main(void)
{
  string s;
  cin >> s;
  exec(s.c_str());
  return 0;
}
