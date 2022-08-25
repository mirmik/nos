#include <nos/log/logmsg.h>
#include <nos/log/target.h>
#include <nos/log/tlogger.h>

nos::log::tlogger::tlogger(const std::string &_name) : logger(_name) {}

void nos::log::tlogger::link(target *tgt)
{
    targets.push_back(tgt);
}

/// Logging method implementation
void nos::log::tlogger::log(nos::log::level lvl, std::string &&msg)
{
    time_t current_time;
    struct tm local_time;

    ::time(&current_time);
#ifndef __WIN32__
    ::localtime_r(&current_time, &local_time);
#else
    ::localtime_s(&local_time, &current_time);
#endif

    std::shared_ptr<nos::log::logmsg> logmsg =
        std::make_shared<nos::log::logmsg>(
            this, lvl, std::move(msg), local_time);

    for (auto *tgt : targets)
    {
        tgt->log(logmsg);
    }
}

void nos::log::tlogger::clear_targets()
{
    targets.clear();
}

void nos::log::tlogger::log(level lvl,
                            const std::string_view &fmt,
                            const visitable_arglist &arglist)
{
    log(lvl, nos::format(fmt, arglist));
}

nos::log::logger nos::log::stdlogger("default");