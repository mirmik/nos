#include <nos/log/target.h>
#include <nos/print.h>

void nos::log::target::set_format(const nos::buffer & fmt)
{
	this->fmt = std::string(fmt.data(), fmt.size());
}

void nos::log::target::set_level(nos::log::level lvl)
{
	this->lvl = lvl;
}