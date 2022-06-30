#ifndef NOS_SERIALIZE_H
#define NOS_SERIALIZE_H

#include <nos/io/ostream.h>
#include <cstdint>
#include <string>

namespace nos
{
    template <class T> void serialize_to(nos::ostream& os, const T& obj);

    class SerializeReflector 
    {
    public:
        nos::ostream& os;
    public:
        SerializeReflector(nos::ostream& os) : os(os) {}

        template <class T>
        void operator()(const T& obj) 
        {
            nos::serialize_to(os, obj);
        }
    };

    template <class T> class serialize_helper 
    {
    public:
        static void serialize_to(nos::ostream& os, const T& obj) 
        { 
            nos::SerializeReflector op(os);
            const_cast<T&>(obj).reflect(op);
        }    
    };

    template <> struct serialize_helper<uint8_t > { static void serialize_to(nos::ostream& os, const uint8_t & obj) { os.write(&obj, 1); } };
    template <> struct serialize_helper<uint16_t> { static void serialize_to(nos::ostream& os, const uint16_t& obj) { os.write(&obj, 2); } };
    template <> struct serialize_helper<uint32_t> { static void serialize_to(nos::ostream& os, const uint32_t& obj) { os.write(&obj, 4); } };
    template <> struct serialize_helper<uint64_t> { static void serialize_to(nos::ostream& os, const uint64_t& obj) { os.write(&obj, 8); } };

    template <> struct serialize_helper<int8_t > { static void serialize_to(nos::ostream& os, const int8_t & obj) { os.write(&obj, 1); } };
    template <> struct serialize_helper<int16_t> { static void serialize_to(nos::ostream& os, const int16_t& obj) { os.write(&obj, 2); } };
    template <> struct serialize_helper<int32_t> { static void serialize_to(nos::ostream& os, const int32_t& obj) { os.write(&obj, 4); } };
    template <> struct serialize_helper<int64_t> { static void serialize_to(nos::ostream& os, const int64_t& obj) { os.write(&obj, 8); } };

    // TODO: что делать с размерами типов float и double?
    template <> struct serialize_helper<float > { static void serialize_to(nos::ostream& os, const float & obj) { os.write(&obj, sizeof(float)); } };
    template <> struct serialize_helper<double> { static void serialize_to(nos::ostream& os, const double& obj) { os.write(&obj, sizeof(double)); } };

    template <> struct serialize_helper<std::string> { 
        static void serialize_to(nos::ostream& os, const std::string& obj) 
        {
            uint64_t size = obj.size();
                 if (size < ((uint64_t)1 << 8 )) { os.put(1); nos::serialize_to<uint8_t >(os, size); }
            else if (size < ((uint64_t)1 << 16)) { os.put(2); nos::serialize_to<uint16_t>(os, size); }
            else if (size < ((uint64_t)1 << 32)) { os.put(4); nos::serialize_to<uint32_t>(os, size); }
            else                                 { os.put(8); nos::serialize_to<uint64_t>(os, size); }
            os.write(obj.data(), size);
        } 
    };

    template <class T> 
    void serialize_to(nos::ostream& os, const T& obj) 
    {
        serialize_helper<T>::serialize_to(os, obj);
    }
}

#endif