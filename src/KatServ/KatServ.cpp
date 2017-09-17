/**
 * Filename: "KatServ.c"
 *
 * Description: This is actual implementation of ListingServer
 *
 * Author: Abhishek Shrivastava <abhishek.shrivastava.ts@gmail.com>
 **/
#include "../../includes/KatServ.h"
#include "../../includes/logger.h"

/**
 * This is the consturctor method for creating a anakata server
 *
 * Does the following-
 * 1. Initializes the internal variables
 * 2. Reads the disk files onto the in_memory data structures
 *
 * @param s_ip          = Server IP
 * @param s_port        = Server Port
 * @param s_repo_file   = Name of repo file
 * @param s_client_info = Name of client info file
 * @param s_base        = Base directory of file
 */
KatServ::KatServ(string s_ip, int s_port, string s_repo_file, string s_client_info, string s_base)
{
  ip          = s_ip;
  port        = s_port;
  file_list   = s_repo_file;
  client_list = s_client_info;
  base_loc    = s_base;
  blackbox    = new Logger(base_loc + "/server_log");
  populateClients();
  populateFiles();
}

/**
 * This method reads the given clients file and populates the inmemory data
 * strcutures
 *
 */
void KatServ::populateClients(void)
{
  string file_path = base_loc + "/" + client_list;

  // check if the file given is valid or not
  struct stat buffer;
  if (stat(file_path.c_str(), &buffer) != 0)
  {
    string msg = (string)__FUNCTION__ + " ERROR: INFO FILEREAD ";
    perror(msg.c_str());
    string err = strerror(errno);
    blackbox -> record(msg + err);
    exit(1);
  }

  // read the data from file to the data structure
  ifstream client_file;
  client_file.open(file_path, ios::in);

  string line;
  while(!client_file.eof())
  {
    getline(client_file, line);

    vector<string> tokens;

    tokenize(line, tokens, ":");

    // for debugging purpose
    blackbox -> record("INFO String tokenized as- ");
    for (string s: tokens)
      blackbox -> record(s);

    if (tokens.size() == 0)
      break;

    string client_alias      = tokens[0];
    string client_ip         = tokens[1];
    int client_port          = stoi(tokens[2]);
    int client_download_port = stoi(tokens[3]);

    client* c          = new client;
    c -> ip_address    = client_ip;
    c -> comm_port     = client_port;
    c -> download_port = client_download_port;
    c -> lastPulse     = -1;

    clients[client_alias] = c;
  }

  // don't need to re read it again
  client_file.close();
}

/**
 * This method reads the repo file and populates the inmemory maps
 */
void KatServ::populateFiles(void)
{
  // file path of the file list , repo list file
  string repo_file_path = base_loc + "/" + file_list;

  struct stat buffer;
  if (stat(repo_file_path.c_str(), &buffer) != 0)
  {
    string msg = (string)__FUNCTION__ + " ERROR: REPO FILEREAD ";
    perror(msg.c_str());
    string err = strerror(errno);
    blackbox -> record(msg + err);
    exit(1);
  }

  // read the data from file to the data structure
  ifstream repo_file;
  repo_file.open(repo_file_path, ios::in);

  string line;
  while(!repo_file.eof())
  {
    getline(repo_file, line);

    vector<string> tokens;
    tokenize(line, tokens, ":");

    // for debugging purpose
    blackbox -> record("REPO String tokenized as- ");
    for (string s: tokens)
      blackbox -> record(s);

    if (tokens.size() == 0)
      break;

    string file_name    = tokens[0]; // name of file which the client is sharing
    string path         = tokens[1]; // relative path in client of file
    string client_alias = tokens[2]; // alias of the respective client

    // retrieve the cclient
    // the client alias must be already present in the clients map
    // else just ignore the line read
    unordered_map<string, client*>::iterator it = clients.find(client_alias);
    if (it == clients.end())
    {
      blackbox -> record("FOUND DIRTY ALIAS REFERENCE: " + line);
      continue;
    }

    // get the reference to client details struct
    client* curr = it -> second;

    if (curr -> files_shared.count(file_name) > 0)
    {
      curr -> files_shared[file_name] = path;
      blackbox -> record("EXISTING updated" + path + " to " + client_alias);
    }
    else
    {
      curr -> files_shared[file_name] = path;
      blackbox -> record("NEW Added " + path + " to " + client_alias);
    }

    // check if the filename exists or not
    if (files.count(file_name) > 0)
    {
      // was found
      files[file_name].insert(client_alias);
      blackbox -> record("EXISTING new client host " + client_alias + " for file " + file_name);
    }
    else
    {
      // not found
      unordered_set<string> aliases;
      aliases.insert(client_alias);
      files[file_name] = aliases;
      blackbox -> record("NEW new client host " + client_alias + " for file " + file_name);
    }
  }

  // don't need to re read it again
  repo_file.close();
}

