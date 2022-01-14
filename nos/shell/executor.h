#ifndef NOS_EXECUTOR_H
#define NOS_EXECUTOR_H

#include <nos/shell/command.h>
#include <nos/shell/argv.h>

namespace nos 
{
	class executor 
	{
		std::vector<nos::command> commands;
		std::string_view undefined_error = "Undefined command"; 

	public:
		executor(std::initializer_list<nos::command> initializer) 
			: commands(initializer.begin(), initializer.end())
		{}

		void add_command(const nos::command& cmd) 
		{
			commands.push_back(cmd);
		}

		int execute(const nos::argv& argv, nos::ostream& os) 
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

		int execute(const char * cmd, nos::ostream& os) 
		{
			nos::tokens tokens(cmd);
			return execute(tokens, os);
		}
	};
}

#endif