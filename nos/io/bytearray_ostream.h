#ifndef NOS_IO_ARRAY_OSTREAM_H
#define NOS_IO_ARRAY_OSTREAM_H

#include <nos/binary/bytearray.h>

namespace nos 
{
    class bytearray_ostream : public nos::ostream
    {
        bytearray& array;

    public:
        bytearray_ostream(bytearray& arr) : array(arr) {}

        int write(const void* ptr, size_t sz) override 
        {
			array.append((std::byte*)ptr, sz);
			return sz;
		}
    };
}

#endif