/**
 * Start the server
 * Bind and use threads for handling incoming connections
 */
void KatServ::start(void)
{
  int listenfd = 0;
  int connfd = 0;

  struct sockaddr_in serv_addr;

  // create a socket on listen file descriptor
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  if (listenfd == -1) // exit the server if socket creation fails
  {
    string msg = (string)__FUNCTION__ + " ERROR: SOCKET CREATION ";
    perror(msg.c_str());
    string err = strerror(errno);
    blackbox -> record(msg + err);
    cout << "Please restart the server." << endl;
    exit(1);
  }

  // intialize the socket struct and buffers
  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET; // defines the family of socket, internet family used
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // which IP to listen on // TODO replace by inet_addr(ip);
  serv_addr.sin_port = htons(port); // port number to listen on

  // bind the socket now
  int res = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  // if the bind call fails
  if (res == -1)
  {
    string msg = (string)__FUNCTION__ + " ERROR: SOCKET BINDING";
    perror(msg.c_str());
    string err = strerror(errno);
    blackbox -> record(msg + err);
    cout << "Cannot bind. Please restart the server." << endl;
    exit(1);
  }

  listen(listenfd, 15);

  struct sockaddr client_addr;
  socklen_t client_len = sizeof(client_addr);

  while(1)
  {
    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_len);
    thread t(&KatServ::handleClient, this, connfd);
    t.detach();
  }
}

/**
 * This method searches for a given file name in the in memory maps.
 * Returns the results in the format as the client expects it to
 *
 * @param file_name = Filename to be searched
 *
 * @return Returns the string pack containing the search results
 */
string KatServ::search(string file_name)
{
  string result;
  vector <pair<string, string> > matching;

  for (auto kv : files)
  {
    string map_filename = kv.first;

    // making the search case insensitive
    string copy_map_filename = map_filename;
    string copy_file_name = file_name;

    transform(copy_map_filename.begin(), copy_map_filename.end(), copy_map_filename.begin(), ::tolower);
    transform(copy_file_name.begin(), copy_file_name.end(), copy_file_name.begin(), ::tolower);


    //this is happening on a string. hence the 0
    if (copy_map_filename.find(copy_file_name) == 0)
    {
      for (auto als : kv.second)
      {
        pair<string, string> p(map_filename, als);
        matching.push_back(p);
      }
    }
  }

  for (auto s : matching)
  {
    string line;

    string file = s.first;
    string alias = s.second;

    client* curr        = clients[alias];
    string cl_comm_port = to_string(curr -> comm_port);
    string cl_down_port = to_string(curr -> download_port);
    string cl_ip        = curr -> ip_address;
    string cl_file_path = curr -> files_shared[file];

    blackbox -> record("Sending: " + line);

    line = file + ":" + cl_file_path + ":" + alias + ":" + cl_ip + ":" + cl_comm_port + ":" + cl_down_port + "`";

    result += line;
  }

  result += '\0';
  return result;
}

/**
 * This method is used to register a file to the server. Registers the file
 * into the in memory maps and also updates the repo file.
 *
 * @param file_path = the file path to be shared
 * @param client_alias = alias of the client which is sharing the file
 *
 * @return the result of the operation
 */
string KatServ::registerFile(string file_path, string client_alias)
{
  vector<string> tokens;
  tokenize(file_path, tokens, "/");

  string file_name = tokens[tokens.size() - 1];

  // add to the files unordered_map
  // check if the filename exists or not
  if (files.count(file_name) > 0)
  {
    // was found
    files[file_name].insert(client_alias);
    blackbox -> record("EXISTING new client host " + client_alias + " for file " + file_name);
  }
  else
  {
    // not found
    unordered_set<string> aliases;
    aliases.insert(client_alias);
    files[file_name] = aliases;
    blackbox -> record("NEW new client host " + client_alias + " for file " + file_name);
  }

  // update the file listing of the alias map too!
  client* curr = clients[client_alias];
  curr -> files_shared[file_name] = file_path;

  updateRepoFile();

  return "True";
}

/**
 * This method is used to dump the contents of the inmemory maps of files
 * shared into the
 * repo file.
 *
 */
