#include <check.h>
#include "s21_string.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

char test1[20] = "Hell0 world\0";
char test2[20] = "Hell0 world\n\0";
char test3[10] = "a\n\0";
char test4[10] = " \n\0";
char test5[10] = " \0";
char test6[10] = "\n\0";
char test7[10] = "\0";

START_TEST(test_s21_memchr) {
    ck_assert_str_eq(s21_memchr("Germany", 'r', 4), memchr("Germany", 'r', 4));
    ck_assert_ptr_eq(s21_memchr("Germany", 'r', 2), s21_NULL);
    ck_assert_ptr_eq(s21_memchr(s21_NULL, 'a', 3), s21_NULL);
    ck_assert_ptr_eq(s21_memchr("Germany", 'G', 0), s21_NULL);

    char *s1 = "This is a s21_memchr test";

    ck_assert_ptr_eq(s21_memchr(s1, 's', 0), memchr(s1, 's', 0));
    ck_assert_ptr_eq(s21_memchr(s1, 's', 2), memchr(s1, 's', 2));
    ck_assert_ptr_eq(s21_memchr(s1, 's', 50), memchr(s1, 's', 50));
    ck_assert_ptr_eq(s21_memchr(s1, 'u', 50), memchr(s1, 'u', 50));
    ck_assert_ptr_eq(s21_memchr(s1, 'u', 32), memchr(s1, 'u', 32));
}
END_TEST

START_TEST(test_s21_memcmp) {
    // ck_assert_int_eq(s21_memcmp("Germany", "ABS", 3), memcmp("Germany", "ABS", 3));
    // ck_assert_int_eq(s21_memcmp("Germany", "Ger", 3), memcmp("Germany", "Ger", 3));
    // ck_assert_int_eq(s21_memcmp("Germany", "aer", 3), memcmp("Germany", "aer", 3));

    char *s1 = "This is a 1st string s21_memcmp test";
    char *s2 = "This is a 2nd string s21_memcmp test";

    ck_assert_msg(s21_memcmp(s1, s2, 256) == memcmp(s1, s2, 256), "1st memcmp test failed.");
    ck_assert_msg(s21_memcmp(s1, s2, 2) == memcmp(s1, s2, 2), "2nd memcmp test failed.");
    ck_assert_msg(s21_memcmp(s1, s2, 123) == memcmp(s1, s2, 123), "3rd memcmp test failed.");
    ck_assert_msg(s21_memcmp(s1, s2, 0) == memcmp(s1, s2, 0), "4rth memcmp test failed.");
    ck_assert_msg(s21_memcmp(s1, s2, 36) == memcmp(s1, s2, 36), "5rth memcmp test failed.");
}
END_TEST

START_TEST(test_s21_memcpy) {
    char s[] = "asdasdfsdfasdfasdfasd";
    ck_assert_str_eq(s21_memcpy(s, "Germany", 5), "Germadfsdfasdfasdfasd");
    ck_assert_ptr_eq(s21_memcpy(s, s21_NULL, 3), s21_NULL);

    char *src1 = "schesrdsfdsfdsfesr";
    int len = s21_strlen(src1);
    char dest1[100] = {0};
    char dest2[100] = {0};
    char dest3[100] = {0};
    char dest4[100] = {0};
    char dest5[100] = {0};
    char dest6[100] = {0};
    char dest7[100] = {0};
    char dest8[100] = {0};
    char dest9[100] = {0};
    char dest10[100] = {0};

    s21_memcpy(dest1, src1, len + 1);
    memcpy(dest2, src1, len + 1);

    s21_memcpy(dest3, src1, 5);
    memcpy(dest4, src1, 5);

    s21_memcpy(dest5, src1, 0);
    memcpy(dest6, src1, 0);

    s21_memcpy(dest7, src1, 18);
    memcpy(dest8, src1, 18);

    s21_memcpy(dest9, src1, 1);
    memcpy(dest10, src1, 1);

    ck_assert_str_eq(dest1, dest2);
    ck_assert_str_eq(dest3, dest4);
    ck_assert_str_eq(dest5, dest6);
    ck_assert_str_eq(dest7, dest8);
    ck_assert_str_eq(dest9, dest10);
}
END_TEST

START_TEST(test_s21_memmove) {
    unsigned char dest[30] = "";
    unsigned char dest_2[30] = "";
    ck_assert_str_eq(s21_memmove(dest, "GeeksforGeeks,Quiz", 5), memmove(dest_2, "GeeksforGeeks,Quiz", 5));

    char *src1 = "schesrdsfdsfdsfesr";
    int len = s21_strlen(src1);
    char dest1[100];
    char dest2[100];
    char dest3[100];
    char dest4[100];
    char dest5[100];
    char dest6[100];
    char dest7[100];
    char dest8[100];
    char dest9[100];
    char dest10[100];

    s21_memmove(dest1, src1, len + 1);
    memmove(dest2, src1, len + 1);

    s21_memmove(dest3, src1, 5);
    memmove(dest4, src1, 5);

    s21_memmove(dest5, src1, 0);
    memmove(dest6, src1, 0);

    s21_memmove(dest7, src1, 18);
    memmove(dest8, src1, 18);

    s21_memmove(dest9, src1, 1);
    memmove(dest10, src1, 1);

    ck_assert_msg(memcmp(dest1, dest2, len) == 0, "1st memmove test failed.");
    ck_assert_msg(memcmp(dest3, dest4, 5) == 0, "2nd memmove test failed.");
    ck_assert_msg(memcmp(dest5, dest6, 0) == 0, "3rd memmove test failed.");
    ck_assert_msg(memcmp(dest7, dest8, 18) == 0, "4rth memmove test failed.");
    ck_assert_msg(memcmp(dest9, dest10, 1) == 0, "5rth memmove test failed.");
}
END_TEST

START_TEST(test_s21_memset) {
    char s21_rez[] = "This is some text";
    char lib_rez[] = "This is some text";
    ck_assert_str_eq(s21_memset(s21_rez, '$', 6), memset(lib_rez, '$', 6));

    char buf1[10] = "";
    char buf2[10] = "";
    ck_assert_str_eq(s21_memset(buf1, 'n', 2), memset(buf2, 'n', 2));
    ck_assert_ptr_eq(s21_memset(s21_NULL, 'A', 150), s21_NULL);

    char str1[] = "School is cool";
    char str2[] = "School-21";
    char str3[] = "amogus";
    char str4[] = "This is a string!";
    char str5[] = "Shrek";
    char res1[] = "School is cool";
    char res2[] = "School-21";
    char res3[] = "amogus";
    char res4[] = "This is a string!";
    char res5[] = "Shrek";

    s21_memset(str1, '_', 5);
    s21_memset(str2, '_', 4);
    s21_memset(str3, 'M', 2);
    s21_memset(str4, '-', 1);
    s21_memset(str5, 'S', 1);

    memset(res1, '_', 5);
    memset(res2, '_', 4);
    memset(res3, 'M', 2);
    memset(res4, '-', 1);
    memset(res5, 'S', 1);

    ck_assert_msg(memcmp(str1, res1, sizeof(str1)) == 0, "1st memset test failed");
    ck_assert_msg(memcmp(str2, res2, sizeof(str2)) == 0, "2nd memset test failed");
    ck_assert_msg(memcmp(str3, res3, sizeof(str3)) == 0, "3rd memset test failed");
    ck_assert_msg(memcmp(str4, res4, sizeof(str4)) == 0, "4rth memset test failed");
    ck_assert_msg(memcmp(str5, res5, sizeof(str5)) == 0, "5rth memset test failed");
}
END_TEST

