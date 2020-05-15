#ifndef igris_SPAM_SERVER_H
#define igris_SPAM_SERVER_H

#include <nos/inet/tcp_server.h>
#include <nos/io/ostream.h>
#include <algorithm>
#include <list>

#include <string.h>
//#include <igris/debug.h>

namespace nos {
	namespace inet {
		class tcpspam_server : public inet::tcp_server {
			std::list<nos::inet::tcp_socket> clients;
	
		public:
			tcpspam_server() = default;
			tcpspam_server(int port) {
				start(port);
			}
	
			int start(int port) {
				inet::tcp_server::init();
				inet::tcp_server::bind("0.0.0.0", port);
				inet::tcp_server::listen(10);
				inet::tcp_server::nonblock(true);
				return 0;
			}	
			ssize_t __send(const char* str) {
				return __send(str, strlen(str));
			};
	
			ssize_t __send(const char* str, size_t n) {
				while(true) {
					nos::inet::tcp_socket newsock = accept();
					if (!newsock.good()) break;
					clients.push_back(newsock);
				}
	
				int ret = 0;
				auto it = clients.begin();
				decltype(it) cit;
				auto eit = clients.end();
				while(it != eit) {
					cit = it; ++it;
					ret = cit->write(str, n);
					if (ret < 0) {
						clients.erase(cit);
					}
				}
				
				/*if (needRemove)	{ 
					std::list<igris::socket>::iterator it;
					auto next = clients.begin();
					auto end = clients.end();
					it = next;
					for(; it != end; it = next) {
						next++;
						if (it->is_connected() == false) clients.erase(it);
					}
				}*/
	
	
				return ret;
			}
	
			ssize_t write(const void* str, size_t sz) override {
				return __send((char*)str, sz);
			}	
	
			void drop_all() {
				for (auto& c : clients) {
					c.close();
				}
				clients.clear();
			}
		};
	}
}

#endif
