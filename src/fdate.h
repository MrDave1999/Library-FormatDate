#ifndef _FDATE_H
#define _FDATE_H

#include <stdint.h>

#define ES 0
#define EN 1

#define YearLeap(year) ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))

struct _Date
{
	int day;
	int month;
	int year;
};

typedef struct _Date Date;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int GetWeekday(const Date* const);
uint8_t Tryparse(const char* const, const char* const, Date* const);
const char* GetNameWeekday(uint8_t, uint8_t);
const char* GetNameMonth(uint8_t, uint8_t);
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _FDATE_H */
