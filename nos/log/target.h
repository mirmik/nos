#ifndef NOS_LOG_TARGET_H
#define NOS_LOG_TARGET_H

#include <nos/log/logmsg.h>
#include <memory>

namespace nos
{
	namespace log
	{
		class target
		{
		protected:
			std::string fmt;
			nos::log::level lvl;

		public:
			virtual void log(
				std::shared_ptr<nos::log::logmsg> logmsg) 
			{
				nos::println("virtual log function");
			}

			void set_format(igris::buffer fmt) { this->fmt = (std::string)fmt; }
			void set_level(nos::log::level lvl) { this->lvl = lvl; }
		};
	}

	/*struct print_target : public target {
		const char* tmplt = "{logger} | {level} | {msg} |";

		void log(std::shared_ptr<logmessage> logmsg) override {
			nos::fprintln(tmplt,
				"msg"_a=logmsg->message,
				"logger"_a=logmsg->logger->name,
				"level"_a=level_to_string(logmsg->level));
		}
	};

	struct colored_print_target : public target {
		const char* tmplt = "{logger} | {level} | {msg} |";

		void log(std::shared_ptr<logmessage> logmsg) override {
			nos::fprintln(tmplt,
				"msg"_a=logmsg->message,
				"logger"_a=logmsg->logger->name,
				"level"_a=level_to_collored_string(logmsg->level));
		}
	};*/
}

#endif