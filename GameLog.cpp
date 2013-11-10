#include "GameLog.h"

/**
* Initialize the game log, usually done in the game Engine itself
* @param  caller    the current caller name to print
* @param  os        the log file handler to print to
* @param  log_level the level of logging we are currently doing
* @return           Returns an instance of GameLog
*/
GameLog::GameLog( const char *caller, std::ostream &os /*= LOG_FILE*/, int log_level /*= LOG_LEVEL*/ )
{
    m_sLogCaller = caller;
    m_cLogFile = &os;
    m_iLogLevel = log_level;
}

GameLog::~GameLog()
{
    m_cLogFile = nullptr;

    m_sLogCaller.clear();

    m_iLogLevel = 0;
}


/**
* Log Some output to our file handler
* @param msg       the message to log
* @param log_level the level of logging to use
*/
void GameLog::Log(const std::string &msg, int log_level)
{
    if(m_iLogLevel >= log_level)
    {
        *m_cLogFile << m_sLogCaller << ": " << msg << std::endl;
    }
}

/**
* Log a general error, will append 'Error: ' to the front automatically
* @param msg the error to log
*/
void GameLog::LogError(const std::string &msg)
{
    std::string error = "Error: ";
    error.append(msg); // put Error in front of our message
    Log(error, 3);
}

/**
* Log SDL errors without worrying about, typing the function all the time
* @param function_name the function and any other relevant info
*/
void GameLog::LogSdlError(const std::string &function_name)
{
    std::string sdl_error = SDL_GetError();
    std::string name = function_name;
    name.append(": " + sdl_error);

    LogError(name);
}

/**
* The Caller that we want logger to report
* @param caller The name of the caller that logger will log
*/
void GameLog::SetCaller(std::string &caller)
{
    m_sLogCaller = caller;
}

/**
* Set the current log file to something
* @param os The file handle to log to
*/
void GameLog::SetLogFile( std::ostream &os )
{
    m_cLogFile = &os;
}

/**
* A Setter for log level
* @param log_level What to set log level to
*/
void GameLog::SetLogLevel(int log_level)
{
    m_iLogLevel = log_level;
}

/**
* A getter for caller
* @return the current log caller
*/
std::string GameLog::GetCaller()
{
    return m_sLogCaller;
}

/**
* A getter for log level
* @return the current log level
*/
int GameLog::GetLogLevel()
{
    return m_iLogLevel;
}