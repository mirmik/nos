#ifndef NOS_META_META_H
#define NOS_META_META_H

namespace nos 
{
	template <typename T> class has_nos_print;
}

#include <nos/io/ostream.h>
#include <nos/util/buffer.h>

class nos_test_ostream : public nos::ostream {};

namespace nos 
{
	template <typename T>
	class has_nos_print
	{
	private:
		template <typename U>
		static decltype( nos_print(
				std::declval<nos_test_ostream&>(), std::declval<U>()
			), std::true_type()) test(int);

		template <typename> static std::false_type test(...);

	public:
		static constexpr const bool value = decltype(test<T>(0))::value;
	};

	template <typename T>
	class has_nos_fprint
	{
	private:
		template <typename U>
		static decltype( nos_fprint(
				std::declval<nos_test_ostream&>(), std::declval<U>(), nos::buffer()
			), std::true_type()) test(int);

		template <typename> static std::false_type test(...);

	public:
		static constexpr const bool value = decltype(test<T>(0))::value;
	};

	template <typename T>
	class has_print_method
	{
	private:
		template <typename U>
		static decltype( 
				std::declval<U>().print_to(std::declval<nos_test_ostream&>())
			, std::true_type()) test(int);

		template <typename> static std::false_type test(...);

	public:
		static constexpr const bool value = decltype(test<T>(0))::value;
	};

	template <typename T>
	class has_fprint_method
	{
	private:
		template <typename U>
		static decltype( 
				std::declval<U>().fprint_to(std::declval<nos_test_ostream&>(), nos::buffer())
			, std::true_type()) test(int);

		template <typename> static std::false_type test(...);

	public:
		static constexpr const bool value = decltype(test<T>(0))::value;
	};
}

#endif