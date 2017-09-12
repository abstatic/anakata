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
 */
KatServ::KatServ(string s_ip, int s_port, string s_repo_file, string s_client_info, string s_base)
{
  /*! TODO: INPUT Sanitisation for IP address
   *  \todo INPUT Sanitisation for IP address
   */
  ip          = s_ip;
  port        = s_port;
  file_list   = s_repo_file;
  client_list = s_client_info;
  base_loc    = s_base;
  blackbox    = new Logger(base_loc + "/server_log");
  populateClients();
  populateFiles();
}

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

    string client_alias      = tokens[0];
    string client_ip         = tokens[1];
    int client_port          = stoi(tokens[2]);
    int client_download_port = stoi(tokens[3]);

    client* c          = new client;
    c -> ip_address    = client_ip;
    c -> comm_port     = client_port;
    c -> download_port = client_download_port;

    clients[client_alias] = c;
  }

  // don't need to re read it again
  client_file.close();
}

void KatServ::populateFiles(void)
{
  // file path of the file list , repo list file
  string file_path = base_loc + "/" + file_list;

  struct stat buffer;
  if (stat(file_path.c_str(), &buffer) != 0)
  {
    string msg = (string)__FUNCTION__ + " ERROR: REPO FILEREAD ";
    perror(msg.c_str());
    string err = strerror(errno);
    blackbox -> record(msg + err);
    exit(1);
  }

  // read the data from file to the data structure
  ifstream repo_file;
  repo_file.open(file_path, ios::in);

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
      curr -> files_shared[file_name].push_back(file_path);
      blackbox -> record("EXISTING Added " + file_path + " to " + client_alias);
    }
    else
    {
      vector<string> paths;
      paths.push_back(path);
      curr -> files_shared[file_name] = paths;
      blackbox -> record("NEW Added " + file_path + " to " + client_alias);
    }

    // check if the filename exists or not
    if (files.count(file_name) > 0)
    {
      // was found
      files[file_name].push_back(client_alias);
      blackbox -> record("EXISTING new client host " + client_alias + " for file " + file_name);
    }
    else
    {
      // not found
      vector<string> aliases;
      aliases.push_back(client_alias);
      files[file_name] = aliases;
      blackbox -> record("NEW new client host " + client_alias + " for file " + file_name);
    }
  }

  // don't need to re read it again
  repo_file.close();
}

