
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>

double math_function(double x);
double derivative_1_math_funct(double x);
double digit_deriv_1_math_left(double x, double h);
double digit_deriv_1_math_r(double x, double h);
void input_for_der(double *x, double *h);
void result(double f);
void research_function(void);
// Головна функція показує меню та викликає обрану операцію.
int main()
{
    for (;;)
    {
        // x — аргумент, h — крок чисельної похідної, var — номер пункту меню.
        double x, h;
        unsigned int var;

        printf("\n1 - Analytical derivative");
    printf("\n2 - Numerical left derivative");
    printf("\n3 - Numerical right derivative");
    printf("\n4 - Function research and tables");
    printf("\n0 - Exit");
    printf("\nChoose option: ");

// Якщо номер пункту не прочитано, завершуємо програму.
if (scanf("%u", &var) != 1)
    return 0;

        switch (var)
        {
            // Обчислення похідної за аналітичною формулою.
            case 1:
                printf("Input x\n");
                scanf("%lf", &x);
                printf("x = %lf\n", x);
                result(derivative_1_math_funct(x));
                break;

            // Введення x, h та обчислення лівої чисельної похідної.
            case 2:
                input_for_der(&x, &h);
                result(digit_deriv_1_math_left(x, h));
                break;

            // Введення x, h та обчислення правої чисельної похідної.
            case 3:
                input_for_der(&x, &h);
                result(digit_deriv_1_math_r(x, h));
                break;
            // Побудова таблиць і пошук інтервалів ізоляції коренів.
            case 4:
                research_function();
                break;

            // Завершення роботи програми.
            case 0:
                return 0;

default:
    printf("Incorrect option!\n");
    break;
        }
    }

    return 0;
}

// Основна математична функція для варіанта 10
double math_function(double x)
{
    // pow підносить вираз до степеня: 2 — квадрат, 3 — куб.
    return 0.25 * pow(x - 25, 2) + pow(x + 25, 3) / 100 + 1;
}

// Обчислення першої похідної аналітичним методом
double derivative_1_math_funct(double x)
{
    // Диференціюємо квадратний і кубічний доданки; похідна сталої дорівнює нулю.
    return 0.5 * (x - 25) + 3 * pow(x + 25, 2) / 100;
}

// Обчислення першої похідної чисельним лівим методом
double digit_deriv_1_math_left(double x, double h)
{
    // Ліва різницева формула використовує значення у точках x та x-h.
    return (math_function(x) - math_function(x - h)) / h;
}

// Обчислення першої похідної чисельним правим методом
double digit_deriv_1_math_r(double x, double h)
{
    // Права різницева формула використовує значення у точках x+h та x.
    return (math_function(x + h) - math_function(x)) / h;
}



// Введення аргументу та перевірка кроку для чисельної похідної
// Вказівники x і h дозволяють записати введені значення у змінні main.
void input_for_der(double *x, double *h)
{
    printf("Input x:\n");
    scanf("%lf", x);

    // Повторюємо введення, поки крок не належить проміжку (0; 0.001].
    do {
        printf("Input h (0 < h <= 0.001):\n");
        scanf("%lf", h);
    } while (*h <= 0 || *h > 0.001);

    printf("x = %lf\n", *x);
    printf("h = %lf\n", *h);
}

// Виводить обчислене значення першої похідної.
void result(double f)
{
    printf("Result der 1 is = %lf\n", f);
}

 // Дослідження функції та побудова таблиць
