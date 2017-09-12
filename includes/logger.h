#ifndef logger
#define logger 
/*! \class logger
 *  \brief The logger class is used to handle loggind for Anakata
 *
 *  This class defines various levels of logging for the application after
 *  reading from a configuration file
 */
#include "base_conf.h"

using namespace std;

class Logger
{
public:
  Logger(string);
  virtual ~Logger();
  void record(std::string message);

protected:
  std::string log_location; /*!< Default location for the log file */
  std::string log_file;
  int log_level;
  std::ofstream log_fp;
};

void tokenize(string str, vector<string>& tokens, const string& delimiters = " ");
void sanitize(string&, char);
#endif /* ifndef logger */
