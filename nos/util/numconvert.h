#ifndef UTIL_NUMBER_CONVERT
#define UTIL_NUMBER_CONVERT

//Набор функций конвертеров в сишним стиле.

#include <sys/cdefs.h>
#include <inttypes.h>

__BEGIN_DECLS

char *nos_util_i64toa( int64_t num, char *buf, uint8_t base );
char *nos_util_i32toa( int32_t num, char *buf, uint8_t base );
char *nos_util_i16toa( int16_t num, char *buf, uint8_t base );
char *nos_util_i8toa( int8_t num, char *buf, uint8_t base );

char *nos_util_u64toa( uint64_t num, char *buf, uint8_t base );
char *nos_util_u32toa( uint64_t num, char *buf, uint8_t base );
char *nos_util_u16toa( uint64_t num, char *buf, uint8_t base );
char *nos_util_u8toa( uint64_t num, char *buf, uint8_t base );

uint32_t nos_util_atou32(const char *buf, uint8_t base, char** end);
int32_t nos_util_atoi32(const char *buf, uint8_t base, char** end);

char * nos_util_ftoa(double f, char * buf, int precision);
double nos_util_atod(const char* str, char** pend);

__END_DECLS

#endif
