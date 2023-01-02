#include "s21_string.h"
#include <stdlib.h>

/* Ищет адрес заданного для поиска символа, считывая каждый байт в буфере (массиве).
Возвращает указатель именно на первое расположение символа. */

void *s21_memchr(const void *str, int c, s21_size_t n) {
    unsigned char *p = (unsigned char *) str;
    unsigned char *isCharfind = s21_NULL;
    while ((str != s21_NULL) && (n--)) {
        if (*p != (unsigned char)c) {
            p++;
        } else {
            isCharfind = p;
            break;
        }
    }
    return isCharfind;
}

/* ------- */

/* Побайтно сравнивает два массива, на которые указывают аргументы.
Сравнение продолжается, пока массив не закончится или пока не будет найдено различие. */

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int res = 0;
    for (s21_size_t i = 0; i < n && res == 0 ; i++) {
        if (((unsigned char *)str1)[i] != ((unsigned char *)str2)[i])
            res = ((unsigned char *)str1)[i] - ((unsigned char *)str2)[i];
    }
    return (res);
}

/* ------- */

/* Копирует байты из src в dest, то есть между буферами.
Размер буфера назначения (куда копируется) должен быть таким же или больше. */

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char *csrc = (unsigned char *)src;
    unsigned char *cdest = s21_NULL;
    if (csrc) {
        cdest = (unsigned char *)dest;
    }
    if (cdest) {
        for (s21_size_t i = 0; i < n; i++)
            cdest[i] = csrc[i];
    }
    return cdest;
}

/* ------- */

/* Копирует байты из src в dest, то есть между буферами.
В отличии от memcpy массивы могут пересекаться между собою.
Размер буфера назначения (куда копируется) должен быть таким же или больше. */

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    if (src < dest) {
        while (n-- > 0)
            *((unsigned char *)dest + n) = *((unsigned char *)src + n);
    } else if (src > dest) {
        for (s21_size_t i = 0; i < n; i++)
            *((unsigned char *)dest + i) = *((unsigned char *)src + i);
    }
    return (dest);
}

/* ------- */

/* Заполняет первые n байт массива символом, указанным в с.*/

void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char* p = (unsigned char*)str;
    if (p) {
        while (n--) {
            *p++ = (unsigned char)c;
        }
    }
    return str;
}

/* ------- */

/* Объединяет указанные в буффере строки в одну,
все строки будут записаны в первый указанный аргумент, её и надо выводить в sprintf. */

char* s21_strcat(char* dest, const char* src) {
    s21_size_t i, dest_len;
    i = 0;
    dest_len = 0;
    while (dest[dest_len]) {
        dest_len++;
    }
    while (src[i]) {
        dest[dest_len] = src[i];
        i++;
        dest_len++;
    }
    dest[dest_len] = '\0';
    return dest;
}

/* ------- */

/* Ищет позицию первого вхождения символа в указанной строке. */

char *s21_strchr(const char *str, int c) {
    char *res = s21_NULL;
    for (; *str && !res ; str++) {
        if (*str == (unsigned char)c)
            res = (char *)str;
    }
    if (c == '\0')
        res = (char *)str;
    return res;
}

/* ------- */

/* Сравнивает две строки и возвращает 0, если строки индентичны,
и положительное или отрицательное число, если строки разные
(взависимости от того, больше или меньше строка другой). */

int s21_strcmp(const char *str1, const char *str2) {
    int res = 0;
    for (s21_size_t i = 0; (str1[i] || str2[i]) && res == 0 ; i++) {
        if (((unsigned char *)str1)[i] != ((unsigned char *)str2)[i])
            res = ((unsigned char *)str1)[i] - ((unsigned char *)str2)[i];
    }
    return (res);
}

/* ------- */

/* Копирует одну строку в другую. */

char* s21_strcpy(char* dest, const char* src) {
    s21_size_t i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);
}

/* ------- */

/* Выполняет поиск первого вхождения в первую строку любого из символов второй строки, 
и возвращает количество символов до найденного первого вхождения. */

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    const char* s1 = str1;
    s21_size_t i = 0;
    s21_size_t j = 0;
    s21_size_t n;
    while (s1[i] != 0) {
        i++;
    }
    n = i;
    while (str2[j]) {
        i = 0;
        while (str1[i] != 0) {
            if (str1[i] == str2[j]) {
                if (i < n) {
                   n = i;
                }
            }
            i++;
        }
        j++;
    }
    return n;
}

