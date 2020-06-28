#include <time.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <Windows.h>
#include "AppLog.h"
#include "Global.h"

AppLog* AppLog::Logger = nullptr;

void AppLog::InitLogToConsoleAndFile()
{
	std::wstring tmp= std::wstring(LoggingPath.begin(), LoggingPath.end());
	std::string Message = "\t\t\t->Simple Engine Log<-\n\n\n\n[ " + LoggingTime + " ]\t\tLogging Started\n";
	CreateDirectory(tmp.c_str(), NULL);
	//LogFile.open(LoggingPath + LogFileName + "." +LogFileExt, std::fstream::out | std::fstream::app);
	std::cout << Message;
	//if (LogFile)
	//{
	//	LogFile << Message;
	//	std::cout << "[ " << LoggingTime << " ]" << "\t\tLogFile Successfully Created\n";
	//	LogFile << "[ " << LoggingTime << " ]" << "\t\tLogFile Successfully Created\n";
	//	LogFile.close();
	//}
	//else
	//	std::cout << "[ " << LoggingTime << " ]" << "\t\tFailed to Create\\Open LogFile\n";
}

AppLog::AppLog()
{
}

AppLog* AppLog::InitiateLogger(const bool& Logging)
{
	if (!Logger)
	{
		Logger = new AppLog();
		Logger->setLogging(Logging);
	}
	return Logger;
}

AppLog* AppLog::InitiateLogger(const bool& Logging, const std::string& FilePath, const std::string& FileName, const std::string& FileExtension)
{
	if (!Logger)
	{
		Logger = new AppLog();
		Logger->setLogging(Logging, FilePath, FileName, FileExtension);
	}
	return Logger;
}

AppLog* AppLog::GetLogger()
{
	return Logger;
}

AppLog::~AppLog()
{
	if (isLogging)
	{
		//if (LogFile)
		//{
		//	LogToFile("Logging Ended");
		//	LogFile.close();
		//}
		LogToConsole("Logging Ended");
	}
}

void AppLog::LogToFile(const std::string& Message)
{
	if (isLogging)
	{
		char cTime[255];
		time_t LogTime = time(0);

		ctime_s(cTime, sizeof(cTime), &LogTime);
		cTime[strlen(cTime) - 1] = '\0';
		LoggingTime = "[ " + std::string(cTime) + " ]\t\t";
		LogFile.open(LoggingPath + LogFileName + "." + LogFileExt, std::fstream::out | std::fstream::app);
		if (LogFile)
		{
			LogFile << LoggingTime << Message << "\n";
			LogFile.close();
		}
		else
			std::cout << LoggingTime << "Failed To Write to Log File!!!\n";
	}
}

void AppLog::LogToConsole(const std::string& Message)
{
	if (isLogging)
	{
		char cTime[255];
		time_t LogTime = time(0);

		ctime_s(cTime, sizeof(cTime), &LogTime);
		cTime[strlen(cTime) - 1] = '\0';
		LoggingTime = "[ " + std::string(cTime) + " ]\t\t";
		std::cout << LoggingTime << Message << "\n";
	}
}

void AppLog::LogToFileAndConsole(const std::string& Message)
{
	if (isLogging)
	{
		char cTime[255];
		time_t LogTime = time(0);

		ctime_s(cTime, sizeof(cTime), &LogTime);
		cTime[strlen(cTime) - 1] = '\0';
		LoggingTime = "[ " + std::string(cTime) + " ]\t\t";
		//LogFile.open(LoggingPath + LogFileName + "." + LogFileExt, std::fstream::out | std::fstream::app);
		//if (LogFile)
		//{
		//	LogFile << LoggingTime << Message << "\n";
			std::cout << LoggingTime << Message << "\n";
		//	LogFile.close();
		//}
		//else
		//	std::cout << LoggingTime << "Failed To Write to Log File!!!\n";
	}
}

void AppLog::setLogging(const bool& Logging)
{
	isLogging = Logging;
	if (isLogging)
	{
		char cTime[255];
		time_t LogTime = time(0);

		ctime_s(cTime, sizeof(cTime), &LogTime);
		cTime[strlen(cTime) - 1] = '\0';
		LoggingTime = cTime;
		std::string _FileNameTime(LoggingTime);
		std::replace(_FileNameTime.begin(), _FileNameTime.end(), ':', '-');

		LogFileName = "SimpleEngine " + _FileNameTime;
		LogFileExt = "log";
		LoggingPath = ".\\EngineLogs\\";
		InitLogToConsoleAndFile();
	}
}

void AppLog::setLogging(const bool& Logging, const std::string& FilePath,
	const std::string& FileName, const std::string& FileExtension)
{
	isLogging = Logging;
	if (isLogging)
	{
		char cTime[255];
		time_t LogTime = time(0);

		ctime_s(cTime, sizeof(cTime), &LogTime);
		cTime[strlen(cTime) - 1] = '\0';
		LoggingTime = cTime;
		std::replace(LoggingTime.begin(), LoggingTime.end(), ':', '-');

		LogFileName = FileName;
		LogFileExt = FileExtension;
		LoggingPath = FilePath;
		InitLogToConsoleAndFile();
	}
}



bool AppLog::GetLoggingStatus()
{
	return isLogging;
}

std::string AppLog::GetLoggingPath() const
{
	if (isLogging)
		return LoggingPath;
	else
		return "Logging Was Turned Off\n";
}

std::string AppLog::GetLogFileName() const
{
	if (isLogging)
		return LogFileName;
	else
		return "Logging Was Turned Off\n";
}

std::string AppLog::GetLogFileExtension() const
{
	if (isLogging)
		return LogFileExt;
	else
		return "Logging Was Turned Off\n";
}
