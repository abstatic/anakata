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

#define PULSERATE 20

using namespace std;

struct client
{
  string ip_address;
  int comm_port;
  int download_port;
  time_t lastPulse;
  // [filename] ==> [filepath]
  unordered_map<string, string> files_shared;
};

class KatServ
{
public:
  KatServ(string, int, string, string, string);
  // virtual ~KatServ();
  string search(string); // search for a file
  string registerFile(string, string); // register a new resource
  string deregisterFile(string, string); // deregister a new resource
  string clientIP(string); // get the client details ?? 
  string keepAlive(string, string); // keep alive the client
  void start(void); // start listening on the given port
  void handleClient(int); // handle a incoming client request on a thread
  void updateRepoFile(void); // update the repo file with the in-memory data structure
  void updateInfoFile(void); // update the client info file
  bool isAlive(void); // checks if the given client is alive or not

  string ip; // the server ip
  int port; // the server port
  string file_list; // file containing list of shared files
  string client_list; // mapping of client data
  string base_loc; // base folder location

  // [client_alias] ===> client (struct pointer)
  unordered_map<string, client*> clients;// hashmap of clients;

  // [file_name] ===> vector<alias_names>
  unordered_map<string, unordered_set<string> > files; // hashmap of files

  Logger* blackbox; // logger for this class
private:
  void populateClients(void);
  void populateFiles(void);
};

#endif
