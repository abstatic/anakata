#include "../../includes/KatClient.h"
#include "../../includes/logger.h"

using namespace std;

int main(int argc, const char *argv[])
{
  // eg. ./client_20172001 "Bob's Computer" 192.168.1.20 8754 192.168.1.2 8750 14000 ~/Desktop
  // if (argc != 8)
  // {
    // cout << "Usage: " << argv[0] << " client_alias client_ip client_port server_ip server_port downloading_port client_root" << endl;
    // return 1;
  // }

  string c_alias  = "DUMMY";//argv[1];
  string c_ip     = "DIRTYIP";//argv[2];
  int c_port      = 2345;//stoi(argv[3]);
  string s_ip     = "SERVERIP";//argv[4];
  int s_port      = 5432;//stoi(argv[5]);
  int c_down_port = 5565;//stoi(argv[6]);
  string c_base   = ".";//argv[7];

  KatClient katalyn(c_alias, c_ip, c_port, s_ip, s_port, c_down_port, c_base);

  string line;
  while (getline(cin, line))
  {
    vector<string> tokens;
    tokenize(line, tokens, "\"");

    // because switch cannot use string
    sanitize(tokens[0], ' ');
    int command = katalyn.interpret_command(tokens[0]);

    switch(command)
    {
      case GET:
        {
          // if we are downloading after a search
          if (tokens[1][0] == '[')
          {
            katalyn.blackbox -> record("Get command for: " + tokens[1]  + " outfile  " + tokens[2]);

            if (katalyn.haveSearchResults)
            {
              string hit_n = tokens[1];

              sanitize(hit_n, '[');
              sanitize(hit_n, ']');

              int hit_no = stoi(hit_n);

              katalyn.downloadFile(hit_no);
            }
            else
              cout << "No search results exist. Try again." << endl;
          }
          else
          {
            string client_alias  = tokens[1];
            string relative_path = tokens[3];
            string outfile       = tokens[5];

            sanitize(client_alias, '"');
            sanitize(relative_path, '"');
            sanitize(outfile, '"');

            katalyn.downloadFile(client_alias, relative_path, outfile);
            katalyn.blackbox -> record("Get command on " + client_alias + " path " + relative_path + " outputfile " + outfile);
          }
        }
        break;
      case SHARE:
        {
          string file_share_path = tokens[1];

          sanitize(file_share_path, '"');

          katalyn.blackbox -> record("Registering file: " + file_share_path + " on server");
          katalyn.registerFile(file_share_path);
        }
        break;
      case DEL:
        {
          string file_share_path = tokens[1];

          sanitize(file_share_path, '"');

          katalyn.blackbox -> record("Deregistering file: " + file_share_path + " on server");
          katalyn.deregisterFile(file_share_path);
        }
        break;
      case EXEC:
        {
          string rpc_alias     = tokens[1];
          string shell_command = tokens[3];

          sanitize(rpc_alias, '"');
          sanitize(shell_command, '"');

          katalyn.blackbox -> record("Executing shell command " + shell_command + " on " + rpc_alias);
          katalyn.exec_command(rpc_alias, shell_command);
        }
        break;
      case SEARCH:
        {
          string file_name = tokens[1];

          sanitize(file_name, '"');

          katalyn.blackbox -> record("Searching for file: " + file_name + " on server");
          katalyn.searchFile(file_name);
        }
        break;
      default:
        cout << "Unknown Command. EOF to exit" << endl;
    }
  }

  cout << "Bye Bye" << endl;

  return 0;
}
