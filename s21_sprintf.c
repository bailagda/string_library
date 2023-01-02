#include "s21_string.h"

/* SPRINTF */

char *dec_to_str(long long int a, int is_neg, struct PutSettings settings) {
    long long int tmp = a;
    short num_len = 0;
    while (tmp) {
        tmp /= 10;
        num_len++;
    }

    num_len = (settings.must_signed || is_neg || settings.must_spaced) + num_len + !a;
    char *ret_str = malloc((num_len + 1) * sizeof(char));

    int i = 0;
    if (!a) {
        *ret_str = '0';
        *(ret_str + 1) = '\0';
        i++;
    }
    while (a) {
        *(ret_str + i) = (48 + a % 10);
        a = a / 10;
        i++;
    }
    if (is_neg) {
        ret_str[i] = '-';
        i++;
    } else if (settings.must_signed) {
        ret_str[i] = '+';
        i++;
    } else if (settings.must_spaced) {
        ret_str[i] = ' ';
        i++;
    }
    ret_str[i] = '\0';
    reverse_str(ret_str);

    return ret_str;
}

char *hex_to_str(long long int a, struct PutSettings settings) {
    int str_size = 1;
    long long a_cpy = a;
    char *ret_str = malloc(str_size * sizeof(char));
    char *tmp = s21_NULL;
    *ret_str = '\0';

    while (a && settings.dot_specifier) {
        str_size++;
        tmp = realloc(ret_str, str_size * sizeof(char));
        if (tmp != s21_NULL) {
            ret_str = tmp;
        }
        int rem = a % 16;
        a /= 16;
        if (rem < 10) {
            *(ret_str + str_size - 2) = (48 + rem);
        } else {
            *(ret_str + str_size - 2) = (97 + (rem - 10) - 32 * settings.big_x);
        }
        *(ret_str + str_size - 1) = '\0';
    }

    if (str_size == 1 && settings.dot_specifier) {
        str_size++;
        tmp = realloc(ret_str, str_size * sizeof(char));
        if (tmp != s21_NULL) {
            ret_str = tmp;
        }
        *(ret_str + str_size - 2) = '0';
        *(ret_str + str_size - 1) = '\0';
    } else {
        while (str_size <= settings.dot_specifier) {
            str_size++;
            tmp = realloc(ret_str, str_size * sizeof(char));
            if (tmp != s21_NULL) {
                ret_str = tmp;
            }
            s21_strcat(ret_str, "0");
        }
        if (settings.zero_specified) {
            int counter = settings.justify_num - 2 * settings.hash;
            while (str_size <= counter) {
                str_size++;
                tmp = realloc(ret_str, str_size * sizeof(char));
                if (tmp != s21_NULL) {
                    ret_str = tmp;
                }
                s21_strcat(ret_str, "0");
            }
        }
    }

    if (settings.hash && str_size != 1 && (a_cpy || settings.pointer)) {
        str_size += 2;
        tmp = realloc(ret_str, str_size * sizeof(char));
        if (tmp != s21_NULL) {
            ret_str = tmp;
        }
        *(ret_str + str_size - 3) = 120 - settings.big_x * 32;
        *(ret_str + str_size - 2) = '0';
        *(ret_str + str_size - 1) = '\0';
    }

    reverse_str(ret_str);

    return ret_str;
}

char *oct_to_str(long long a, struct PutSettings settings) {
    int str_size = 1;
    long long a_cpy = a;
    char *ret_str = malloc(str_size * sizeof(char));
    char *tmp;
    *ret_str = '\0';

    while (a && settings.dot_specifier) {
        str_size++;
        tmp = realloc(ret_str, str_size * sizeof(char));
        if (tmp != s21_NULL) {
            ret_str = tmp;
        }
        int rem = a % 8;
        a /= 8;
        *(ret_str + str_size - 2) = (48 + rem);
        *(ret_str + str_size - 1) = '\0';
    }

    if (str_size == 1 && settings.dot_specifier) {
        str_size++;
        tmp = realloc(ret_str, str_size * sizeof(char));
        if (tmp != s21_NULL) {
            ret_str = tmp;
        }
        *(ret_str + str_size - 2) = '0';
        *(ret_str + str_size - 1) = '\0';
    }

    if (settings.hash && a_cpy && settings.dot_specifier) {
        str_size++;
        ret_str = realloc(ret_str, str_size * sizeof(char));
        *(ret_str + str_size - 2) = '0';
        *(ret_str + str_size - 1) = '\0';
    }

    reverse_str(ret_str);
    ret_str = specify_for_int(ret_str, settings);

    return ret_str;
}

