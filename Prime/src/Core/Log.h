#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Core/Core.h"

namespace prm {
	class Logger {
	public:
		static void init();

		static Ref<spdlog::logger> getClientLogger() { return s_clientLogger; }
		static Ref<spdlog::logger> getCoreLogger() { return s_coreLogger; }
	private:
		static Ref<spdlog::logger> s_clientLogger;
		static Ref<spdlog::logger> s_coreLogger;
	};
}

// Core Logger macros
#define PRM_CORE_TRACE(...)    ::prm::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define PRM_CORE_INFO(...)     ::prm::Logger::getCoreLogger()->info(__VA_ARGS__)
#define PRM_CORE_WARN(...)     ::prm::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define PRM_CORE_ERROR(...)    ::prm::Logger::getCoreLogger()->error(__VA_ARGS__)
#define PRM_CORE_CRITICAL(...) ::prm::Logger::getCoreLogger()->critical(__VA_ARGS__)

// Client Logger macros
#define PRM_TRACE(...)         ::prm::Logger::getClientLogger()->trace(__VA_ARGS__)
#define PRM_INFO(...)          ::prm::Logger::getClientLogger()->info(__VA_ARGS__)
#define PRM_WARN(...)          ::prm::Logger::getClientLogger()->warn(__VA_ARGS__)
#define PRM_ERROR(...)         ::prm::Logger::getClientLogger()->error(__VA_ARGS__)
#define PRM_CRITICAL(...)      ::prm::Logger::getClientLogger()->critical(__VA_ARGS__)