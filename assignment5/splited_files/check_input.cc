#include "assigment5.h"

bool  is_operator(char c)
{
  if (c == ')' || c == '/' || c == '*' || c == '-' || c == '+' || c == '(')
    return (true);
  return (false);
} // 제곱 (**) 연산자는 따로 처리해줄 것이므로 여기에서 제외함.

bool    check_bracket_matching(string input)
{
  int i = 0;
  StackNode<string> *tmp;
  string ch, prev;
  Stack<string> *match = new Stack<string>;

  while (input[i])
  {
    ch = "";
    ch += input[i++];
    if (ch.compare("(") == 0)
      match->pushLS(ch);
    else if (ch.compare(")") == 0)
    {
      if (match->isLinkedStackEmpty() == true)
        return (false); // 동일 타입의 괄호에서 왼쪽 괄호는 오른쪽 괄호보다 먼저 나와야 한다.
      tmp = match->popLS();
      prev = tmp->data;
      free(tmp);
    }
  }
  if (match->isLinkedStackEmpty() == false)
    return (false); // 왼쪽 괄호의 개수와 오른쪽의 괄호의 개수가 같아야한다.
  delete match;
  return (true);
} // 입력값에서 괄호 형식이 올바른 지 체크한다.

bool    check_inputFormat(string input)
{
  string op[7] = {"**", ")", "/","*","-", "+", "("};
  int flag = -1;
  int op_cnt = 0, nb_cnt = 0;
  int size = input.size();

  if (check_bracket_matching(input) == false)
  {
    cout<<"[error] Wrong format of brackets"<<endl;
    return (false);
  }
  for (int i = 0; i < size; i++)
  {
    if (input[i] == ')' || input[i] == '(') ; // 괄호는 그냥 넘어감.
    else if ((i < size - 1 && input[i] == '*' && input[i + 1] == '*') 
      || is_operator(input[i]) == true) // 연산자가 발견되었다면 플래그 체크해준 후 다음 루프로 넘어감
    {
      if (i < size - 1 && input[i] == '*' && input[i + 1] == '*')
        i++; // 제곱 연산자일 경우는 인덱스 하나 더 넘어간다.
      flag = 1;
      op_cnt++;
    }
    else // 연산자가 발견되지 않았다면, 해당 위치가 숫자인지 확인.
    {
      int nb;
      if (flag == 0) // 저번에 연산자가 있었는 지
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
  } // 괄호를 제외하면, 연산자-숫자- 이렇게 번갈아 나와야 정상임. 
  if ((nb_cnt + op_cnt) == 1) // 연산자나 숫자 하나로만 구성된 수식을 에러처리.
    return (false);
  if (op_cnt >= nb_cnt)
    return (false); // 숫자 개수보다 연산자 개수가 더 많거나 같으면 에러 처리.
    // 참고 : 여기서 숫자 개수는 연산자 개수 + 1을 넘어갈 수 없다. 숫자가 연산자를 기준으로 분리되기 때문.
  return (true);
} // 입력된 중위연산 수식이 올바른 형식인 지 체크.