char *s21_itoa(long long a, struct PutSettings settings) {
    char *ret_str = NULL;
    short is_neg = 0;
    if (a < 0) {
        is_neg = 1;
        a = a * (-1);
    }

    if (settings.base == 10) {
        ret_str = dec_to_str(a, is_neg, settings);
    } else if (settings.base == 16) {
        ret_str = hex_to_str(a, settings);
    } else if (settings.base == 8) {
        ret_str = oct_to_str(a, settings);
    }

    return ret_str;
}

void reverse_str(char* src) {
    for (int i = 0; i < (int)(s21_strlen(src) / 2); i++) {
        char tmp = src[s21_strlen(src) - 1 - i];
        src[s21_strlen(src) - 1 - i] = src[i];
        src[i] = tmp;
    }
    src[s21_strlen(src)] = '\0';
}

int value_width_precis_from_format(char* str) {
    char tmp[15];
    int i = 0;
    while (*str >= 48 && *str <= 57) {
        *(tmp + i) = *str;
        i++;
        str++;
    }
    if (i == 0) {
        *tmp = '0';
        i++;
    }
    *(tmp + i) = '\0';
    return atoi(tmp);
}

void clean_struct(struct PutSettings *settings) {
    settings->r_justify = 1;
    settings->justify_num = 0;
    settings->must_signed = 0;
    settings->must_spaced = 0;
    settings->dot_specifier = -1;
    settings->mem_allocated = 1;
    settings->h_defined = 0;
    settings->l_defined = 0;
    settings->L_defined = 0;
    settings->base = 10;
    settings->big_x = 0;
    settings->hash = 0;
    settings->big_e = 0;
    settings->g_specified = 0;
    settings->dot_specified = 0;
    settings->zero_specified = 0;
    settings->is_num = 0;
    settings->pointer = 0;
}

const char *check_flags(const char *format, struct PutSettings *settings, va_list args, int set_def) {
    if (set_def) {
        clean_struct(settings);
    }

    switch (*format) {
        case '-':
            settings->r_justify = 0;
            format++;
            if (*format == '*' || *format == '+' || *format == '#' || *format == ' ') {
                format = check_flags(format, settings, args, 0);
            }
            break;
        case '+':
            settings->must_signed = 1;
            format++;
            if (*format == '-' || *format == '*' || *format == '#' || *format == '0') {
                format = check_flags(format, settings, args, 0);
            }
            break;
        case ' ':
            settings->must_spaced = 1;
            format++;
            if (*format == '-' || *format == '*' || *format == '#' || *format == '0') {
                format = check_flags(format, settings, args, 0);
            }
            break;
        case '*':
            settings->justify_num = va_arg(args, int);
            if (settings->justify_num < 0) {
                settings->r_justify = 0;
                settings->justify_num = settings->justify_num * (-1);
            }
            format++;
            break;
        case '0':
            settings->zero_specified = 1;
            format++;
            if (*format == '#') {
                format = check_flags(format, settings, args, 0);
            }
            break;
        case '#':
            settings->hash = 1;
            format++;
            if (*format == '+' || *format == '0' || *format == '-' || *format == '*') {
                format = check_flags(format, settings, args, 0);
            }
            break;
    }

    if (*format >= 48 && *format <= 57 && !settings->justify_num && settings->dot_specifier == -1) {
        settings->justify_num = value_width_precis_from_format((char *)format);
        while (*format >= 48 && *format <= 57) {
            format++;
        }
    }

    if (*format == '.' && !settings->dot_specified) {
        settings->dot_specified = 1;
        format++;
    }

    if (settings->dot_specified && settings->dot_specifier == -1) {
        if (*format == '*') {
            settings->dot_specifier = va_arg(args, int);
            format++;
        } else {
            settings->dot_specifier = value_width_precis_from_format((char *)format);
        }
    }

    while (*format >= 48 && *format <= 57) {
        format++;
    }

    switch (*format) {
        case 'l':
            settings->l_defined = 1;
            format++;
            if (*format == 'l') {
                settings->l_defined = 2;
                format++;
            }
            break;
        case 'h':
            settings->h_defined = 1;
            format++;
            break;
        case 'L':
            settings->L_defined = 1;
            format++;
            break;
    }

    return format;
}

