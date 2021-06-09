#include <nos/log/target.h>
#include <nos/print.h>

void nos::log::target::log(
    std::shared_ptr<nos::log::logmsg> logmsg)
{
	nos::println("virtual log function");
}

void nos::log::target::set_format(nos::buffer fmt) { this->fmt = (std::string)fmt; }
void nos::log::target::set_level(nos::log::level lvl) { this->lvl = lvl; }