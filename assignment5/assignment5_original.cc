#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
* 여기에 아직 Template 클래스 사용 안함. 사용할 수 있도록 고치기.
* 계산 시 stack에 int, string 모두를 넣을 수 있도록 ...
*/

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

Stack::Stack()
{
    this->stack = (LinkedStack*)malloc(sizeof(LinkedStack));
}

Stack::~Stack()
{
  	if (this->stack == NULL)
    {
      	printf("[error] Null Object : stack\n");
      	return ;
    }
  	int index = this->stack->currentElementCount;
  	for (int i = 0; i < index; i++)
    {
      	StackNode *pNode = this->popLS();
      	free(pNode);
    } // 하나씩 노드 pop() 해오고 그걸 매번 free() 해준다.
  	free(this->stack);
}

bool    Stack::pushLS(string element)
{
  	StackNode *pNode = NULL;
  	if (this->stack == NULL)
    {
      	printf("[error] Null Object : stack\n");
      	return (false);
    }
  	pNode = (StackNode*)malloc(sizeof(StackNode));
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

StackNode* Stack::popLS()
{
  	StackNode *delNode = NULL;
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

StackNode* Stack::peekLS()
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

void  Stack::displayLS()
{
    StackNode   *pNode = this->stack->pTopElement;

    cout<<"Stack Status  ==================================="<<endl;
    for(int i = 0; i < this->stack->currentElementCount; i++)
    {
        cout << pNode->data << " ";
        pNode = pNode->pLink;
    }
    cout << endl;
    cout<<"================================================="<<endl;
}

bool    Stack::isLinkedStackEmpty()
{
    if (this->stack->currentElementCount == 0)
    {
        return (true);
    }
    return (false);
}

bool    Stack::isLinkedStackFull()
{
  	return (false);
}
/* 무조건 False 인 이유 -> maxElementCount도 없는데다가 링크드리스트 구조이므로
 가득 찰 리가 없다. */

bool  is_operator(char c)
{
  if (c == ')' || c == '/' || c == '*' || c == '-' || c == '+' || c == '(')
    return (true);
  return (false);
} // 제곱 (**) 연산자는 따로 처리해줄 것이므로 여기에서 제외함.

bool    check_bracket_matching(string input)
{
  int i = 0;
  StackNode *tmp;
  string ch, prev;
  Stack *match = new Stack;

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

void    popAll(Stack *a, vector<string> *output)
{
  while (1)
  {
    if (a->isLinkedStackEmpty())
      break;
    StackNode *node = a->popLS();
    if (node->data != ")" && node->data != "(")
      output->push_back(node->data);
    free(node);
  }
} // 모든 연산자를 스택에서 pop하고 후위 연산식에 넣어준다.

void    push_operand(Stack *a, char op, vector<string> *output)
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
    StackNode *node = a->popLS();
    if (q != 1 && q != 6)
      output->push_back(node->data);
    free(node);
    break;
  }
  a->pushLS(s);
} // 후위 연산식에 연산자를 넣는다.

void    push_OpLeft(Stack *a, vector<string> *output)
{
  while (1)
  {
    if (a->isLinkedStackEmpty() == true)
      break;
    StackNode *node = a->popLS();
    int q = op_number(node->data);
    if (q != 1 && q != 6)
      output->push_back(node->data);
    free(node);
  }
} // 다 끝나고 스택에 남아있는 연산자들을 후위연산 수식 뒤에 모두 넣어준다. 

bool    process_postfix(Stack *a, string *input, vector<string> *output)
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

void  calculate(Stack *a, vector<string> output)
{
  StackNode *node;

  int n1, n2, result;
  node = a->popLS();
  n1 = stoi(node->data);
  free(node);
  node = a->popLS();
  n2 = stoi(node->data);
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
  a->pushLS(to_string(result));
} // 스택에 있는 연산자와 숫자 2개를 뽑아서 연산해줌

void  calculate_postfix(Stack *a, vector<string> output)
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
      a->pushLS(output[0]);
    output.erase(output.begin());
  }
} // 후위 연산식을 계산한다.

int     main()
{
  string input;
  while (1)
  { 
      cin >> input; // input 값에 띄어쓰기 포함되었는지 예외처리할 수 없음 (cin은 공백 나오면 입력 끝냄) 
      if (input.compare((string)".") == 0)
      {
        cout << "==================== Terminate The Program ===================="<<endl;
        break;
      }
      else if (check_inputFormat(input) == false)
      {
        cout << "[error] Wrong input format"<<endl;
        continue;
      }
      else
      {
        Stack *a = new Stack;
        vector<string> output; // 입력된 요소를 띄어쓰기 넣어 출력해야하기 때문에 이렇게 선언함.
        // ================ 중위 수식을 후위 수식으로 바꿈 ===============
        process_postfix(a, &input, &output);
        for (int i = 0; i < output.size(); i++)
        {
          cout << output[i] << " ";
        }
        cout <<endl;
        // ================ 후위 수식을 이용해서 연산함 ==================
        calculate_postfix(a, output);
        delete a;
        //break;
      }
  }
  //system("leaks a.out"); // 메모리 누수 체크
  return (0);
}
