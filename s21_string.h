#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#define s21_size_t unsigned long long
#define s21_NULL (void*)0

#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include <wchar.h>

typedef struct Stack {
    int code;
    struct Stack *next;
} Stack;

struct PutSettings {
    int r_justify;
    int justify_num;
    int dot_specifier;
    int must_signed;
    int must_spaced;
    int mem_allocated;
    int l_defined;
    int h_defined;
    int L_defined;
    int base;
    int big_x;
    int char_counter;
    int hash;
    int big_e;
    int g_specified;
    int dot_specified;
    int zero_specified;
    int is_num;
    int pointer;
};

void init(Stack **stackPointer);
void push(Stack **stackPointer, int data);
int pop(Stack **stackPointer);
int peek(Stack **stackPointer);
int isAny(Stack *stackPointer, int value);
void destroy(Stack **stackPointer);

#if defined(__APPLE__)
    #define MAX 106
    #define error {"Undefined error: 0", \
"Operation not permitted", \
"No such file or directory", \
"No such process", \
"Interrupted system call", \
"Input/output error", \
"Device not configured", \
"Argument list too long", \
"Exec format error", \
"Bad file descriptor", \
"No child processes", \
"Resource deadlock avoided", \
"Cannot allocate memory", \
"Permission denied", \
"Bad address", \
"Block device required", \
"Resource busy", \
"File exists", \
"Cross-device link", \
"Operation not supported by device", \
"Not a directory", \
"Is a directory", \
"Invalid argument", \
"Too many open files in system", \
"Too many open files", \
"Inappropriate ioctl for device", \
"Text file busy", \
"File too large", \
"No space left on device", \
"Illegal seek", \
"Read-only file system", \
"Too many links", \
"Broken pipe", \
"Numerical argument out of domain", \
"Result too large", \
"Resource temporarily unavailable", \
"Operation now in progress", \
"Operation already in progress", \
"Socket operation on non-socket", \
"Destination address required", \
"Message too long", \
"Protocol wrong type for socket", \
"Protocol not available", \
"Protocol not supported", \
"Socket type not supported", \
"Operation not supported", \
"Protocol family not supported", \
"Address family not supported by protocol family", \
"Address already in use", \
"Can't assign requested address", \
"Network is down", \
"Network is unreachable", \
"Network dropped connection on reset", \
"Software caused connection abort", \
"Connection reset by peer", \
"No buffer space available", \
"Socket is already connected", \
"Socket is not connected", \
"Can't send after socket shutdown", \
"Too many references: can't splice", \
"Operation timed out", \
"Connection refused", \
"Too many levels of symbolic links", \
"File name too long", \
"Host is down", \
"No route to host", \
"Directory not empty", \
"Too many processes", \
"Too many users", \
"Disc quota exceeded", \
"Stale NFS file handle", \
"Too many levels of remote in path", \
"RPC struct is bad", \
"RPC version wrong", \
"RPC prog. not avail", \
"Program version wrong", \
"Bad procedure for program", \
"No locks available", \
"Function not implemented", \
"Inappropriate file type or format", \
"Authentication error", \
"Need authenticator", \
"Device power is off", \
"Device error", \
"Value too large to be stored in data type", \
"Bad executable (or shared library)", \
"Bad CPU type in executable", \
"Shared library version mismatch", \
"Malformed Mach-o file", \
"Operation canceled", \
"Identifier removed", \
"No message of desired type", \
"Illegal byte sequence", \
"Attribute not found", \
"Bad message", \
"EMULTIHOP (Reserved)", \
"No message available on STREAM", \
"ENOLINK (Reserved)", \
"No STREAM resources", \
"Not a STREAM", \
"Protocol error", \
"STREAM ioctl timeout", \
"Operation not supported on socket", \
"Policy not found", \
"State not recoverable", \
"Previous owner died", \
"Interface output queue is full"}
#elif defined (__linux__)
    #define MAX 133
    #define error {"Success", \
