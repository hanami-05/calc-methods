#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

long double f(long double x)
{
    return sin(x) - (x * x) / 2;
}

vector<long double> precompute_d(vector<pair<long double, long double>> &dots)
{
    int m = dots.size();
    vector<long double> res(m, 0);

    for (int i = 0; i < m; ++i)
    {
        long double p = 1.0L;
        for (int j = 0; j < m; ++j)
        {
            if (j == i)
                continue;
            p *= (dots[i].first - dots[j].first);
        }
        res[i] = p;
    }

    return res;
}

long double m_zero = 1e-18;

long double lagrange(vector<pair<long double, long double>> &dots, long double x, vector<long double> &d)
{
    int n = dots.size();
    vector<long double> vals(n, 0);
    long double pref = 1.0L;

    for (int i = 0; i < n; ++i)
    {
        if (fabsl(x - dots[i].first) < m_zero)
            return dots[i].second;
        vals[i] = pref;
        pref *= (x - dots[i].first);
    }

    pref = 1.0L;

    for (int i = n - 1; i > -1; --i)
    {
        vals[i] *= pref;
        pref *= (x - dots[i].first);
    }

    long double res = 0.0L;

    for (int i = 0; i < n; ++i)
        res += dots[i].second * (vals[i] / d[i]);

    return res;
}

vector<long double> div_diff(vector<pair<long double, long double>> &dots)
{
    int n = dots.size();
    vector<vector<long double>> D(n, vector<long double>(n));

    for (int i = 0; i < n; ++i)
        D[i][0] = dots[i].second;

    for (int j = 1; j < n; ++j)
        for (int i = 0; i < n - j; ++i)
            D[i][j] = (D[i + 1][j - 1] - D[i][j - 1]) / (dots[i + j].first - dots[i].first);
    vector<long double> coeff(n);

    for (int i = 0; i < n; ++i)
        coeff[i] = D[0][i];

    return coeff;
}

long double newton(vector<pair<long double, long double>> &dots, vector<long double> &coeff, long double x)
{
    int n = dots.size();
    long double res = coeff[n - 1];

    for (int i = n - 2; i > -1; --i)
        res = res * (x - dots[i].first) + coeff[i];

    return res;
}

vector<pair<long double, long double>> n_closest(vector<pair<long double, long double>> &dots, int n, long double x)
{
    int L = 0, R = dots.size() - n + 1;

    while (R - L > 1)
    {
        int m = (R + L) / 2;

        if (x - dots[m].first >= dots[m + n - 1].first - x)
        {
            L = m;
        }
        else
            R = m;
    }

    return vector<pair<long double, long double>>(dots.begin() + L, dots.begin() + L + n);
}

vector<pair<long double, long double>> n_closest_dots(vector<pair<long double, long double>> &dots, int count, long double x)
{
    vector<pair<long double, int>> t;
    for (int i = 0; i < dots.size(); ++i)
        t.push_back({fabsl(x - dots[i].first), i});
    sort(t.begin(), t.end());
    vector<pair<long double, long double>> res(count);

    for (int i = 0; i < count; ++i)
        res[i] = dots[t[i].second];

    return res;
}

int main()
{
    cout << setprecision(15);

    cout << "Задание 2: Построение интерполяционного многочлена" << '\n';

    int m;
    cout << "Введите значение m + 1: ";
    cin >> m;
    m--;

    long double A, B;
    cout << "Введите A: ";
    cin >> A;

    cout << "Введите B: ";
    cin >> B;

    int is_random;

    cout << "Введите 0 для выбора точек, равноудаленных друг от друга, введите 1 для выбора рандомных значений точек: ";
    cin >> is_random;

    vector<pair<long double, long double>> dots;

    if (is_random)
    {
        mt19937_64 gen(random_device{}());
        uniform_real_distribution<long double> dist(A, B);

        for (int i = 0; i < m + 1; ++i)
        {
            long double r = dist(gen);
            dots.push_back({r, f(r)});
        }

        sort(dots.begin(), dots.end());
    }
    else
    {
        long double h = (B - A) / m;
        for (int i = 0; i < m + 1; ++i)
        {
            long double p = A + h * i;
            dots.push_back({p, f(p)});
        }
    }

    cout << "Таблица значений функции: " << '\n';

    for (int i = 0; i < m + 1; ++i)
        cout << dots[i].first << " | " << dots[i].second << '\n';

    string s = "да";

    while (s == "да")
    {
        long double x;
        int n;
        cout << "Введите значение x: ";
        cin >> x;

        cout << "Введите максимальную степень интерполяционного многочлена (не больше " << m << "): ";
        cin >> n;

        while (n > m)
        {
            cout << "Неподходящее значение n!" << '\n';
            cout << "Введите максимальную степень интерполяционного многочлена (не больше " << m << "): ";
            cin >> n;
        }
        cout << '\n';

        vector<pair<long double, long double>> closest_dots = n_closest_dots(dots, n + 1, x);
        cout << n + 1 << " ближайших к " << x << " точек из таблицы" << '\n';

        for (int i = 0; i < n + 1; ++i)
            cout << closest_dots[i].first << " | " << closest_dots[i].second << '\n';

        vector<long double> d = precompute_d(closest_dots);
        long double y = lagrange(closest_dots, x, d);
        cout << "Результат интерполяции по Лагранжу: " << y << '\n';
        cout << "Фактическая погрешность: " << fabsl(f(x) - y) << '\n';

        cout << '\n';

        vector<long double> coeff = div_diff(closest_dots);
        y = newton(closest_dots, coeff, x);

        cout << "Результат интерполяции по Ньютону: " << y << '\n';
        cout << "Фактическая погрешность: " << fabsl(f(x) - y) << '\n';

        cout << "Хотите ввести новые значения x и n? ";
        cin >> s;
    }

    return 0;
}