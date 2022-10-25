#ifndef PBJSON_SERIALIZE_H
#define PBJSON_SERIALIZE_H

#include <cstdint>

namespace nos
{
    class pbjson_deserializer
    {
        nos::buffer buf;

        std::pair<int, int> get_type_and_length(int pos)
        {
            // type  located in the first 3 bits
            // length located in the last 5 bits
            uint8_t type_and_length = buf[pos];
            int type = type_and_length >> 5;
            int length = type_and_length & 0x1F;
            buf = {buf.data() + 1, buf.size() - 1};
            return {type, length};
        }

    public:
        pbjson_deserializer(nos::buffer buf) : buf(buf) {}

        template <std::integral T> bool reflect(const char *name, T &value)
        {
            auto [type, length] = get_type_and_length(pos);
            if (type != 2 && type != 4)
                return false;
            if (length == 0)
                return false;

            int64_t v = 0;
            for (int i = 0; i < length; i++)
            {
                v = (v << 8) | buf[i];
            }
            if (type == 4)
                v = -v;
            buf = {buf.data() + length, buf.size() - length};
            return true;
        }

        template <std::floating_point T>
        {
            auto [type, length] = get_type_and_length(pos);
            if (type != 6)
                return false;
            if (length == 0)
                return false;

            value = 0; /// WHAT???
            for (int i = 0; i < length; i++)
            {
                value = (value << 8) | buf[i];
            }
            buf = {buf.data() + length, buf.size() - length};
            return true;
        }

        bool reflect(const char *name, const std::string &value)
        {
            auto [type, length] = get_type_and_length(pos);
            if (type != 8)
                return false;
            if (length == 0)
                return false;

            value = std::string(buf.data(), length);
            buf = {buf.data() + length, buf.size() - length};
            return true;
        }
    };
}

#endif