#ifndef NOS_AGGREGATE_EXECUTOR_H
#define NOS_AGGREGATE_EXECUTOR_H

#include <nos/shell/executor.h>

namespace nos
{
	class aggregate_executor : public nos::executor_basic
	{
		std::vector<nos::executor_basic*> executors;

	public:
		using executor_basic::execute;

		aggregate_executor(const std::vector<nos::executor_basic*>& executors) 
			: executors(executors)
		{}

		int execute(const nos::argv& argv, nos::ostream& os) override 
		{
			if (argv[0] == "help") 
			{
				help(os);
				return 0;
			}

			for (auto & ex: executors) 
			{
				auto command_it = ex->find(argv[0]);
				if (command_it) 
				{
					return command_it->execute(argv, os);
				}			
			}

			print_undefined(os, argv[0]);	
			return -1;
		}

		void help(nos::ostream& os) 
		{
			for (auto* ex: executors) 
			{
				ex->help(os);
			}
		}

		nos::command * find(const nos::buffer& name) override
		{
			nos::command * ptr = nullptr;
			for (auto it = executors.begin(); it != executors.end() && !ptr; ++it) 
			{
				ptr = (*it)->find(name);
			}

			return ptr;
		}
	};
}

#endif