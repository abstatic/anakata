#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void)
{
  string STRING;
  ifstream infile;
  infile.open("test.txt");

  while (!infile.eof())
  {
    getline(infile, STRING);
    cout << STRING;
  }
  infile.close();
  return 0;
}
