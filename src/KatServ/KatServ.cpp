/**
 * Filename: "KatServ.c"
 *
 * Description: This is actual implementation of ListingServer
 *
 * Author: Abhishek Shrivastava <abhishek.shrivastava.ts@gmail.com>
 **/
#include "../../includes/base_conf.h"
#include "../../includes/KatServ.h"

//./executable server_ip server_port main_repofile client_list_file server_root

//eg. ./server_20172001 192.168.1.2 8750 repo.txt list.txt ~/Desktop/eval

KatServ::KatServ(string s_ip, int s_port, string s_repo_file, string s_client_info, string s_base)
{
  string ip = s_ip;
  int port = s_port;
  string file_list = s_repo_file;
  string client_list = s_client_info;
}
