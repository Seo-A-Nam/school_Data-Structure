#include "assigment5.h"

void  calculate(Stack<int> *a, vector<string> output)
{
  StackNode<int> *node;

  int n1, n2, result;
  node = a->popLS();
  n1 = node->data;
  free(node);
  node = a->popLS();
  n2 = node->data;
  free(node);
  if (output[0].compare((string)"**") == 0)
  {
    result = pow(n2, n1);
  }
  else if (output[0].compare((string)"*") == 0)
  {
    result = n2 * n1;
  }
  else if (output[0].compare((string)"/") == 0)
  {
    result = n2 / n1;
  }
  else if (output[0].compare((string)"+") == 0)
  {
    result = n2 + n1;
  }
  else if (output[0].compare((string)"-") == 0)
  {
    result = n2 - n1;
  }
  a->pushLS(result);
} // 스택에 있는 연산자와 숫자 2개를 뽑아서 연산해줌

void  calculate_postfix(Stack<int> *a, vector<string> output)
{
  while (1)
  {
    if (output.size() == 0)
    {
      cout<< (a->peekLS())->data<<endl;
      break;
    }
    if (is_operator((char)output[0][0]) == true || output[0].compare((string)"**") == 0)
      calculate(a, output);
    else
      a->pushLS(stoi(output[0]));
    output.erase(output.begin());
  }
} // 후위 연산식을 계산한다.
