#ifndef NOS_SHELL_RPC_H
#define NOS_SHELL_RPC_H

#include <nos/serialize/serialize.h>
#include <nos/serialize/deserialize.h>
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
    class remote_call_answer 
    {
        uint8_t error;
        Ret answer;
    };

    template <class Id, class ... Args>
    std::string serialize_bind(const Id& id, const Args& ... args) 
    {
        std::tuple<const Args& ...> tuple_args(args ...);
        nos::stringstream ret;
        nos::serialize_to(ret, id);
        nos::serialize_to(ret, tuple_args);
        return ret.str();
    }

    template <class R, class ... Args >
    class serialized_bind_invoker 
    {
        std::function<R(Args...)> foo;

    public:
        serialized_bind_invoker(const std::function<R(Args...)>& foo) : foo(foo) {}

        void operator()(nos::ostream& input, nos::istream& output) 
        {
            std::tuple<Args...> args = nos::deserialize_from<std::tuple<Args...>>(input);
            R ret = std::invoke(foo, args);
            nos::serialize_to<R>(output, ret);
        }
    };

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