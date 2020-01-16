/*
https://ru.wikibooks.org/wiki/%D0%90%D1%81%D1%81%D0%B5%D0%BC%D0%B1%D0%BB%D0%B5%D1%80_%D0%B2_Linux_%D0%B4%D0%BB%D1%8F_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%81%D1%82%D0%BE%D0%B2_C
*/

.code32
.data                         /* поместить следующее в сегмент данных
                                                                    */
hello_str:                    /* наша строка                        */
        .string "Hello, world!\n"
                              /* длина строки                       */
        .set hello_str_length, . - hello_str - 1
.text                         /* поместить следующее в сегмент кода */
.globl  main                  /* main - глобальный символ, видимый
                                 за пределами текущего файла        */
.type   main, @function       /* main - функция (а не данные)       */
main:
        movl    $4, %eax      /* поместить номер системного вызова
                                 write = 4 в регистр %eax           */
        movl    $1, %ebx      /* первый параметр - в регистр %ebx;
                                 номер файлового дескриптора 
                                 stdout - 1                         */
        movl    $hello_str, %ecx  /* второй параметр - в регистр %ecx;
                                     указатель на строку            */
        movl    $hello_str_length, %edx /* третий параметр - в регистр
                                           %edx; длина строки       */
        int     $0x80         /* вызвать прерывание 0x80            */

	ret

        movl    $1, %eax      /* номер системного вызова exit - 1   */
        movl    $0, %ebx      /* передать 0 как значение параметра  */
        int     $0x80         /* вызвать exit(0)                    */
 
	call	printf

        .size   main, . - main    /* размер функции main            */

