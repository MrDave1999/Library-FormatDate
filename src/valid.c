#include <stdio.h>
#include "fdate.h"
#include "valid.h"

#define SIGN const uint8_t sign = (formatid == FORMAT_1 || formatid == FORMAT_3) ? ('/') : ('-')

uint8_t CountSign(const char* buf, const uint8_t formatid)
{
	SIGN;
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

uint8_t CountNumberSign(const char* buf, const uint8_t formatid)
{
	SIGN;
	uint32_t countNumber = 0;
	uint8_t group_num = 0;
	for (; *buf != '\0'; ++buf)
	{
		if (!group_num && *buf == sign)
		{
			/* Cuando se esté analizando yyyy/ or dd/ */
			if(((formatid == FORMAT_1 || formatid == FORMAT_2) && (countNumber != 4)) || 
				((formatid == FORMAT_3 || formatid == FORMAT_4) && (countNumber != 1 && countNumber != 2)))
				return 1;
			countNumber = 0;
			group_num = 1;
		}
		else if (group_num && *buf == sign)
		{
			/* Cuando se esté analizando yyyy/mm/ or dd/mm/ */
			if (countNumber != 1 && countNumber != 2) return 1;
			countNumber = 0;
			group_num = 2;
		}
		else ++countNumber;
	}
	/* Cuando se esté analizando yyyy/mm/dd or dd/mm/yyyy */
	return (((formatid == FORMAT_1 || formatid == FORMAT_2) && (countNumber != 1 && countNumber != 2)) ||
		((formatid == FORMAT_3 || formatid == FORMAT_4) && (countNumber != 4))) ? (1) : (0);
}

void ConvertDateToInt(const char* buf, Date* const date, const uint8_t formatid)
{
	SIGN;
	uint32_t aux = 0;
	uint8_t group_num = 0;
	for (; *buf != '\0'; ++buf)
	{
		if (!group_num && *buf == sign)
		{
			(formatid == FORMAT_1 || formatid == FORMAT_2) ? (date->year = aux) : (date->day = aux);
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
	(formatid == FORMAT_1 || formatid == FORMAT_2) ? (date->day = aux) : (date->year = aux);
}

/* Validar día, mes y año. */
uint8_t ValidDMY(const InfoMonth* const iMonth, const Date* const date)
{
	uint8_t dayMax;
	uint8_t error = 0;
	if (!(date->year >= 1000 && date->year <= 9999))
	{
		printf("Error: El anio debe estar en el rango de 1000 a 9999.\n");
		error = 1;
	}
	if (!(date->month >= 1 && date->month <= 12))
	{
		printf("Error: El mes debe estar en el rango de 1 a 12.\n");
		return 1;
	}
	if ((YearLeap(date->year) && (!(date->day >= 1 && date->day <= (dayMax = iMonth[date->month - 1].dayMax)))) || /* Para año bisiesto */
		((!YearLeap(date->year) && (!(date->day >= 1 && date->day <= (((date->month - 1) == 1) ? (dayMax = iMonth[date->month - 1].dayMax - 1) : (dayMax = iMonth[date->month - 1].dayMax))))))) /* Para año no bisiesto */
	{
		printf("Error: El dia debe estar en el rango de 1 a %d\n", dayMax);
		error = 1;
	}
	return error;
}
