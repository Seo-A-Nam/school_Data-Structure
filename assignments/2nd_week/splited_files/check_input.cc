#include "assigment5.h"

bool  is_operator(char c)
{
  if (c == '^' || c == ')' || c == '/' || c == '*' || c == '-' || c == '+' || c == '(')
    return (true);
  return (false);
} // 주어진 문자가 operator인지 확인

bool    check_overInt(string input, int i, int size)
{
  long long num = 0;
  int idx = 0;
  int minus = 0;
  
  if (input[i] == '-')
  {
    idx++;
    minus = 1;
  }
  while (idx < size - i)
  {
    if (!(input[i + idx] >= '0' && input[i + idx] <= '9'))
      break;
    num *= 10;
    num += (input[i + idx] - '0');
    try {
      if (minus == 0 && num > INT_MAX)
        throw "Input value : Int Overflow."; // 이 프로그램은 정수 범위의 수만 계산하기 때문에 정수 범위가 아닌 수에 대해서는 리턴.
      if (minus == 1 && num - 1 > INT_MAX)
        throw "Input value : Int Underflow."; // 이 프로그램은 정수 범위의 수만 계산하기 때문에 정수 범위가 아닌 수에 대해서는 리턴.
    }
    catch (const char *err)
    {
      cout << "[error] "<<err<<endl;
      return (false);
    }
    idx++;
  }
  return (true);
}

bool    check_bracket_matching(string input)
{
  int i = 0;
  StackNode<char> *tmp;
  char prev;
  Stack<char> *match = new Stack<char>;

  while (input[i])
  {
    if (input[i] == '(')
      match->pushLS(input[i]);
    else if (input[i] == ')')
    {
      if (i > 0 && is_operator(input[i - 1]))
      { // 닫는 괄호 바로 앞에 연산자가 오는 경우 예외처리.
        delete match;
        return (false);
      }
      if (match->isLinkedStackEmpty() == true)
      {
        delete match; // 중요 : 리턴하기 전에 할당된 메모리 해제해야함! (메모리 누수 방지)
        return (false); // 조건 : 동일 타입의 괄호에서 왼쪽 괄호는 오른쪽 괄호보다 먼저 나와야 한다.
      }
      tmp = match->popLS();
      prev = tmp->data;
      free(tmp);
    }
    i++;
  }
  if (match->isLinkedStackEmpty() == false)
  {
    delete match;
    return (false); // 조건 : 왼쪽 괄호의 개수와 오른쪽의 괄호의 개수가 같아야한다.
  }
  delete match;
  return (true);
} // 입력값에서 괄호 형식이 올바른 지 체크한다.

bool    check_inputFormat(string input)
{
  char op[7] = {'^', ')', '/', '*', '-', '+', '('};
  int flag = -1, op_cnt = 0, nb_cnt = 0, i = 0, nb = 0;
  int size = input.size();

  if (check_bracket_matching(input) == false)
  {
    cout<<"[error] Wrong format of brackets"<<endl;
    return (false);
  }
  while (i < size)
  {
    if (input[i] == ')' || input[i] == '(') ; // 괄호는 그냥 넘어감.
    else if (input[i] == '-' && nb_cnt == 0)
    {
      if (check_overInt(input, i, size) == false)
        return (false);
      nb = atoi(input.c_str() + i);
      if (nb == 0) // 이번 것이 숫자인 지. (문자(연산자 포함)라면 오류)
        return (false); 
      nb_cnt++;
      i += to_string(nb).size();
      if (i == size)
        break;
    } // 음수인 정수가 맨 앞부터 등장하는 부분 예외처리
    else if (i < size - 1 && is_operator(input[i]) == true) // 연산자가 발견되었다면 플래그 체크해준 후 다음 루프로 넘어감
    {
      flag = 1;
      op_cnt++;
    }
    else // 연산자가 발견되지 않았다면, 해당 위치가 숫자인지 확인.
    {
      if (flag == 0) // 저번에 연산자가 있었는 지
        return (false);
      if (check_overInt(input, i, size) == false)
        return (false);
      nb = atoi(input.c_str() + i);
      if (nb == 0 && input[i] != '0') // 이번 것이 숫자인 지. (문자(연산자 포함)라면 오류)
        return (false); 
      nb_cnt++;
      i += to_string(nb).size() - 1;
      if (i == size)
        break;
      flag = 0;
    }
    i++;
  } // 괄호를 제외하면, 연산자-숫자- 이렇게 번갈아 나와야 정상임. 
  if ((nb_cnt + op_cnt) == 1) // 연산자나 숫자 하나로만 구성된 수식을 에러처리.
    return (false);
  if (op_cnt >= nb_cnt)
    return (false); // 숫자 개수보다 연산자 개수가 더 많거나 같으면 에러 처리.
    // 참고 : 여기서 숫자 개수는 연산자 개수 + 1을 넘어갈 수 없다. 숫자가 연산자를 기준으로 분리되기 때문.
  return (true);
} // 입력된 중위연산 수식이 올바른 형식인 지 체크.
