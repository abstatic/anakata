#include "../../includes/base_conf.h"
#include "../../includes/KatClient.h"

using namespace std;

int main(int argc, const char *argv[])
{
  // eg. ./client_20172001 "Bob's Computer" 192.168.1.20 8754 192.168.1.2 8750 14000 ~/Desktop
  if (argc != 8)
  {
    cout << "Usage: " << argv[0] << " client_alias client_ip client_port server_ip\
      server_port downloading_port client_root" << endl;
    return 1;
  }
  string c_alias  = argv[1];
  string c_ip     = argv[2];
  int c_port      = stoi(argv[3]);
  string s_ip     = argv[4];
  int s_port      = stoi(argv[5]);
  int c_down_port = stoi(argv[6]);
  string c_base   = argv[7];

  KatClient katalyn(c_alias, c_ip, c_port, s_ip, s_port, c_down_port, c_base);

  return 0;
}
