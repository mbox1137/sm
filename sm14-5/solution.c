//http://mycpp.ru/cpp/scpp/cppd_uncertainnumpars.htm

/* Пример списка аргументов переменной длины сумма ряда . */

#include <stdio.h>
#include <stdarg.h>

double sum_series(int, ...);

int main(void)
{
	double d;

	d = sum_series(5, 0.5, 0.25, 0.125, 0.0625, 0.03125);
	printf("Сумма ряда равна %f\n",d);

	return 0;
}

double sum_series(int num, ...)
{
	double sum = 0.0, t;
	va_list argptr;

	/* Инициализируем указатель argptr. */
	va_start(argptr, num);

	/* Суммируем ряд. */
	for(; num; num--) {
		t = va_arg(argptr, double);
		sum += t;
	}

	/* Реализуем корректное завершение. */
	va_end(argptr);

	return sum;
}
