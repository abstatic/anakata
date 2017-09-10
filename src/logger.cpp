#include "../includes/logger.h"
#include <fstream>
#include <iostream>

using namespace std;

/**
 * Constructor for the logger
 */
Logger::Logger(void)
{
  log_location = "None";
  log_level = 0;
  std::string log_file = "currentLOG";

  log_fp.open(log_file, ios::out | ios::app);
}

void Logger::writeLog(std::string message)
{
  log_fp << message << std::endl;
}


/**
 * Destructor for the logger
 */
Logger::~Logger(void)
{
  log_fp.close();
}


