#ifndef _VALID_H
#define _VALID_H

#include <stdint.h>

/* Formatos generales */
#define yyyyMMdd (0)
#define ddMMyyyy (1)

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
	Esta función detecta como máximo dos signos (ya sea el slash o guion) en la fecha.
	Además también verifica si la fecha tiene valores númericos.
*/
uint8_t CountSign(const char*, const uint8_t, const uint8_t);

/*
	-> ConvertDateToInt:
	Esta función convierte la fecha a valores númericos (día, mes, año).
*/
void ConvertDateToInt(const char*, Date* const, const uint8_t, const uint8_t);

/*
	-> ValidDMY:
	Esta función valida si el día, mes y año están en los rangos correspondientes.
*/
uint8_t ValidDMY(const InfoMonth* const, const Date* const date);

#endif /* _VALID_H *