void KatServ::updateRepoFile(void)
{
  ofstream repofile;
  repofile.open(file_list, ios::out | ios::trunc);
  client* temp;
  for (auto client : clients)
  {
    time_t current;
    time(&current);

    string alias = client.first;
    temp         = client.second;

    // if (current - temp -> lastPulse > PULSERATE * 1000)
      // continue;

    for (auto f : temp -> files_shared)
      repofile << f.first << ":" << f.second << ":" << alias << endl;
  }
  // repofile.close();
}
/**
 * This method is used to dump the contents of the client maps into the client
 * info file
 */
void KatServ::updateInfoFile(void)
{
  ofstream infofile;
  infofile.open(client_list, ios::out | ios::trunc);

  for(auto c : clients)
  {
    string alias = c.first;
    client* cl = c.second;

    infofile << alias << ":" << cl -> ip_address << ":" << cl -> comm_port << ":" << cl -> download_port << endl;
  }
}

/**
 * This method is used to handle the client. Called as a thread
 *
 * @param connfd = Socket descriptor of the connected client
 *
 */
void KatServ::handleClient(int connfd)
{
  char recvBuff[1024];
  bzero(recvBuff, sizeof(recvBuff));
  int bytes_read = recv(connfd, recvBuff, sizeof(recvBuff), 0);

  if (bytes_read == 0 || bytes_read == -1)
  {
    string msg = (string)__FUNCTION__ + " ERROR";
    perror(msg.c_str());
    string err = strerror(errno);
    blackbox -> record(msg + err);
    close(connfd);
  }

  string command_string(recvBuff);
  blackbox -> record(command_string);

  vector<string> tokens;
  tokenize(command_string, tokens, "`");

  string client_alias = tokens[2];

  int cmd = interpret_command(tokens[0]);

  string result;
  switch (cmd)
  {
    case SEARCH:
      {
        string file_name = tokens[1];
        result = search(file_name);
      }
      break;
    case SHARE:
      {
        string file_path = tokens[1];
        result = registerFile(file_path, client_alias);
      }
      break;
    case DEL:
      {
        string file_path = tokens[1];
        result = deregisterFile(file_path, client_alias);
      }
      break;
    case IP:
      {
         result = clientIP(client_alias);
      }
      break;
    case PULSE:
      {
        string client_details = tokens[1];
        result = keepAlive(client_alias, client_details);
      }
      break;
    default:
      {
        result = "Failure: Unsupported command";
      }
      break;
  }

  int len = result.length();
  cout << "Sending out " << result << endl;
  send(connfd, result.c_str(), len, 0);

  close(connfd);
}


/**
 * This methos is used to remove a given file from the inmemory data
 * strctures.
 *
 * Also updates the repofile;
 *
 * @param file_path    = path of the file which is shared
 * @param client_alias = Alias of the client which wants to remove the file
 */
string KatServ::deregisterFile(string file_path, string client_alias)
{

  vector<string> tokens;
  tokenize(file_path, tokens, "/");

  string file_name = tokens[tokens.size() - 1];

  cout << "Deregistering " << file_path << " " << file_name << " " << client_alias << endl;

  // add to the files unordered_map
  // check if the filename exists or not
  if (files.count(file_name) > 0)
  {
    // was found
    files[file_name].erase(client_alias);
    blackbox -> record("EXISTING new client host " + client_alias + " for file " + file_name);
  }
  else
  {
    return "False";
  }

  // update the file listing of the alias map too!
  client* curr = clients[client_alias];

  if (curr -> files_shared.find(file_name) != curr -> files_shared.end())
    curr -> files_shared.erase(file_name);
  else
    return "False";

  updateRepoFile();

  return "True";
}


// return the ip address of the given client
string KatServ::clientIP(string alias)
{
  if (clients.find(alias) == clients.end())
    return "Fail:";

  client* c = clients[alias];
  int d_port = c -> download_port;
  string ret = c -> ip_address + ":" + to_string(d_port) + ":";
  return ret;
}

// received a heartbeat, give new life to client
string KatServ::keepAlive(string client_alias, string client_details)
{
  vector<string> cl_details;
  tokenize(client_details, cl_details, ":");

  time_t current;
  time(&current);

  client* c;
  if (clients.find(client_alias) == clients.end())
  {
    c = new client;
    clients[client_alias] = c;
  }
  else
    c = clients[client_alias];

  c -> ip_address    = cl_details[0];
  c -> comm_port     = stoi(cl_details[1]);
  c -> download_port = stoi(cl_details[2]);
  c -> lastPulse     = current;

  c -> lastPulse = current;

  updateInfoFile();
  return "True";
}