START_TEST(test_s21_strcat) {
    char dest1[25] = "This is ";
    char dest2[25] = "This is ";
    ck_assert_str_eq(s21_strcat(dest1, "some text"), strcat(dest2, "some text"));

    char str1[21] = "TEST";
    char str2[8] = "strcat";
    char str3[9] = "function";
    char str4[1] = "";
    char str5[2] = " ";

    s21_strcat(str1, str5);
    ck_assert_msg(!memcmp(str1, "TEST ", 6), "1st strcat test failed");

    s21_strcat(str1, str2);
    ck_assert_msg(!memcmp(str1, "TEST strcat", 12), "2nd strcat test failed");

    s21_strcat(str1, str5);
    ck_assert_msg(!memcmp(str1, "TEST strcat ", 13), "3rd strcat test failed");

    s21_strcat(str1, str3);
    ck_assert_msg(!memcmp(str1, "TEST strcat function", 21), "4rth strcat test failed");

    s21_strcat(str1, str4);
    ck_assert_msg(!memcmp(str1, "TEST strcat function", 21), "5th strcat test failed");
}
END_TEST

START_TEST(test_s21_strncat) {
    char dest1[25] = "This is ";
    char dest2[25] = "This is ";
    char source1[25] = "some text for testing";
    char source2[25] = "some text for testing";
    ck_assert_str_eq(s21_strncat(dest1, source1, 9), strncat(dest2, source2, 9));

    char str1[25] = "TEST";
    char str2[8] = "strncat";
    char str3[35] = "function";
    char str4[1] = "";
    char str5[30] = "amogus";

    s21_strncat(str1, str2,  3);
    ck_assert_msg(!memcmp(str1, "TESTstr", 8), "1st strncat test failed");

    s21_strncat(str1, str4,  3);
    ck_assert_msg(!memcmp(str1, "TESTstr", 8), "2nd strncat test failed");

    s21_strncat(str2, str4,  1);
    ck_assert_msg(!memcmp(str2, "strncat", 8), "3rd strncat test failed");

    s21_strncat(str5, str3,  3);
    ck_assert_msg(!memcmp(str5, "amogusfun", 10), "4rth strncat test failed");

    char str_1[25] = "TEST";
    char str_5[30] = "amogus";
    s21_strncat(str_5, str_1,  1);
    ck_assert_str_eq(str_5, "amogusT");
}
END_TEST

START_TEST(test_s21_strchr) {
    ck_assert_str_eq(
        s21_strchr("This is some text for testing", '\0'), strchr("This is some text for testing", '\0'));
    ck_assert_str_eq(
        s21_strchr("This is some text for testing", 's'), strchr("This is some text for testing", 's'));

    char *str1 = "TEST";
    char *str2 = "strchr";
    char *str3 = "function";
    char *str4 = "";
    char *str5 = "amogus";
    ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
    ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
    ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
    ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
    ck_assert_ptr_eq(s21_strchr(str2, 'E'), strchr(str2, 'E'));
    ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
    ck_assert_ptr_eq(s21_strchr(str4, ' '), strchr(str4, ' '));
    ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
}
END_TEST

START_TEST(test_s21_strcmp) {
    ck_assert_int_eq(s21_strcmp("abc", "abc"), strcmp("abc", "abc"));
    ck_assert_int_eq(s21_strcmp("abc", "bc"), strcmp("abc", "bc"));
    ck_assert_int_eq(s21_strcmp("", "ab"), -'a');
    ck_assert_int_eq(s21_strcmp("\0", "abc"), -'a');
    ck_assert_int_eq(s21_strcmp("bbn", "abb"), strcmp("bbn", "abb"));
    ck_assert_int_eq(s21_strcmp("", ""), strcmp("", ""));

    char t1[] = "Sample Text";
    char t2[] = "Sample Text Plus Some Text";
    ck_assert_msg(s21_strcmp(t1, t2) == -32, "1st strcmp test failed");

    char t3[] = "AAA";
    char t4[] = "B";
    ck_assert_msg(s21_strcmp(t3, t4) == -1, "2nd strcmp test failed");

    char t5[] = "A\0BCD";
    char t6[] = "A";
    ck_assert_msg(s21_strcmp(t5, t6) == 0, "3rd strcmp test failed");

    char t7[] = "amogus";
    char t8[] = "m";
    ck_assert_msg(s21_strcmp(t7, t8) == -12, "4rth strcmp test failed");

    char t9[] = "shrek";
    char t10[] = "as";
    ck_assert_msg(s21_strcmp(t9, t10) == 18, "5th strcmp test failed");
}
END_TEST

START_TEST(test_s21_strncmp) {
    ck_assert_int_eq(s21_strncmp("abc", "abc", 10000), strncmp("abc", "abc", 10000));
    ck_assert_int_eq(s21_strncmp("abc", "abz", 3), strncmp("abc", "abz", 3));
    ck_assert_int_eq(s21_strncmp("", "a", 1), strncmp("", "a", 1));

    char *t1 = "Sample Text";
    char *t2 = "Sample Text Plus Some Text";
    ck_assert_msg(!s21_strncmp(t1, t2, 10) && !strncmp(t1, t2, 10), "1st strncmp test failed");
    ck_assert_msg(s21_strncmp(t1, t2, 14) < 0 && strncmp(t1, t2, 14) < 0, "2nd strncmp test failed");
    char *t3 = "";
    char *t4 = "A";
    ck_assert_msg(s21_strncmp(t3, t4, 0) == 0 && strncmp(t3, t4, 0) == 0, "3rd strncmp test failed");
    ck_assert_msg(s21_strncmp(t3, t4, 1) < 0 && strncmp(t3, t4, 1) < 0, "3rd strncmp test failed");
    char *t5 = "ShrekAmogus";
    char *t6 = "Shr";
    ck_assert_msg(s21_strncmp(t5, t6, 5) > 0 && strncmp(t5, t6, 5) > 0, "4rth strncmp test failed");
    ck_assert_msg(s21_strncmp(t5, t6, 0) == 0 && strncmp(t5, t6, 0) == 0, "5th strncmp test failed");
}
END_TEST

START_TEST(test_s21_strcpy) {
    char src1[] = "C programming";
    char dest1[10]= "abc";
    ck_assert_str_eq(s21_strcpy(dest1, src1), strcpy(dest1, src1));

    char src2[] = "C programming";
    char dest2[]= "1234567890";
    ck_assert_str_eq(s21_strcpy(dest2, src2), strcpy(dest2, src2));

    char src3[] = "C programming";
    char dest3[15];
    ck_assert_str_eq(s21_strcpy(dest3, src3), strcpy(dest3, src3));

    char s1[50] = "Sample Text";
    char d1[50] = "";
    s21_strcpy(d1, s1);
    ck_assert_msg(!strcmp(d1, s1), "1st  strcpy test failed");

    char s2[50] = "AAAAA";
    char d2[50] = "NO";
    s21_strcpy(d2, s2);
    ck_assert_msg(!strcmp(d2, s2), "2nd strcpy test failed");

    char s3[50] = "";
    char d3[50] = "HELLO";
    s21_strcpy(d3, s3);
    ck_assert_msg(!strcmp(d3, s3), "3rd strcpy test failed");

    char s4[50] = "amogus";
    char d4[50] = "HELLO";
    s21_strcpy(d4, s4);
    ck_assert_msg(!strcmp(d4, s4), "4rth strcpy test failed");

    char s5[50] = "Shrek";
    char d5[50] = "what";
    s21_strcpy(d5, s5);
    ck_assert_msg(!strcmp(d5, s5), "5th strcpy test failed");
}
END_TEST