void research_function(void)
{
    // mode — спосіб введення, N — кількість точок, i — індекс, found — лічильник знахідок.
    unsigned int mode, N, i, found = 0;
    // isolated показує, чи підтверджено єдиність кореня на поточному інтервалі.
    int isolated;
    // X1, X2 — межі; delta — крок; x, fx — поточні дані; prev_x, prev_f — попередні.
    double X1, X2, delta, x, fx, prev_x, prev_f;
    // d1, d2 — перша похідна на кінцях інтервалу; vertex — аргумент її мінімуму.
    double d1, d2;
    double vertex = -100.0 / 3.0;

    // Вибір способу введення
    do {
        printf("\n1 - Input X1, X2, N");
        printf("\n2 - Input X1, X2, delta");
        printf("\nChoose input method: ");

        if (scanf("%u", &mode) != 1)
            return;

    } while (mode != 1 && mode != 2);

    // Введення та перевірка меж
    do {
        printf("Input X1: ");
        if (scanf("%lf", &X1) != 1)
            return;

        printf("Input X2: ");
        if (scanf("%lf", &X2) != 1)
            return;

    } while (X1 >= X2);

    if (mode == 1)
    {
        // Введення кількості точок
        do {
            printf("Input N (2...1000): ");
            if (scanf("%u", &N) != 1)
                return;

        } while (N < 2 || N > 1000);

        // N точок утворюють N-1 проміжків, тому ділимо довжину відрізка на N-1.
        delta = (X2 - X1) / (N - 1);
    }
    else
    {
        // Введення кроку аргументу
        do {
            printf("Input delta: ");
            if (scanf("%lf", &delta) != 1)
                return;

        } while (delta <= 0 ||
                 delta > X2 - X1 ||
                 (X2 - X1) / delta > 998);

        // Визначаємо кількість точок за кроком, враховуючи початкову точку X1.
        N = (unsigned int)((X2 - X1) / delta) + 1;

        // Додаємо точку X2; останній проміжок може бути коротшим за delta.
        if (X1 + (N - 1) * delta < X2)
            N++;
    }

    // Виведення початкових даних
    printf("\nX1 = %.6lf", X1);
    printf("\nX2 = %.6lf", X2);
    printf("\nN = %u", N);
    printf("\ndelta = %.6lf\n", delta);

    // Таблиця значень функції
    printf("\nTable of function:\n");
    printf("-------------------------------------\n");
    printf(" N       x              f(x)\n");
    printf("-------------------------------------\n");

    // Перебираємо всі точки сітки; останню явно прирівнюємо до X2.
    for (i = 0; i < N; i++)
    {
        x = X1 + i * delta;

        if (i == N - 1)
            x = X2;

        printf("%3u   %12.6lf   %12.6lf\n",
               i + 1, x, math_function(x));
    }

    // Таблиця значень першої похідної
    printf("\nTable of derivative:\n");
    printf("-------------------------------------\n");
    printf(" N       x              f'(x)\n");
    printf("-------------------------------------\n");

    for (i = 0; i < N; i++)
    {
        x = X1 + i * delta;

        if (i == N - 1)
            x = X2;

        printf("%3u   %12.6lf   %12.6lf\n",
               i + 1, x, derivative_1_math_funct(x));
    }

    // Пошук проміжків зміни знака функції
    printf("\nRoot isolation intervals:\n");

    prev_x = X1;
    prev_f = math_function(prev_x);

    // Порівнюємо значення у сусідніх точках, починаючи з другої точки сітки.
    for (i = 1; i < N; i++)
    {
        x = X1 + i * delta;

        if (i == N - 1)
            x = X2;

        fx = math_function(x);

        if (prev_f == 0)
        {
            printf("Root at x = %.6lf\n", prev_x);
            found++;
        }

        // Зміна знака неперервної функції вказує на корінь між цими точками.
        if ((prev_f < 0 && fx > 0) ||
            (prev_f > 0 && fx < 0))
        {
            // Перевірка сталості знака похідної
            d1 = derivative_1_math_funct(prev_x);
            d2 = derivative_1_math_funct(x);

            isolated = 0;

            if (d1 < 0 && d2 < 0)
                isolated = 1;

            // Для додатної похідної на кінцях враховуємо також її мінімум усередині.
            if (d1 > 0 && d2 > 0 &&
                (vertex <= prev_x || vertex >= x ||
                 derivative_1_math_funct(vertex) > 0))
                isolated = 1;

            if (isolated == 1)
                printf("One root in [%.6lf; %.6lf]\n",
                       prev_x, x);
            else
                printf("Check interval [%.6lf; %.6lf]\n",
                       prev_x, x);

            found++;
        }

        // Поточна точка стає попередньою для наступної ітерації.
        prev_x = x;
        prev_f = fx;
    }

    if (prev_f == 0)
    {
        printf("Root at x = %.6lf\n", prev_x);
        found++;
    }

    if (found == 0)
        printf("No root intervals detected.\n");
}
