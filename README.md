# Library-FormatDate
[![pscanf.h](https://shields.southcla.ws/badge/FormatDate-v1.0-2f2f2f.svg?style=flat-square)](https://github.com/MrDave1999/Library-FormatDate)

Esta biblioteca permite validar fechas con un determinado formato.

## Instalación

- Si usas cl.exe (de Visual Studio) como  compilador de C/C++, debes agregar lo siguiente:

  - La biblioteca estática llamada libpscanf.lib la debes añadir en la carpeta `lib` y se lo encuentra en la siguiente ruta:            	`C:\Program Files\Microsoft Visual Studio 12.0\VC\lib`
	
	Para evitar esta posible advertencia del enlazador: 
	`warning LNK4099: PDB 'libfdate.pdb' was not found with 'libfdate.pdb.lib' or at 'libfdate.pdb'; linking object as if no debug info`
	
	Agrega el archivo `libfdate.pdb` en la misma carpeta donde metas `libfdate.lib` .
	
	Luego de añadir la biblioteca y el archivo .PDB, abrimos el Visual Studio y nos vamos a la sección de Proyecto -> Propiedades de configuración -> Vinculador -> Entrada -> Dependencias adicionales (en esta opción agregas el nombre de la biblioteca estática con su respectiva extensión .lib) .
	
  - El archivo de cabecera llamado fdate.h la debes añadir en la carpeta `include` y se lo encuentra en la siguiente ruta:
	`C:\Program Files\Microsoft Visual Studio 12.0\VC\include`
 
Cuando hayas hecho los dos pasos anteriores, procedes a incluir el archivo fdate.h en el archivo de origen (donde está el main):
```C
#include <fdate.h>
```
- Si usas Dev-C++ como IDE(Entorno de desarrollo integrado) para compilar códigos de C/C++, debes agregar lo siguiente:

  - La biblioteca estática llamada libpscanf.a la debes añadir en la carpeta `lib` y se lo encuentra en la siguiente ruta: 
  `C:\Program Files\Dev-Cpp\lib`
	
	Luego de añadir la biblioteca, abrimos el Dev-C++ y nos vamos a la sección de Proyecto -> Opciones del proyecto -> Parámetros -> Linker (en esta opción agregas el siguiente comando: -lfdate) .
	
  - El archivo de cabecera llamado fdate.h la debes añadir en la carpeta `include` y se lo encuentra en la siguiente ruta:
  `C:\Program Files\Dev-Cpp\include`
  
La biblioteca y el archivo de cabecera lo debes descargar aquí: [Library-FormatDate](https://github.com/MrDave1999/Library-FormatDate/releases/tag/v1.0)

## Funciones

- ### GetWeekday

`int GetWeekday(const Date* const date);`

Calcula el día de la semana con el siguiente [algoritmo](https://es.wikibooks.org/wiki/Algoritmia/Algoritmo_para_calcular_el_d%C3%ADa_de_la_semana).

**Parámetros:**

`const Date* const date`: Este puntero recibe la dirección base de una variable de estructura de tipo Date.

**Valor de retorno:**

Devuelve un valor que esté en el rango de 0 a 6, que básicamente representa el código de la semana. Si llega a ocurrir un error en la ejecución, retorna -1. La función envía un mensaje de error por defecto.

**Ejemplo:**
```C
#include <stdio.h>
#include <fdate.h>

int main(void)
{
	Date date = {23, 02, 2008};
	int codeWeekday = GetWeekday(&date);
	if (codeWeekday != -1)
		printf("Code WeekDay: %d\n", codeWeekday);
	return 0;
}
```

- ### Tryparse

`uint8_t Tryparse(const char* const format, const char* const buf, Date* const date);`

Valida la fecha con un formato.

**Parámetros:**

`const char* const format`: Este puntero recibe la dirección base del formato especificado. 

  Los formatos válidos son:
  
    - yyyy/mm/dd
    - yyyy-mm-dd
    - dd/mm/yyyy
    - dd-mm-yyyy

`const char* const buf`: Este puntero recibe la dirección base de un búfer (básicamente ahí es donde está la fecha a validar).

`Date* const date)`: Este puntero recibe la dirección base de una variable de estructura de tipo Date. 

**Valor de retorno:**

Retorna 0 si la función no encontró ningún error en la fecha, de lo contrario, devuelve 1. La función envía un mensaje de error por defecto.

**Ejemplo:**
```C
#include <stdio.h>
#include <fdate.h>
int main(void)
{
	Date date;
	const char* stringDate = "20/05/2098";
	if (Tryparse("yyyy/mm/dd", stringDate, &date) != 1) //La función dará true, no se cumplió con el formato.
		printf("%d %d %d", date.year, date.month, date.day);
   
	return 0;
}
```

- ### GetNameWeekday

`const char* GetNameWeekday(uint8_t code, uint8_t language)`

Obtiene el nombre del día de la semana, ya sea en español o inglés.

**Parámetros:**

`uint8_t code`: Este parámetro recibe el código de la semana.

`ùint8_t language`: Este parámetro recibe la id del lenguaje. 0 si es español, 1 si es en inglés.

**Valor de retorno:**

Retorna el nombre del día de la semana (Lunes, martes, ...).

**Ejemplo:**
```C
#include <stdio.h>
#include <fdate.h>

int main(void)
{
	printf("%s, %s\n", GetNameWeekday(0, ES), GetNameWeekday(0, EN));
  //Resultado en pantalla: Lunes, Monday
	return 0;
}

```

- ### GetNameMonth

`const char* GetNameMonth(uint8_t codeMonth, uint8_t language)`

Obtiene el nombre del mes, ya sea en español o inglés.

**Parámetros:**

`uint8_t codeMonth`: Este parámetro recibe el código del mes (1-12).

`uint8_t language`: Este parámetro recibe la id del lenguaje. 0 si es español, 1 si es en inglés.

**Valor de retorno:**

Retorna el nombre del mes (Enero, febrero, ...).

**Ejemplo:**
```C
#include <stdio.h>
#include <fdate.h>

int main(void)
{
	printf("%s, %s\n", GetNameMonth(1, ES), GetNameMonth(1, EN));
  //Resultado en pantalla: Enero, January
	return 0;
}
```

### Uso

En el siguiente ejemplo, se le pide al usuario que ingrese su fecha de nacimiento para poder calcular su determinada edad.

```C
#include <stdio.h>
#include <pscanf.h> /* www.github.com/MrDave1999/pscanf.h */
#include <fdate.h>

#include <time.h>

int main()
{
	Date date;
	string dateStr = { NULL };
	int yearCurrent;
	time_t t;
	struct tm *tm;
	t = time(NULL);
	tm = localtime(&t);
	yearCurrent = 1900 + tm->tm_year;
	do
	{
		strread(&dateStr, "Ingrese su fecha de nacimiento (Formato: yyyy/mm/dd) \n");
	} while (Tryparse("yyyy/dd/mm", dateStr.s, &date));
	printf("Tu Edad es de: %d anios\n", yearCurrent - date.year);
	pause();
}
```

### Créditos

- [MrDave](https://github.com/MrDave1999)

- [Microsoft](https://github.com/Microsoft) 
