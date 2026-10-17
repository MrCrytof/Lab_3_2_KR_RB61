#include "Functions.h"
/**
 * @brief Головна точка входу в програму.
 *
 * @return 0 у разі успішного завершення.
 */
int main(void) {
    /** Ліва межа інтервалу (a) */
    double a;

    /** Права межа інтервалу (b) */
    double b;

    /** Точність обчислень (eps) */
    double eps;

    /** Максимальна кількість ітерацій (N) */
    int maxIter;

    /** Вибір пункту меню */
    int choice;

    /* Виведення шапки програми */
    printf("====================================================\n");
    printf(" Equation: f(x) = -0.5*(x - 64)^3 - 3*x^2 + 10 = 0  \n");
    printf("====================================================\n\n");

    /* Введення початкових даних */
    printf("--- Input Parameters ---\n");
    a = readDouble("Enter left bound (a): ");
    b = readDouble("Enter right bound (b): ");
    eps = readDouble("Enter tolerance (eps, e.g. 0.0001): ");
    maxIter = readPositiveInt("Enter max iterations count (N): ");

    /* Головний цикл меню */
    while (1) {
        /* Відображення меню та поточних налаштувань */
        printf("\n====================================================\n");
        printf("                     MAIN MENU                      \n");
        printf("====================================================\n");
        printf(" Current settings:\n");
        printf("   Interval [a, b]       : [%.4f, %.4f]\n", a, b);
        printf("   Tolerance (eps)       : %.8f\n", eps);
        printf("   Max iterations (N)    : %d\n", maxIter);
        printf("----------------------------------------------------\n");
        printf(" 1. Verify root isolation interval [a, b]\n");
        printf(" 2. Solve with CHORD METHOD (Standard mode)\n");
        printf(" 3. Solve with CHORD METHOD (Debug mode)\n");
        printf(" 4. Solve with BISECTION METHOD (Standard mode)\n");
        printf(" 5. Solve with BISECTION METHOD (Debug mode)\n");
        printf(" 0. Exit program\n");
        printf("----------------------------------------------------\n");

        /* Зчитати вибір користувача */
        choice = (int)readDouble("Select an option: ");

        /* Обробка пунктів меню */
        switch (choice) {
            case 1:
                /* Перевірка наявності кореня */
                verifyInterval(a, b);
                break;

            case 2:
                /* Метод хорд (звичайний) */
                chordMethod(a, b, eps, maxIter, false);
                break;

            case 3:
                /* Метод хорд (debug) */
                chordMethod(a, b, eps, maxIter, true);
                break;

            case 4:
                /* Метод бісекції (звичайний) */
                bisectionMethod(a, b, eps, maxIter, false);
                break;

            case 5:
                /* Метод бісекції (debug) */
                bisectionMethod(a, b, eps, maxIter, true);
                break;

            case 0:
                /* Вихід з програми */
                printf("\nExiting program. Goodbye!\n");
                return 0;

            default:
                /* Некоректне значення */
                printf("\nInvalid option! Please try again.\n");
                break;
        }
    }

    return 0;
}