/* ------- */

/* Формирует отчёт об ошибке в определённой строке. */

char *s21_strerror(int errnum) {
    static char mes[101];
    s21_memset(mes, 0, 101);
    if (errnum < 0 || errnum > MAX) {
#ifdef __APPLE__
        s21_sprintf(mes, "Unknown error: %d", errnum);
#elif defined __linux__
        s21_sprintf(mes, "No error information");
#endif
    } else {
        static char *arr[] = error;
        s21_memcpy(mes, arr[errnum], s21_strlen(arr[errnum]));
    }
    return mes;
}

/* ------- */

/* Длина строки. 
Вычисляет количество символов в строке до её конца. 
Конец строки не входит в подсчёт символов. */

s21_size_t s21_strlen(const char *str) {
    s21_size_t lenght = 0;
    while (str && *str != '\0') {
        lenght++;
        str++;
    }
    return lenght;
}

/* ------- */

/* Добавляет в строку, на которую указывает аргумент dest, 
строку, на которую указывает аргумент src, пока не встретится символ конца строки 
или пока не будет добавлено n символов. */

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *x;
    x = dest;
    while (*dest)
            dest++;
    while (*src && n--)
        *dest++ = *src++;
    *dest = 0;
    return x;
}

/* ------- */

/* Побайтово проверяет n символов в двух строках и возвращает значение 0,
если строки отличаются, и положительное или отрицательное число, если идентичны. 
Если первый отличающийся символ или его код больше, чем у второй строки - положительное число.
Если меньше - отрицательное. */

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int res = 0;
    for (s21_size_t i = 0; i < n && res == 0; i++) {
        if (((unsigned char *)str1)[i] != ((unsigned char *)str2)[i])
            res = ((unsigned char *)str1)[i] - ((unsigned char *)str2)[i];
        if (str1[i] == '\0')
            i = n;
    }
    return (res);
}

/* ------- */

/* Копирует n символов из строки src в строку dest. 
Если значение n больше строки, то остальное пространство заполнится нулевыми символами. */

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = 0;
    return dest;
}

/* ------- */

/* Ищет первое вхождение любого символа из строки sym. 
Поиск осуществляется в строчке str.
Выводится, на какой позиции находится первый найденный символ из множества. */

char *s21_strpbrk(const char *str1, const char *str2) {
    char *res = s21_NULL;
    while (*str1 && !res) {
        s21_size_t j = 0;
        while (str2[j] != '\0') {
            if (*str1 == str2[j])
                res = (char*) str1;
            j++;
        }
        str1++;
    }
    return (res);
}

/* ------- */

/* Ищет позицию последнего вхождения символа c в строке str. */

char *s21_strrchr(const char *str, int c) {
    char *found = s21_NULL;
    s21_size_t len = s21_strlen(str);
    char *a = (char *)str + len;
    s21_size_t count = 0;
    if (str != s21_NULL) {
        while ((*a != (char)c) && (count <= len)) {
            a--;
            count++;
        }
        if (count <= len) {
            found = a;
        }
    }
    return found;
}

/* ------- */

/* Определяет наибольшую длину начального участка строки, на которую указывает аргумент str1, 
содержащего только символы строки, на которую указывает аргумент str2.
Если первый символ строки str1 не входит в строку str2, то возвращаемая длина – 0. */

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t i = 0;
        while (str1[i]) {
            s21_size_t j = 0;
            while (str2[j]) {
                if (str1[i] == str2[j])
                    break;
                j++;
            }
            if (str2[j] == '\0')
                break;
            i++;
        }
    return (i);
}

/* ------- */

/* ищет первое вхождение строки, на которую указывает аргумент haystack, 
в строку , на которую указывает аргумент needle. 
Если строка haystack имеет нулевую длину, то функция вернет указатель на начало строки needle. */


