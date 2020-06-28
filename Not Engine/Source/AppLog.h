#pragma once
#include <fstream>

class AppLog
{
protected:
	static AppLog* Logger;
	bool isLogging;
	std::ofstream LogFile;
	std::string LogFileName;
	std::string LogFileExt;
	std::string LoggingPath;
	std::string LoggingTime;

	virtual void InitLogToConsoleAndFile();
	AppLog();
public:
	~AppLog();
	static AppLog* InitiateLogger(const bool& Logging);
	static AppLog* InitiateLogger(const bool& Logging, const std::string& FilePath,
		const std::string& FileName, const std::string& FileExtension);
	static AppLog* GetLogger();

	virtual void LogToFile(const std::string& Message);
	virtual void LogToConsole(const std::string& Message);
	virtual void LogToFileAndConsole(const std::string& Message);

	virtual void setLogging(const bool& LoggingStatus);
	virtual void setLogging(const bool& LoggingStatus, const std::string& FilePath,
		const std::string& FileName, const std::string& FileExtension);

	bool GetLoggingStatus();
	std::string GetLoggingPath() const;
	std::string GetLogFileName() const;
	std::string GetLogFileExtension() const;
};