START_TEST(test_s21_strncpy) {
    char src1[] = "12345\0006789";
    char dst1[] = "1111111111";
    ck_assert_str_eq(s21_strncpy(dst1, src1, 7), strncpy(dst1, src1, 7));

    char src2[] = "12345\0006789";
    char dst2[] = "1111111111";
    ck_assert_str_eq(s21_strncpy(dst2, src2, 3), strncpy(dst2, src2, 3));

    char src3[10]="12345\0006789";
    char dst3[10]="1111111111";
    ck_assert_str_eq(s21_strncpy(dst3, src3, 0), strncpy(dst3, src3, 0));

    char a[20]="abcdefghijwertyuijhg";
    char b[20] = "";
    ck_assert_str_eq(s21_strncpy(b, a, 10), strncpy(b, a, 10));

    ck_assert_str_eq(s21_strncpy("", "abcd", 0), strncpy("", "abcd", 0));

    char s1[50] = "Sample Text";
    char d1[50] = "";
    s21_strncpy(d1, s1, 2);
    ck_assert_msg(!strcmp(d1, "Sa"), "1st strncpy test failed");

    char s2[50] = "AAAAA";
    char d2[50] = "NO";
    s21_strncpy(d2, s2, 0);
    ck_assert_msg(!strcmp(d2, "NO"), "2nd strncpy test failed");

    char s3[50] = "H";
    char d3[50] = "fELLO";
    s21_strncpy(d3, s3, 1);
    ck_assert_msg(!strcmp(d3, "HELLO"), "3rd strncpy test failed");

    char s4[50] = "amo";
    char d4[50] = "qwegus";
    s21_strncpy(d4, s4, 3);
    ck_assert_msg(!strcmp(d4, "amogus"), "4rth strncpy test failed");

    char s5[50] = "shrek";
    char d5[50] = "s";
    s21_strncpy(d5, s5, 5);
    ck_assert_msg(!strcmp(d5, "shrek"), "5th strncpy test failed");
}
END_TEST

START_TEST(test_s21_strcspn) {
    char test1[] = "aaaa";
    ck_assert_int_eq(s21_strcspn("sorry", test1), strcspn("sorry", test1));
    ck_assert_int_eq(s21_strcspn("make\0", test1), strcspn("make\0", test1));
    ck_assert_int_eq(s21_strcspn("\0", test1), strcspn("\0", test1));
    ck_assert_int_eq(s21_strcspn("123", test1), strcspn("123", test1));

    char *str1 = "0123456789";
    char *str2 = "9876";
    ck_assert_msg(s21_strcspn(str1, str2) == strcspn(str1, str2), "1st strcspn test failed");

    char *str3 = "0123456789";
    char *str4 = "";
    ck_assert_msg(s21_strcspn(str3, str4) == strcspn(str3, str4), "2nd strcspn test failed");

    char *str5 = "";
    char *str6 = "123";
    ck_assert_msg(s21_strcspn(str5, str6) == strcspn(str5, str6), "3rd strcspn test failed");

    char *str7 = "1337";
    char *str8 = "228";
    ck_assert_msg(s21_strcspn(str7, str8) == strcspn(str7, str8), "4rth strcspn test failed");

    char *str9 = "19642";
    char *str10 = "64";
    ck_assert_msg(s21_strcspn(str9, str10) == strcspn(str9, str10), "5th strcspn test failed");
}
END_TEST

START_TEST(test_s21_strerror) {
    FILE *f;
    f = fopen("qwerty.txt", "r");
    if (f == NULL) {
        ck_assert_str_eq(s21_strerror(errno), strerror(errno));
    }

    ck_assert_str_eq(s21_strerror(200), strerror(200));
    ck_assert_str_eq(s21_strerror(-15), strerror(-15));

    char *str1 = s21_strerror(20);
    char *str2 = strerror(20);
    ck_assert_str_eq(str1, str2);

    char *str3 = s21_strerror(12);
    char *str4 = strerror(12);
    ck_assert_str_eq(str3, str4);

    char *str5 = s21_strerror(1337);
    char *str6 = strerror(1337);
    ck_assert_str_eq(str5, str6);

    char *str7 = s21_strerror(1);
    char *str8 = strerror(1);
    ck_assert_str_eq(str7, str8);

    char *str9 = s21_strerror(25);
    char *str10 = strerror(25);
    ck_assert_str_eq(str9, str10);
}
END_TEST

START_TEST(test_s21_strlen) {
    ck_assert_int_eq(s21_strlen("abc"), strlen("abc"));
    ck_assert_int_eq(s21_strlen("abc\0"), strlen("abc\0"));
    ck_assert_int_eq(s21_strlen(""), strlen(""));
    ck_assert_int_eq(s21_strlen("\0"), strlen("\0"));

    char *s1 = "0123456789";
    ck_assert_msg(s21_strlen(s1) == strlen(s1), "1st strlen test failed");

    char *s2 = "";
    ck_assert_msg(s21_strlen(s2) == strlen(s2), "2nd strlen test failed");

    char *s3 = "amogus";
    ck_assert_msg(s21_strlen(s3) == strlen(s3), "3rd strlen test failed");

    char *s4 = "shrek";
    ck_assert_msg(s21_strlen(s4) == strlen(s4), "4rth strlen test failed");

    char *s5 = "is love";
    ck_assert_msg(s21_strlen(s5) == strlen(s5), "5th strlen test failed");
}
END_TEST

START_TEST(test_s21_strpbrk) {
    char test1[] = "aaaaa";
    ck_assert_str_eq(s21_strpbrk("Germany", test1), strpbrk("Germany", test1));
    ck_assert_str_eq(s21_strpbrk("Germany\0", test1), strpbrk("Germany\0", test1));

    char *str1 = "hello";
    char *str2 = "hel";
    char *res1, *res2;
    res1 = s21_strpbrk(str1, str2);
    res2 = strpbrk(str1, str2);
    ck_assert_str_eq(res1, res2);

    char *str4 = "ab";
    res1 = s21_strpbrk(str1, str4);
    res2 = strpbrk(str1, str4);
    ck_assert_ptr_eq(res1, res2);

    char *str5 = "o";
    res1 = s21_strpbrk(str1, str5);
    res2 = strpbrk(str1, str5);
    ck_assert_str_eq(res1, res2);

    char *str6 = "abcdefghjkl";
    char *str7 = "abcd";
    res1 = s21_strpbrk(str6, str7);
    res2 = strpbrk(str6, str7);
    ck_assert_str_eq(res1, res2);

    char *str8 = "amogus is shrek?";
    char *str9 = "is";
    res1 = s21_strpbrk(str8, str9);
    res2 = s21_strpbrk(str8, str9);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strrchr) {
    ck_assert_str_eq(s21_strrchr("Germ eaney", 'e'), strrchr("Germ eaney", 'e'));
    ck_assert_ptr_eq(s21_strrchr("Germany", 'c'), s21_NULL);
    ck_assert_ptr_eq(s21_strrchr(s21_NULL, 'c'), s21_NULL);

    char *s1 = "School-21";
    char *s2 = "";
    char *s3 = "amogus";

    ck_assert_msg(s21_strrchr(s1, 'm') == strrchr(s1, 'm'), "1st strrchr test failed");
    ck_assert_msg(s21_strrchr(s1, 'o') == strrchr(s1, 'o'), "2nd strrchr test failed");
    ck_assert_msg(s21_strrchr(s2, 'o') == strrchr(s2, 'o'), "3rd strrchr test failed");
    ck_assert_msg(s21_strrchr(s3, ' ') == strrchr(s3, ' '), "4rth strrchr test failed");
    ck_assert_msg(s21_strrchr(s3, 's') == strrchr(s3, 's'), "5th strrchr test failed");
}
END_TEST

