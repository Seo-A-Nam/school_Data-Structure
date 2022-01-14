
// =============================          STACK CLASS  /  FUCTION DECLARATION          =============================================

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

// =============================                CALCULATE                  =============================================

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
      cout<< "> "<<(a->peekLS())->data<<endl;
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

// =============================          CONVERT TO POSTFIX              =============================================

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

// =============================          CHECK INPUT FORMAT              =============================================

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

// =============================              MAIN                  =============================================

int     main()
{
  string input;
  cout <<endl<< "=================================================================="<<endl;
  cout << "                Welcome to our stack calculater!" << endl;
  cout<< "               (press .(dot) to terminte program)" << endl <<endl;
  while (1)
  {
      cout << "> Type any infix math expression to calculate."<<endl<<" (without any whitespace)"<<endl<<endl;
      cout << "Infix : ";
      cin >> input; // input 값에 띄어쓰기 포함되었는지 예외처리할 수 없음 (cin은 공백 나오면 입력 끝냄) 
      // 조건 : 띄어쓰기 없이, 0~9 자연수 입력.
      if (input.compare((string)".") == 0)
      {
        cout << "==================== Terminate The Program ===================="<<endl;
        break;
      }
      else if (check_inputFormat(input) == false)
      {
        cout << "[error] Wrong input format"<<endl<<endl;
        cout << "Try again !" <<endl;
        // 다음 루프로 넘어가서 처음부터 다시할 수 있도록 함
      }
      else
      {
        Stack<char> *a = new Stack<char>;
        Stack<int> *b = new Stack<int>;
        vector<string> output; // 입력된 요소를 띄어쓰기 넣어 출력해야하기 때문에 이렇게 선언함.
        // ================ 중위 수식을 후위 수식으로 바꿈 ===============
        if (process_postfix(a, &input, &output) == false) // int overflow 일어나는 경우 (아직 코드 안넣음!)
        {
          delete a;
          delete b;
          cout << "Try again !" <<endl;
          continue; // 다음 루프로 넘어가서 처음부터 다시할 수 있도록 함
        }
        cout << "Postfix : ";
        for (int i = 0; i < output.size(); i++)
        {
          cout << output[i];
          if (i < output.size() - 1)
            cout << ",";
        }
        cout <<endl;
        // ================ 후위 수식을 이용해서 연산함 ==================
        if (calculate_postfix(b, output) == false)
        {
          delete a;
          delete b;
          continue;
        }
        delete a;
        delete b;
        break;
      }
  }
  return (0);
}