char *s21_strstr(const char *haystack, const char *needle) {
    char *pointer = s21_NULL;
    if (haystack && needle) {
        if (*needle) {
            s21_size_t len = s21_strlen(needle);
            for (s21_size_t i = 0; haystack[i] != '\0' && pointer == s21_NULL; i++) {
                if (!s21_strncmp(haystack + i, needle, len)) {
                    pointer = (char *)haystack + i;
                }
            }
        } else {
            pointer = (char *)haystack;
        }
    }
    return pointer;
}

/* ------- */

/* Разбивает строку str на части по указанному в delim разделителе. 
Это может быть любой символ, который не будет печататься с остальными строками. */

char *s21_strtok(char *str, const char *delim) {
    static char* buff = s21_NULL;
    char* res = s21_NULL;
    s21_size_t i = 0;

    if (str)
        buff = str;
    if (buff && s21_strlen(buff) == 0)
        buff = s21_NULL;
    if (buff && s21_strchr(delim, buff[i])) {
        while (s21_strchr(delim, buff[i]))
            buff++;
    }
    while (buff && !res) {
        if (buff[i] == '\0') {
            res = buff;
            buff = s21_NULL;
        } else if (s21_strchr(delim, buff[i])) {
            buff[i] = '\0';
            res = buff;
            buff += i + 1;
        }
        i++;
    }
    return res;
}

/* ------- */


/* Возвращает новую строку, в которой указанная строка (str) 
вставлена в указанную позицию (start_index) в данной строке (src). 
В случае какой-либо ошибки возвращает значение NULL. */

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *string = s21_NULL;
    if (src && str && s21_strlen(src) >= start_index) {
        string = calloc((s21_strlen(src) + s21_strlen(str) + 1), sizeof(char));
        if (string) {
            s21_strncpy(string, src, start_index);
            string[start_index] = '\0';
            s21_strcat(string, str);
            s21_strcat(string, src + start_index);
        }
    }
    return string;
}

/* ------- */

/* Возвращает копию строки (str), преобразованной в нижний регистр. 
В случае какой-либо ошибки возвращает значение NULL */

void *s21_to_lower(const char *str) {
    char *string = s21_NULL;
    if (str != s21_NULL) {
        s21_size_t n = s21_strlen(str);
        string = calloc(n + 1, sizeof(char));
        if (string) {
            for (s21_size_t i = 0; i < n ; i++) {
                if (str[i] >= 'A' && str[i] <= 'Z')
                    string[i] = str[i] + 32;
                else
                    string[i] = str[i];
            }
            string[n] ='\0';
        }
    }
    return string;
}

/* ------- */

/* Возвращает копию строки (str), преобразованной в верхний регистр. 
В случае какой-либо ошибки возвращает значение NULL. */

void *s21_to_upper(const char *str) {
    char *string = s21_NULL;
    if (str != s21_NULL) {
        s21_size_t n = s21_strlen(str);
        string = calloc(n + 1, sizeof(char));
        if (string) {
            for (s21_size_t i = 0; i < n ; i++) {
                if (str[i] >= 'a' && str[i] <= 'z')
                    string[i] = str[i] - 32;
                else
                    string[i] = str[i];
            }
            string[n] ='\0';
        }
    }
    return string;
}

/* ------- */

/* Возвращает новую строку, в которой из первоначальной строки 
удаляются все начальные и конечные вхождения набора заданных символов. 
В случае какой-либо ошибки следует вернуть значение NULL */

void *s21_trim(const char *src, const char *trim_chars) {
    char *string = s21_NULL;
    if (!trim_chars || s21_strlen(trim_chars) == 0)
        trim_chars = " \f\n\r\t\v";
    if (src && trim_chars) {
        char *first_string = (char *)src;
        char *last_string = (char *)src + s21_strlen(src);
        for ( ; *first_string && s21_strchr(trim_chars,
        *first_string); first_string++) {
        }
        for ( ; last_string != first_string &&
        s21_strchr(trim_chars, * (last_string - 1)); last_string--) {
        }
        string = calloc((last_string - first_string + 1), sizeof(char));
        if (string) {
        s21_strncpy(string, first_string, last_string - first_string);
        *(string + (last_string - first_string)) = '\0';
        }
    }
    return string;
}
