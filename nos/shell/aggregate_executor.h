#ifndef NOS_AGGREGATE_EXECUTOR_H
#define NOS_AGGREGATE_EXECUTOR_H

#include <nos/shell/executor.h>

namespace nos
{
	class aggregate_executor : public nos::executor_basic
	{
		std::vector<nos::executor_basic*> executors;

	public:
		aggregate_executor(const std::vector<nos::executor_basic*>& executors) 
			: executors(executors)
		{}

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