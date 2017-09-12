#include "../../includes/KatClient.h"
#include "../../includes/logger.h"

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
  haveSearchResults = false;

  blackbox = new Logger(base_loc + "/client_log");
}

int KatClient::interpret_command(string cmd_str)
{
  if (cmd_str == "get")
    return GET;
  else if (cmd_str == "share")
    return SHARE;
  else if (cmd_str == "del")
    return DEL;
  else if (cmd_str == "exec")
    return EXEC;
  else if (cmd_str == "search")
    return SEARCH;
  else
    return 0;
}

void KatClient::start(void)
{
  cout << "Starting katalyn..." << endl;
  cout << "Starting to send heart beats";
}

void KatClient::downloadFile(int hit_no)
{
  cout << "Downloading hit " << hit_no << endl;
}

void KatClient::downloadFile(string client_alias, string relative_path, string outfile)
{
  cout << "Download file on " << client_alias << " from " << relative_path << " saving as " << outfile << endl;
}

void KatClient::registerFile(string fileSharePath)
{
  cout << "Registering file " << fileSharePath << endl;
}

void KatClient::deregisterFile(string fileSharePath)
{
  cout << "Deregistering file " << fileSharePath << endl;
}

void KatClient::exec_command(string rpc_alias, string shell_command)
{
  cout << "Executing command " << shell_command << " on " << rpc_alias << endl;
}

void KatClient::searchFile(string file_name)
{
  cout << "Search file " << file_name << endl;
}

