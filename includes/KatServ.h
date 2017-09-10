#ifndef katserv_h
#define katserv_h

/*! \class KatServ
 *  \brief This is the base class for the listing server
 *
 *  KatServ is the file listing server which listens of port 
 *
 */
#include "base_conf.h"

using namespace std;

class KatServ
{
public:
  KatServ(string, int, string, string, string);
  virtual ~KatServ();
  void search();
  void share();
  void deregister();

  string ip; // the server ip
  int port; // the server port
  string file_list; // file containing list of shared files
  string client_list; // mapping of client data
  string base_loc; // base folder location
private:
};

#endif
