#ifndef __TINY_LOGGER_HPP__
#define __TINY_LOGGER_HPP__

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>

#include <sys/time.h>

using std::string;
using std::ofstream;
using std::ostream;
using std::stringstream;
using std::ostringstream;
using std::ios;
using std::endl;
using std::clog;

const int kLogLevelTrace = 0;
const int kLogLevelDebug = 1;
const int kLogLevelInfo = 2;
const int kLogLevelWarn = 3;
const int kLogLevelError = 4;
const int kLogLevelFatal = 5;

const int LOG_LEVEL_TRACE = kLogLevelTrace;
const int LOG_LEVEL_DEBUG = kLogLevelDebug;
const int LOG_LEVEL_INFO = kLogLevelInfo;
const int LOG_LEVEL_WARN = kLogLevelWarn;
const int LOG_LEVEL_ERROR = kLogLevelError;
const int LOG_LEVEL_FATAL = kLogLevelFatal;

const string LOG_LEVEL_NAME[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL" };

class TinyLogger {
public:
    string _path;
    int _level;
    
public:
    TinyLogger(string path="", int level = kLogLevelTrace)
    {
        _path = path;
        _level = level;
    }
    
    void log(int level, const string &msg, const char* filename, const int &line)
    {
        if (level<_level) return;
        ostream *pOS = NULL;
        if (_path != "")
        {
            pOS = new ofstream(_path.c_str(), ios::app);
        }
        else
        {
            pOS = &clog;
        }
        ostream &os = *pOS;
        time_t timep;
        tm *pTM;
        time(&timep);
        //char *timestr = ctime(&timep);
        //string datetime = timestr; //YYYY-MM-DD hh:mm:ss.SSS
        pTM = localtime(&timep);
        char pTimeStr[25];
        sprintf(pTimeStr, 
            "%04d-%02d-%02d %02d:%02d:%02d.%03d", 
            pTM->tm_year+1900,
            pTM->tm_mon+1,
            pTM->tm_mday,
            pTM->tm_hour,
            pTM->tm_min,
            pTM->tm_sec,
            0
        );
        //format
        string datetime = pTimeStr;
        if (level>kLogLevelFatal) level = kLogLevelFatal;
        if (level<LOG_LEVEL_TRACE) level = LOG_LEVEL_TRACE;
        // datetime [level] message [filename - line]
        os << datetime << " [" << LOG_LEVEL_NAME[level] << "] " << msg << " [" << filename << "-" << line << "]" << endl;
        os.clear();
        //os.close();
    }
};

#define TLOG_TRACE(logger, msg){\
    ostringstream oss;\
    oss<<msg;\
    logger.log(kLogLevelTrace,oss.str(),__FILE__,__LINE__);\
}

#define TLOG_DEBUG(logger, msg){\
    ostringstream oss;\
    oss<<msg;\
    logger.log(kLogLevelDebug,oss.str(),__FILE__,__LINE__);\
}

#define TLOG_INFO(logger, msg){\
    ostringstream oss;\
    oss<<msg;\
    logger.log(kLogLevelInfo,oss.str(),__FILE__,__LINE__);\
}

#define TLOG_WARN(logger, msg){\
    ostringstream oss;\
    oss<<msg;\
    logger.log(kLogLevelWarn,oss.str(),__FILE__,__LINE__);\
}

#define TLOG_ERROR(logger, msg){\
    ostringstream oss;\
    oss<<msg;\
    logger.log(kLogLevelError,oss.str(),__FILE__,__LINE__);\
}

#define TLOG_FATAL(logger, msg){\
    ostringstream oss;\
    oss<<msg;\
    logger.log(kLogLevelFatal,oss.str(),__FILE__,__LINE__);\
}

#endif//__TINY_LOGGER_HPP__
