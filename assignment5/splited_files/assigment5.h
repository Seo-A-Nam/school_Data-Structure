#ifndef _ASSIGNMENT5_H_
#define _ASSIGNMENT5_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct StackNode
{
    string data; // 제곱(**) 연산자의 경우에는 2자리라서 char이 아닌 string으로 받음
    struct StackNode* pLink;
};

struct LinkedStack
{
    int currentElementCount;
    StackNode* pTopElement;
};

class Stack {
private :
    LinkedStack *stack;
public :
    Stack();
    ~Stack();
    bool            pushLS(string element);
    StackNode*      popLS();
    StackNode*      peekLS();
    void            displayLS();
    bool            isLinkedStackEmpty();
    bool            isLinkedStackFull();
};

// =============== check_input.cc =================
bool    is_operator(char c);
bool    check_bracket_matching(string input);
bool    check_inputFormat(string input);
int     op_number(string a);

// ============ convert_to_postfix.cc ==============
void    popAll(Stack *a, vector<string> *output);
void    push_operand(Stack *a, char op, vector<string> *output);
void    push_OpLeft(Stack *a, vector<string> *output);
bool    process_postfix(Stack *a, string *input, vector<string> *output);

// ================ calcuate.cc ====================
void  calculate(Stack *a, vector<string> output);
void  calculate_postfix(Stack *a, vector<string> output);


# endif