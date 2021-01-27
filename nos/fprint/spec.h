#ifndef NOS_FPRINT_SPEC_H
#define NOS_FPRINT_SPEC_H

#include <string.h>

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

		char* analyze(char* ptr)
		{
			if (isdigit(*ptr))
			{
				width = strtoul(ptr, &ptr, 10);
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
		integer_spec(nos::buffer opts)
		{
			char* ptr = opts.begin();
			char* end = opts.end();
			while (ptr != end)
			{
				ptr = analyze(ptr);
			}
		}
	};

	struct float_spec : public basic_spec
	{
		float_spec(nos::buffer opts)
		{
			char* ptr = opts.begin();
			char* end = opts.end();
			while (ptr != end)
			{
				ptr = analyze(ptr);
			}
		}
	};

	struct text_spec : public basic_spec
	{
		text_spec(nos::buffer opts)
		{
			char* ptr = opts.begin();
			char* end = opts.end();
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
