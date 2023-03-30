#include "logger.hpp"

namespace logger
{

std::optional<LogLevel> logLevelFromStr(const std::string& logLevelStr)
{
    std::optional<LogLevel> logLevel = std::nullopt;

    if (logLevelStr == "trace")
    {
        logLevel = LogLevel::Trace;
    }
    else if (logLevelStr == "debug")
    {
        logLevel = LogLevel::Debug;
    }
    else if (logLevelStr == "info")
    {
        logLevel = LogLevel::Info;
    }
    else if (logLevelStr == "warn")
    {
        logLevel = LogLevel::Warn;
    }
    else if (logLevelStr == "error")
    {
        logLevel = LogLevel::Error;
    }
    else if (logLevelStr == "critical")
    {
        logLevel = LogLevel::Critical;
    }
    else if (logLevelStr == "off")
    {
        logLevel = LogLevel::Off;
    }

    return logLevel;
}

void set_level(LogLevel level)
{
    spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
}

} // namespace samos::log::logger
