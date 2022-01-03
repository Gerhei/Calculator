#include "calculator.h"
std::stack<std::string> Calculator::ReverseNotation(std::string input)
{
    std::stack<std::string> output;
    std::stack<std::string> stack;//for operation

    std::string temp = "";
    for (int i = 0; i < input.length() && warning==""; i++, temp = "")
    {
        if (input[i] == ' ') continue;
        if(input[i] == '.') warning="Лишние точки.";
        if (isDigit(input[i]))
        {
            int count_point = 0;
            while (isDigit(input[i]) || (input[i]=='.' && count_point<=1))//или постфиксной функцией
            {
                if (input[i] == '.') count_point++;
                if (count_point > 1) warning="Лишние точки.";//синтаксическая ошибка

                temp += input[i];
                i++;
            }
            output.push(temp);
            i--;
            continue;
        }

        if (isChar(input[i]))
        {
            while (isChar(input[i]))//для префиксных функций
            {
                temp += input[i];
                i++;
            }
            i--;
        }
        if (input[i] == '-')//проверяем унарный минус:
        {
            //заменяем обычный минус на унарный, если
            if (i == 0) temp = "—";//начало строки
            else {
                std::string s = "";
                s = input[i - 1];
                //скобка или другая операция перед минусом
                if (input[i - 1] == '(' || isChar(input[i - 1]) || isBinOper(s))
                    temp = "—";
            }
        }
        if (isUnaryOper(temp))
        {
            stack.push(temp);
            continue;
        }

        temp += input[i];
        if (temp == "(")
        {
            stack.push(temp);
            continue;
        }
        if (temp == ")")
        {
            if(!stack.empty())
                while (stack.top() != "(")
                {
                    if(stack.empty())
                    {
                        warning="Отсутсвует (.";
                        continue;
                    }
                    output.push(stack.top());
                    stack.pop();
                }
            else {warning="Отсутсвует (."; continue;}
            stack.pop();
            continue;
        }
        if (isBinOper(temp))
        {
            if (stack.empty())
            {
                stack.push(temp);
                continue;
            }
            while (isUnaryOper(stack.top()) || comparePrior(temp, stack.top()))
            {
                output.push(stack.top());
                stack.pop();
                if (stack.empty()) break;
            }
            stack.push(temp);
        }
    }
    while (!stack.empty())
    {
        if(stack.top()=="(") warning="Отсутствует ).";
        output.push(stack.top());
        stack.pop();
    }
    return output;
}

std::string Calculator::calculated(std::string input)
{
    std::stack<std::string> stack = ReverseNotation(input);//for operand
    if(warning!="") return warning;
    std::stack<std::string> output;
    //reverse stack
    while (!stack.empty())
    {
        output.push(stack.top());
        stack.pop();
    }
    /*while (!output.empty())
    {
        std::cout << output.top() << "  ";
        output.pop();
    }*/
    while (!output.empty() && warning=="")
    {
        if (isUnaryOper(output.top()))
        {
            std::string oper = "";
            if (!stack.empty())
            {
                oper=stack.top();
                stack.pop();
            }
            stack.push(UnaryCalculated(output.top(), oper));
        }
        else if (isBinOper(output.top()))
        {
            std::string rightOper="";
            if (!stack.empty())
            {
                rightOper = stack.top();
                stack.pop();
            }

            std::string leftOper= "";
            if (!stack.empty())
            {
                leftOper = stack.top();
                stack.pop();
            }

            stack.push(BinaryCalculated(output.top(), leftOper, rightOper));
        }
        else{//number
            stack.push(output.top());
        }
        output.pop();
    }
    std::string result = "Неизвестный символ.";//неопознанный оператор, вложенные унарные операторы без аргумента
    if(!stack.empty())
    result = stack.top();
    else return result;

    //убираем ненужную дробь
    if(atoi(result.c_str())!=atof(result.c_str()))
    {
           while(result.back()=='0')
           {
               result.pop_back();
           }
           if(result.back()=='.') result.pop_back();
    } else result=std::to_string(atoi(result.c_str()));

    return result;
}

std::string Calculator::UnaryCalculated(std::string operation, std::string operand)
{
    if(operand=="")
    {
        warning="Отсутсвует аргумент в унарном операторе "+operation+'.';
        return operand;
    }
    double number = atof(operand.c_str());//преобразование к численному значению
    std::string result;
    if (operation == "sin")
    {
        result = std::to_string(sin(number));
    }
    if (operation == "cos")
    {
        result = std::to_string(cos(number));
    }
    if (operation == "tg")
    {
        result = std::to_string(tan(number));
    }
    if (operation == "sqrt")
    {
        if(number<0) warning="Корень из отрицательного числа.";
        result = std::to_string(sqrt(number));
    }
    if (operation == "—")//унарный минус
    {
        result = std::to_string(-number);
    }
    return result;
}

std::string Calculator::BinaryCalculated(std::string operation, std::string LeftOperand, std::string RightOperand)
{
    if (LeftOperand == "" || RightOperand == "")
    {
        double RightNumber = atof(RightOperand.c_str());
        warning ="Отсутствует операнд бинарной операции "+operation+'.';
        return std::to_string(RightNumber);
        //иначе синтаксическая ошибка
    }
    double LeftNumber = atof(LeftOperand.c_str());
    double RightNumber = atof(RightOperand.c_str());
    std::string result="";
    if (operation == "+")
    {
        result = std::to_string(LeftNumber + RightNumber);
    }
    if (operation == "-")
    {
        result = std::to_string(LeftNumber - RightNumber);
    }
    if (operation == "*")
    {
        result = std::to_string(LeftNumber * RightNumber);
    }
    if (operation == "/")
    {
        if(RightNumber==0) warning="Деление на ноль.";
        result = std::to_string(LeftNumber / RightNumber);
    }
    if (operation == "^")
    {
        result = std::to_string(pow(LeftNumber ,RightNumber));//order
    }
    return result;
}
