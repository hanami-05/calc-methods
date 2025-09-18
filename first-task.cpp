#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

long double f(long double x)
{
    return x - 10 * sin(x);
}

long double df(long double x)
{
    return 1 - 10 * cos(x);
}

vector<pair<long double, long double>> separate_roots(long double A, long double B, int N)
{
    vector<pair<long double, long double>> intervals;

    long double h = (B - A) / N;
    long double start = A, end;

    for (int i = 0; i < N; ++i)
    {
        end = start + h;

        if (f(end) * f(start) < 0)
        {
            intervals.push_back({start, end});
        }
        else if (f(end) == 0)
        {
            intervals.push_back({end, end});
        }
        else if (i == 0 && f(start) == 0)
        {
            intervals.push_back({start, start});
        }

        start = end;
    }

    return intervals;
}

void print(long double a)
{
    cout << setprecision(15) << a << endl;
}

void bisect_method(long double A, long double B, long double eps)
{
    long double start = A, end = B;
    long double x = start;
    int iter = 0;

    cout << "Bisect Method" << endl;

    while (end - start > eps)
    {
        ++iter;
        x = (start + end) / 2;
        if (f(start) * f(x) < 0 && f(x) * f(end) < 0 || f(start) * f(x) > 0 && f(x) * f(end) > 0)
        {
            cout << "Error in bisect method: even roots" << endl;
            return;
        }

        if (f(start) * f(x) < 0)
            end = x;
        else if (f(end) * f(x) < 0)
            start = x;
        else
            break;
    }

    cout << "Length of last interval: ";
    print(end - start);

    cout << "Root: ";
    print(x);

    cout << "Iter count: " << iter << endl;

    cout << "f(x): ";
    print(fabsl(f(x)));
}

void newthon_method(long double A, long double B, long double eps, int max_iter, long double df_eps)
{
    long double x = (A + B) / 2;
    long double x0 = x;
    int iter = 0;

    cout << "Newthon Method" << endl;

    while ((fabsl(x - x0) > eps || iter == 0) && iter < max_iter)
    {

        ++iter;
        x0 = x;

        if (fabsl(df(x0)) < df_eps)
        {
            cout << "Error in newthon method, df(x0) == " << fabs(df(x0)) << ", at step: " << iter << endl;
            return;
        }

        x = x0 - (f(x0) / df(x0));
    }

    if (fabsl(x - x0) > eps)
    {
        cout << "Newthon method has maximum iterations: " << max_iter << endl;

        cout << "Root: ";
        print(x);

        cout << "Last transform: ";
        print(fabsl(x - x0));

        cout << "|f(x)|: ";
        print(fabsl(f(x)));

        return;
    }

    cout << "Newthon method complited at: " << iter << " steps" << endl;

    cout << "Root: ";
    print(x);

    cout << "Last transform: ";
    print(fabsl(x - x0));

    cout << "f(x): ";
    print(fabsl(f(x)));
}

void advanced_newthon_method(long double A, long double B, long double eps, int max_iter,
                             long double df_eps, int m)
{
    long double x = (A + B) / 2;
    long double x0 = x;
    int iter = 0;

    cout << "Advanced Newthon Method" << endl;

    while ((fabsl(x - x0) > eps || iter == 0) && iter < max_iter)
    {

        ++iter;
        x0 = x;

        if (fabs(df(x0)) < df_eps)
        {
            cout << "Error in adv. newthon method, df(x0) == " << fabs(df(x0)) << ", at step: " << iter << endl;
            return;
        }

        x = x0 - m * (f(x0) / df(x0));
    }

    if (fabs(x - x0) > eps)
    {
        cout << "Advanced Newthon method has maximum iterations: " << max_iter << endl;

        cout << "Root: ";
        print(x);

        cout << "Last transform: ";
        print(fabsl(x - x0));

        cout << "|f(x)|: ";
        print(fabsl(f(x)));

        return;
    }

    cout << "Advanced Newthon method complited at: " << iter << " steps" << endl;

    cout << "Root: ";
    print(x);

    cout << "Last transform: ";
    print(fabsl(x - x0));

    cout << "f(x): ";
    print(fabsl(f(x)));
}

void secant_method(long double A, long double B, long double eps, int max_iter, long double df_eps)
{
    long double x0 = A, x1 = B, x2;

    cout << "Secant Method" << endl;
    int iter = 0;

    for (int i = 1; i <= max_iter; ++i)
    {
        long double f0 = f(x0), f1 = f(x1);

        if (fabsl(f1 - f0) < df_eps)
        {
            cout << "|f1 - f0| is to small: " << fabsl(f1 - f0) << endl;
            return;
        }

        x2 = x1 - (f1 / (f1 - f0)) * (x1 - x0);

        if (fabs(x2 - x1) < eps)
        {
            iter = i;
            break;
        }

        x0 = x1;
        x1 = x2;
    }

    if (iter == 0)
    {
        cout << "Secant method has max_iter steps: " << max_iter << endl;
        cout << "Root: ";
        print(x2);

        cout << "Last transform: ";
        print(fabsl(x2 - x1));

        cout << "|f(x)|: ";
        print(fabsl(f(x2)));
        return;
    }

    cout << "Method complete after: " << iter << " steps" << endl;

    cout << "Root: ";
    print(x2);

    cout << "Last transform: ";
    print(fabsl(x2 - x1));

    cout << "|f(x)|: ";
    print(fabsl(f(x2)));
}

int main()
{
    long double eps, A, B;
    int N;

    cout << "Enter A: ";
    cin >> A;

    cout << "Enter B: ";
    cin >> B;

    string s = "yes";
    vector<pair<long double, long double>> intervals;

    while (s != "no")
    {
        cout << "Enter N: ";
        cin >> N;
        intervals = separate_roots(A, B, N);
        cout << "Итоговое разбиенеие с шагом: " << (B - A) / N << endl;

        for (auto &p : intervals)
        {
            cout << "[" << p.first << "; " << p.second << "]" << endl;
        }

        cout << endl;
        cout << "Нужно ли новое N? ";
        cin >> s;
    }

    int newthon_max_iter = 200, secant_max_iter = 300;
    long double df_eps = 1e-15L;
    s = "yes";

    while (s != "no")
    {
        cout << "Enter eps: ";
        cin >> eps;

        cout << "Roots" << endl;

        for (auto &interval : intervals)
        {
            cout << endl;
            cout << "Current roots interval: [" << interval.first << "; " << interval.second << "]" << endl;

            cout << endl;
            bisect_method(interval.first, interval.second, eps);

            cout << endl;
            newthon_method(interval.first, interval.second, eps, newthon_max_iter, df_eps);

            cout << endl;
            secant_method(interval.first, interval.second, eps, secant_max_iter, df_eps);
        }

        cout << endl;
        cout << "Нужен ли новый eps: ";
        cin >> s;
    }

    return 0;
}