char *just_flags(char* str, struct PutSettings settings) {
    char *ret_str = NULL;
    if (settings.justify_num > (int)s21_strlen(str)) {
        ret_str = malloc((settings.justify_num + 1) * sizeof(char));
        if (!settings.r_justify) {
            *(ret_str) = '\0';
            s21_strcat(ret_str, str);
            for (int i = 0; i < settings.justify_num - (int)s21_strlen(str); i++) {
                *(ret_str + s21_strlen(str) + i) = ' ';
            }
            ret_str[settings.justify_num] = '\0';
        } else {
            int sign = 0;
            if (settings.is_num && (*str == '+' || *str == '-' || *str == ' ') && settings.zero_specified) {
                *ret_str = *str;
                sign = 1;
            }
            for (int i = sign; i < settings.justify_num - (int)s21_strlen(str) + sign; i++) {
                if (settings.zero_specified) {
                    *(ret_str + i) = '0';
                } else {
                    *(ret_str + i) = ' ';
                }
            }
            *(ret_str + settings.justify_num - s21_strlen(str) + sign) = '\0';
            s21_strcat(ret_str, str + sign);
        }
        free(str);
    } else {
        ret_str = str;
    }

    return ret_str;
}

char *float_to_str(long double f_num, struct PutSettings settings) {
    if (!settings.dot_specified) {
        settings.dot_specifier = 6;
    }

    if (settings.g_specified) {
        settings.dot_specifier--;
    }

    char *ret_str = NULL;

    long long int_part = (long long)f_num;

    long long mul = 1;
    int p = settings.dot_specifier;
    while (p > 0) {
        mul *= 10;
        p--;
    }
    long long float_part = (long long)roundl((f_num - int_part) * mul);

    if (settings.dot_specifier == 0) {
        int_part = (long long)roundl(f_num);
    }

    if (float_part < 0) {
        float_part = float_part * (-1);
    }

    struct PutSettings tmp_settings;
    clean_struct(&tmp_settings);
    char *int_str = s21_itoa(int_part, settings);
    char *float_str = s21_itoa(float_part, tmp_settings);
    float_str = specify_for_int(float_str, settings);

    ret_str = malloc((s21_strlen(int_str) + s21_strlen(float_str) + 2) * sizeof(char));
    *ret_str = '\0';
    s21_strcat(ret_str, int_str);

    if (settings.dot_specifier || settings.hash) {
        s21_strcat(ret_str, ".");
        if (settings.dot_specifier) {
            s21_strcat(ret_str, float_str);
        }
    }

    free(int_str);
    free(float_str);

    return ret_str;
}

