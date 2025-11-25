#include <bits/stdc++.h>
using namespace std;

using ld = long double;

ld f1(ld x) 
{
    return 2 * (x * x) - 6 * x + 5;
}

ld f2(ld x) 
{
    return 0.25 * (x * x * x) + 6 * x * x + 4;
}

ld f3(ld x) 
{
    return 2 * sin(x) - cos(4 * x) + 0.2 * (x * x);
}


ld f4(ld x) 
{
    return exp(3 * x - 5) + 3;
}

ld df1(ld x) 
{
    return 4 * x - 6;
}

ld df2(ld x) 
{
    return 0.75 * (x * x) + 12 * x;
}

ld df3(ld x) 
{
    return 2 * cos(x) + 4 * sin(4 * x) + 0.4 * x;
}

ld df4(ld x) 
{
    return 3 * exp(3 * x - 5);
}

ld ddf1(ld x) 
{
    return 4;
}

ld ddf2(ld x) 
{
    return 1.5 * x + 12;
}

ld ddf3(ld x) 
{
    return -2 * sin(x) + 16 * cos(4 * x) + 0.4;
}

ld ddf4(ld x) 
{
    return 9 * exp(3 * x -5);
}

ld computedf11(ld y1, ld y2, ld h) 
{
    return (y1 - y2) / (2 * h);
}

ld computedf12(ld y1, ld y2, ld y3, ld h) 
{
    return (-3 * y1 + 4 * y2 - y3) / (2 * h);
}

ld computedf13(ld y1, ld y2, ld y3, ld h)
{
    return -1 * computedf12(y1, y2, y3, h);
}

ld computedf21(ld y1, ld y2, ld y3, ld h) 
{
    return (y1 - 2 * y2 + y3) / (h * h);
}

ld computedf22(ld y1, ld y2, ld y3, ld y4, ld h) {
    return (2 * y1 - 5 * y2 + 4 * y3 - y4) / (h * h);
}

ld computedf14(ld y1, ld y2, ld y3, ld y4, ld y5, ld h) {
    return (-25 * y1 + 48 * y2 - 36 * y3 + 16 * y4 - 3 * y5) / (12 * h);
}

ld computedf15(ld y1, ld y2, ld y3, ld y4, ld y5, ld h) {
    return (-3 * y1 - 10 * y2 + 18 * y3 - 6 * y4 + y5) / (12 * h);
}

ld computedf16(ld y1, ld y2, ld y3, ld y4, ld h) {
    return (y1 - 8 * y2 + 8 * y3 - y4) / (12 * h);
}

ld computedf17(ld y1, ld y2, ld y3, ld y4, ld y5, ld h) {
    return (3 * y1 + 10 * y2 - 18 * y3 + 6 * y4 - y5) / (12 * h);
}

ld computedf18(ld y1, ld y2, ld y3, ld y4, ld y5, ld h) {
    return (25 * y1 - 48 * y2 + 36 * y3 - 16 * y4 + 3 * y5) / (12 * h);
}

