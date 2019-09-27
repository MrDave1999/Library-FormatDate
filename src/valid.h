#ifndef _VALID_H
#define _VALID_H

#include <stdint.h>

#define FORMAT_1	0 /* yyyy/mm/dd */
#define FORMAT_2	1 /* yyyy-mm-dd */
#define FORMAT_3	2 /* dd/mm/yyyy */
#define FORMAT_4	3 /* dd-mm-yyyy */

struct _Weekday
{
	const char* const es;
	const char* const en;
};

struct _MonthYear
{
	const char* const es;
	const char* const en;
};

struct _InfoMonth
{
	uint8_t codeMonth; //Código año normal.
	uint8_t codeMonth_Leap; //Código año bisiesto.
	uint8_t dayMax; //Día máximo del mes.
};

typedef struct _InfoMonth InfoMonth;


/* 
	-> CountSign:
	Esta función detecta como máximo dos signos (ya sea el slash o guion) en el string.
	Además también verifica si el string es númerico.
*/
uint8_t CountSign(const char*, const uint8_t);

/*
	-> CountNumberSign:
	Esta función cuenta los dígitos que estén alrededor del signo (slash o guion).
	Si el formato es yyyy/mm/dd, la función al principio contará los dígitos del año, luego del mes y por último los días.
*/
uint8_t CountNumberSign(const char*, const uint8_t);

/*
	-> ConvertDateToInt:
	Esta función convierte la fecha a valores númericos (día, mes, año).
*/
void ConvertDateToInt(const char*, Date* const, const uint8_t);

/*
	-> ValidDMY:
	Esta función valida si el día, mes y año están en los rangos correspondientes.
*/
uint8_t ValidDMY(const InfoMonth* const, const Date* const date);

#endif /* _VALID_H */
