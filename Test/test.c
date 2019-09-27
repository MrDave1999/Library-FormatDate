#include <stdio.h>
#include <pscanf.h> /* www.github.com/MrDave1999/pscanf.h */
#include <fdate.h>

void EntryDate(const char*const);

int main(void)
{
	while (1)
	{
		EntryDate("yyyy/mm/dd");
		EntryDate("yyyy-mm-dd");
		EntryDate("dd/mm/yyyy");
		EntryDate("dd-mm-yyyy");
	}
	return 0;
}

void EntryDate(const char* const format)
{
	Date date;
	string strDate = { NULL };
	do
	{
		strread(&strDate, "Ingrese una fecha con formato: %s\n", format);
	} while (Tryparse(format, strDate.s, &date));
	printf("Year: %d, Month: %d (%s), Day: %d (%s)\n\n", date.year, date.month, GetNameMonth(date.month, ES), date.day, GetNameWeekday(GetWeekday(&date), ES));
	pause();
}
