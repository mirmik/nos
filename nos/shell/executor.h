#ifndef NOS_EXECUTOR_H
#define NOS_EXECUTOR_H

#include <nos/shell/command.h>
#include <nos/shell/argv.h>
#include <nos/print.h>
#include <algorithm>

namespace nos 
{
	class executor_basic 
	{
		nos::buffer undefined_error_message = "Undefined command:"; 

	public:
		virtual void help(nos::ostream& os) = 0;  
		virtual nos::command * find(const nos::buffer& name) = 0;

		int execute(const char * cmd, nos::ostream& os) 
		{
			nos::tokens tokens(cmd);
			return execute(tokens, os);
		}

		void print_undefined(nos::ostream& os, const nos::buffer& name) 
		{
			os.println(undefined_error_message, name);
		}

		int execute(const nos::argv& argv, nos::ostream& os)
		{
			if(argv.size() == 0) 
				return 0;

			if (argv[0] == "help") 
			{
				help(os);
				return 0;
			}

			auto cmd = find(argv[0]);

			if (cmd)
				cmd->execute(argv, os);
			else
				print_undefined(os, argv[0]);	
			
			return -1;
		}

	};

	class executor : public executor_basic 
	{
		std::vector<nos::command> commands;

	public:
		executor(const std::vector<nos::command>& vec) 
			: commands(vec)
		{}

		void add_command(const nos::command& cmd) 
		{
			commands.push_back(cmd);
		}

		void help(nos::ostream& os) 
		{
			for (auto & cmd : commands) 
			{
				os.println(cmd.name(), "-", cmd.help());
			}
		}

		nos::command* find(const nos::buffer& name) override
		{
			auto it = std::find_if(commands.begin(), commands.end(), [&](const auto& cmd){
				return name == cmd.name();
			});

			if (it == commands.end()) 
			{
				return nullptr;
			}

			return &*it;
		} 
	};
}

#endif