#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DEG 100

typedef struct {
    double coefficients[MAX_DEG + 1];
    int degree;
} Polynomial;

void init_polynomial(Polynomial *p, int degree) {
    p->degree = degree;
    for (int i = 0; i <= degree; i++) {
        p->coefficients[i] = 0.0;
    }
}

double evaluate(const Polynomial *p, double x) {
    double result = 0.0;
    for (int i = p->degree; i >= 0; i--) {
        result = result * x + p->coefficients[i];
    }
    return result;
}

Polynomial differentiate(const Polynomial *p) {
    Polynomial result;
    if (p->degree == 0) {
        init_polynomial(&result, 0);
        result.coefficients[0] = 0;
        return result;
    }

    init_polynomial(&result, p->degree - 1);
    for (int i = 1; i <= p->degree; i++) {
        result.coefficients[i - 1] = i * p->coefficients[i];
    }
    return result;
}

double newton_raphson(const Polynomial *p, double initial_guess) {
    double x = initial_guess;
    Polynomial dp = differentiate(p);
    for (int i = 0; i < 10; i++) {          
	  double fx = evaluate(p, x);
        double dfx = evaluate(&dp, x);
        if (dfx == 0) {
            printf("Derivative is zero. No solution found.\n");
            return x;
        }
        x = x - fx / dfx;
    }
    return x;
}

void print_polynomial(const Polynomial *p) {
    int first = 1;
    printf("Your polynomial: ");
    for (int i = p->degree; i >= 0; i--) {
        if (p->coefficients[i] != 0) {
            if (!first && p->coefficients[i] > 0) printf(" +");
            printf(" %.2fx^%d", p->coefficients[i], i);
            first = 0;
        }
    }
    printf("\n");
}

int main() {
    Polynomial p;
    int degree;
    printf("Enter the highest degree of the polynomial: ");
    scanf("%d", &degree);

    init_polynomial(&p, degree);
    for (int i = degree; i >= 0; i--) {
        printf("Enter the coefficient for x^%d: ", i);
        scanf("%lf", &p.coefficients[i]);
    }

    print_polynomial(&p);

    Polynomial dp = differentiate(&p);
    printf("Derivative of the polynomial:\n");
    print_polynomial(&dp);

    double initial_guess;
    printf("Enter initial guess for Newton-Raphson method: ");
    scanf("%lf", &initial_guess);

    double root = newton_raphson(&p, initial_guess);
    printf("Approximate root: %f\n", root);
    return 0;
}