"Operation not permitted", \
"No such file or directory", \
"No such process", \
"Interrupted system call", \
"I/O error", \
"No such device or address", \
"Argument list too long", \
"Exec format error", \
"Bad file descriptor", \
"No child process", \
"Resource temporarily unavailable", \
"Out of memory", \
"Permission denied", \
"Bad address", \
"Block device required", \
"Resource busy", \
"File exists", \
"Cross-device link", \
"No such device", \
"Not a directory", \
"Is a directory", \
"Invalid argument", \
"Too many open files in system", \
"No file descriptors available", \
"Not a tty", \
"Text file busy", \
"File too large", \
"No space left on device", \
"Invalid seek", \
"Read-only file system", \
"Too many links", \
"Broken pipe", \
"Domain error", \
"Result not representable", \
"Resource deadlock would occur", \
"Filename too long", \
"No locks available", \
"Function not implemented", \
"Directory not empty", \
"Symbolic link loop", \
"No error information", \
"No message of desired type", \
"Identifier removed", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"Device not a stream", \
"No data available", \
"Device timeout", \
"Out of streams resources", \
"No error information", \
"No error information", \
"No error information", \
"Link has been severed", \
"No error information", \
"No error information", \
"No error information", \
"Protocol error", \
"Multihop attempted", \
"No error information", \
"Bad message", \
"Value too large for data type", \
"No error information", \
"File descriptor in bad state", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"No error information", \
"Illegal byte sequence", \
"No error information", \
"No error information", \
"No error information", \
"Not a socket", \
"Destination address required", \
"Message too large", \
"Protocol wrong type for socket", \
"Protocol not available", \
"Protocol not supported", \
"Socket type not supported", \
"Not supported", \
"Protocol family not supported", \
"Address family not supported by protocol", \
"Address in use", \
"Address not available", \
"Network is down", \
"Network unreachable", \
"Connection reset by network", \
"Connection aborted", \
"Connection reset by peer", \
"No buffer space available", \
"Socket is connected", \
"Socket not connected", \
"Cannot send after socket shutdown", \
"Too many references: cannot splice", \
"Connection timed out", \
"Connection refused", \
"Host is down", \
"No route to host", \
"Operation already in progress", \
"Operation now in progress", \
"Stale file handle", \
"Structure needs cleaning", \
"Not a XENIX named type file", \
"No XENIX semaphores available", \
"Is a named type file", \
"Remote I/O error", \
"Disk quota exceeded", \
"No medium found", \
"Wrong medium type", \
"Operation canceled", \
"Required key not available", \
"Key has expired", \
"Key has been revoked", \
"Key was rejected by service", \
"Owner died", \
"State not recoverable", \
"Operation not possible due to RF-kill", \
"Memory page has hardware error"}
#endif  // (__unix__)

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

char *dec_to_str(long long a, int is_neg, struct PutSettings settings);
char *hex_to_str(long long int a, struct PutSettings settings);
char *oct_to_str(long long a, struct PutSettings settings);
char *s21_itoa(long long int a, struct PutSettings settings);
void reverse_str(char* src);
int value_width_precis_from_format(char* str);
void clean_struct(struct PutSettings *settings);
const char *check_flags(const char *format, struct PutSettings *settings, va_list args, int set_def);
char *just_flags(char* str, struct PutSettings settings);
char *float_to_str(long double f_num, struct PutSettings settings);
char *get_g_as_string(long double f_num, struct PutSettings settings);
char *specify_for_int(char *num_str, struct PutSettings settings);
char *specify_str(char *str, struct PutSettings settings);
char *exponent_to_str(int exp);
char *exp_to_str(long double f_num, struct PutSettings settings);
char *arg_to_str(const char *format, struct PutSettings *settings, va_list args);
int s21_sprintf(char *str, const char *format, ...);

int s21_sscanf(const char *str, const char *format, ...);
long int s21_strtol(const char **str, Stack **stackPointer, int radix);
long double s21_strtold(const char **str, Stack **stackPointer);
int getArg(const char **str, va_list *argp, int type, int mod, Stack **stackPointer, char *strMem);

int getCharacter(const char **str, va_list *argp, Stack **stackPointer);
int getString(const char **str, va_list *argp, Stack **stackPointer);
int getInteger(const char **str, va_list *argp, Stack **stackPointer, int mod, int radix);
int getDouble(const char **str, va_list *argp, Stack **stackPointer, int mod);
int getPointer(const char **str, va_list *argp, Stack **stackPointer);
int getNothing(const char **str, va_list *argp, Stack **stackPointer, const char *strMem);
int getPercent(const char **str, Stack **stackPointer);

int getWidth(Stack **stackPointer);
char *getFirstDigit(const char *str);
int getAsterisk(Stack **stackPointer);

int s21_atoi(char **str);
int specifierReader(char **pfl, int *mod);
int formatLineReader(char **pfl);
#endif  // SRC_S21_STRING_H_
