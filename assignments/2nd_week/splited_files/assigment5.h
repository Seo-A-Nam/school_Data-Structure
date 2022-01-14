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
    T data;
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

template <class T>
Stack<T>::Stack()
{
    this->stack = (LinkedStack<T>*)malloc(sizeof(LinkedStack<T>));
}

template <class T>
Stack<T>::~Stack()
{
  	if (this->stack == NULL)
    {
      	printf("[error] Null Object : stack\n");
      	return ;
    }
  	int index = this->stack->currentElementCount;
  	for (int i = 0; i < index; i++)
    {
      	StackNode<T> *pNode = this->popLS();
      	free(pNode);
    } // 하나씩 노드 pop() 해오고 그걸 매번 free() 해준다.
  	free(this->stack);
}

template <class T>
bool    Stack<T>::pushLS(T element)
{
  	StackNode<T> *pNode = NULL;
  	if (this->stack == NULL)
    {
      	printf("[error] Null Object : stack\n");
      	return (false);
    }
  	pNode = (StackNode<T>*)malloc(sizeof(StackNode<T>));
  	if (pNode == NULL)
    {
      	printf("[error] malloc failure : pNode\n");
        return (false);
    }
  	pNode->data = element;
  	pNode->pLink = this->stack->pTopElement;
  	this->stack->pTopElement = pNode;
    this->stack->currentElementCount++;
	return (true);
} // pTopElement(헤더노드) 자체가 0번째 element

template <class T>
StackNode<T>* Stack<T>::popLS()
{
  	StackNode<T> *delNode = NULL;
	  if (this->stack == NULL)
    {
      	printf("[error] Null Object : stack\n");
      	return (NULL);
    }
  	if (this->isLinkedStackEmpty() == true)
    {
      	printf("[error] Stack Underflow\n");
      	return (NULL);
    }
  	delNode = this->stack->pTopElement;
  	this->stack->pTopElement = delNode->pLink;
  	delNode->pLink = NULL; //어차피 반환할 노드니까 pLink를 널로.
  	this->stack->currentElementCount--;
  	return (delNode);
}

template <class T>
StackNode<T>* Stack<T>::peekLS()
{
  	if (this->stack == NULL)
    {
      	printf("[error] Null Object : stack\n");
      	return (NULL);
    }
  	if (this->isLinkedStackEmpty() == true)
    {
      	//printf("[error] Cannot try peek() on emtpy stack\n");
      	return (NULL);
    }
  	return (this->stack->pTopElement);
}

template <class T>
bool    Stack<T>::isLinkedStackEmpty()
{
    if (this->stack->currentElementCount == 0)
    {
        return (true);
    }
    return (false);
}

template <class T>
bool    Stack<T>::isLinkedStackFull()
{
  	return (false);
}

// =============== check_input.cc =================
bool    is_operator(char c);
bool    check_overInt(string input, int i, int size);
bool    check_bracket_matching(string input);
bool    check_inputFormat(string input);
int     op_number(string a);

// ============ convert_to_postfix.cc ==============
void    popAll(Stack<char> *a, vector<string> *output);
void    push_operand(Stack<char> *a, char op, vector<string> *output);
void    push_OpLeft(Stack<char> *a, vector<string> *output);
bool    process_postfix(Stack<char> *a, string *input, vector<string> *output);

// ================ calcuate.cc ====================
bool    calculate(Stack<int> *a, vector<string> output);
bool    calculate_postfix(Stack<int> *a, vector<string> output);


# endif