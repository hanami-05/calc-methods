#include <iostream>
#include <cmath>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

long double r;
long double ro;

void print(long double a)
{
    //
}

long double f(long double d)
{
    return M_PI / 3 * (d * d * d - 3 * d * d * r + 4 * r * r * r * ro);
}

long double df(long double d)
{
    return M_PI * (d * d - 6 * r * d);
}

vector<pair<long double, long double>> separate_roots(long double A, long double B, int N)
{
    vector<pair<long double, long double>> res;

    long double h = (B - A) / N;
    long double start = A, end;

    for (int i = 0; i < N; ++i)
    {
        end = start + h;

        if (f(start) * f(end) < 0)
            res.push_back({start, end});

        else if (f(end) == 0)
            res.push_back({end, end});

        else if (f(start) == 0 && i == 0)
            res.push_back({end, end});
    }

    return res;
}

long double newthon_method(long double A, long double B, long double eps, int max_iter, long double df_eps)
{
    long double x = (A + B) / 2;
    long double x0 = x;
    int iter = 0;

    while ((fabsl(x - x0) > eps || iter == 0) && iter < max_iter)
    {

        ++iter;
        x0 = x;

        if (fabsl(df(x0)) < df_eps)
        {
            cout << "Error in newthon method, df(x0) == " << fabs(df(x0)) << ", at step: " << iter << endl;
            return -1;
        }

        x = x0 - (f(x0) / df(x0));
    }

    /*if (fabsl(x - x0) > eps)
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
    print(fabsl(f(x)));*/

    return x;
}

struct SDPair
{
    string s;
    long double p;
};

int main()
{
    vector<SDPair> ro_data =
        {
            {"Пробка", 0.25},
            {"Бамбук", 0.4},
            {"Сосна", 0.5},
            {"Кедр", 0.55},
            {"Дуб", 0.7},
            {"Бук", 0.75},
            {"Красное дерево", 0.8},
            {"Тиковое дерево", 0.85},
            {"Парафин", 0.9},
            {"Лёд", 0.92},
            {"Полиэтилен", 0.92},
            {"Пчелиный воск", 0.95}};

    vector<SDPair> res;

    cout << "Введите радиус шара в см: ";
    cin >> r;
    r /= 100;

    cout << "Введите погрешность: ";
    long double eps;
    cin >> eps;

    long double A = 0, B = 2 * r;

    int max_iter = 200;
    long double df_eps = 1e-12L;

    for (auto &p : ro_data)
    {
        ro = p.p;
        auto curr = newthon_method(A, B, eps, max_iter, df_eps);
        res.push_back({p.s, curr});
    }

    cout << endl;

    for (auto &p : res)
    {
        cout << p.s << " - ";
        printf("%.2Lf", 100 * p.p);
        cout << endl;
    }
    return 0;
}