#include <stdio.h>
#include <pscanf.h> /* www.github.com/MrDave1999/pscanf.h */
#include <fdate.h>

int main(void)
{
	Date date;
	string strDate = { NULL };
	while (1)
	{
		do
		{
			strread(&strDate, "Ingrese una fecha: \n");
		} while (Tryparse("yyyy/mm/dd", strDate.s, &date));
		printf("Year: %d, Month: %d (%s), Day: %d (%s)\n\n", date.year, date.month, GetNameMonth(date.month, ES), date.day, GetNameWeekday(GetWeekday(&date), ES));
		pause();
	}
	return 0;
}
     
