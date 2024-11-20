#ifndef FEHUTILITY_H
#define FEHUTILITY_H


/* Utility Macros for error logging */
#define CONSOLE_RED(val) "\033[31m" << val << "\033[0m"
#define CONSOLE_GREEN(val) "\033[32m" << val << "\033[0m"
#define CONSOLE_YELLOW(val) "\033[33m" << val << "\033[0m"
#define CONSOLE_BLUE(val) "\033[34m" << val << "\033[0m"

#define CONSOLE_WARN(val) CONSOLE_YELLOW("WARNING: ") << val
#define CONSOLE_ERR(val) CONSOLE_RED("ERROR: ") << val



/// @brief Sleep for a specified number of milliseconds
/// @note an int param means MILLISECONDS, not seconds. Use float or double for seconds
/// @param msec The number of milliseconds to sleep
void Sleep( int msec );

/// @brief Sleep for a specified number of seconds
/// @param sec The number of seconds to sleep
void Sleep( float sec );

/// @brief Sleep for a specified number of seconds
/// @param sec The number of seconds to sleep
void Sleep( double sec );

double TimeNow();
unsigned int TimeNowSec();
unsigned long TimeNowMSec();
void ResetTime();

#endif // FEHUTILITY_H