START_TEST(test_s21_strspn) {
    ck_assert_int_eq(s21_strspn("qwertyyy", "qwy"), strspn("qwertyyy", "qwy"));
    ck_assert_int_eq(s21_strspn("asdasd", "qwy"), strspn("asdasd", "qwy"));

    char *s1 = "School-21";
    char *s2 = "ho";
    char *s3 = "";

    ck_assert_msg(s21_strspn(s1, s2) == strspn(s1, s2), "1st strspn test failed");
    ck_assert_msg(s21_strspn(s3, s2) == strspn(s3, s2), "2nd strspn test failed");
    ck_assert_msg(s21_strspn(s2, s3) == strspn(s2, s3), "3rd strspn test failed");
    ck_assert_msg(s21_strspn(s1, s3) == strspn(s1, s3), "4rth strspn test failed");
    ck_assert_msg(s21_strspn(s3, s1) == strspn(s3, s1), "5th strspn test failed");
}
END_TEST

START_TEST(test_s21_strstr) {
    ck_assert_str_eq(s21_strstr("Germany", "ma"), strstr("Germany", "ma"));
    ck_assert_ptr_eq(s21_strstr("Germany", "tar"), s21_NULL);
    ck_assert_ptr_eq(s21_strstr(s21_NULL, "ter"), s21_NULL);
    ck_assert_ptr_eq(s21_strstr(s21_NULL, s21_NULL), s21_NULL);
    ck_assert_ptr_eq(s21_strstr("qwe", "qwerty"), s21_NULL);
    ck_assert_str_eq(s21_strstr("qwerty", "qwerty"), strstr("qwerty", "qwerty"));

    char *s1 = "School-21";
    char *s2 = "ho";
    char *s3 = "";

    ck_assert_msg(s21_strstr(s1, s2) == strstr(s1, s2), "1st strstr test failed");
    ck_assert_msg(s21_strstr(s1, s3) == strstr(s1, s3), "2nd strstr test failed");
    ck_assert_msg(s21_strstr(s3, s2) == strstr(s3, s2), "3rd strstr test failed");
    ck_assert_msg(s21_strstr(s2, s3) == strstr(s2, s3), "4rth strstr test failed");
    ck_assert_msg(s21_strstr(s3, s1) == strstr(s3, s1), "5th strstr test failed");
}
END_TEST

START_TEST(test_s21_strtok) {
    char src_str1[] = "Hello World, everything is ok";
    char src_str2[] = "Hello World, everything is ok";
    const char *delim = " ";

    char *my_token = s21_strtok(src_str1, delim);
    char *orig_token = strtok(src_str2, delim);

    while (my_token && orig_token) {
        ck_assert_str_eq(my_token, orig_token);
        my_token = s21_strtok(s21_NULL, delim);
        orig_token = strtok(s21_NULL, delim);
    }

    char src_str3[] = "";
    const char *delim3 = " AAAA";

    my_token = s21_strtok(src_str3, delim3);
    ck_assert_ptr_eq(my_token, s21_NULL);

    char *src_str4 = s21_NULL;
    const char *delim4 = " AAAA";

    my_token = s21_strtok(src_str4, delim4);
    ck_assert_ptr_eq(my_token, s21_NULL);

    char test1[50] = "aboba,hello,world,trim";
    char test2[50] = "aboba,hello,world,trim";
    char delim1[10] = "123,";
    char *orig1, *copy1;
    orig1 = strtok(test1, delim1);
    copy1 = s21_strtok(test2, delim1);
    char orig_res1[1000] = {0};
    char copy_res1[1000] = {0};
    while (orig1 != NULL) {
      strcat(orig_res1, orig1);
      orig1 = strtok(NULL, delim1);
    }
    while (copy1 != NULL) {
      strcat(copy_res1, copy1);
      copy1 = s21_strtok(NULL, delim1);
    }
    ck_assert_str_eq(orig_res1, copy_res1);



    char str[] = "School-21";
    char *tok1 = s21_strtok(str, "-");
    char *tok2 = strtok(str, "-");
    char *tok3 = s21_strtok(str, "");
    char *tok4 = strtok(str, "");
    char *tok5 = s21_strtok(str, "oo");
    char *tok6 = strtok(str, "oo");
    char *tok7 = s21_strtok(str, "Sc");
    char *tok8 = strtok(str, "Sc");
    char *tok9 = s21_strtok(str, "21");
    char *tok10 = strtok(str, "21");

    ck_assert_msg(!strcmp(tok1, tok2), "1st strtok test failed");
    ck_assert_msg(!strcmp(tok3, tok4), "2nd strtok test failed");
    ck_assert_msg(!strcmp(tok5, tok6), "3rd strtok test failed");
    ck_assert_msg(!strcmp(tok7, tok8), "4rth strtok test failed");
    ck_assert_msg(!strcmp(tok9, tok10), "5th strtok test failed");
}
END_TEST

START_TEST(test_s21_to_upper) {
    char *a = "hello";
    a = s21_to_upper(a);
    ck_assert_str_eq(a, "HELLO");
    free(a);

    char *b = "HeLlO WoRlD";
    b = s21_to_upper(b);
    ck_assert_str_eq(b, "HELLO WORLD");
    free(b);

    char *c = "HELLO";
    c = s21_to_upper(c);
    ck_assert_str_eq(c, "HELLO");
    free(c);

    char *d = "";
    d = s21_to_upper(d);
    ck_assert_str_eq(d, "");
    free(d);

    char *e = s21_NULL;
    e = s21_to_upper(e);
    ck_assert_ptr_eq(e, s21_NULL);
    free(e);

    char *s1 = "";
    char *s2 = "School is Cool";
    char *s3 = "amogus";
    char *s4 = "Shrek is amogus";
    char *s5 = "what";

    char *r1 = s21_to_upper(s1);
    char *r2 = s21_to_upper(s2);
    char *r3 = s21_to_upper(s3);
    char *r4 = s21_to_upper(s4);
    char *r5 = s21_to_upper(s5);

    ck_assert_str_eq(r1, "");
    ck_assert_str_eq(r2, "SCHOOL IS COOL");
    ck_assert_str_eq(r3, "AMOGUS");
    ck_assert_str_eq(r4, "SHREK IS AMOGUS");
    ck_assert_str_eq(r5, "WHAT");

    free(r1);
    free(r2);
    free(r3);
    free(r4);
    free(r5);
}
END_TEST

START_TEST(test_s21_to_lower) {
    char *a = "hello";
    a = s21_to_lower(a);
    ck_assert_str_eq(a, "hello");
    free(a);

    char *b = "HeLlO WoRlD";
    b = s21_to_lower(b);
    ck_assert_str_eq(b, "hello world");
    free(b);

    char *c = "HELLO";
    c = s21_to_lower(c);
    ck_assert_str_eq(c, "hello");
    free(c);

    char *d = "";
    d = s21_to_lower(d);
    ck_assert_str_eq(d, "");
    free(d);

    char *e = s21_NULL;
    e = s21_to_lower(e);
    ck_assert_ptr_eq(e, s21_NULL);
    free(e);

    char s1[] = "SChOOl-21";
    char s2[] = "ScHool is CoOl";
    char s3[] = "amogus";
    char s4[] = "ShrEK is Amogus";
    char s5[] = "what";

    char *r1 = s21_to_lower(s1);
    char *r2 = s21_to_lower(s2);
    char *r3 = s21_to_lower(s3);
    char *r4 = s21_to_lower(s4);
    char *r5 = s21_to_lower(s5);

    ck_assert_msg(!strcmp(r1, "school-21"), "1st to_lower test failed");
    ck_assert_msg(!strcmp(r2, "school is cool"), "2nd to_lower test failed");
    ck_assert_msg(!strcmp(r3, "amogus"), "3rd to_lower test failed");
    ck_assert_msg(!strcmp(r4, "shrek is amogus"), "4rth to_lower test failed");
    ck_assert_msg(!strcmp(r5, "what"), "5th to_lower test failed");

    free(r1);
    free(r2);
    free(r3);
    free(r4);
    free(r5);
}
END_TEST

