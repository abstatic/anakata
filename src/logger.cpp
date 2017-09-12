#include "../includes/logger.h"

using namespace std;

/**
 * Constructor for the logger
 */
Logger::Logger(string logfile_path)
{
  log_location = "None";
  log_level = 0;
  log_file = logfile_path;

  log_fp.open(log_file, ios::out | ios::app);
}

/**
 * This is the log reccording function. TIMESTAMP MESSAGE
 */
void Logger::record(std::string message)
{
  time_t t = time(0);
  struct tm* now = localtime(&t);
  log_fp <<(now -> tm_year + 1900) << '-'
         <<(now -> tm_mon + 1) << '-'
         << now -> tm_mday << ' '
         << now -> tm_hour << ':'
         << now -> tm_min << ':'
         << now -> tm_sec;
  log_fp << " " << message << std::endl;
}


/**
 * Destructor for the logger
 */
Logger::~Logger(void)
{
  log_fp.close();
}

/**
 * This method is used to tokenize a string with a delimiter provided
 */
void tokenize(string str, vector<string>& tokens, const string& delimiters)
{
  // skip the initial delimiters
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);

  // find the first non delimiter
  string::size_type pos = str.find_first_of(delimiters,lastPos);

  while (string::npos != pos || string::npos != lastPos)
  {
    // Found a token, add it to the vector
    tokens.push_back(str.substr(lastPos, pos - lastPos));

    // Skip delimiters, on to the next token we go
    lastPos = str.find_first_not_of(delimiters, pos);

    // Find next "non-delimiter" position of next delimiter
    pos = str.find_first_of(delimiters, lastPos);
  }
}

/**
 * This method is used to sanitize a string by removing a particular
 * character
 */
void sanitize(string& str, char c)
{
  str.erase(remove(str.begin(), str.end(), c), str.end());
}
