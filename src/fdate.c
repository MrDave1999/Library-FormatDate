#include <stdio.h>
#include <stdint.h>
#include "fdate.h"
#include "valid.h"

const struct _Weekday weekday[7] =
{
	{ "Domingo",	"Sunday"	},
	{ "Lunes",		"Monday"	},
	{ "Martes",		"Tuesday"	},
	{ "Miercoles",	"Wednesday" },
	{ "Jueves",		"Thursday"	},
	{ "Viernes",	"Friday"	},
	{ "Sabado",		"Saturday"	}
};

const struct _MonthYear monthyear[12] = 
{
	{"Enero",		"January"	},
	{"Febrero",		"February"	},
	{"Marzo",		"March"		},
	{"Abril",		"April"		},
	{"Mayo",		"May"		},
	{"Junio",		"June"		},
	{"Julio",		"July"		},
	{ "Agosto",		"August"	},
	{"Septiembre",	"September" },
	{"Octubre",		"October"	},
	{"Noviembre",	"November"	},
	{"Diciembre",	"December"	},
};

const struct _InfoMonth iMonth[12] =
{
	{ 0, 0, 31 },	//Enero
	{ 3, 3, 29 },	//Febrero
	{ 3, 4, 31 },	//Marzo
	{ 6, 0, 30 },	//Abril
	{ 1, 2, 31 },	//Mayo
	{ 4, 5, 30 },	//Junio
	{ 6, 0, 31 },	//Julio
	{ 2, 3, 31 },	//Agosto
	{ 5, 6, 30 },	//Septiembre
	{ 0, 1, 31 },	//Octubre
	{ 3, 4, 30 },	//Noviembre
	{ 5, 6, 31 }	//Diciembre
};

int GetWeekday(const Date* const date)
{
	int x, y, z;
	if (ValidDMY(iMonth, date)) return -1;
	x = (date->year - 1) % 7;
	y = ((((date->year - 1) / 4) - (3 * ((((date->year - 1) / 100) + 1) / 4))) % 7) + (date->day % 7);
	z = YearLeap(date->year) ? (iMonth[date->month - 1].codeMonth_Leap) : (iMonth[date->month - 1].codeMonth);
	return (x + y + z) % 7;
}

uint8_t Tryparse(const char* const format, const char* const buf, Date* const date)
{
	const uint8_t formatid = ((format[0] == 'y' && format[4] == '/') ? (0) : //Formato: yyyy/mm/dd
		((format[0] == 'y' && format[4] == '-') ? (1) : //Formato: yyyy-mm-dd
		((format[0] == 'd' && format[2] == '/') ? (2) : //Formato: dd/mm/yyy
		((format[0] == 'd' && format[2] == '-') ? (3) : //Formato: dd-mm-yyyy
		(4))))) //Formato erróneo.
	;
	if (CountSign(buf, formatid) || CountNumberSign(buf, formatid))
	{
		printf("Error: No estas cumpliendo con el formato esperado: %s\n", format);
		return 1;
	}

	ConvertDateToInt(buf, date, formatid);
	
	return ValidDMY(iMonth, date) ? (1) : (0);
}

const char* GetNameWeekday(uint8_t code, uint8_t language)
{
	return (language == ES) ? (weekday[code].es) : (weekday[code].en);
}

const char* GetNameMonth(uint8_t codeMonth, uint8_t language)
{
	return (language == ES) ? (monthyear[codeMonth - 1].es) : (monthyear[codeMonth - 1].en);
}
