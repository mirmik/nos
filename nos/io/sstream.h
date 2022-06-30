#include <nos/io/ostream.h>

namespace nos {
    class stringstream : public nos::ostream, public nos::istream {
	private:
		std::string _str = {};
        size_t read_marker = 0;

	public:	
		int write(const void* ptr, size_t sz) override {
			_str.append((char*)ptr, sz);
			return sz;
		}

        int read(void* ptr, size_t sz) override 
        {
			memcpy(ptr, _str.data() + read_marker, sz);
            read_marker += sz;
            return sz;
		}

		std::string & str() { return _str; }
	};
}