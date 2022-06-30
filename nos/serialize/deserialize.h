#ifndef NOS_DESERIALIZE_H
#define NOS_DESERIALIZE_H

#include <nos/io/ostream.h>
#include <nos/io/istream.h>
#include <cstdint>
#include <string>

namespace nos
{
    template <class T> void deserialize_from(nos::istream& os, T& obj);
    template <class T> T deserialize_from(nos::istream& os);
        
    class DeserializeReflector 
    {
    public:
        nos::istream& os;
    public:
        DeserializeReflector(nos::istream& os) : os(os) {}

        template <class T>
        void operator()(T& obj) 
        {
            nos::deserialize_from(os, obj);
        }
    };

    template <class T> class deserialize_helper 
    {
    public:
        static void deserialize_from(nos::istream& os, T& obj) 
        { 
            nos::DeserializeReflector op(os);
            obj.reflect(op);
        }    
    };

    template <> struct deserialize_helper<uint8_t > { static void deserialize_from(nos::istream& os, uint8_t & obj) { os.read(&obj, 1); } };
    template <> struct deserialize_helper<uint16_t> { static void deserialize_from(nos::istream& os, uint16_t& obj) { os.read(&obj, 2); } };
    template <> struct deserialize_helper<uint32_t> { static void deserialize_from(nos::istream& os, uint32_t& obj) { os.read(&obj, 4); } };
    template <> struct deserialize_helper<uint64_t> { static void deserialize_from(nos::istream& os, uint64_t& obj) { os.read(&obj, 8); } };

    template <> struct deserialize_helper<int8_t > { static void deserialize_from(nos::istream& os, int8_t & obj) { os.read(&obj, 1); } };
    template <> struct deserialize_helper<int16_t> { static void deserialize_from(nos::istream& os, int16_t& obj) { os.read(&obj, 2); } };
    template <> struct deserialize_helper<int32_t> { static void deserialize_from(nos::istream& os, int32_t& obj) { os.read(&obj, 4); } };
    template <> struct deserialize_helper<int64_t> { static void deserialize_from(nos::istream& os, int64_t& obj) { os.read(&obj, 8); } };
    
    template <> struct deserialize_helper<float > { static void deserialize_from(nos::istream& os, float & obj) { os.read(&obj, sizeof(float )); } };
    template <> struct deserialize_helper<double> { static void deserialize_from(nos::istream& os, double& obj) { os.read(&obj, sizeof(double)); } };

    template <> struct deserialize_helper<std::string> { 
        static void deserialize_from(nos::istream& os, std::string& obj) 
        {
            size_t size; 
            uint8_t sizesize = nos::deserialize_from<uint8_t>(os);
                 if (sizesize == 1) { size = nos::deserialize_from<uint8_t >(os); }
            else if (sizesize == 2) { size = nos::deserialize_from<uint16_t>(os); }
            else if (sizesize == 4) { size = nos::deserialize_from<uint32_t>(os); }
            else                    { size = nos::deserialize_from<uint64_t>(os); }
            obj.resize(size);
            os.read(&obj[0], size);
        } 
    };

    template <class T> 
    void deserialize_from(nos::istream& os, T& obj) 
    {
        deserialize_helper<T>::deserialize_from(os, obj);
    }

    template <class T> 
    T deserialize_from(nos::istream& os) 
    {
        T obj;
        deserialize_helper<T>::deserialize_from(os, obj);
        return obj;
    }
}

#endif