#ifndef NOS_PRINT_PRINT_H
#define NOS_PRINT_PRINT_H

#include <stdlib.h>
#include <iterator>

#include <nos/util/buffer.h>

#if __has_include(<igris/buffer.h>)
#include <igris/buffer.h>
#endif

namespace nos
{
												class ostream;
												extern ostream* current_ostream;


												ssize_t putchar_to(nos::ostream&, char);
												ssize_t write_to(nos::ostream& out, const void* buf, size_t sz);
												ssize_t writeln_to(nos::ostream& out, const void* buf, size_t sz);
	template<typename Arg> 						ssize_t print_to(nos::ostream& out, const Arg& arg);
	template<typename Head, typename ... Tail> 	ssize_t print_to(nos::ostream& out, const Head& head, const Tail& ... tail);
												ssize_t println_to(nos::ostream&);
	template<typename ... Args> 				ssize_t println_to(nos::ostream& out, const Args& ... args);
	template<typename V> 						ssize_t print_list_to(nos::ostream& out, const V& vec);
	template<typename M> 						ssize_t print_matrix_to(nos::ostream& out, const M& mat);
	template<typename ... Args> 				ssize_t printhex_to(nos::ostream& out, const Args& ... args);
	template<typename Arg> 						ssize_t printptr_to(nos::ostream& out, const Arg* arg);
	template<typename Arg> 						ssize_t printptrln_to(nos::ostream& out, const Arg* arg);
												ssize_t print_dump_to(nos::ostream&, const void *mem, size_t len, unsigned int columns = 8);

												ssize_t putchar(char c);
												ssize_t write(const void* buf, size_t sz);
												ssize_t writeln(const void* buf, size_t sz);
	template<typename ... Args> 				ssize_t print(const Args& ... args);
												ssize_t println();
	template<typename ... Args>					ssize_t println(const Args& ... args);
	template<typename V> 						ssize_t print_list(const V& vec);
	template<typename M> 						ssize_t print_matrix(const M& mat);
	template<typename ... Args> 				ssize_t printhex(const Args& ... args);
	template<typename ... Args> 				ssize_t printhexln(const Args& ... args);
	template<typename Arg> 						ssize_t printptr(const Arg& arg);
												ssize_t print_dump(const void *mem, size_t len, unsigned int columns = 8);

												ssize_t print_dump(nos::buffer buf, unsigned int columns = 8);
#if __has_include(<igris/buffer.h>)
												ssize_t print_dump(igris::buffer buf, unsigned int columns = 8);
#endif

	static inline ssize_t print(void* ptr) { return nos::printptr(ptr); }
	static inline ssize_t print_to(nos::ostream& out, void* ptr) { return nos::printptr_to(out, ptr); }
}

#include <nos/io/ostream.h>
#include <nos/print/meta.h>

template<typename Arg> 			ssize_t nos::print_to(nos::ostream& out, const Arg& arg) 	{ return nos::print_implementation<Arg>::print_to(out, arg); }
template<typename ... Args> 	ssize_t nos::print(const Args& ... args) 					{ return print_to(*current_ostream, args ...); }
template<typename ... Args> 	ssize_t nos::println(const Args& ... args) 					{ return println_to(*current_ostream, args ...); }
template<typename ... Args> 	ssize_t nos::printhex(const Args& ... args) 				{ return current_ostream->printhex(args ...); }
//template<typename ... Args> 	ssize_t nos::printptr(const Args& ... args) 				{ return current_ostream->printptr(args ...); }
template<typename V> 			ssize_t nos::print_list(const V& vec) 						{ return print_list_to(*current_ostream, vec); }
template<typename M> 			ssize_t nos::print_matrix(const M& mat) 					{ return print_matrix_to(*current_ostream, mat); }
template<typename T>			ssize_t nos::printptr_to(nos::ostream& out, const T* arg) 	{ return out.printptr(arg); }

template<typename ... Args> 	
ssize_t nos::printhexln(const Args& ... args) { 
	int ret = current_ostream->printhex(args ...);
	ret += current_ostream->println();
	return ret; 
}

template<typename Head, typename ... Tail>
ssize_t nos::print_to(nos::ostream& out, const Head& head, const Tail& ... tail)
{
	ssize_t res = 0;
	res += print_to(out, head);
	res += nos::putchar_to(out, ' ');
	res += print_to(out, tail ...);
	return res;
}

template<typename ... Args>
ssize_t nos::println_to(nos::ostream& out, const Args& ... args)
{
	ssize_t res = 0;
	res += print_to(out, args ...);
	res += nos::println_to(out);
	return res;
}

template<typename V>
ssize_t nos::print_list_to(nos::ostream& out, const V& vec)
{
	size_t ret = 0;
	
	if (std::size(vec) == 0) 
	{
		return out.write("{}",2);
	}

	ret += out.putchar('{');

	for (unsigned int i = 0; i < std::size(vec) - 1; ++i)
	{
		ret += print_to(out, vec[i]);
		ret += out.putchar(',');
	}
		ret += print_to(out, vec[std::size(vec) - 1]);
	ret += out.putchar('}');

	return ret;
}

template<typename M>
ssize_t nos::print_matrix_to(nos::ostream& out, const M& mat)
{
	size_t ret = 0;
	
	for (unsigned int i = 0; i < mat.size1(); ++i)
	{
		for (unsigned int j = 0; j < mat.size2(); ++j) 
		{
			nos::print(mat(i,j));
			nos::print(" ");
		}
		nos::println();
	}

	return ret;
}

#endif
