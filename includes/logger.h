/*! \class logger
 *  \brief The logger class is used to handle loggind for Anakata
 *
 *  This class defines various levels of logging for the application after
 *  reading from a configuration file
 */
class logger
{
public:
  logger();
  virtual ~logger();
  void printLog(string message);

protected:
  string log_location; /*!< Default location for the log file */
  int log_level;
};
