#include "assigment5.h"

bool  calculate(Stack<int> *a, vector<string> output)
{
  StackNode<int> *node;

  long long n1, n2;
  long long result;
  node = a->popLS();
  n1 = node->data;
  free(node);
  node = a->popLS();
  n2 = node->data;
  free(node);
  if (output[0].compare((string)"^") == 0)
  {
    result = pow(n2, n1);
  }
  else if (output[0].compare((string)"*") == 0)
  {
    result = n2 * n1;
  }
  else if (output[0].compare((string)"/") == 0)
  {
    if (n1 == 0)
    {
      cout <<"[error] devide by zero." <<endl;
      return (false);
    }
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
  //cout <<"result :" <<result<<endl;
  if (result < (long long)INT_MIN)
  {
    cout <<"[error] Int Underflow."<<endl;
    return (false);
  }
  if (result > (long long)INT_MAX)
  {
    cout << "[error] Int Overflow. " <<endl;
    return (false);
  }
  a->pushLS(result);
  return (true);
} // 스택에 있는 연산자와 숫자 2개를 뽑아서 연산해줌

bool  calculate_postfix(Stack<int> *a, vector<string> output)
{
  while (1)
  {
    if (output.size() == 0)
    {
      cout<<"> "<<(a->peekLS())->data<<endl;
      break;
    }
    if (is_operator((char)output[0][0]) == true && output[0].size() == 1)
    {
      if (calculate(a, output) == false)
        return (false);
    }
    else
      a->pushLS(stoi(output[0])); // 숫자라면 스택에 넣어줌.
    output.erase(output.begin());
  }
  return (true);
} // 후위 연산식을 계산한다.
