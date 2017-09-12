#ifndef katserv_h
#define katserv_h

/*! \class KatServ
 *  \brief This is the base class for the listing server
 *
 *  KatServ is the file listing server which listens of port 
 *
 */
#include "base_conf.h"
#include "logger.h"

using namespace std;

struct client
{
  string ip_address;
  int comm_port;
  int download_port;
  // [filename] ==> [filepath]
  unordered_map<string, vector<string> > files_shared;
};

class KatServ
{
public:
  KatServ(string, int, string, string, string);
  // virtual ~KatServ();
  void search();
  void register_file();
  void deregister_file();

  string ip; // the server ip
  int port; // the server port
  string file_list; // file containing list of shared files
  string client_list; // mapping of client data
  string base_loc; // base folder location

  // [client_alias] ===> client (struct pointer)
  unordered_map<string, client*> clients;// hashmap of clients;

  // [file_name] ===> vector<alias_names>
  map<string, vector<string> > files; // hashmap of files

  Logger* blackbox; // logger for this class
private:
  void populateClients(void);
  void populateFiles(void);
};

#endif
