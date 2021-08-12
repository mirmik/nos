/**
	@file
*/

#ifndef NOS_PRINT_PRINT_H
#define NOS_PRINT_PRINT_H

#include <stdlib.h>
#if __has_include(<string_view>)
#include <string_view>
#endif

namespace nos
{
												class ostream;
												extern ostream* current_ostream;

												int putbyte_to(nos::ostream& out, char c);
												int write_to(nos::ostream& out, const void* buf, size_t sz);
												int writeln_to(nos::ostream& out, const void* buf, size_t sz);
	template<typename Arg> 						int print_to(nos::ostream& out, const Arg& arg);
	template<typename Head, typename ... Tail> 	int print_to(nos::ostream& out, const Head& head, const Tail& ... tail);
												int println_to(nos::ostream&);
	template<typename ... Args> 				int println_to(nos::ostream& out, const Args& ... args);
	template<typename V> 						int print_list_to(nos::ostream& out, const V& vec);
	template<typename M> 						int print_matrix_to(nos::ostream& out, const M& mat);
	template<typename ... Args> 				int printhex_to(nos::ostream& out, const Args& ... args);
	template<typename Arg> 						int printptr_to(nos::ostream& out, const Arg* arg);
	template<typename Arg> 						int printptrln_to(nos::ostream& out, const Arg* arg);
												int print_dump_to(nos::ostream&, const void *mem, size_t len, unsigned int columns = 8);

												int putbyte(char c);
												int write(const void* buf, size_t sz);
												int writeln(const void* buf, size_t sz);
	template<typename ... Args> 				int print(const Args& ... args);
												int println();
	template<typename ... Args>					int println(const Args& ... args);
	template<typename V> 						int print_list(const V& vec);
	template<typename M> 						int print_matrix(const M& mat);
	template<typename ... Args> 				int printhex(const Args& ... args);
	template<typename ... Args> 				int printhexln(const Args& ... args);
	template<typename Arg> 						int printptr(const Arg& arg);
												int print_dump(const void *mem, size_t len, unsigned int columns = 8);

												int print_dump(const std::string_view & buf, unsigned int columns = 8);

	static inline int print(void* ptr) { return nos::printptr(ptr); }
	static inline int print_to(nos::ostream& out, void* ptr) { return nos::printptr_to(out, ptr); }
}

#include <nos/io/ostream.h>
#include <nos/print/meta.h>

template<typename Arg> 			int nos::print_to(nos::ostream& out, const Arg& arg) 	{ return nos::print_implementation<Arg>::print_to(out, arg); }
template<typename ... Args> 	int nos::print(const Args& ... args) 					{ return print_to(*current_ostream, args ...); }
template<typename ... Args> 	int nos::println(const Args& ... args) 					{ return println_to(*current_ostream, args ...); }
template<typename ... Args> 	int nos::printhex(const Args& ... args) 				{ return current_ostream->printptr(args ...); }
template<typename V> 			int nos::print_list(const V& vec) 						{ return print_list_to(*current_ostream, vec); }
template<typename M> 			int nos::print_matrix(const M& mat) 					{ return print_matrix_to(*current_ostream, mat); }
template<typename T>			int nos::printptr_to(nos::ostream& out, const T* arg) 	{ return out.printptr(arg); }

template<typename ... Args> 	
int nos::printhexln(const Args& ... args) { 
	int ret = current_ostream->printhex(args ...);
	ret += current_ostream->println();
	return ret; 
}

template<typename Head, typename ... Tail>
int nos::print_to(nos::ostream& out, const Head& head, const Tail& ... tail)
{
	char c = ' ';
	int res = 0;
	res += print_to(out, head);
	res += nos::write_to(out, &c, 1);
	res += print_to(out, tail ...);
	return res;
}

template<typename ... Args>
int nos::println_to(nos::ostream& out, const Args& ... args)
{
	int res = 0;
	res += print_to(out, args ...);
	res += nos::println_to(out);
	return res;
}

template<typename V>
int nos::print_list_to(nos::ostream& out, const V& vec)
{
	size_t ret = 0;
	
	if (std::size(vec) == 0) 
	{
		return out.write("{}",2);
	}

	ret += out.putbyte('{');

	for (unsigned int i = 0; i < std::size(vec) - 1; ++i)
	{
		ret += print_to(out, vec[i]);
		ret += out.putbyte(',');
	}
		ret += print_to(out, vec[std::size(vec) - 1]);
	ret += out.putbyte('}');

	return ret;
}

template<typename M>
int nos::print_matrix_to(nos::ostream& out, const M& mat)
{
	size_t ret = 0;
	
	for (unsigned int i = 0; i < mat.size1(); ++i)
	{
		for (unsigned int j = 0; j < mat.size2(); ++j) 
		{
			nos::print_to(out, mat(i,j));
			nos::print_to(out, " ");
		}
		nos::println_to(out);
	}

	return ret;
}

#endif
