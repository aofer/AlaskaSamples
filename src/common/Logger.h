#pragma once
#include <string>
#include "spdlog/spdlog.h"

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


		void Logger::LogDebug(std::string msg)
		{
			spdlog::get("console")->debug(msg);
			m_consoleLogger->debug(msg);
		}

		void Logger::LogError(std::string msg)
		{
			spdlog::get("console")->error(msg);
		}

		void Logger::LogWarning(std::string msg)
		{
			spdlog::get("console")->warn(msg);
		}

		void Logger::LogInfo(std::string msg)
		{
			spdlog::get("console")->info(msg);
		}

		void Logger::Init()
		{
			m_consoleLogger = spdlog::stdout_color_mt("console");
		}
	};
}