char *get_g_as_string(long double f_num, struct PutSettings settings) {
    if (settings.dot_specifier == 0) {
        settings.dot_specifier = 1;
    }

    char *ret_str = NULL;
    int dot_fixed = 0;
    long long int_part = (long long)f_num;
    if (settings.dot_specifier == 0) {
        int_part = (long long)roundl(f_num);
    }
    char *int_str = s21_itoa(int_part, settings);
    int int_len = s21_strlen(int_str) - (*int_str == '+' || *int_str == '-' || *int_str == ' ');

    if (settings.dot_specified && settings.dot_specifier > int_len) {
        settings.dot_specifier -= int_len;
        dot_fixed = 1;
    }

    long long mul = 1;
    int p = settings.dot_specifier;
    while (p > 0) {
        mul *= 10;
        p--;
    }
    long long float_part = (long long)roundl((f_num - int_part) * mul);

    if (float_part < 0) {
        float_part = float_part * (-1);
    }

    struct PutSettings tmp_settings;
    clean_struct(&tmp_settings);
    char *float_str = s21_itoa(float_part, tmp_settings);
    float_str = specify_for_int(float_str, settings);
    settings.dot_specifier += (!int_part);

    ret_str = malloc((s21_strlen(int_str) + s21_strlen(float_str) + 10) * sizeof(char));
    *ret_str = '\0';
    int float_len = s21_strlen(float_str);
    if (settings.dot_specifier < int_len && !dot_fixed) {
        long double tmp_num = int_part / pow(10, int_len - settings.dot_specified);
        long double tmp_l = tmp_num;
        free(ret_str);
        ret_str = exp_to_str(tmp_l, settings);
        int exp = 0;
        exp = ret_str[s21_strlen(ret_str) - 1] - 48 + 10 * (ret_str[s21_strlen(ret_str) - 2] - 48);
        exp += (int_len - settings.dot_specified);
        ret_str[s21_strlen(ret_str) - 1] = (exp % 10) + 48;
        ret_str[s21_strlen(ret_str) - 2] = (int)(exp / 10) + 48;
    } else if (((settings.dot_specifier < int_len + float_len && !dot_fixed) ||
    (settings.dot_specifier < float_len && dot_fixed))) {
        s21_strcat(ret_str, int_str);
        char *tmp_fl = calloc(float_len, sizeof(char));
        s21_strncat(tmp_fl, float_str, settings.dot_specifier - int_len);
        free(float_str);
        float_str = tmp_fl;
        if (settings.dot_specifier > int_len || settings.hash) {
            s21_strcat(ret_str, ".");
            if (settings.dot_specifier) {
                s21_strcat(ret_str, float_str);
            }
        }
        int len = s21_strlen(ret_str);
        while (len > 0) {
            if (ret_str[len - 1] == '0') {
                ret_str[len - 1] = '\0';
                len--;
            } else {
                break;
            }
        }
    } else {
        s21_strcat(ret_str, int_str);
        if (settings.dot_specifier || settings.hash) {
            s21_strcat(ret_str, ".");
            if (settings.dot_specifier) {
                s21_strcat(ret_str, float_str);
            }
        }
    }

    if (!settings.hash && s21_strchr(ret_str, '.')) {
        int len = s21_strlen(ret_str);
        while (len > 0) {
            if (ret_str[len - 1] == '0') {
                ret_str[len - 1] = '\0';
                len--;
            } else {
                break;
            }
        }
    }

    free(int_str);
    free(float_str);

    return ret_str;
}

char *specify_for_int(char *num_str, struct PutSettings settings) {
    char *ret_str = num_str;
    int sign = 0;

    if (*num_str == '+' || *num_str == '-' || *num_str == ' ') {
        sign = 1;
    }

    if (settings.dot_specifier > (int)s21_strlen(ret_str) - sign) {
        ret_str = malloc((settings.dot_specifier + sign + 1) * sizeof(char));
        if (sign) {
            *ret_str = *num_str;
        }
        for (int i = 0; i < settings.dot_specifier; i++) {
            *(ret_str + i + sign) = '0';
        }
        ret_str[settings.dot_specifier - (s21_strlen(num_str) - sign) + sign] = '\0';
        s21_strcat(ret_str, num_str + sign);
        free(num_str);
    }

    return ret_str;
}

char *specify_str(char *str, struct PutSettings settings) {
    int n = s21_strlen(str);
    if (settings.dot_specified && settings.dot_specifier < n) {
        n = settings.dot_specifier > 0 ? settings.dot_specifier : 0;
    }

    char *ret_str = malloc((n + 1) * sizeof(char));
    *ret_str = '\0';
    s21_strncat(ret_str, str, n);

    if (settings.l_defined) {
        free(str);
    }

    return ret_str;
}

