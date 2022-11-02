#ifndef NOS_KWARGS_FUNCTIONS_H
#define NOS_KWARGS_FUNCTIONS_H

#include <functional>
#include <nos/util/arglist.h>
#include <string>

namespace nos
{
    class runtime_argument
    {
        bool inited;
        const void *value;
    };

    struct type_convertor
    {
        template <class From, class To> static To convert(const From &from)
        {
            return (To)from;
        }
    };

    template <class F> class signature
    {
    };

    template <class R, class... Args> class signature<R(Args...)>
    {
        constexpr static size_t count = sizeof...(Args);
        using result_type = R;

    public:
        template <template <class> class T>
        struct argument_template_parametrization
        {
            using type = T<Args...>;
        };

        template <size_t I>
        using nth_argtype =
            typename std::tuple_element_t<I, std::tuple<Args...>>;
    };

    template <class, template <class...> class>
    inline constexpr bool is_specialization = false;
    template <template <class...> class T, class... Args>
    inline constexpr bool is_specialization<T<Args...>, T> = true;

    template <class T> concept ArgPair = is_specialization<T, nos::argpair>;

    template <class F, class TypeConvertor = nos::type_convertor>
    class comfortable_function
    {
        std::function<F> func;
        constexpr static size_t count = 3;
        std::array<std::string, count> argument_names;

    public:
        comfortable_function(std::function<F> &&f,
                             const std::array<std::string, count> &names)
            : func(f), argument_names(names){};

        template <class... Args2> auto operator()(Args2 &&... args) const
        {
            std::tuple<Args2...> args_tuple = std::make_tuple(args...);
            std::array<runtime_argument, count> rarguments = {};

            // parse each argument
            parse_arguments(
                rarguments, args_tuple, std::make_index_sequence<count>{});

            return call(rarguments);
        }

        template <size_t... I>
        nos::signature<F>::result_type
        call(const std::array<runtime_argument, count> &arr) const
        {
            // return func(
            //    *static_cast<typename nos::signature<F>::nth_argtype<I> *>(
            //        arr[I].value)...);
        }

        template <class... Args2, size_t... I>
        void parse_arguments(std::array<runtime_argument, count> &rarguments,
                             const std::tuple<Args2...> &args_tuple,
                             std::index_sequence<I...>) const
        {
            (parse_argument(I, rarguments, std::get<I>(args_tuple)), ...);
        }

        template <ArgPair Arg>
        void parse_argument(size_t index,
                            std::array<runtime_argument, count> &rarguments,
                            const Arg &arg) const
        {
        }
    };
}

#endif