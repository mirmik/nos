#ifndef NOS_PRINTABLE_H
#define NOS_PRINTABLE_H

namespace nos 
{
	template <class T>
	class array_printable 
	{
	public:
		ssize_t print_to(nos::ostream& os) const
		{
			return nos::print_list_to(os, *(T*)this);
		}
	};

	template <class T>
	class matrix_printable 
	{
	public:
		ssize_t print_to(nos::ostream& os) const
		{
			return nos::print_matrix_to(os, *(T*)this);
		}
	};
}

#endif
