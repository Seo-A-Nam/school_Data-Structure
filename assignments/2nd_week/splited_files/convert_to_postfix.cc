#include "assigment5.h"

int   op_number(char a)
{
  char op[7] = {'^', ')', '/', '*', '-', '+', '('};

  for (int i = 0; i < 7; i++)
  {
    if (a == op[i])
      return (i);
  }
  return (-1);
} // 몇 번째 operator인지 -> 이걸 인덱스로해서 isp, icp의 값을 찾음.

void    popAll(Stack<char> *a, vector<string> *output)
{
  while (1)
  {
    if (a->isLinkedStackEmpty())
      break;
    StackNode<char> *node = a->popLS();
    if (node->data != ')' && node->data != '(')
    {
      string tmp = "";
      tmp += node->data;
      output->push_back(tmp);
    }
    free(node);
  }
} // 모든 연산자를 스택에서 pop하고 후위 연산식에 넣어준다.

void    push_operand(Stack<char> *a, char op, vector<string> *output)
{
  // char op[7] = {'^', ')', '/', '*', '-', '+', '('};
  int isp[7] = {1, 10, 2, 2, 3, 3, 8}; // In Stack Priority : 스택에 저장된 연산자 우선순위.
  int icp[7] = {1, 10, 2, 2, 3, 3, 0}; // In Coming Priority : 스택에 저장되기 직전 연산자 우선순위.
  int p, q;

  p = op_number(op); // 현재 연산자 인덱스
  if (a->isLinkedStackEmpty())
  {
    a->pushLS(op);
    return ;
  }
  q = op_number(a->peekLS()->data); // 스택 top의 연산자
  if (q == 1) // 만약 닫는 괄호 ")"를 만나면 모든 연산자 pop.
    popAll(a, output);
  while (icp[p] >= isp[q]) // 현재 연산자의 icp와 스택 top의 isp를 비교.
  {
    q = op_number(a->peekLS()->data);
    if (a->isLinkedStackEmpty())
      break;
    StackNode<char> *node = a->popLS();
    if (q != 1 && q != 6) // 괄호가 아닌 연산자들만 후위연산식에 push
    {
      string tmp = "";
      tmp += node->data;
      output->push_back(tmp);
    }
    free(node);
    break;
  }
  a->pushLS(op);
} // 후위 연산식에 연산자를 넣는다.

void    push_OpLeft(Stack<char> *a, vector<string> *output)
{
  while (1)
  {
    if (a->isLinkedStackEmpty() == true)
      break;
    StackNode<char> *node = a->popLS();
    int q = op_number(node->data);
    if (q != 1 && q != 6) // 괄호가 아닌 연산자들만 후위연산식에 push
    {
      string tmp = "";
      tmp += node->data;
      output->push_back(tmp);
    }
    free(node);
  }
} // 다 끝나고 스택에 남아있는 연산자들을 후위연산 수식 뒤에 모두 넣어준다. 

bool    process_postfix(Stack<char> *a, string *input, vector<string> *output)
{
    char op[7] = {'^', ')', '/', '*', '-', '+', '('};
    int size = (*input).size();
    int nb_flag = 0;
    
    for (int i = 0; i < size; i++)
    {
      if ((*input)[i] == '-' && nb_flag == 0)
      {
        int num = atoi((*input).c_str() + i); // 이렇게하면 int 범위 밖의 (long long 등)은 저장 못한다는 단점이 있다.
        string nb = to_string(num);
        output->push_back(nb);
        i += nb.size() - 1; // minus 연산자 크기까지 포함하므로.
      } // 첫 항이 음수일 경우를 예외처리.
      else if (is_operator((*input)[i]))
      {
        push_operand(a, (*input)[i], output);
        continue;
      }
      else // 이번에 발견한 값이 연산자가 아니라면 (숫자라면). 결과값 문자열에 저장.
      { // 숫자가 여러 자리일수도 있다는 점을 고려하자.
        int num = atoi((*input).c_str() + i);
        string nb = to_string(num);
        output->push_back(nb);
        i += nb.size() - 1;
      }
      nb_flag = 1;
    }
    push_OpLeft(a, output); // 스택에 남은 연사자들을 결과값 뒤에 다 넣어줌
    return (true);
} // 중위표기로 입력받은 식을 후위표기로 변환해줌.
