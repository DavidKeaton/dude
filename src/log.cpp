#include "log.h"

#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdarg>
#include <ctime>


#define MAX_LOG_LINE    65535
#define CHUNK           4096

static std::map<log_type, const std::string> types = {
    {LOG_DEBUG, "DBG"},
    {LOG_FATAL, "FTL"},
    {LOG_ERROR, "ERR"},
    {LOG_WARN,  "WRN"},
    {LOG_INFO,  "NFO"}
};

logger::logger(const std::string &filename)
{
    fd.open(filename, std::ios_base::out | std::ios_base::app);
    if(!fd.good()) {
        printf("Unable to open log file %s.\n", filename.c_str());
        if(fd.is_open()) {
            fd.close();
        }
    }
}

logger::~logger(void)
{
    if(fd.is_open()) {
        fd.close();
    }
}

void logger::write(log_type type, const char *fmt, va_list va)
{
    // if less than the filter level, early exit
    if(type < get_level()) {
        return;
    }
    // maximum size for `log_type' level is 12
    char *level = new char[12];
    // if the type doesn't exist, use `LOG_INFO'
    auto t = (types.find(type) == types.end()) ? 
        types[LOG_INFO] : types[type];
    std::snprintf(level, 12, "[%s]: ", t.c_str());
    // maximum size of string per line is MAX_LOG_LINE above
    int size = (strlen(fmt) > MAX_LOG_LINE) ? 
        MAX_LOG_LINE : ((strlen(fmt) % CHUNK) + 1) * CHUNK;
    char *msg = new char[size];
    vsnprintf(msg, size, fmt, va);
    // get now for the time of the log message, display in ISO format
    std::time_t now = std::time(NULL);
    char *time = new char[4096];
    std::strftime(time, 4096, "[%F@%T%z]", std::gmtime(&now));
    // write to log file
    fd << time << level << msg << std::endl;
    delete[] time;
    delete[] msg;
    delete[] level;
}

void logger::operator()(log_type type, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    write(type, fmt, va);
    va_end(va);
}

void logger::operator()(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
#if defined(DEBUG)
    write(LOG_DEBUG, fmt, va);
#else
    write(LOG_INFO, fmt, va);
#endif
}

void logger::set_level(log_type type)
{
    log_level = type;
}

log_type logger::get_level(void) const
{
    return log_level;
}

/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */
