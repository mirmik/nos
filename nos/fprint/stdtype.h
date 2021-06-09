#ifndef NOS_FPRINT_STDTYPE_H
#define NOS_FPRINT_STDTYPE_H

/**
	@file
*/

#include <string_view>

namespace nos { class ostream; }

int nos_fprint(nos::ostream& os, const char* obj, const std::string_view & opts);

int nos_fprint(nos::ostream& os, bool obj, const std::string_view & opts);

int nos_fprint(nos::ostream& os, int8_t obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, int16_t obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, int32_t obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, int64_t obj, const std::string_view & opts);

int nos_fprint(nos::ostream& os, uint8_t obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, uint16_t obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, uint32_t obj, const std::string_view & opts);
int nos_fprint(nos::ostream& os, uint64_t obj, const std::string_view & opts);

#include <nos/io/ostream.h>

#endif
