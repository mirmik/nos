#ifndef CIRCULAR_RECTANGLE_STREAM_H
#define CIRCULAR_RECTANGLE_STREAM_H

#include <nos/io/ostream.h>
#include <string_view>

namespace nos
{
	class circular_textframe : public nos::ostream
	{
		int cols = 0;
		int rows = 0;

		int cursor_row = 0;
		int cursor_col = 0;

		char * _data = nullptr;

	public:
		circular_textframe(int cols, int rows, char* buffer)
			: cols(cols), rows(rows), _data(buffer)
		{
			memset(_data, ' ', cols * rows);
		}

		void fixup()
		{
			while (cursor_col >= cols) { cursor_col -= cols; ++cursor_row; }
			while (cursor_row >= rows) { cursor_row -= rows; }
		}

		int putbyte(char c)
		{
			if (c == '\n') 
			{
				cursor_col = 0;
				cursor_row++;
				fixup();
				return 1;
			}

			_data[cursor_row * cols + cursor_col] = c;
			cursor_col++;

			fixup();
			return 1;
		}

		int write(const void * data, size_t size) override
		{
			int ret = 0;
			const char * it = (const char*) data;
			const char * eit = (const char*) data + size;
			for (;it!=eit;++it) 
			{
				ret += putbyte(*it);
			}
			return ret;
		}

		std::string_view get_string(int i)
		{
			int rowidx = cursor_row - i;
			while(rowidx < 0) rowidx += rows;

			return std::string_view(_data + rowidx * cols, cols);
		}
	};
}

#endif