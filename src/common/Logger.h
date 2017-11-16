#pragma once
#include <string>
#include "spdlog/spdlog.h"

//Wrapper class for SPD LOG

namespace Common
{
	class Logger {

	private:

		std::string m_loggerFile;
		Logger(void) {}
		std::shared_ptr<spdlog::logger> m_consoleLogger;
	public:

		static Logger& GetInstance()
		{
			static Logger    instance; // Guaranteed to be destroyed.
									   // Instantiated on first use.
			return instance;
		}
		Logger(Logger const&) = delete;
		void operator=(Logger const&) = delete;

		template<typename T>
		void Logger::LogDebug(const T& msg)
		{
			spdlog::get("console")->debug(msg);
			//m_consoleLogger->debug(msg);
		}

		template <typename Arg1, typename... Args>
		void Logger::LogDebugFormated(const char* fmt, const Arg1 &arg1, const Args&... args)
		{
			spdlog::get("console")->debug(fmt, arg1, args...);
		}

		template<typename T>
		void Logger::LogError(const T& msg)
		{
			spdlog::get("console")->error(msg);
		}

		template <typename Arg1, typename... Args>
		void Logger::LogErrorFormated(const char* fmt, const Arg1 &arg1, const Args&... args)
		{
			spdlog::get("console")->error( fmt, arg1, args...);
		}

		template<typename T>
		void Logger::LogWarning(const T& msg)
		{
			spdlog::get("console")->warn(msg);
		}
		
		template <typename Arg1, typename... Args>
		void Logger::LogWarningFormated(const char* fmt, const Arg1 &arg1, const Args&... args)
		{
			spdlog::get("console")->warn(fmt, arg1, args...);
		}
		
		template<typename T>
		void Logger::LogInfo(const T& msg)
		{
			spdlog::get("console")->info(msg);
		}

		template <typename Arg1, typename... Args>
		void Logger::LogInfoFormated(const char* fmt, const Arg1 &arg1, const Args&... args)
		{
			spdlog::get("console")->info(fmt, arg1, args...);
		}

		void Logger::Init()
		{
			m_consoleLogger = spdlog::stdout_color_mt("console");
		}
	};
}

