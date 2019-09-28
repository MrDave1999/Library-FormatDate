#include <stdio.h>
#include "fdate.h"
#include "valid.h"

uint8_t CountSign(const char* buf, const uint8_t formatid, const uint8_t sign)
{
	uint32_t countSign = 0;
	for (; *buf != '\0'; ++buf)
	{
		if (*buf == sign)
		{
			++countSign;
			continue;
		}
		if (!(*buf >= '0' && *buf <= '9')) return 1;
	}
	return (countSign == 2) ? (0) : (1);
}

void ConvertDateToInt(const char* buf, Date* const date, const uint8_t formatid, const uint8_t sign)
{
	uint32_t aux = 0;
	uint8_t group_num = 0;
	for (; *buf != '\0'; ++buf)
	{
		if (!group_num && *buf == sign)
		{
			(formatid == yyyyMMdd) ? (date->year = aux) : (date->day = aux);
			aux = 0;
			group_num = 1;
		}
		else if (group_num && *buf == sign)
		{
			date->month = aux;
			aux = 0;
			group_num = 2;
		}
		else aux = (aux * 10) + (*buf - '0');
	}
	(formatid != ddMMyyyy) ? (date->day = aux) : (date->year = aux);
}

/* Validar día, mes y año. */
uint8_t ValidDMY(const InfoMonth* const iMonth, const Date* const date)
{
	uint8_t dayMax;
	if (!(date->year >= 1000 && date->year <= 9999))
	{
		printf("Error: El a%co debe estar en el rango de 1000 a 9999.\n", 164);
		return 1;
	}
	if (!(date->month >= 1 && date->month <= 12))
	{
		printf("Error: El mes debe estar en el rango de 1 a 12.\n");
		return 1;
	}
	if ((YearLeap(date->year) && (!((date->day >= 1) & (date->day <= (dayMax = iMonth[date->month - 1].dayMax)))) || /* Para año bisiesto */
		((!YearLeap(date->year) && (!((date->day >= 1) & (date->day <= (((date->month - 1) == 1) ? (dayMax = iMonth[date->month - 1].dayMax - 1) : (dayMax = iMonth[date->month - 1].dayMax))))))))) /* Para año no bisiesto */
	{
		printf("Error: El d%ca debe estar en el rango de 1 a %d.\n", 161, dayMax);
		return 1;
	}
	return 0;
}
