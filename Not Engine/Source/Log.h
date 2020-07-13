#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Logger
{
private:
	static bool Initialized;
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
public:
	static void Init();

	static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
};

// Core log macros
#define NE_CORE_TRACE(...)    Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define NE_CORE_INFO(...)     Logger::GetCoreLogger()->info(__VA_ARGS__)
#define NE_CORE_WARN(...)     Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define NE_CORE_ERROR(...)    Logger::GetCoreLogger()->error(__VA_ARGS__)
#define NE_CORE_CRITICAL(...) Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define NE_TRACE(...)         Logger::GetClientLogger()->trace(__VA_ARGS__)
#define NE_INFO(...)          Logger::GetClientLogger()->info(__VA_ARGS__)
#define NE_WARN(...)          Logger::GetClientLogger()->warn(__VA_ARGS__)
#define NE_ERROR(...)         Logger::GetClientLogger()->error(__VA_ARGS__)
#define NE_CRITICAL(...)      Logger::GetClientLogger()->critical(__VA_ARGS__)