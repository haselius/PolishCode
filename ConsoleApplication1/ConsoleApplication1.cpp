#include <iostream>
#include <string>
#include <vector>
#include <stack>

int SimvolWeight(char c) {
    int p;
    switch (c)
    {
    case '(':
        p = 0;
    case ')':
        p = 1;
    case '+':
        p = 5;
        break;
    case '-':
        p = 5;
        break;
    case '*':
        p = 4;
        break;
    case '/':
        p = 4;
        break;
    case '^':
        p = 2;
        break;
    default:
        break;
    }
    return p;
}

bool IsOperator(char c) {
    return SimvolWeight(c) >= 0; // проверка, является ли символ оператором
}

double ApplyOperator(char op, double operand1, double operand2) {
    switch (op) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    case '^':
        return std::pow(operand1, operand2);
    default:
        return 0; // в случае ошибки вернуть 0
    }
}

double EvaluateReversePolish(const std::string& expression) {
    std::stack<double> stk;
    for (char c : expression) {
        if (isdigit(c)) {
            stk.push(c - '0'); // символы цифр преобразуются в числа
        }
        else if (IsOperator(c)) {
            if (stk.size() < 2) {
                // ошибка: недостаточно операндов в стеке
                std::cerr << "Error: Insufficient operands for operator " << c << std::endl;
                return 0;
            }
            double operand2 = stk.top();
            stk.pop();
            double operand1 = stk.top();
            stk.pop();
            double result = ApplyOperator(c, operand1, operand2);
            stk.push(result);
        }
        else {
            // игнорировать пробелы и другие символы
            continue;
        }
    }
    if (stk.size() != 1) {
        // ошибка: неверное количество операндов
        std::cerr << "Error: Incorrect number of operands" << std::endl;
        return 0;
    }
    return stk.top(); // результат вычисления на вершине стека
}

int main() {
    std::vector<char> stk;
    std::cout << "Enter equation" << std::endl;
    std::string eq, out, tmp;
    std::cin >> eq;
    for (int i = 0; i < eq.length(); i++) {
        //std::cout << eq[i] << "\n";
        if (!isdigit(eq[i])) {
            if (stk.empty()) {
                stk.push_back(eq[i]);
            }
            else if ((SimvolWeight(eq[i]) >= SimvolWeight(stk.front()))) {
                if (eq[i] == ')') {
                    while (stk.back() != '(') {
                        out += stk.back();
                        stk.pop_back();
                    }
                    stk.pop_back();
                }
                else {
                    stk.push_back(eq[i]);
                }
            }
            else {
                while (!stk.empty()) {
                    out += stk.back();
                    stk.pop_back();
                }
                stk.push_back(eq[i]);
            }
        }
        else {
            out += eq[i];
            std::cout << out << std::endl;
        }
    }
    while (!stk.empty()) {
        out += stk.back();
        stk.pop_back();
    }
    std::cout << out << std::endl;


    double result = EvaluateReversePolish(out);
    std::cout << "Result: " << result << std::endl;

    return 0;
}