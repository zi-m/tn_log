#include <tn_log.h>


static void ( *TN_log_fn )(const char*, int, const char*, int, const char*, size_t) = nullptr;


void TN_log_init()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("%^[%H:%M:%S]%$ %v"); // "%^[%Y-%m-%d %H:%M:%S.%e] [%s:%#:%!]%$ %v"

    TN_log_set_fn(TN_log_default_fn);
}

void TN_log_default_fn(const char* filename, int line, const char* funcname, int lvl, const char* data, size_t size)
{
    auto logger = spdlog::default_logger_raw();
    spdlog::string_view_t message{ data, size };
    spdlog::source_loc loc{ filename, line, funcname };
    logger->log(loc, (spdlog::level::level_enum)lvl, message);
}

void TN_log_set_fn(void (*fn)(const char*, int, const char*, int, const char*, size_t))
{
    TN_log_fn = fn;
}

void TN_log(boost::source_location loc, spdlog::level::level_enum lvl, std::string_view msg)
{
    assert(TN_log_fn != nullptr);
    TN_log_fn(loc.file_name(), loc.line(), loc.function_name(), lvl, msg.data(), msg.size());
}

void TN_log_current_nested_exception(const std::exception& current, spdlog::level::level_enum lvl) noexcept
{
    try
    {
        std::rethrow_if_nested(current);
    }
    catch(const std::exception& e)
    {
        TN_log_current_nested_exception(e, lvl);
        TN_log(boost::get_throw_location(e), lvl, fmt::format("[Nested] {}", e.what()));
    }
    catch(const std::error_code& ec)
    {
        TN_log({}, lvl, fmt::format("[Nested] ({}) {}", ec.value(), ec.message()));
    }
    catch(...)
    {
        TN_log({}, lvl, "[Nested] Unknown exception");
    }
}

void TN_log_current_exception(boost::source_location loc, spdlog::level::level_enum lvl, const std::string& msg)
{
    try
    {
        if(std::exception_ptr current = std::current_exception())
            std::rethrow_exception(current);
    }
    catch(const std::exception& e)
    {
        TN_log_current_nested_exception(e, lvl);
        TN_log(boost::get_throw_location(e), lvl, fmt::format("[Nested] {}", e.what()));
    }
    catch(const std::error_code& ec)
    {
        TN_log({}, lvl, fmt::format("[Nested] ({}) {}", ec.value(), ec.message()));
    }
    catch(...)
    {
        TN_log({}, lvl, "[Nested] Unknown exception");
    }
    TN_log(loc, lvl, msg);
}
