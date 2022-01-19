#ifndef NOS_UTIL_NUMCONVERT_H
#define NOS_UTIL_NUMCONVERT_H

char *__nos_ftoa(float f, char *buf, int8_t precision);
char *__nos_dtoa(double f, char *buf, int8_t precision);
char *__nos_ldtoa(long double f, char *buf, int8_t precision);

#endif
