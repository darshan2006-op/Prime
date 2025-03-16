#include "Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace prm {
	Ref<spdlog::logger> Logger::s_clientLogger ;
	Ref<spdlog::logger> Logger::s_coreLogger ;
	void Logger::init()
	{
		std::vector<spdlog::sink_ptr> loggerSinks;
		loggerSinks.emplace_back(createRef<spdlog::sinks::stdout_color_sink_mt>());
		loggerSinks.emplace_back(createRef<spdlog::sinks::basic_file_sink_mt>("engine_logs/prime.log", true));

		loggerSinks[0]->set_pattern("%^[%T] %n: %v%$");
		loggerSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_coreLogger = createRef<spdlog::logger>("PrimeLog", loggerSinks.begin(), loggerSinks.end());
		spdlog::register_logger(s_coreLogger);
		s_coreLogger->set_level(spdlog::level::trace);
		s_coreLogger->flush_on(spdlog::level::trace);

		s_clientLogger = createRef<spdlog::logger>("Client", loggerSinks.begin(), loggerSinks.end());
		spdlog::register_logger(s_clientLogger);
		s_clientLogger->set_level(spdlog::level::trace);
		s_clientLogger->flush_on(spdlog::level::trace);
	}
}