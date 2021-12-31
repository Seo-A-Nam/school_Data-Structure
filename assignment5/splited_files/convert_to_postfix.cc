#include "assigment5.h"

int   op_number(string a)
{
  string op[7] = {"**", ")", "/","*","-", "+", "("};

  for (int i = 0; i < 7; i++)
  {
    if (a.compare(op[i]) == 0)
      return (i);
  }
  return (-1);
} // 몇 번째 operator인지 -> 이걸 인덱스로해서 isp, icp의 값을 찾음.

void    popAll(Stack<string> *a, vector<string> *output)
{
  while (1)
  {
    if (a->isLinkedStackEmpty())
      break;
    StackNode<string> *node = a->popLS();
    if (node->data != ")" && node->data != "(")
      output->push_back(node->data);
    free(node);
  }
} // 모든 연산자를 스택에서 pop하고 후위 연산식에 넣어준다.

void    push_operand(Stack<string> *a, char op, vector<string> *output)
{
  //string op[7] = {"**", ")", "/","*","-", "+", "("};
  int isp[7] = {3, -1, 2, 2, 1, 1, 0}; // In Stack Priority : 스택에 저장된 연산자 우선순위.
  int icp[7] = {3, -1, 2, 2, 1, 1, 3}; // In Coming Priority : 스택에 저장되기 직전 연산자 우선순위.
  int p, q;

  string s;
  s += op;
  p = op_number(s); // 현재 연산자
  if (a->isLinkedStackEmpty())
  {
    a->pushLS(s);
    return ;
  }
  q = op_number(a->peekLS()->data); // 스택 top의 연산자
  if (q == 1) // 만약 닫는 괄호 ")"를 만나면 모든 연산자 pop.
    popAll(a, output);
  while (icp[p] < isp[q]) // 현재 연산자의 icp와 스택 top의 isp를 비교.
  {
    q = op_number(a->peekLS()->data);
    if (a->isLinkedStackEmpty())
      break;
    StackNode<string> *node = a->popLS();
    if (q != 1 && q != 6)
      output->push_back(node->data);
    free(node);
    break;
  }
  a->pushLS(s);
} // 후위 연산식에 연산자를 넣는다.

void    push_OpLeft(Stack<string> *a, vector<string> *output)
{
  while (1)
  {
    if (a->isLinkedStackEmpty() == true)
      break;
    StackNode<string> *node = a->popLS();
    int q = op_number(node->data);
    if (q != 1 && q != 6)
      output->push_back(node->data);
    free(node);
  }
} // 다 끝나고 스택에 남아있는 연산자들을 후위연산 수식 뒤에 모두 넣어준다. 

bool    process_postfix(Stack<string> *a, string *input, vector<string> *output)
{
    string op[7] = {"**", ")", "/","*","-", "+", "("};
    int size = (*input).size();

    for (int i = 0; i < size; i++)
    {
      if ((i < size - 1) && ((*input)[i] == '*' && (*input)[i + 1] == '*'))
      {
        a->pushLS(op[0]);
        i++;
        continue;
      } // 제곱 연산자일 경우를 처리
      if (is_operator((*input)[i]))
      {
        push_operand(a, (*input)[i], output);
        continue;
      }
      else // 이번에 발견한 값이 연산자가 아니라면 (숫자라면). 결과값 문자열에 저장.
      { // 숫자가 여러 자리일수도 있다는 점을 고려하자.
        int num = atoi((*input).c_str() + i); // 이렇게하면 int 범위 밖의 (long long 등)은 저장 못한다는 단점이 있다.
        string nb = to_string(num);
        output->push_back(nb);
        i += nb.size() - 1;
      }
    }
    push_OpLeft(a, output); // 스택에 남은 연사자들을 결과값 뒤에 다 넣어줌
    return (true);
} // 중위표기로 입력받은 식을 후위표기로 변환해줌.