START_TEST(test_s21_insert) {
    char *src1 = "abc";
    char *str1 = "123";
    src1 = s21_insert(src1, str1, 1);
    ck_assert_str_eq(src1, "a123bc");
    free(src1);

    char *src2 = "abc def";
    char *str2 = "123";
    src2 = s21_insert(src2, str2, 4);
    ck_assert_str_eq(src2, "abc 123def");
    free(src2);

    char *src3 = "";
    char *str3 = "123 456";
    src3 = s21_insert(src3, str3, 0);
    ck_assert_str_eq(src3, "123 456");
    free(src3);

    char *src4 = s21_NULL;
    char *str4 = s21_NULL;
    src4 = s21_insert(src4, str4, 4);;
    ck_assert_ptr_eq(src4, s21_NULL);
    free(src4);

    char *s1 = "School-21 test";
    char *s2 = "insert ";
    char *s3 = "amogus";
    char *s4 = "is";
    char *s5 = "shrek";
    char *res1 = s21_insert(s1, " ", 3);
    char *res2 = s21_insert(s5, s3, 5);
    char *res3 = s21_insert(s3, s5, 0);
    char *res4 = s21_insert(s5, s4, 5);
    char *res5 = s21_insert(s2, s1, 4);

    ck_assert_str_eq(res1, "Sch ool-21 test");
    ck_assert_str_eq(res2, "shrekamogus");
    ck_assert_str_eq(res3, "shrekamogus");
    ck_assert_str_eq(res4, "shrekis");
    ck_assert_str_eq(res5, "inseSchool-21 testrt ");

    free(res1);
    free(res2);
    free(res3);
    free(res4);
    free(res5);
}
END_TEST

START_TEST(test_s21_trim) {
    char *src1 = "123abc123abc123";
    char *trim_chars1 = "123";
    src1 = s21_trim(src1, trim_chars1);
    ck_assert_str_eq(src1, "abc123abc");
    free(src1);

    char *src2 = "123abc123";
    char *trim_chars2 = "123";
    src2 = s21_trim(src2, trim_chars2);
    ck_assert_str_eq(src2, "abc");
    free(src2);

    char *src3 = "132abc321";
    char *trim_chars3 = "123";
    src3 = s21_trim(src3, trim_chars3);
    ck_assert_str_eq(src3, "abc");
    free(src3);

    char *src4 = "132abc123 abc321";
    char *trim_chars4 = "123";
    src4 = s21_trim(src4, trim_chars4);
    ck_assert_str_eq(src4, "abc123 abc");
    free(src4);

    char *src5 = "";
    char *trim_chars5 = "123";
    src5 = s21_trim(src5, trim_chars5);
    ck_assert_str_eq(src5, "");
    free(src5);

    char *s1 = "School-21";
    char *s2 = "";
    char *s3 = "S";
    char *s4 = "Sch";
    char *s5 = "School";
    char *s6 = "School-21";
    char *s7 = NULL;
    char *r1 = s21_trim(s1, s2);
    char *r2 = s21_trim(s1, s3);
    char *r3 = s21_trim(s1, s4);
    char *r4 = s21_trim(s1, s5);
    char *r5 = s21_trim(s1, s6);
    char *r6 = s21_trim(s1, s7);
    ck_assert_msg(!strcmp(r1, "School-21"), "1st trim test failed");
    ck_assert_msg(!strcmp(r2, "chool-21"), "2nd trim test failed");
    ck_assert_msg(!strcmp(r3, "ool-21"), "3rd trim test failed");
    ck_assert_msg(!strcmp(r4, "-21"), "4rth trim test failed");
    ck_assert_msg(!strcmp(r5, ""), "5th trim test failed");
    ck_assert_msg(!strcmp(r6, "School-21"), "6th trim test failed");
    free(r1);
    free(r2);
    free(r3);
    free(r4);
    free(r5);
    free(r6);
}
END_TEST

