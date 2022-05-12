#include <nos/fprint/stdtype.h>
#include <nos/fprint/spec.h>

int nos_fprint(nos::ostream& os,
                   const char* text,
                   int size,
                   const nos::basic_spec& spec)
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
		ret += os.write_upper(text, size);
	}
	else if (spec.tcase == nos::text_case::lower)
	{
		ret += os.write_lower(text, size);
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

int nos_fprint_integer_impl(nos::ostream& os, char* buf, size_t len, const nos::integer_spec& spec)
{
	return nos_fprint(os, buf, len, spec);
}

int nos_fprint(nos::ostream& os, const char* text, const nos::basic_spec& spec)
{
	return nos_fprint(os, text, strlen(text), spec);
}

int nos_fprint(nos::ostream& os, const char* obj, const nos::buffer & opts)
{
	nos::text_spec spec(opts);
	return nos_fprint(os, obj, strlen(obj), spec);
}

int nos_fprint(nos::ostream& os, const std::string& obj, const nos::buffer & opts)
{
	nos::text_spec spec(opts);
	return nos_fprint(os, obj.data(), obj.size(), spec);
}

int nos_fprint(nos::ostream& os, char* obj, const nos::buffer & opts)
{
	nos::text_spec spec(opts);
	return nos_fprint(os, obj, strlen(obj), spec);
}

int nos_fprint(nos::ostream& os, bool obj, const nos::buffer & opts)
{
	return nos_fprint(os, obj ? "true" : "false", opts);
}

int nos_fprint(nos::ostream& os, signed char obj, const nos::buffer & opts) { return nos_fprint(os, (signed int)obj, opts); }
int nos_fprint(nos::ostream& os, signed short obj, const nos::buffer & opts) { return nos_fprint(os, (signed int)obj, opts); }
int nos_fprint(nos::ostream& os, signed int obj, const nos::buffer & opts)
{
	nos::integer_spec spec(opts);
	char buf[64+1];
	//char * end = i32toa(obj, buf, 10);
	int len = snprintf(buf, sizeof(buf), "%d", obj);
	return nos_fprint_integer_impl(os, buf, len, spec);
}

int nos_fprint(nos::ostream& os, signed long obj, const nos::buffer & opts)
{
	nos::integer_spec spec(opts);
	char buf[64+1];
	int len = snprintf(buf, sizeof(buf), "%ld", obj);
	return nos_fprint_integer_impl(os, buf, len, spec);
}

int nos_fprint(nos::ostream& os, signed long long obj, const nos::buffer & opts)
{
	nos::integer_spec spec(opts);
	char buf[64+1];
	int len = snprintf(buf, sizeof(buf), "%lld", obj);
	return nos_fprint_integer_impl(os, buf, len, spec);
}

int nos_fprint(nos::ostream& os, unsigned char obj, const nos::buffer & opts) { return nos_fprint(os, (unsigned int)obj, opts); }
int nos_fprint(nos::ostream& os, unsigned short obj, const nos::buffer & opts) { return nos_fprint(os, (unsigned int)obj, opts); }
int nos_fprint(nos::ostream& os, unsigned int obj, const nos::buffer & opts)
{
	nos::integer_spec spec(opts);
	char buf[64+1];
	int len = snprintf(buf, sizeof(buf), "%u", obj);
	return nos_fprint_integer_impl(os, buf, len, spec);
}

int nos_fprint(nos::ostream& os, unsigned long int obj, const nos::buffer & opts)
{
	nos::integer_spec spec(opts);
	char buf[64+1];
	int len = snprintf(buf, sizeof(buf), "%lu", obj);
	return nos_fprint_integer_impl(os, buf, len, spec);
}

int nos_fprint(nos::ostream& os, unsigned long long int obj, const nos::buffer & opts)
{
	nos::integer_spec spec(opts);
	char buf[64+1];
	int len = snprintf(buf, sizeof(buf), "%llu", obj);
	return nos_fprint_integer_impl(os, buf, len, spec);
}

int nos_fprint(nos::ostream& os, double obj, const nos::buffer & opts)
{
	int len;
	nos::float_spec spec(opts);
	char buf[64+1];
	if (spec.after_dot != -1)
		len = snprintf(buf, sizeof(buf), "%.*lf", spec.after_dot, obj);
	else
		len = snprintf(buf, sizeof(buf), "%lf", obj);
	return nos_fprint(os, buf, len, spec);
}

int nos_fprint(nos::ostream& os, float obj, const nos::buffer & opts)
{
	return nos_fprint(os, static_cast<double>(obj), opts);
}