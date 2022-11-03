#ifndef NOS_KWARGS_FUNCTIONS_H
#define NOS_KWARGS_FUNCTIONS_H

#include <functional>
#include <nos/trent/trent.h>
#include <nos/util/arglist.h>
#include <stdexcept>
#include <string>

namespace nos
{
    struct runtime_argument
    {
        bool inited;
        nos::trent value;
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

    template <class R, class... Args> struct signature<R(Args...)>
    {
        constexpr static size_t count = sizeof...(Args);
        using result_type = R;

        template <template <class> class T>
        struct argument_template_parametrization
        {
            using type = T<Args...>;
        };

        template <size_t I>
        using nth_argtype =
            typename std::tuple_element_t<I, std::tuple<Args...>>;

        using args_tuple = std::tuple<Args...>;
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
        constexpr static size_t count = signature<F>::count;
        std::array<std::string, count> argument_names;

    public:
        comfortable_function(std::function<F> &&f,
                             const std::array<std::string, count> &names)
            : func(f), argument_names(names){};

        template <class... Args2> auto operator()(Args2 &&... args) const
        {
            std::tuple<Args2...> args_tuple{(args)...};
            std::array<runtime_argument, count> rarguments = {};

            // parse each argument
            parse_arguments(rarguments,
                            args_tuple,
                            std::make_index_sequence<sizeof...(Args2)>{});

            return call(rarguments, std::make_index_sequence<count>{});
        }

        template <size_t... I>
        nos::signature<F>::result_type
        call(const std::array<runtime_argument, count> &arr,
             std::index_sequence<I...>) const
        {
            for (size_t i = 0; i < count; i++)
            {
                if (!arr[i].inited)
                {
                    throw std::runtime_error("Argument " + argument_names[i] +
                                             " is not inited");
                }
            }

            return func(
                trent_to_type<typename nos::signature<F>::nth_argtype<I>>(
                    arr[I].value)...);
        }

        template <class T> static T trent_to_type(const nos::trent &t)
        {
            if constexpr (std::is_same_v<T, nos::trent>)
            {
                return t;
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                return t.as_string();
            }
            else if constexpr (std::is_same_v<T, bool>)
            {
                return t.as_bool();
            }
            else
            {
                return t.as_numer();
            }
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
            int index2 = -1;
            for (size_t i = 0; i < count; i++)
            {
                if (argument_names[i] == arg.name)
                {
                    index2 = i;
                    break;
                }
            }

            if (index2 == -1)
            {
                throw std::runtime_error("Argument is not found");
            }

            rarguments[index2].inited = true;
            rarguments[index2].value = arg.value();
        }

        template <typename Arg>
        void parse_argument(size_t index,
                            std::array<runtime_argument, count> &rarguments,
                            const Arg &arg) const
        {
            rarguments[index].inited = true;
            rarguments[index].value = arg;
        }
    };
}

#endif