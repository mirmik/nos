#ifndef NOS_FPRINT_STDTYPE_H
#define NOS_FPRINT_STDTYPE_H

/**
	@file
*/

#include <string_view>

namespace nos { class ostream; }

int nos_fprint(nos::ostream& os, const char* obj, const std::string_view & opts);

int nos_fprint(nos::ostream& os, bool obj, const std::string_view & opts);

int nos_fprint(nos::ostream& os, signed char obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, signed short obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, signed int obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, signed long obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, signed long long obj, const std::string_view & opts);

int nos_fprint(nos::ostream& os, unsigned char obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, unsigned short obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, unsigned int obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, unsigned long obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, unsigned long long obj, const std::string_view & opts);

#include <nos/io/ostream.h>

#endif
