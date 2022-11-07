#ifndef NOS_CF_ABSTRACT_H
#define NOS_CF_ABSTRACT_H

#include <nos/shell/comfortable_function.h>

namespace nos
{
    class cf_abstract_basic
    {
    public:
        virtual nos::trent
        execute(const std::vector<nos::trent_argument> &args) = 0;
        virtual ~cf_abstract_basic() = default;
    };

    template <class R, class... Args>
    class cf_abstract : public cf_abstract_basic
    {
        using cf_type = nos::comfortable_function<R(Args...)>;
        cf_type _cf;

    public:
        nos::trent
        execute(const std::vector<nos::trent_argument> &args) override
        {
            auto value = cf().call_with_args(args);
            return nos::trent(value);
        }

        cf_abstract(std::function<R(Args...)> f) : _cf(f) {}

        cf_type &cf()
        {
            return _cf;
        }

        virtual ~cf_abstract() {}
    };

    template <class R, class... Args>
    std::unique_ptr<cf_abstract_basic>
    make_cf_abstract(std::function<R(Args...)> f)
    {
        return std::make_unique<cf_abstract<R, Args...>>(
            std::forward<decltype(f)>(f));
    }

    class cf_abstract_collection
    {
        std::map<std::string, std::unique_ptr<cf_abstract_basic>> collection =
            {};

    public:
        template <class R, class... Args>
        void add(const std::string &name, std::function<R(Args...)> f)
        {
            collection.emplace(name, make_cf_abstract(f));
        }

        nos::trent execute(const std::string &name,
                           const std::vector<nos::trent_argument> &args)
        {
            auto it = collection.find(name);
            if (it == collection.end())
                throw std::runtime_error("Undefined function: " + name);
            return it->second->execute(args);
        }
    };
}

#endif