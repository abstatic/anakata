#ifndef katclient_H
#define katclient_H

#include "base_conf.h"

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
  void registerFile(void);
  void downloadFile(void);
  void searchFile(void);
  void deregisterFile(void);

  // variable declarations;
  string alias; // the client alias name
  string ip; // the ip of the client
  int port; // port number of client
  string server_ip; // the ip address of the listing server
  string server_port; // the server port on which to connect
  int down_port; // the port at which cliend will download
  string base_loc; // the location of base_folder of client

private:
  void makeBaseFolder(string base_location);
};

#endif /* ifndef KatClient_H */
