#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif

#include "spdlog/spdlog.h"
#include "spdlog/common.h"
#include "fmt/core.h"
#include <string>
#include <optional>

namespace logger
{

enum class LogLevel
{
    Trace = spdlog::level::trace,
    Debug = spdlog::level::debug,
    Info = spdlog::level::info,
    Warn = spdlog::level::warn,
    Error = spdlog::level::err,
    Critical = spdlog::level::critical,
    Off = spdlog::level::off
};

std::optional<LogLevel> logLevelFromStr(const std::string& logLevelStr);

template<class ... Args>
void log(LogLevel level, const fmt::format_string<Args...> format, Args&&... args)
{
    switch (level)
    {
    case LogLevel::Info:
        spdlog::info(format, std::forward<Args>(args)...);
        break;

    case LogLevel::Trace:
        spdlog::trace(format, std::forward<Args>(args)...);

    case LogLevel::Debug:
        spdlog::debug(format, std::forward<Args>(args)...);
        break;

    case LogLevel::Warn:
        spdlog::warn(format, std::forward<Args>(args)...);
        break;

    case LogLevel::Error:
        spdlog::error(format, std::forward<Args>(args)...);
        break;

    case LogLevel::Critical:
        spdlog::critical(format, std::forward<Args>(args)...);
        break;

    default:
        break;
    }
}

template<class ... Args>
void trace(const fmt::format_string<Args...> format, Args&&... args)
{
    spdlog::trace(format, std::forward<Args>(args)...);
}

template<class ... Args>
void info(const fmt::format_string<Args...> format, Args&&... args)
{
    spdlog::info(format, std::forward<Args>(args)...);
}

template<class ... Args>
void debug(const fmt::format_string<Args...> format, Args&&... args)
{
    spdlog::debug(format, std::forward<Args>(args)...);
}

template<class ... Args>
void warn(const fmt::format_string<Args...> format, Args&&... args)
{
    spdlog::warn(format, std::forward<Args>(args)...);
}

template<class ... Args>
void error(const fmt::format_string<Args...> format, Args&&... args)
{
    spdlog::error(format, std::forward<Args>(args)...);
}

template<class ... Args>
void critical(const fmt::format_string<Args...> format, Args&&... args)
{
    spdlog::critical(format, std::forward<Args>(args)...);
}

template<typename FormatString>
void set_pattern(const FormatString& fmt)
{
    spdlog::set_pattern(fmt);
}

void set_level(LogLevel level);

}

#endif // LOGGER_HPP
