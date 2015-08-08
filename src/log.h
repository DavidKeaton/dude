#ifndef  LOG_INC
#define  LOG_INC

#include <string>
#include <fstream>
#include <cstdarg>

/** log_level_e
 * Determines the level of logging that takes place, based on how
 * important the information is.
 */
enum log_type {
    LOG_DEBUG = 0,  // debugging information (calls with arguments, return values)
    LOG_INFO,       // non-error information ('loaded doom2.wad as main iwad')
    LOG_WARN,       // non-critical errors ('exporting map before building nodes and rejects')
    LOG_ERROR,      // critical errors ('unable to load WAD, does not exist')
    LOG_FATAL       // fatal errors ('unable to allocate memory for internal structures')
};

class logger
{
    private:
        std::fstream fd;
#if defined(DEBUG)
        log_type log_level = LOG_DEBUG;
#else
        log_type log_level = LOG_WARN;
#endif
        // write to the log file (all operator() functions call this)
        void write(log_type type, const char *fmt, va_list va);
    public:
        // initiate logger with file (required)
        logger(const std::string &filename);
        ~logger(void);

        // write the logfile with `type' category
        void operator()(log_type type, const char *fmt, ...);
        // write to the logfile, with category `LOG_INFO'
        void operator()(const char *fmt, ...);

        // set the filter level of log messages, any message
        // that is below this `log_type' filter will be ignored
        void set_level(log_type type);
        // returns the filter log level (`log_level')
        log_type get_level(void) const;
};

extern logger *log;

#endif   /* ----- #ifndef LOG_INC  ----- */
/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */

