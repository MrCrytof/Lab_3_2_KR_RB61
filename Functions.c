#include "Functions.h"

double f(double x) {
    double term = x - 64.0;
    return -0.5 * term * term * term - 3.0 * x * x + 10.0;
}

double df(double x) {
    double term = x - 64.0;
    return -1.5 * term * term - 6.0 * x;
}

double d2f(double x) {
    return -3.0 * (x - 64.0) - 6.0;
}

double readDouble(const char *prompt) {
    double val;

    printf("%s", prompt);

    while (scanf("%lf", &val) != 1) {
        while (getchar() != '\n')
        printf("Invalid input! Try again: ");
    }

    return val;
}

int readPositiveInt(const char *prompt) {
    int val;

    printf("%s", prompt);

    while (scanf("%d", &val) != 1 || val <= 0) {
        while (getchar() != '\n')
        printf("Invalid input! Enter positive integer: ");
    }

    return val;
}

bool verifyInterval(double a, double b) {
    printf("\n=== Verification of Interval [%.4f, %.4f] ===\n", a, b);

    double fa = f(a);
    double fb = f(b);

    if (fa * fb >= 0) {
        printf("ERROR: f(a) = %.4f and f(b) = %.4f have the SAME sign!\n",
               fa, fb);
        printf("The method cannot guarantee finding a root on this interval.\n");
        return false;
    }

    printf("1. f(a) * f(b) < 0 (f(a) = %.4f, f(b) = %.4f) -> Root exists.\n",
           fa, fb);

    double dfa = df(a);
    double dfb = df(b);

    printf("\n2. Derivative check:\n");
    printf("   f'(a) = %.6f\n", dfa);
    printf("   f'(b) = %.6f\n", dfb);

    if (dfa * dfb > 0) {
        printf("   f'(x) keeps the same sign on the interval.\n");
        printf("   f(x) is monotonic on [a,b].\n");
        printf("   Therefore the interval contains exactly one root.\n");
    } else {
        printf("   WARNING: derivative may change sign on the interval.\n");
        printf("   Uniqueness of the root is not confirmed by this test.\n");
    }

    return true;
}

static char askIterationAction(void) {
    char option;

    printf("\nWhat do you want to do?\n");
    printf("a - Continue with the same number of iterations\n");
    printf("b - Continue until the root is found\n");
    printf("c - Exit and show intermediate result\n");
    printf("Select option: ");

    scanf(" %c", &option);

    return option;
}

void chordMethod(double a, double b, double eps, int maxIter, bool debug) {
    if (f(a) * f(b) >= 0) {
        printf("\n[ERROR] Cannot start Chord Method: f(a) and f(b) have same sign!\n");
        return;
    }

    double fixed_point;
    double x_curr;

    if (f(a) * d2f(a) > 0) {
        fixed_point = a;
        x_curr = b;
    } else {
        fixed_point = b;
        x_curr = a;
    }

    double f_fixed = f(fixed_point);
    int iter = 0;
    bool continueForever = false;

    clock_t start = clock();

    if (debug) {
        printf("\n====================================================\n");
        printf("                CHORD METHOD SOLVER                 \n");
        printf("====================================================\n");
        printf("%-5s | %-16s | %-16s | %-16s\n",
               "Iter", "x_n", "f(x_n)", "|x_n - x_prev|");
        printf("----------------------------------------------------\n");
    }

    while (1) {
        double x_prev = x_curr;
        double f_prev = f(x_prev);
        double denominator = f_fixed - f_prev;

        if (fabs(denominator) < 1e-15) {
            printf("\n[ERROR] Division by zero in Chord Method.\n");
            break;
        }

        x_curr = x_prev -
                 (f_prev * (fixed_point - x_prev)) /
                 denominator;

        iter++;

        double error = fabs(x_curr - x_prev);

        if (debug) {
            printf("%-5d | %-16.8f | %-16.8e | %-16.8e\n",
                   iter, x_curr, f(x_curr), error);
        }

        if (error <= eps) {
            break;
        }

        if (!continueForever && iter >= maxIter) {
            printf("\n[WARNING] Reached maximum iterations limit (%d).\n",
                   maxIter);

            char option = askIterationAction();

            if (option == 'a' || option == 'A') {
                continue;
            } else if (option == 'b' || option == 'B') {
                continueForever = true;
            } else if (option == 'c' || option == 'C') {
                break;
            } else {
                printf("Invalid option. Calculation stopped.\n");
                break;
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n=== RESULT (Chord Method) ===\n");
    printf("Root value (x)         : %.10f\n", x_curr);
    printf("Function value f(x)    : %.10e\n", f(x_curr));
    printf("Number of iterations   : %d\n", iter);
    printf("Execution time         : %.6f sec.\n", time_spent);
}

void bisectionMethod(double a, double b, double eps, int maxIter, bool debug) {
    if (f(a) * f(b) >= 0) {
        printf("\n[ERROR] Cannot start Bisection Method: f(a) and f(b) have same sign!\n");
        return;
    }

    double c = a;
    int iter = 0;
    bool continueForever = false;

    clock_t start = clock();

    if (debug) {
        printf("\n====================================================\n");
        printf("              BISECTION METHOD SOLVER               \n");
        printf("====================================================\n");
        printf("%-5s | %-16s | %-16s | %-16s\n",
               "Iter", "c (midpoint)", "f(c)", "(b - a) / 2");
        printf("----------------------------------------------------\n");
    }

    while (1) {
        c = (a + b) / 2.0;
        iter++;

        double halfInterval = (b - a) / 2.0;

        if (debug) {
            printf("%-5d | %-16.8f | %-16.8e | %-16.8e\n",
                   iter, c, f(c), halfInterval);
        }

        if (halfInterval <= eps || fabs(f(c)) <= eps) {
            break;
        }

        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }

        if (!continueForever && iter >= maxIter) {
            printf("\n[WARNING] Reached maximum iterations limit (%d).\n",
                   maxIter);

            char option = askIterationAction();

            if (option == 'a' || option == 'A') {
                continue;
            } else if (option == 'b' || option == 'B') {
                continueForever = true;
            } else if (option == 'c' || option == 'C') {
                break;
            } else {
                printf("Invalid option. Calculation stopped.\n");
                break;
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n=== RESULT (Bisection Method) ===\n");
    printf("Root value (x)         : %.10f\n", c);
    printf("Function value f(x)    : %.10e\n", f(c));
    printf("Number of iterations   : %d\n", iter);
    printf("Execution time         : %.6f sec.\n", time_spent);
}