#ifndef katclient_H
#define katclient_H

#include "base_conf.h"
#include "logger.h"

#define GET 1
#define SHARE 2
#define DEL 3
#define EXEC 4
#define SEARCH 5

using namespace std;

/*! \class KatClient
 *  \brief Brief class description
 *
 *  Detailed description
 */
class KatClient
{
public:
  // Constructor and Method declarations
  KatClient(string, string, int, string, int, int, string);
  // virtual ~KatClient(); // desturctor MUST be defined. 

  // member functions go here
  void registerFile(string); // share file details to trackr
  void downloadFile(string, string, string); // download a file from other client;
  void downloadFile(int); // in case search result present
  void searchFile(string); // search a file on trackr;
  void deregisterFile(string); // remove a file from trackr;
  void start(void);
  void isAlive(void); // send heartbeats to trackr
  void exec_command(string, string); // execute command on server
  int interpret_command(string); // interpret the command line command

  // variable declarations;
  string alias; // the client alias name
  string ip; // the ip of the client
  int port; // port number of client
  string server_ip; // the ip address of the listing server
  string server_port; // the server port on which to connect
  int down_port; // the port at which cliend will download
  string base_loc; // the location of base_folder of client
  bool haveSearchResults;

  Logger* blackbox; // logger for this class
private:
  void makeBaseFolder(string base_location);
};

#endif /* ifndef KatClient_H */
