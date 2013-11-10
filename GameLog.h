#pragma once
#include "Utils.h"

class GameLog
{
private:
    std::ostream* m_cLogFile;
    int m_iLogLevel;
    std::string m_sLogCaller;

public:
    GameLog(const char *caller, std::ostream &os = LOG_FILE, int log_level = LOG_LEVEL);
    ~GameLog();
    void Log(const std::string &msg, int log_level = 5);
    void LogError(const std::string &msg);
    void LogSdlError(const std::string &function_name);

    // getters and setters
    void SetCaller(std::string &caller);
    void SetLogLevel(int log_level);
    void SetLogFile( std::ostream &os );

    int GetLogLevel();
    std::string GetCaller();
};