int main() 
{
    cout << fixed << setprecision(15) << '\n';
    
    bool isActive = true;

    while (isActive) {
        cout << "Выберите функцию" << '\n' << '\n';

        cout << "1. f_1(x) = 2x^2 - 6x + 5" << '\n';
        cout << "2. f_2(x) = 0.25x^3 + 6x + 4" << '\n';
        cout << "3. f_3(x) = 2sin(x) + cos(4x) + 0.2x^2" << '\n';
        cout << "4. f_4(x) = exp(3x - 5) + 3" << '\n';

        cout << "Номер функции: ";
        int num;
        cin >> num;
        
        while (num < 1 || num > 4) {
            cout << "Некорректно введен номер: введите число от 1 до 4" << '\n';
            cout << "Номер функции: ";
            cin >> num;
        }

        function<ld(ld)> f, df, ddf;

        if (num == 1) {
            f = f1;
            df = df1;
            ddf = ddf1;
        }

        else if (num == 2) {
            f = f2;
            df = df2;
            ddf = ddf2;
        }

        else if (num == 3) {
            f = f3;
            df = df3;
            ddf = ddf3;
        }

        else {
            f = f4;
            df = df4;
            ddf = ddf4;
        }

        cout << '\n' << "Введите количество точек m: ";
        int m;
        cin >> m;

        while (m <= 0) {
            cout << "Количество точек должно быть положительным целым числом" << '\n';
            cout << "Введите количество точек снова: ";
            cin >> m;
        }

        cout << '\n' << "Введите начальную (первую) точку: ";
        ld x0;
        cin >> x0;

        cout << '\n' << "Введите шаг, на который отдаляется следующая точка от предыдущей: ";
        ld h;
        cin >> h;

        cout << '\n' << "\t\t\t\t\t\t\t\t\tТаблица сравнения" << '\n'; 
        
        cout << '\n' << "1 столбец - производная 1 порядка с погрешностью порядка O(h^2)" << '\n';
        cout << "2 столбец - производная 1 порядка с погрешностью порядка O(h^4)" << '\n';
        cout << "3 столбец - производная 2 порядка с погрешностью порядка O(h^2)" << '\n';
        cout << "4 столбец - производная 1 порядка из таблицы" << '\n';
        cout << "5 столбец - производная 2 порядка из таблицы" << '\n';
        cout << '\n';

        ld norm1 = 0, norm2 = 0, norm3 = 0;
        int dot1 = 0, dot2 = 0, dot3 = 0;

        for (int i = 0; i < m; ++i) {
            ld x = x0 + h * i;
            cout << i + 1 << ") Точка: " << x << '\t';
            ld d1, d2, dd, dt, ddt;

            if (i == 0)
                d1 = computedf12(f(x), f(x + h), f(x + 2 * h), h);
            else if (i == m - 1)
                d1 = computedf13(f(x), f(x - h), f(x - 2 * h), h);
            else
                d1 = computedf11(f(x + h), f(x - h), h);
            
            if (i == 0)
                d2 = computedf14(f(x), f(x + h), f(x + 2 * h), f(x + 3 * h), f(x + 4 * h), h);
            else if (i == 1) 
                d2 = computedf15(f(x - h), f(x), f(x + h), f(x + 2 * h), f(x + 3 * h), h);
            else if (i == m - 2)
                d2 = computedf17(f(x + h), f(x), f(x - h), f(x - 2 * h), f(x - 3 * h), h);
            else if (i == m - 1)
                d2 = computedf18(f(x), f(x - h), f(x - 2 * h), f(x - 3 * h), f(x - 4 * h), h);
            else
                d2 = computedf16(f(x - 2 * h), f(x - h), f(x + h), f(x + 2 * h), h);
            
            if (i == 0)
                dd = computedf22(f(x), f(x + h), f(x + 2 * h), f(x + 3 * h), h);
            else if (i == m - 1)
                dd = computedf22(f(x), f(x - h), f(x - 2 * h), f(x - 3 * h), h);
            else
                dd = computedf21(f(x + h), f(x), f(x - h), h);
            
            dt = df(x);
            ddt = ddf(x);
            cout << d1 << '\t' << d2 << '\t' << dd << '\t' << dt << '\t' << ddt << '\t';
            cout << '\n';

            if (norm1 < fabsl(d1 - dt)) {
                norm1 = fabsl(d1 - dt);
                dot1 = i;
            }
            
            if (norm2 < fabsl(d2 - dt)) {
                norm2 = fabsl(d2 - dt);
                dot2 = i;
            }
            
            if (norm3 < fabsl(dd - ddt)) {
                norm3 = fabsl(dd - ddt);
                dot3 = i;
            }
        }

        cout << '\n' << "Чебышевская норма для погрешности по всему множеству точек для df с O(h^2): " << norm1 << '\t' << "Точка, в которой достигается норма: " << x0 + h * dot1 << '\n';
        cout << "Чебышевская норма для погрешности по всему множеству точек для df с O(h^4): " << norm2 << '\t' << "Точка, в которой достигается норма: " << x0 + h * dot2 << '\n';
        cout << "Чебышевская норма для погрешности по всему множеству точек для ddf с O(h^2): " << norm3 << '\t' << "Точка, в которой достигается норма: " << x0 + h * dot3 << '\n';
        cout << setprecision(30);
        cout << '\n' << "h^2: " << h * h << '\t' << '\t' << "h^4: " << h * h * h * h << '\n';

        cout  << '\n' << "Будете вводить данные заново: ";
        string s;
        cin >> s;
        if (s != "да")
            isActive = false;
    }

    return 0;
}