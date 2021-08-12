#ifndef NOS_FPRINT_SPEC_H
#define NOS_FPRINT_SPEC_H

/**
	@file
*/

#include <string.h>
#include <ctype.h>
#include <nos/util/buffer.h>

namespace nos
{
	enum class alignment
	{
		left, right, center
	};

	enum class text_case
	{
		upper, lower, none
	};

	struct basic_spec
	{
		alignment align = alignment::left;
		text_case tcase = text_case::none;
		int width = 0;
		char fill = ' ';

		const char* analyze(const char* ptr)
		{
			if (isdigit(*ptr))
			{
				width = strtoul(ptr, (char**)&ptr, 10);
				return ptr;
			}

			switch (*ptr)
			{
				case '<':
					align = alignment::left;
					break;

				case '>':
					align = alignment::right;
					break;

				case '^':
					align = alignment::center;
					break;

				case 'f':
					fill = *++ptr;
					break;
			}
			return ++ptr;
		}
	};

	struct integer_spec : public basic_spec
	{
		integer_spec(const nos::buffer & opts)
		{
			const char* ptr = opts.begin();
			const char* end = opts.end();
			while (ptr != end)
			{
				ptr = analyze(ptr);
			}
		}
	};

	struct float_spec : public basic_spec
	{
		float_spec(const nos::buffer & opts)
		{
			const char* ptr = opts.begin();
			const char* end = opts.end();
			while (ptr != end)
			{
				ptr = analyze(ptr);
			}
		}
	};

	struct text_spec : public basic_spec
	{
		text_spec(const nos::buffer & opts)
		{
			const char* ptr = opts.begin();
			const char* end = opts.end();
			while (ptr != end)
			{
				switch (*ptr)
				{
					case 'u':
						tcase = text_case::upper;
						break;

					case 'l':
						tcase = text_case::lower;
						break;

					default:
						ptr = analyze(ptr);
						continue;
				}
				ptr++;
			}
		}
	};
}

#endif
