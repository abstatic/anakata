/**
 * Filename: "trackr.c"
 *
 * Description: This is the main class which instantiates and drives a listing
 * server
 *
 * Author: Abhishek Shrivastava <abhishek.shrivastava.ts@gmail.com>
 **/
#include "../../includes/base_conf.h"
#include "../../includes/KatServ.h"

using namespace std;

int main(int argc, const char *argv[])
{
  // eg. ./client_20172001 "Bob's Computer" 192.168.1.20 8754 192.168.1.2 8750 14000 ~/Desktop
  string s_ip     = argv[1];
  int s_port      = stoi(argv[2]);
  string s_repo_file = argv[3];
  string s_client_info = argv[4];
  string s_base   = argv[5];

  KatServ trackr(s_ip, s_port, s_repo_file, s_client_info, s_base);

  return 0;
}
