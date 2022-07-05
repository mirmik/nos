#ifndef NOS_SHELL_RPC_H
#define NOS_SHELL_RPC_H

#include <nos/serialize/serialize.h>
#include <nos/serialize/deserialize.h>
#include <nos/binary/bytearray.h>
#include <nos/io/bytearray_ostream.h>
#include <tuple>
#include <functional>

namespace nos 
{
    template <class Id, class ... Args>
    class remote_call_request
    {
        Id function_name;
        std::tuple<Args...> tpl;
    };

    template <class Ret>
    struct remote_call_answer 
    {
        int16_t errorcode;
        Ret object;

        template <class Reflector>
        void reflect(Reflector& op) 
        {
            op(errorcode);
            op(object);
        }
    };

    template <class Id, class ... Args>
    nos::bytearray serialize_remote_call(const Id& id, const Args& ... args) 
    {
        std::tuple<const Args& ...> tuple_args(args ...);
        nos::bytearray array;
        nos::bytearray_ostream writer(array);
        nos::serialize_to(writer, id);
        nos::serialize_to(writer, tuple_args);
        return array;
    }

    template <class Id>
    class rpc_socket 
    {
        nos::istream& is;
        nos::ostream& os;

    public:
        rpc_socket(nos::istream& is, nos::ostream& os) : is(is), os(os) {}

        template<class Ret, class ... Args>
        std::pair<int16_t, Ret> request(Id id, const Args& ... args) 
        {
            {
                auto req = serialize_bind(args ...);
                os.print(req);
            }   
            {
                int16_t errcode = nos::deserialize_from<int16_t>(is);
                if (errcode) 
                {
                    return { errcode, {} };
                } 
                Ret answer = nos::deserialize_from<Ret>(is);
                return { 0, answer };
            }
        }
    };
}

#endif