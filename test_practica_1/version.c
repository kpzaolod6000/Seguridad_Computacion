#include <stdio.h>


int main(void) {
    #ifdef __STDC_VERSION__
        printf("Aparentemente compatible con __STDC_VERSION__\n");
    #   if __STDC_VERSION__ == 199901L
        printf("Este código fue compilando con el estandar C99.\n");
    #   elif __STDC_VERSION__ == 201112L
        printf("Este codigo fue compilado con el estandar C11.\n");
    #   else
        printf("Este codigo fue compilado con el estandar C94.\n");
    #   endif /* == */
    #endif /* __STDC_VERSION__ */


    #ifdef __cplusplus
        printf("Aparentemente compilado con un compilador de C++\n");
    #   if __cplusplus >= 201103L
        printf("Este codigo fue compilado bajo un estandar mayor o igual a C++11.\n");
    #   else
        printf("Este codigo fue compilado bajo un estandar menor a C++11.");
    #   endif /* >= */
    #endif /* __cplusplus */

    #ifdef __STDC__
        printf("Aparentemente compatible con __STDC__ y los estandares C89 y C90 ...\n");
    #endif /* __STDC__ */
}