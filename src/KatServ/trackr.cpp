/**
 * Filename: "trackr.c"
 *
 * Description: This is the main class which instantiates and drives a listing
 * server
 *
 * Author: Abhishek Shrivastava <abhishek.shrivastava.ts@gmail.com>
 **/
#include "../../includes/KatServ.h"

using namespace std;

int main(int argc, const char *argv[])
{
  // eg. ./client_20172001 "Bob's Computer" 192.168.1.20 8754 192.168.1.2 8750 14000 ~/Desktop
  // if (argc != 6)
  // {
    // cout << "Usage: " << argv[0] << " server_ip server_port main_repofile client_file_list server_root";
    // return 1;
  // }

  string s_ip          = "hello";//argv[1];
  int s_port           = 23;//stoi(argv[2]);
  string s_repo_file   = argv[1];//argv[3];
  string s_client_info = argv[2];//argv[4];
  string s_base        = argv[3];//argv[5];

  KatServ trackr(s_ip, s_port, s_repo_file, s_client_info, s_base);

  return 0;
}
