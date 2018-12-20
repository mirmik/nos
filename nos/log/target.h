#ifndef NOS_TARGET_H
#define NOS_TARGET_H

#include <gxx/log/logger.h>

namespace nos {
	namespace log {
		struct target {
			virtual void log(std::shared_ptr<logmessage> logmsg) {
				gxx::println("virtual log function");
			}
		};

		struct print_target : public target {
			const char* tmplt = "{logger} | {level} | {msg} |";

			void log(std::shared_ptr<logmessage> logmsg) override {
				gxx::fprintln(tmplt, 
					"msg"_a=logmsg->message, 
					"logger"_a=logmsg->logger->name,
					"level"_a=level_to_string(logmsg->level));
			}
		};

		struct colored_print_target : public target {
			const char* tmplt = "{logger} | {level} | {msg} |";

			void log(std::shared_ptr<logmessage> logmsg) override {
				gxx::fprintln(tmplt, 
					"msg"_a=logmsg->message, 
					"logger"_a=logmsg->logger->name,
					"level"_a=level_to_collored_string(logmsg->level));
			}
		};
	}
}

#endif