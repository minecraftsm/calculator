#include <iostream>
#include <cmath>
using namespace std;

double differentiate(double x, double h, double (*func)(double));
double integrate(double a, double b, double (*func)(double), int n);
double findRoot(double (*func)(double), double a, double b, double tol);
void calculateNthRoot(double a, double b);
double customFunction(double x);

int main() {
    double a;
    string c;
    cout << "������Ҫ�����һ���� (a): ";
    cin >> a;
    cout << "������������� (+, -, *, /, log, sin, cos, tan, diff(΢��), integrate(����), ^, sqrt(�η���), findroot(�󷽳̸�)):";
    cin >> c;

    double answer;

    if (c == "+") {
        cout << "��������һ���� (b): ";
        double b;
        cin >> b;
        answer = a + b;
    } else if (c == "-") {
        cout << "��������һ���� (b): ";
        double b;
        cin >> b;
        answer = a - b;
    } else if (c == "*") {
        cout << "��������һ���� (b): ";
        double b;
        cin >> b;
        answer = a * b;
    } else if (c == "/") {
        cout << "��������һ���� (b): ";
        double b;
        cin >> b;
        if (b == 0) {
            cout << "��������Ϊ��!";
            return 1;
        } else {
            answer = a / b;
        }
    } else if (c == "log") {
        cout << "��ѡ����������� (�Զ���(����a) �� e): ";
        string baseChoice;
        cin >> baseChoice;
        double base = 0.0;
        if (baseChoice == "a") {
            cout << "���������: ";
            cin >> base;
            if (a <= 0 || base <= 0 || base == 1) {
                cout << "�������������Ч!";
                return 1;
            }
        } else if (baseChoice == "e") {
            base = exp(1.0);
            if (a <= 0) {
                cout << "�������������Ч!";
                return 1;
            }
        } else {
            cout << "��Ч�ĵ���ѡ��!";
            return 1;
        }
        answer = log(a) / log(base);
    } else if (c == "sin") {
        answer = sin(a);
    } else if (c == "cos") {
        answer = cos(a);
    } else if (c == "tan") {
        if (cos(a) == 0) {
            cout << "tan�����Ĳ�����Ч!";
            return 1;
        } else {
            answer = tan(a);
        }
    } else if (c == "diff") {
        cout << "����������㵼���ĵ� x: ";
        double x;
        cin >> x;
        cout << "����΢�ֲ��� (h): ";
        double h;
        cin >> h;
        answer = differentiate(x, h, customFunction);
    } else if (c == "integrate") {
        cout << "����������� (a): ";
        double a;
        cin >> a;
        cout << "����������� (b): ";
        double b;
        cin >> b;
        cout << "������������� (n): ";
        int n;
        cin >> n;
        answer = integrate(a, b, customFunction, n);
    } else if (c == "findroot") {
        cout << "������Ҹ������� (a): ";
        double a;
        cin >> a;
        cout << "������Ҹ������� (b): ";
        double b;
        cin >> b;
        double root = findRoot(customFunction, a, b, 1e-6);
        cout << "�ҵ��ĸ���: " << root << endl;
    } else if (c == "^") {
        cout << "������ָ�� (b): ";
        double b;
        cin >> b;
        answer = pow(a, b);
    } else if (c == "sqrt" || c == "cbrt") {
        cout << "�������ݴ���: ";
        double b;
        cin >> b;
        calculateNthRoot(a, b);
    } else {
        cout << "��������Ч�������!";
        return 1;
    }

    cout << "���: " << answer << endl;
    cout << "��лʹ��! ���ߣ������" << endl;
    char d;
    cout << "������������رճ���...";
    cin >> d;
    return 0;
}

void calculateNthRoot(double a, double b) {
    double nthRoot = 0.0;
    if (a < 0 && b == 2) {
        cout << "���ܼ��㸺����ƽ����!" << endl;
    } else if (a < 0 && b == 3) {
        cout << "���ܼ��㸺����������!" << endl;
    } else {
        nthRoot = pow(a, 1.0 / b);
        cout << "������: " << nthRoot << endl;
    }
}

double differentiate(double x, double h, double (*func)(double)) {
    return (func(x + h) - func(x - h)) / (2 * h);
}

double integrate(double a, double b, double (*func)(double), int n) {
    double h = (b - a) / n;
    double integral = (func(a) + func(b)) / 2;
    for (int i = 1; i < n; i++) {
        integral += func(a + i * h);
    }
    return integral * h;
}

double findRoot(double (*func)(double), double a, double b, double tol) {
    double fa = func(a);
    double fb = func(b);

    if (fa * fb > 0) {
        cout << "�����ܲ����ڻ�����ָ���������ж������" << endl;
        return NAN;
    }

    while (fabs(b - a) > tol) {
        double mid = (a + b) / 2;
        double fmid = func(mid);

        if (fmid == 0) {
            return mid;
        } else if (fa * fmid < 0) {
            b = mid;
            fb = fmid;
        } else {
            a = mid;
            fa = fmid;
        }
    }

    return (a + b) / 2;
}

double customFunction(double x) {
    return x * x;
}
