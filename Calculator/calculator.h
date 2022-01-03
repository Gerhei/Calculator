#ifndef CALCULATOR_H
#define CALCULATOR_H


#pragma once
#include<string>
#include<vector>
#include<map>
#include<stack>
#include<algorithm>
#include<cmath>
#include<iostream>
class Calculator
{
public:
    //для добавления новой функции добавить ее имя в контейнер и реализацию в функцию-вычисления
    const std::vector<std::string> Numbers = { "7","8","9","4","5","6","1","2","3","0" };
    //name and priority
    const std::map<std::string, int> BinaryOperations =
    {
        {"^",3},
        {"/",2},
        {"*",2},
        {"-",1},
        {"+",1}
    };
    std::string warning="";
    const std::vector<std::string> UnaryOperations = { "sin","cos","tg","sqrt","—"};
    std::string calculated(std::string input);//in Reverse Polish notation

private:
    std::stack<std::string> ReverseNotation(std::string input);//Reverse Polish notation
    //функции вычисления
    std::string UnaryCalculated(std::string operation, std::string operand);
    std::string BinaryCalculated(std::string operation, std::string LeftOperand, std::string RightOperand);

    bool isDigit(char c) { return '0' <= c && c <= '9'; }
    bool isChar(char c) { return 'a' <= c && c <= 'z'; }
    bool isBinOper(std::string s) { return BinaryOperations.find(s) != BinaryOperations.end(); }
    bool isUnaryOper(std::string s)
    {
        auto it = std::find(UnaryOperations.begin(), UnaryOperations.end(), s);
        return it != UnaryOperations.end();
    }

    bool comparePrior(std::string oper1, std::string oper2)//isLess
    {
        auto it1 = BinaryOperations.find(oper1);
        auto it2 = BinaryOperations.find(oper2);
        if (it1 != BinaryOperations.end() && it2 != BinaryOperations.end())
        {
            if (it1->second <= it2->second)
            {
                return true;
            }
            else return false;
        }
        else return false;
    }
};

#endif // CALCULATOR_H
