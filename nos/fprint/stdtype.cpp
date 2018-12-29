#include <nos/fprint/stdtype.h>
#include <nos/fprint/spec.h>

ssize_t nos_fprint(nos::ostream& os, const char* text, int size, const nos::basic_spec& spec)
{

	int ret = 0;

	int pre_fill_len = 0;
	char post_fill_len = 0;

	int difflen = spec.width - size;

	if (difflen > 0)
	{
		switch (spec.align)
		{
			case nos::alignment::left:
				post_fill_len = difflen;
				break;

			case nos::alignment::right:
				pre_fill_len = difflen;
				break;

			case nos::alignment::center:
				pre_fill_len = difflen / 2;
				post_fill_len = difflen / 2;

				if (difflen % 2) pre_fill_len++;

				break;
		}
	}

	if (pre_fill_len)
	{
		ret += os.fill(spec.fill, pre_fill_len);
	}


	if (spec.tcase == nos::text_case::upper)
	{
		ret += os.write_lower(text, size);
	}
	else if (spec.tcase == nos::text_case::lower)
	{
		ret += os.write_upper(text, size);
	} 
	else
	{
		ret += os.write(text, size);
	}

	if (post_fill_len)
	{
		ret += os.fill(spec.fill, post_fill_len);
	}

	return ret;
}

ssize_t nos_fprint(nos::ostream& os, const char* text, const nos::basic_spec& spec) 
{
	return nos_fprint(os, text, strlen(text), spec);
}

ssize_t nos_fprint(nos::ostream& os, const char* obj, nos::buffer opts)
{
	nos::text_spec spec(opts);
	return nos_fprint(os, obj, strlen(obj), spec);
}

ssize_t nos_fprint(nos::ostream& os, bool obj, nos::buffer opts) 
{
	return nos_fprint(os, obj ? "true" : "false", opts);
}

ssize_t nos_fprint(nos::ostream& os, int8_t obj, nos::buffer opts);
ssize_t nos_fprint(nos::ostream& os, int16_t obj, nos::buffer opts);
ssize_t nos_fprint(nos::ostream& os, int32_t obj, nos::buffer opts);
ssize_t nos_fprint(nos::ostream& os, int64_t obj, nos::buffer opts);

ssize_t nos_fprint(nos::ostream& os, uint8_t obj, nos::buffer opts);
ssize_t nos_fprint(nos::ostream& os, uint16_t obj, nos::buffer opts);
ssize_t nos_fprint(nos::ostream& os, uint32_t obj, nos::buffer opts);
ssize_t nos_fprint(nos::ostream& os, uint64_t obj, nos::buffer opts);