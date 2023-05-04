#ifndef WEAKED_FUNCTION_INTERPRETER_H
#define WEAKED_FUNCTION_INTERPRETER_H

#include <nos/shell/argv.h>
#include <nos/shell/weaked_function.h>

namespace nos
{
    class weaked_function_interpreter
    {
        nos::wf_collection functions = {};

    public:
        weaked_function_interpreter() = default;

        template <class R, class... Args>
        void add(const std::string &name,
                 std::function<R(Args...)> f,
                 const std::array<std::string, sizeof...(Args)> &argnames = {})
        {
            functions.add(name, f, argnames);
        }

        nos::trent execute_console_command(std::string str)
        {
            auto tokens = nos::tokens(str);
            auto argv = nos::argv(tokens);
            std::string name = argv[0];
            auto argw = argv.without(1);

            std::vector<nos::trent_argument> targs;
            for (auto &arg : argw)
            {
                targs.emplace_back(arg);
            }

            return functions.execute(argv[0], targs);
        }
    };
}

#endif