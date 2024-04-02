#ifndef TN_LOG_H
#define TN_LOG_H

#ifndef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif

#include <boost/throw_exception.hpp>
#include <spdlog/spdlog.h>

/* *INDENT-OFF* */

#define TN_RUNTIME_ERROR(...) boost::detail::with_throw_location<std::runtime_error>(std::runtime_error(fmt::format(__VA_ARGS__)), BOOST_CURRENT_LOCATION);
#define TN_THROW_WITH_NESTED(...) std::throw_with_nested(boost::detail::with_throw_location<std::runtime_error>(std::runtime_error(fmt::format(__VA_ARGS__)), BOOST_CURRENT_LOCATION))

#define TN_ENSURE(x) if(!(x)) throw TN_RUNTIME_ERROR("{}", "!(" #x ")")
#define TN_LOG_CURRENT_EXCEPTION_ERROR(...) TN_log_current_exception(BOOST_CURRENT_LOCATION, spdlog::level::err, fmt::format(__VA_ARGS__))
#define TN_LOG_CURRENT_EXCEPTION_WARNING(...) TN_log_current_exception(BOOST_CURRENT_LOCATION, spdlog::level::warn, fmt::format(__VA_ARGS__))

#define TN_LOG_INFO(...)    TN_log(BOOST_CURRENT_LOCATION, spdlog::level::info,  fmt::format(__VA_ARGS__))
#define TN_LOG_WARNING(...) TN_log(BOOST_CURRENT_LOCATION, spdlog::level::warn,  fmt::format(__VA_ARGS__))
#define TN_LOG_ERROR(...)   TN_log(BOOST_CURRENT_LOCATION, spdlog::level::err,   fmt::format(__VA_ARGS__))
#define TN_LOG_DEBUG(...)   TN_log(BOOST_CURRENT_LOCATION, spdlog::level::debug, fmt::format(__VA_ARGS__))

void TN_log_init();
void TN_log_default_fn(const char* filename, int line, const char* funcname, int lvl, const char* data, size_t size);
void TN_log_set_fn(void (*fn)(const char*, int, const char*, int, const char*, size_t));
void TN_log(boost::source_location loc, spdlog::level::level_enum lvl, std::string_view msg);
void TN_log_current_exception(boost::source_location loc, spdlog::level::level_enum lvl, const std::string& msg);

/* *INDENT-ON* */

#endif