char *exponent_to_str(int exp) {
    char *ret_str = s21_NULL;
    struct PutSettings tmp_settings;
    clean_struct(&tmp_settings);
    tmp_settings.must_signed = 1;
    tmp_settings.dot_specifier = 2;
    ret_str = s21_itoa(exp, tmp_settings);
    ret_str = specify_for_int(ret_str, tmp_settings);

    return ret_str;
}

char *exp_to_str(long double f_num, struct PutSettings settings) {
    char *ret_str;
    int exp = 0;

    while ((f_num >= 10 || f_num <= -10) && exp <= 100) {
        f_num /= 10;
        exp++;
    }
    while ((f_num > -1 && f_num < 1) && exp >= -100) {
        f_num *= 10;
        exp--;
    }

    if (exp == -101) {
        exp = 0;
    }

    char *mantissa = s21_NULL;
    if (settings.g_specified) {
        mantissa = get_g_as_string(f_num, settings);
    } else {
        mantissa = float_to_str(f_num, settings);
    }

    if (settings.g_specified && !settings.hash) {
        while (mantissa[s21_strlen(mantissa) - 1] == '0') {
            mantissa[s21_strlen(mantissa) - 1] = '\0';
        }
    }
    char *exponent = exponent_to_str(exp);

    ret_str = malloc((s21_strlen(mantissa) + s21_strlen(exponent) + 5) * sizeof(char));
    *ret_str = '\0';
    s21_strcat(ret_str, mantissa);
    if (s21_strlen(exponent) > 2) {
        if (settings.big_e) {
            s21_strcat(ret_str, "E");
        } else {
            s21_strcat(ret_str, "e");
        }
        s21_strcat(ret_str, exponent);
    }
    free(mantissa);
    free(exponent);

    return ret_str;
}

