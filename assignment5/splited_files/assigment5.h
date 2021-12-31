#ifndef _ASSIGNMENT5_H_
#define _ASSIGNMENT5_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
struct StackNode
{
    T data; // 제곱(**) 연산자의 경우에는 2자리라서 char이 아닌 string으로 받음
    struct StackNode* pLink;
};

template <typename T>
struct LinkedStack
{
    int currentElementCount;
    StackNode<T>* pTopElement;
};

template <typename T>
class Stack {
private :
    LinkedStack<T> *stack;
public :
    Stack();
    ~Stack();
    bool            pushLS(T element);
    StackNode<T>*      popLS();
    StackNode<T>*      peekLS();
    void            displayLS();
    bool            isLinkedStackEmpty();
    bool            isLinkedStackFull();
};

// ================= stack.cc =====================
template <> // 탬플릿 함수 선언 시 이렇게 해줘야하는 것 같다...
Stack<int>::Stack();
template <>
bool    Stack<int>::pushLS(int element);
template <>
StackNode<int>* Stack<int>::popLS();
template <>
StackNode<int>* Stack<int>::peekLS();
template <>
bool    Stack<int>::isLinkedStackEmpty();
template <>
bool    Stack<int>::isLinkedStackFull();

template <>
Stack<string>::Stack();
template <>
bool    Stack<string>::pushLS(string element);
template <>
StackNode<string>* Stack<string>::popLS();
template <>
StackNode<string>* Stack<string>::peekLS();
template <>
bool    Stack<string>::isLinkedStackEmpty();
template <>
bool    Stack<string>::isLinkedStackFull();

// =============== check_input.cc =================
bool    is_operator(char c);
bool    check_bracket_matching(string input);
bool    check_inputFormat(string input);
int     op_number(string a);

// ============ convert_to_postfix.cc ==============
void    popAll(Stack<string> *a, vector<string> *output);
void    push_operand(Stack<string> *a, char op, vector<string> *output);
void    push_OpLeft(Stack<string> *a, vector<string> *output);
bool    process_postfix(Stack<string> *a, string *input, vector<string> *output);

// ================ calcuate.cc ====================
void  calculate(Stack<int> *a, vector<string> output);
void  calculate_postfix(Stack<int> *a, vector<string> output);


# endif