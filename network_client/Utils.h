#pragma once
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>


/*
** pack() -- сохраняет в буфер данные, переданные в строке "format"
**
**  h - 16-bit              l - 32-bit
**  c - 8-bit char          f - float, 32-bit
**  s - string (автоматически добавляется длинна в 16 бит)
*/
int32_t pack(unsigned char *buf, char *format, ...);

/*
** unpack() -- распаковывает в буфер данные, переданные в строке "format"
*/
void unpack(unsigned char *buf, char *format, ...);

//Вывод текста в консоль
void Print(char *message);