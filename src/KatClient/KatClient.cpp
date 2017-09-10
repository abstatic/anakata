#include "../../includes/base_conf.h"
#include "../../includes/KatClient.h"

using namespace std;

KatClient::KatClient(string c_alias, string c_ip, int c_port, string s_ip, int s_port, int c_down_port, string c_base)
{
  alias = c_alias;
  ip = c_ip;
  port = c_port;
  server_ip = s_ip;
  server_port = s_port;
  down_port = c_down_port;
  base_loc = c_base;
}

void KatClient::makeBaseFolder(string base_location)
{
 return; 
}