char *arg_to_str(const char *format, struct PutSettings *settings, va_list args) {
    char *ret_str = s21_NULL;
    wchar_t *wret_str = s21_NULL;
    long long num;
    long double f_num;
    int *char_num;

    switch (*format) {
        case 'c':
            ret_str = malloc(2 * sizeof(char));
            if (settings->l_defined) {
                wret_str = malloc(sizeof(wchar_t));
                *wret_str = va_arg(args, wchar_t);
                wcstombs(ret_str, wret_str, 1);
                free(wret_str);
            } else {
                *ret_str = va_arg(args, int);
            }
            *(ret_str + 1) = '\0';
            ret_str = just_flags(ret_str, *settings);
            break;

        case 's':
            if (settings->l_defined) {
                wret_str = va_arg(args, wchar_t*);
                int l = wcslen(wret_str);
                ret_str = malloc((l + 1) * sizeof(char));
                if (wcstombs(ret_str, wret_str, l)) {
                    ret_str[l] = '\0';
                }
            } else {
                ret_str = va_arg(args, char*);
            }
            ret_str = specify_str(ret_str, *settings);
            ret_str = just_flags(ret_str, *settings);
            break;

        case 'u':
            if (settings->h_defined) {
                num = va_arg(args, int);
                num = (unsigned short int)num;
            } else if (settings->l_defined) {
                num = va_arg(args, unsigned long);
            } else {
                num = va_arg(args, unsigned int);
            }
            ret_str = s21_itoa(num, *settings);
            ret_str = specify_for_int(ret_str, *settings);
            ret_str = just_flags(ret_str, *settings);
            break;

        case 'i':
        case 'd':
            settings->is_num = 1;
            if (settings->h_defined) {
                num = va_arg(args, int);
                num = (long)(short)num;
            } else if (settings->l_defined == 1) {
                num = va_arg(args, long long);
            } else if (settings->l_defined == 2) {
                num = va_arg(args, long long);
            } else {
                num = va_arg(args, int);
            }
            ret_str = s21_itoa(num, *settings);
            ret_str = specify_for_int(ret_str, *settings);
            ret_str = just_flags(ret_str, *settings);
            break;

        case 'f':
            settings->is_num = 1;
            if (settings->L_defined) {
                f_num = va_arg(args, long double);
            } else {
                f_num = va_arg(args, double);
            }
            ret_str = float_to_str(f_num, *settings);
            ret_str = just_flags(ret_str, *settings);
            break;
        case 'E':
        case 'e':
            if (*format == 'E') {
                settings->big_e = 1;
            }
            if (settings->L_defined) {
                f_num = va_arg(args, long double);
            } else {
                f_num = va_arg(args, double);
            }
            ret_str = exp_to_str(f_num, *settings);
            ret_str = just_flags(ret_str, *settings);
            break;
        case 'X':
        case 'x':
            if (*format == 'X') {
                settings->big_x = 1;
            }
            settings->base = 16;
            num = va_arg(args, long);
            ret_str = s21_itoa(num, *settings);
            ret_str = just_flags(ret_str, *settings);
            break;

        case 'o':
            settings->base = 8;
            if (settings->h_defined) {
                num = va_arg(args, unsigned int);
                num = (long)(short)num;
            } else if (settings->l_defined == 1) {
                num = va_arg(args, unsigned long);
            } else if (settings->l_defined == 2) {
                num = va_arg(args, unsigned long long);
            } else {
                num = va_arg(args, unsigned int);
            }
            ret_str = s21_itoa(num, *settings);
            ret_str = just_flags(ret_str, *settings);
            break;
        case 'n':
            char_num = va_arg(args, int*);
            *char_num = settings->char_counter;
            ret_str = malloc(sizeof(char));
            *ret_str = '\0';
            break;
        case '%':
            ret_str = malloc(2 * sizeof(char));
            *ret_str = '%';
            *(ret_str + 1) = '\0';
            break;
        case 'p':
            settings->pointer = 1;
            num = va_arg(args, long);
            settings->base = 16;
            settings->hash = 1;
            ret_str = s21_itoa(num, *settings);
            ret_str = just_flags(ret_str, *settings);
            break;

        case 'G':
        case 'g':
            settings->g_specified = 1;
            if (!settings->dot_specified) {
                settings->dot_specified = 1;
                settings->dot_specifier = 6;
            }
            settings->is_num = 1;
            if (settings->L_defined) {
                f_num = va_arg(args, long double);
            } else {
                f_num = va_arg(args, double);
            }
            if (*format == 'G') {
                settings->big_e = 1;
            }

            if (f_num > 1 || f_num < -1) {
                long double tmp = f_num;
                int exp = 0;
                while (tmp > 10 && tmp < -10) {
                    tmp /= 10;
                    exp++;
                }
                if (exp >= 6) {
                    ret_str = exp_to_str(f_num, *settings);
                } else {
                    ret_str = get_g_as_string(f_num, *settings);
                }
            } else {
                long double tmp = f_num;
                int exp = 0;
                while ((int)tmp < 10 && (int)tmp > -10 && exp > -100) {
                    tmp *= 10;
                    exp--;
                }
                if (exp <= -4 && exp > -100) {
                    ret_str = exp_to_str(f_num, *settings);
                } else {
                    ret_str = get_g_as_string(f_num, *settings);
                }
            }
            ret_str = just_flags(ret_str, *settings);
            break;
    }
    return ret_str;
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    struct PutSettings settings;
    settings.char_counter = 0;
    char *src = s21_NULL;
    char *start_str = str;

    for (; *format; format++) {
        if (*format == '%') {
            format++;

            format = check_flags(format, &settings, args, 1);
            src = arg_to_str(format, &settings, args);
            *str = '\0';
            s21_strcat(str, src);
            str += s21_strlen(src);
            settings.char_counter += s21_strlen(src);
            if (src != s21_NULL) {
                free(src);
                src = s21_NULL;
            }
        } else {
            *str = *format;
            str++;
            settings.char_counter++;
        }
    }
    *str = '\0';
    va_end(args);

    return s21_strlen(start_str);
}

/* END_SPRINTF */
