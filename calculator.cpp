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
    cout << "请输入要计算的一个数 (a): ";
    cin >> a;
    cout << "请输入操作符号 (+, -, *, /, log, sin, cos, tan, diff(微分), integrate(积分), ^, sqrt(次方根), findroot(求方程根)):";
    cin >> c;

    double answer;

    if (c == "+") {
        cout << "请输入另一个数 (b): ";
        double b;
        cin >> b;
        answer = a + b;
    } else if (c == "-") {
        cout << "请输入另一个数 (b): ";
        double b;
        cin >> b;
        answer = a - b;
    } else if (c == "*") {
        cout << "请输入另一个数 (b): ";
        double b;
        cin >> b;
        answer = a * b;
    } else if (c == "/") {
        cout << "请输入另一个数 (b): ";
        double b;
        cin >> b;
        if (b == 0) {
            cout << "除数不能为零!";
            return 1;
        } else {
            answer = a / b;
        }
    } else if (c == "log") {
        cout << "请选择底数操作数 (自定义(输入a) 或 e): ";
        string baseChoice;
        cin >> baseChoice;
        double base = 0.0;
        if (baseChoice == "a") {
            cout << "请输入底数: ";
            cin >> base;
            if (a <= 0 || base <= 0 || base == 1) {
                cout << "对数运算参数无效!";
                return 1;
            }
        } else if (baseChoice == "e") {
            base = exp(1.0);
            if (a <= 0) {
                cout << "对数运算参数无效!";
                return 1;
            }
        } else {
            cout << "无效的底数选择!";
            return 1;
        }
        answer = log(a) / log(base);
    } else if (c == "sin") {
        answer = sin(a);
    } else if (c == "cos") {
        answer = cos(a);
    } else if (c == "tan") {
        if (cos(a) == 0) {
            cout << "tan函数的参数无效!";
            return 1;
        } else {
            answer = tan(a);
        }
    } else if (c == "diff") {
        cout << "输入您想计算导数的点 x: ";
        double x;
        cin >> x;
        cout << "输入微分步长 (h): ";
        double h;
        cin >> h;
        answer = differentiate(x, h, customFunction);
    } else if (c == "integrate") {
        cout << "输入积分下限 (a): ";
        double a;
        cin >> a;
        cout << "输入积分上限 (b): ";
        double b;
        cin >> b;
        cout << "输入积分区间数 (n): ";
        int n;
        cin >> n;
        answer = integrate(a, b, customFunction, n);
    } else if (c == "findroot") {
        cout << "输入查找根的下限 (a): ";
        double a;
        cin >> a;
        cout << "输入查找根的上限 (b): ";
        double b;
        cin >> b;
        double root = findRoot(customFunction, a, b, 1e-6);
        cout << "找到的根是: " << root << endl;
    } else if (c == "^") {
        cout << "请输入指数 (b): ";
        double b;
        cin >> b;
        answer = pow(a, b);
    } else if (c == "sqrt" || c == "cbrt") {
        cout << "请输入幂次数: ";
        double b;
        cin >> b;
        calculateNthRoot(a, b);
    } else {
        cout << "请输入有效运算符号!";
        return 1;
    }

    cout << "结果: " << answer << endl;
    cout << "感谢使用! 作者：孙明昊" << endl;
    char d;
    cout << "请输入任意键关闭程序...";
    cin >> d;
    return 0;
}

void calculateNthRoot(double a, double b) {
    double nthRoot = 0.0;
    if (a < 0 && b == 2) {
        cout << "不能计算负数的平方根!" << endl;
    } else if (a < 0 && b == 3) {
        cout << "不能计算负数的立方根!" << endl;
    } else {
        nthRoot = pow(a, 1.0 / b);
        cout << "计算结果: " << nthRoot << endl;
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
        cout << "根可能不存在或者在指定区间内有多个根。" << endl;
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
