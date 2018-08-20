#pragma once
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>


/*
** pack() -- ��������� � ����� ������, ���������� � ������ "format"
**
**  h - 16-bit              l - 32-bit
**  c - 8-bit char          f - float, 32-bit
**  s - string (������������� ����������� ������ � 16 ���)
*/
int32_t pack(unsigned char *buf, char *format, ...);

/*
** unpack() -- ������������� � ����� ������, ���������� � ������ "format"
*/
void unpack(unsigned char *buf, char *format, ...);

//����� ������ � �������
void Print(char *message);