START_TEST(test_s21_sprintf) {
    char s21_str[100];
    char str[100];

    s21_sprintf(s21_str, "qwerty");
    sprintf(str, "qwerty");
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "qwerty %c %-5c %15c", '$', '/', '!');
    sprintf(str, "qwerty %c %-5c %15c", '$', '/', '!');
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "qwerty %s qwe", "qwerty");
    sprintf(str, "qwerty %s qwe", "qwerty");
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %u abc", 166);
    sprintf(str, "abc %u abc", 166);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %d abc", -166);
    sprintf(str, "abc %d abc", -166);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %f abc", -166.87);
    sprintf(str, "abc %f abc", -166.87);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %3c abc", '*');
    sprintf(str, "abc %3c abc", '*');
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %-3c abc", '*');
    sprintf(str, "abc %-3c abc", '*');
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %3i abc", 5);
    sprintf(str, "abc %3i abc", 5);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %+i abc", 5);
    sprintf(str, "abc %+i abc", 5);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %+.4f abc", 166.087);
    sprintf(str, "abc %+.4f abc", 166.087);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %-12.3f abc", 166.87);
    sprintf(str, "abc %-12.3f abc", 166.87);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %.5i abc", 5);
    sprintf(str, "abc %.5i abc", 5);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc % 5i abc", 5);
    sprintf(str, "abc % 5i abc", 5);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %*d", 5, 4);
    sprintf(str, "abc %*d", 5, 4);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %e", 0.4784);
    sprintf(str, "abc %e", 0.4784);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %E", 0.4784);
    sprintf(str, "abc %E", 0.4784);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %x", 4784);
    sprintf(str, "abc %x", 4784);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %#x", 4784);
    sprintf(str, "abc %#x", 4784);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %x", 0);
    sprintf(str, "abc %x", 0);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %X", 4784);
    sprintf(str, "abc %X", 4784);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %o", 4784);
    sprintf(str, "abc %o", 4784);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %#o", 4784);
    sprintf(str, "abc %#o", 4784);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %o", 0);
    sprintf(str, "abc %o", 0);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %*o", -5, 0);
    sprintf(str, "abc %*o", -5, 0);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %010d", 50);
    sprintf(str, "abc %010d", 50);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %.*f", 1, 50.897);
    sprintf(str, "abc %.*f", 1, 50.897);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %ld", 58787878958);
    sprintf(str, "abc %ld", 58787878958);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %d", 87878958);
    sprintf(str, "abc %d", 87878958);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %lld", (long long int)88888858787878958);
    sprintf(str, "abc %lld", (long long int)88888858787878958);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %hd", 87878958);
    sprintf(str, "abc %hd", 87878958);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %Lf", (long double)58787.878958);
    sprintf(str, "abc %Lf", (long double)58787.878958);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %.Lf", (long double)58787.878958);
    sprintf(str, "abc %.Lf", (long double)58787.878958);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %.10f", 587.00089);
    sprintf(str, "abc %.10f", 587.00089);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %e", 7.8);
    sprintf(str, "abc %e", 7.8);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %e", 17.8);
    sprintf(str, "abc %e", 17.8);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %hu", 17);
    sprintf(str, "abc %hu", 17);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %lu", 17123121);
    sprintf(str, "abc %lu", (long unsigned int)17123121);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %Le", (long double)17.8);
    sprintf(str, "abc %Le", (long double)17.8);
    ck_assert_str_eq(s21_str, str);

    s21_sprintf(s21_str, "abc %%");
    sprintf(str, "abc %%");
    ck_assert_str_eq(s21_str, str);

    char str1[150];
    char str2[150];
    void *p = (void*)0x3456;
    int n1, n2;
    int r1 = sprintf(str1, "%d|%o|%s|%c|%i|%e|%f|%E|%g|%u|%x|%G|%X|%n|%p|%%|%s",
    25, 342, "aboba", 'a', 123, 25.34, 4325.23434,
    0.0000000123, 2.12345, 12345u, 8342, 0.0000456, 1235, &n1, p, "hello my friend");
    int r2 = s21_sprintf(str2, "%d|%o|%s|%c|%i|%e|%f|%E|%g|%u|%x|%G|%X|%n|%p|%%|%s", 25, 342, "aboba", 'a',
    123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u, 8342, 0.0000456, 1235, &n2, p, "hello my friend");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(r1, r2);

    char str3[100];
    char str4[100];
    int r3 = sprintf(str3, "%+-25.3d/%25.15o/%#10.f/%015d", 252, 243, 256.34, 15);
    int r4 = s21_sprintf(str4, "%+-25.3d/%25.15o/%#10.f/%015d", 252, 243, 256.34, 15);
    ck_assert_str_eq(str3, str4);
    ck_assert_int_eq(r3, r4);

    char str5[100];
    char str6[100];
    int r5 = sprintf(str5, "%#+34.10g|%#.10x|%#15.1o|%25.10s", 25.3456, 1234, 4567, "HELLOMYDEARFRIEND");
    int r6 = s21_sprintf(str6, "%#+34.10g|%#.10x|%#15.1o|%25.10s", 25.3456, 1234, 4567, "HELLOMYDEARFRIEND");
    ck_assert_str_eq(str5, str6);
    ck_assert_int_eq(r5, r6);

    char str7[100];
    char str8[100];
    void *p1 = (void*)43252342;
    int r7 = sprintf(str7, "%#24.e%-15.20i%20p%020u", 43253242.4342, 4567899, p1, 43252342u);
    int r8 = s21_sprintf(str8, "%#24.e%-15.20i%20p%020u", 43253242.4342, 4567899, p1, 43252342u);
    ck_assert_str_eq(str7, str8);
    ck_assert_int_eq(r7, r8);
    char str9[50];
    char str10[100];
    int r9 = sprintf(str9, "%*.0f", 25, 25432.34345);
    int r10 = s21_sprintf(str10, "%*.0f", 25, 25432.34345);
    ck_assert_str_eq(str9, str10);
    ck_assert_int_eq(r9, r10);

    char str11[1000];
    char str12[1000];
    short h = 34;
    int r11 = sprintf(str11, "%-25.10d/%-30.2d/%10.12d/%11d/%*d/%*.*d/%+-25.*d/%+10.2ld/%-11.*hd",
    253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
    int r12 = s21_sprintf(str12, "%-25.10d/%-30.2d/%10.12d/%11d/%*d/%*.*d/%+-25.*d/%+10.2ld/%-11.*hd",
    253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
    ck_assert_str_eq(str11, str12);
    ck_assert_int_eq(r11, r12);

    char str13[1000];
    char str14[1000];
    short h1 = 34;
    long l1 = 2353423523424;
    int r13 = sprintf(str13, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
    34567, 225, 5230, 125, 10, 5, 456, 10, 377, l1, 12, h1);
    int r14 = s21_sprintf(str14, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
    34567, 225, 5230, 125, 10, 5, 456, 10, 377, l1, 12, h1);
    ck_assert_str_eq(str13, str14);
    ck_assert_int_eq(r13, r14);

    char str15[1000];
    char str16[1000];
    wchar_t c1 = 'T', c2 = 'Z';
    int r15 = sprintf(str15, "%10c/%-10c/%25c/%-30c/%25c/%*c/%2c/%*c/%lc/%-50lc",
    'a', 'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
    int r16 = s21_sprintf(str16, "%10c/%-10c/%25c/%-30c/%25c/%*c/%2c/%*c/%lc/%-50lc",
    'a', 'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
    ck_assert_str_eq(str15, str16);
    ck_assert_int_eq(r15, r16);

    char str17[1000];
    char str18[1000];
    int r17 = sprintf(str17,
    "%+-20e/%010.*e/%-*.16e/%#025.10e/%*.*e/%*.15e/%#010.*e/%25.16e",
    2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
    11111.22, 16, -3245.3425342, 16, -0.00123, 235423424.43252);
    int r18 = s21_sprintf(str18,
    "%+-20e/%010.*e/%-*.16e/%#025.10e/%*.*e/%*.15e/%#010.*e/%25.16e",
    2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
    11111.22, 16, -3245.3425342, 16, -0.00123, 235423424.43252);
    ck_assert_str_eq(str17, str18);
    ck_assert_int_eq(r17, r18);

    char str19[1000];
    char str20[1000];
    int r19 = sprintf(str19, "%+-25.4E/%25.*E/%-*.10E/%#02.E/%*.*E/%*.15E/%*E%12.16E",
    3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432, 10, 2, 53242.4242,
    10, 456789.43242, 25, 1111122222.34567899, 2345678.23453242);
    int r20 = s21_sprintf(str20, "%+-25.4E/%25.*E/%-*.10E/%#02.E/%*.*E/%*.15E/%*E%12.16E",
    3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432, 10, 2, 53242.4242,
    10, 456789.43242, 25, 1111122222.34567899, 2345678.23453242);
    ck_assert_str_eq(str19, str20);
    ck_assert_int_eq(r19, r20);

    char str21[1000];
    char str22[1000];
    int r21 = sprintf(str21, "%+-10.5f/%+10.2f/%15.16f/%+*.10f/%*.16f/%-10.*f/%25.*f/%25.f/%#+10.f/%*.*f",
    2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245, 2, 12345.6788,
    1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2, 34567.43244);
    int r22 = s21_sprintf(str22, "%+-10.5f/%+10.2f/%15.16f/%+*.10f/%*.16f/%-10.*f/%25.*f/%25.f/%#+10.f/%*.*f",
    2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245, 2, 12345.6788,
    1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2, 34567.43244);
    ck_assert_str_eq(str21, str22);
    ck_assert_int_eq(r21, r22);

    char str23[1000] = "";
    char str24[1000] = "";
    unsigned short h2 = 253;
    unsigned long l2 = 4325234324242l;
    int r23 = sprintf(str1, "%-25.10o/%-10o/%#-30.2o/%#*.10o/%#*.*o/%25.*o/%#.10ho/%*lo",
    12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h2, 10, l2);
    int r24 = s21_sprintf(str2, "%-25.10o/%-10o/%#-30.2o/%#*.10o/%#*.*o/%25.*o/%#.10ho/%*lo",
    12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h2, 10, l2);
    ck_assert_str_eq(str23, str24);
    ck_assert_int_eq(r23, r24);

    char str25[1000];
    char str26[1000];
    unsigned short h3 = 345;
    unsigned long l3 = 52342353242l;
    int r25 =
    sprintf(str25,
    "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*x%#10.*x%*.5hx%10.25lx",
    235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h3, l3);
    int r26 =
    s21_sprintf(str26,
    "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*x%#10.*x%*.5hx%10.25lx",
    235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h3, l3);
    ck_assert_str_eq(str25, str26);
    ck_assert_int_eq(r25, r26);

    char str27[1000];
    char str28[1000];
    unsigned short h4 = 234;
    unsigned long l4 = 4325243132l;
    int r27 = sprintf(str27,
    "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*X%#12.*X%*.8hx%14.12lX",
    235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h4, l4);
    int r28 = s21_sprintf(str28,
    "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*X%#12.*X%*.8hx%14.12lX",
    235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h4, l4);
    ck_assert_str_eq(str27, str28);
    ck_assert_int_eq(r27, r28);

    char str29[1000];
    char str30[1000];
    unsigned short h5 = 115;
    unsigned long l6 = 123325242342l;
    int r29 = sprintf(str29, "%u/%15u/%-20u/%010u/%-15.10u/%20.*u/%*.*u/%*.10u/%-20.12lu/%19hu",
    4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l6, h5);
    int r30 = s21_sprintf(str30, "%u/%15u/%-20u/%010u/%-15.10u/%20.*u/%*.*u/%*.10u/%-20.12lu/%19hu",
    4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l6, h5);
    ck_assert_str_eq(str29, str30);
    ck_assert_int_eq(r29, r30);

    char str31[1000] = "";
    char str32[1000] = "";
    wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
    int r31 = sprintf(str1,
    "%s/%23s/%-15s/%10.s/%15.2s/%16.*s/%*.*s/%*s/%15.3ls",
    "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10, "QWERTY",
    15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s);
    int r32 = s21_sprintf(str2,
    "%s/%23s/%-15s/%10.s/%15.2s/%16.*s/%*.*s/%*s/%15.3ls",
    "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10, "QWERTY",
    15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s);
    ck_assert_str_eq(str31, str32);
    ck_assert_int_eq(r31, r32);

    char str33[1000];
    char str34[1000];
    void *p2 = (void*)0x123456789;
    void *p3 = (void*)4325234;
    void *p4 = (void*)0x123f324b;
    void *p5 = (void*)432520;
    int r33 = sprintf(str33, "%p%20p%-15p%10p%-15p%*p%10p%*p",
    p2, p3, p4, p5, p3, 10, p4, p2, 10, p5);
    int r34 = s21_sprintf(str34, "%p%20p%-15p%10p%-15p%*p%10p%*p",
    p2, p3, p4, p5, p3, 10, p4, p2, 10, p5);
    ck_assert_str_eq(str33, str34);
    ck_assert_int_eq(r33, r34);

    char str35[1000];
    char str36[1000];
    int r35 = sprintf(str35, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    int r36 = s21_sprintf(str36, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    ck_assert_str_eq(str35, str36);
    ck_assert_int_eq(r35, r36);

    char str37[1000];
    char str38[1000];
    int r37 = sprintf(str37, "%g/%23g/%-10g/%015g/%10.5g/%0#15.10g/%+10.6g/%#*.g/%-10.*g",
    2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234, 2445.4234,
    5, 22456.4424, 9, 234567.43242);
    int r38 = s21_sprintf(str38, "%g/%23g/%-10g/%015g/%10.5g/%0#15.10g/%+10.6g/%#*.g/%-10.*g",
    2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234, 2445.4234,
    5, 22456.4434, 9, 234567.43242);
    ck_assert_str_eq(str37, str38);
    ck_assert_int_eq(r37, r38);

    char str39[1000];
    char str40[1000];
    int r39 =
    sprintf(str39, "%G/%25G/%-15G/%017G/%#05.2G/%#010.16G/%+#8.6G/%*.8G/%#-10.*G/%+#12.16G",
    43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5 , 111.432534243243242, 4324.43242,
    25, -3213.43242, 16, -43.43242353242342, 111.24324242);
    int r40 =
    s21_sprintf(str40, "%G/%25G/%-15G/%017G/%#05.2G/%#010.16G/%+#8.6G/%*.8G/%#-10.*G/%+#12.16G",
    43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5 , 111.432534243243242, 4324.43242,
    25, -3213.43242, 16, -43.43242353242342, 111.24324242);
    ck_assert_str_eq(str39, str40);
    ck_assert_int_eq(r39, r40);
}
END_TEST

START_TEST(specifier_c) {
#define STR " AbCdEfGhIjKlMnOp"
#define FL " %c %4c %c"
    char a1 = 0, b1[10] = "", c1 = 0, a2 = 0, b2[10] = "", c2 = 0;
    int ret1 = sscanf(STR, FL, &a1, b1, &c1);
    int ret2 = s21_sscanf(STR, FL, &a2, b2, &c2);
    ck_assert_int_eq(a1, a2);
    ck_assert_mem_eq(b1, b2, 10);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

START_TEST(specifier_c_2) {
#define STR "  AbCdEfGhIjKlMnOp"
#define FL " %c %*10c %10c"
    char a1 = 0, b1[10] = "", a2 = 0, b2[10] = "";
    int ret1 = sscanf(STR, FL, &a1, b1);
    int ret2 = s21_sscanf(STR, FL, &a2, b2);
    ck_assert_int_eq(a1, a2);
    ck_assert_mem_eq(b1, b2, 10);
    ck_assert_int_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIER %d
START_TEST(specifier_d) {
#define STR "a 42 0 -2021k"
#define FL "a%1d %d %d"
    int a1 = 0, b1 = 0, c1 = 0, a2 = 0, b2 = 0, c2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

START_TEST(specifier_d_hl) {
#define STR "a 42 123123123213 k123"
#define FL "a%1hd %d %ld %d"
    short a1 = 0, a2 = 0;
    int b1 = 0, d1 = 0, b2 = 0, d2 = 0;
    long c1 = 0, c2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1, &d1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2, &d2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
    ck_assert_int_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIER %i
START_TEST(specifier_i) {
#define STR "042abc-0x2Ad -2021k"
#define FL "%4iabc%i %*i"
    int a1 = 0, b1 = 0, a2 = 0, b2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIERS %e, %E, %f, %g, %G
START_TEST(specifiers_eEfgG) {
#define STR "a 4.123 0.0000123E4 -2021k -inf -0.0"
#define FL "a%4e %*E %fk %g %G"
    float a1 = 0, b1 = 0, c1 = 0, d1 = 0, a2 = 0, b2 = 0, c2 = 0, d2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1, &d1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2, &d2);
    ck_assert_float_eq(a1, a2);
    ck_assert_float_eq(b1, b2);
    ck_assert_float_eq(c1, c2);
    ck_assert_float_eq(d1, d2);
    ck_assert_float_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

START_TEST(specifiers_eEfgG_L) {
#define STR "a 42.123e20   -0.0000123E4 -2021k 3.4   a-34.175"
#define FL "a%Le %E %fk %Lg %G"
    long double a1 = 0, d1 = 0, a2 = 0, d2 = 0;
    float b1 = 0, c1 = 0, e1 = 0, b2 = 0, c2 = 0, e2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1, &d1, &e1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2, &d2, &e2);
    ck_assert_ldouble_eq(a1, a2);
    ck_assert_float_eq(b1, b2);
    ck_assert_float_eq(c1, c2);
    ck_assert_ldouble_eq(d1, d2);
    ck_assert_float_eq(e1, e2);
    ck_assert_float_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIER %o
START_TEST(specifier_o) {
#define STR "42 0157sega-2021"
#define FL "%4o %osega%o"
    unsigned int a1 = 0, b1 = 0, c1 = 0, a2 = 0, b2 = 0, c2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2);
    ck_assert_uint_eq(a1, a2);
    ck_assert_uint_eq(b1, b2);
    ck_assert_uint_eq(c1, c2);
    ck_assert_uint_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIER %s
START_TEST(specifier_s) {
#define STR " AbCdEfGhIjKlMnOp"
#define FL " %3s %7s %*s"
    char a1[20], b1[20];
    char a2[20], b2[20];
    int ret1 = sscanf(STR, FL, a1, b1);
    int ret2 = s21_sscanf(STR, FL, a2, b2);
    ck_assert_str_eq(a1, a2);
    ck_assert_str_eq(b1, b2);
    ck_assert_uint_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIER %u
START_TEST(specifier_u) {
#define STR "a 42class0 -2021k"
#define FL "a%4uclass%u %u"
    unsigned int a1 = 0, b1 = 0, c1 = 0, a2 = 0, b2 = 0, c2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2);
    ck_assert_uint_eq(a1, a2);
    ck_assert_uint_eq(b1, b2);
    ck_assert_uint_eq(c1, c2);
    ck_assert_uint_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIERS %x, %X
START_TEST(specifiers_xX) {
#define STR "42 0xA1B2C3D -31 0"
#define FL "%x %X %x %X"
    unsigned int a1 = 0, b1 = 0, c1 = 0, d1 = 0, a2 = 0, b2 = 0, c2 = 0, d2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1, &d1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2, &d2);
    ck_assert_uint_eq(a1, a2);
    ck_assert_uint_eq(b1, b2);
    ck_assert_uint_eq(c1, c2);
    ck_assert_uint_eq(d1, d2);
    ck_assert_uint_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIER %p
START_TEST(specifier_p) {
#define STR "0xa1b2kc3d 1234A z42"
#define FL " %6pk%p %p %p"
    void *a1 = NULL, *b1 = NULL, *c1 = NULL, *d1 = NULL;
    void *a2 = NULL, *b2 = NULL, *c2 = NULL, *d2 = NULL;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1, &d1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2, &d2);
    ck_assert_ptr_eq(a1, a2);
    ck_assert_ptr_eq(b1, b2);
    ck_assert_ptr_eq(c1, c2);
    ck_assert_ptr_eq(d1, d2);
    ck_assert_uint_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIER %n
START_TEST(specifier_n) {
#define STR "0xa1b2k123123 1234A 42"
#define FL " %6Xk%n %d %n"
    unsigned int a1 = 0, a2 = 0;
    int b1 = 0, c1 = 0, d1 = 0;
    int b2 = 0, c2 = 0, d2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1, &c1, &d1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2, &c2, &d2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
    ck_assert_uint_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

// SPECIFIER %%
START_TEST(specifier_percent) {
#define STR "123456 % 42"
#define FL " %d %% %d %%"
    int a1 = 0, b1 = 0, a2 = 0, b2 = 0;
    int ret1 = sscanf(STR, FL, &a1, &b1);
    int ret2 = s21_sscanf(STR, FL, &a2, &b2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(ret1, ret2);
#undef STR
#undef FL
}
END_TEST

Suite *s21_string_test_suite() {
    Suite *s = suite_create("s21_string_test_suite");

    TCase *s_strtok = tcase_create("strtok");
    suite_add_tcase(s, s_strtok);
    tcase_add_test(s_strtok, test_s21_strtok);

    TCase *s_memchr = tcase_create("s_memchr");
    suite_add_tcase(s, s_memchr);
    tcase_add_test(s_memchr, test_s21_memchr);

    TCase *s_strstr = tcase_create("s_strstr");
    suite_add_tcase(s, s_strstr);
    tcase_add_test(s_strstr, test_s21_strstr);

    TCase *s_strspn = tcase_create("s_strspn");
    suite_add_tcase(s, s_strspn);
    tcase_add_test(s_strspn, test_s21_strspn);

    TCase *s_strrchr = tcase_create("s_strrchr");
    suite_add_tcase(s, s_strrchr);
    tcase_add_test(s_strrchr, test_s21_strrchr);

    TCase *s_memset = tcase_create("s_memset");
    suite_add_tcase(s, s_memset);
    tcase_add_test(s_memset, test_s21_memset);

    TCase *s_strcat = tcase_create("s_strcat");
    suite_add_tcase(s, s_strcat);
    tcase_add_test(s_strcat, test_s21_strcat);

    TCase *s_strncat = tcase_create("s_strncat");
    suite_add_tcase(s, s_strncat);
    tcase_add_test(s_strncat, test_s21_strncat);

    TCase *s_strchr = tcase_create("s_strchr");
    suite_add_tcase(s, s_strchr);
    tcase_add_test(s_strchr, test_s21_strchr);

    TCase *s_strncmp = tcase_create("s_strncmp");
    suite_add_tcase(s, s_strncmp);
    tcase_add_test(s_strncmp, test_s21_strncmp);

    TCase *s_strcmp = tcase_create("s_strcmp");
    suite_add_tcase(s, s_strcmp);
    tcase_add_test(s_strcmp, test_s21_strcmp);

    TCase *s_memcmp = tcase_create("s_memcmp");
    suite_add_tcase(s, s_memcmp);
    tcase_add_test(s_memcmp, test_s21_memcmp);

    TCase *s_strncpy = tcase_create("s_strncpy");
    suite_add_tcase(s, s_strncpy);
    tcase_add_test(s_strncpy, test_s21_strncpy);

    TCase *s_strcpy = tcase_create("s_strcpy");
    suite_add_tcase(s, s_strcpy);
    tcase_add_test(s_strcpy, test_s21_strcpy);

    TCase *s_strlen = tcase_create("s_strlen");
    suite_add_tcase(s, s_strlen);
    tcase_add_test(s_strlen, test_s21_strlen);

    TCase *s_memcpy = tcase_create("s_memcpy");
    suite_add_tcase(s, s_memcpy);
    tcase_add_test(s_memcpy, test_s21_memcpy);

    TCase *s_memmove = tcase_create("s_memmove");
    suite_add_tcase(s, s_memmove);
    tcase_add_test(s_memmove, test_s21_memmove);

    TCase *s_to_upper = tcase_create("s_to_upper");
    suite_add_tcase(s, s_to_upper);
    tcase_add_test(s_to_upper, test_s21_to_upper);

    TCase *s_to_lower = tcase_create("s_to_lower");
    suite_add_tcase(s, s_to_lower);
    tcase_add_test(s_to_lower, test_s21_to_lower);

    TCase *s_insert = tcase_create("s_insert");
    suite_add_tcase(s, s_insert);
    tcase_add_test(s_insert, test_s21_insert);

    TCase *s_trim = tcase_create("s_trim");
    suite_add_tcase(s, s_trim);
    tcase_add_test(s_trim, test_s21_trim);

    TCase *s_strcspn = tcase_create("s_strcspn");
    suite_add_tcase(s, s_strcspn);
    tcase_add_test(s_strcspn, test_s21_strcspn);

    TCase *s_strpbrk = tcase_create("s_strpbrk");
    suite_add_tcase(s, s_strpbrk);
    tcase_add_test(s_strpbrk, test_s21_strpbrk);

    TCase *s_sprintf = tcase_create("s_sprintf");
    suite_add_tcase(s, s_sprintf);
    tcase_add_test(s_sprintf, test_s21_sprintf);

    TCase *s_strerror = tcase_create("s_strerror");
    suite_add_tcase(s, s_strerror);
    tcase_add_test(s_strerror, test_s21_strerror);

    TCase *s_sscanf = tcase_create("s_sscanf");
    suite_add_tcase(s, s_sscanf);
    tcase_add_test(s_sscanf, specifier_c);
    tcase_add_test(s_sscanf, specifier_c_2);
    tcase_add_test(s_sscanf, specifier_d);
    tcase_add_test(s_sscanf, specifier_d_hl);
    tcase_add_test(s_sscanf, specifier_i);
    tcase_add_test(s_sscanf, specifiers_eEfgG);
    tcase_add_test(s_sscanf, specifiers_eEfgG_L);
    tcase_add_test(s_sscanf, specifier_o);
    tcase_add_test(s_sscanf, specifier_s);
    tcase_add_test(s_sscanf, specifier_u);
    tcase_add_test(s_sscanf, specifiers_xX);
    tcase_add_test(s_sscanf, specifier_p);
    tcase_add_test(s_sscanf, specifier_n);
    tcase_add_test(s_sscanf, specifier_percent);

    return s;
}

int main() {
    int no_failed = 0;

    Suite *s = s21_string_test_suite();

    SRunner *runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
