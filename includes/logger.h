#ifndef logger
#define logger 
/*! \class logger
 *  \brief The logger class is used to handle loggind for Anakata
 *
 *  This class defines various levels of logging for the application after
 *  reading from a configuration file
 */
#include "base_conf.h"
class Logger
{
public:
  Logger(void);
  virtual ~Logger();
  void writeLog(std::string message);

protected:
  std::string log_location; /*!< Default location for the log file */
  std::string log_file;
  int log_level;
  std::ofstream log_fp;
};
#endif /* ifndef logger */
