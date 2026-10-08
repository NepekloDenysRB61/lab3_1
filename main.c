
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>

double math_function(double x);
double derivative_1_math_funct(double x);
double derivative_2_math_funct(double x);
double digit_deriv_1_math_left(double x, double h);
double digit_deriv_1_math_r(double x, double h);

void input_for_der(double *x, double *h);
void result(double f);

int main()
{
    for (;;)
    {
        double x, h;
        unsigned int var;

        printf("1 - original der.\n2 - der. digit left \n3 - der. r c.\n");
        scanf("%u", &var);

        switch (var)
        {
            case 1:
                printf("Input x\n");
                scanf("%lf", &x);
                printf("x = %lf\n", x);
                result(derivative_1_math_funct(x));
                break;

            case 2:
                input_for_der(&x, &h);
                result(digit_deriv_1_math_left(x, h));
                break;

            case 3:
                input_for_der(&x, &h);
                result(digit_deriv_1_math_r(x, h));
                break;
        }
    }

    return 0;
}

// Основна математична функція для варіанта 10
double math_function(double x)
{
    return 0.25 * pow(x - 25, 2) + pow(x + 25, 3) / 100 + 1;
}

// Обчислення першої похідної аналітичним методом
double derivative_1_math_funct(double x)
{
    return 0.5 * (x - 25) + 3 * pow(x + 25, 2) / 100;
}

// Обчислення другої похідної аналітичним методом
double derivative_2_math_funct(double x)
{
    return 0.5 + 6 * (x + 25) / 100;
}

// Обчислення першої похідної чисельним лівим методом
double digit_deriv_1_math_left(double x, double h)
{
    return (math_function(x) - math_function(x - h)) / h;
}

// Обчислення першої похідної чисельним правим методом
double digit_deriv_1_math_r(double x, double h)
{
    return (math_function(x + h) - math_function(x)) / h;
}



// Введення аргументу та перевірка кроку для чисельної похідної
void input_for_der(double *x, double *h)
{
    printf("Input x:\n");
    scanf("%lf", x);

    do {
        printf("Input h (0 < h <= 0.001):\n");
        scanf("%lf", h);
    } while (*h <= 0 || *h > 0.001);

    printf("x = %lf\n", *x);
    printf("h = %lf\n", *h);
}

void result(double f)
{
    printf("Result der 1 is = %lf\n", f);
}
