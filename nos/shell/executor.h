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
		virtual int execute(const nos::argv& argv, nos::ostream& os) = 0;
		virtual int help(nos::ostream& os) = 0;  

		int execute(const char * cmd, nos::ostream& os) 
		{
			nos::tokens tokens(cmd);
			return execute(tokens, os);
		}
	}

	class executor : public executor_basic 
	{
		std::vector<nos::command> commands;
		nos::buffer undefined_error = "Undefined command"; 

	public:
		executor(std::initializer_list<nos::command> initializer) 
			: commands(initializer.begin(), initializer.end())
		{}

		void add_command(const nos::command& cmd) 
		{
			commands.push_back(cmd);
		}

		int execute(const nos::argv& argv, nos::ostream& os) override
		{
			auto it = std::find_if(commands.begin(), commands.end(), [&](const auto& cmd){
				return cmd.name() == argv[0];
			});
			if (it == commands.end()) 
			{
				os.println(undefined_error);
				return -1;
			}
			return it->execute(argv.without(1), os); 		
		}

		void help(nos::ostream& os) 
		{
			for (auto & cmd : commands) 
			{
				os.println(cmd.name, "-", cmd.help)
			}
		}
	};
}

#endif