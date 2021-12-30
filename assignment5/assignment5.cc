#include <iostream>
using namespace std;

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

// bool    check_inputFormat(string input, char *op, int size)
// {
//   int flag = 0;

//   for (int i = 0; i < size; i++)
//   {
//     for (int j = 0; j < size; j++)
//     {
//       if (input[i] == op[j])
//       {
//         flag = 1;
//         break;
//       }
//     }
//     if (flag == 1) // 연산자가 발견되었다면 다음 루프로 넘어감
//     {
//       flag = 1;
//       continue;
//     }
//     else // 연산자가 발견되지 않았다면, 해당 위치가 숫자인지 확인.
//     {
//       atoi
//     }

//   }
// }

bool    process_postfix(Stack *a, string *input, string *output)
{
    string op[7] = {"**", ")", "/","*","-", "+", "("};
    int isp[7] = {3, -1, 2, 2, 1, 1, 0}; // In Stack Priority : 스택에 저장된 연산자 우선순위.
    int icp[7] = {3, -1, 2, 2, 1, 1, 3}; // In Coming Priority : 스택에 저장되기 직전 연산자 우선순위.
    int size = (*input).size();
    int flag = 0;

    cout<<"!"<<endl;
    for (int i = 0; i < size; i++)
    {
      if ((i < size - 1) && (*input)[i] == '*' && (*input)[i + 1] == '*')
      {
        a->pushLS(op[0]);
        i++;
        continue;
      } // 제곱 연산자일 경우를 처리
      for (int j = 1; j < 7; j++)
      {
        cout<<"op[j]"<<op[j]<<"      input[i]"<<(*input)[i]<<endl;
        if (op[j].compare(to_string((*input)[i])) == 0)
        {
          a->pushLS(op[j]);
          flag = 1;
          break;
        }
      }
      if (flag == 1) // 이번에 발견한 값이 연산자라면. 다음 루프로 넘어감.
      {
        flag = 0;
        continue;
      }
      else // 이번에 발견한 값이 연산자가 아니라면 (숫자라면). 결과값 문자열에 저장.
      { // 숫자가 여러 자리일수도 있다는 점을 고려하자.
        int num = atoi((*input).c_str() + i); // 이렇게하면 int 범위 밖의 (long long 등)은 저장 못한다는 단점이 있다.
        string nb = to_string(num);
        (*output).append(nb);
        i += nb.size();
      }
    }
    cout<<"!!"<<endl;
    while (1)
    {
      if (a->isLinkedStackEmpty() == true)
        break;
      StackNode *ele = a->popLS();
      (*output).append(ele->data);
      free(ele);
    }
    cout<<"!!!"<<endl;
    return (true);
} // 중위표기로 입력받은 식을 후위표기로 변환해줌.

int     main()
{
    while (1)
    {
        Stack *a = new Stack;
        Stack b; // a : 연산자를 뽑아서 후위 수식에 넣어줄 스택, b : 연산자를 뽑아서 
        string input, output;
    
        cin >> input;
        // ================ 중위 수식을 후위 수식으로 바꿈 ===============
        process_postfix(a, &input, &output);
        for (int i = 0; i < output.size(); i++)
        {
          cout << output[i] << " ";
        }
        cout <<endl;
        // ================ 후위 수식을 이용해서 연산함 ==================
        break;
    }
    return (0);
}

/*
 * 템플릿? : https://blockdmask.tistory.com/43
 * 스택응용 - 수식 계산 : https://rpatm.tistory.com/43  (이게 짱)
 * https://monzeac.tistory.com/28
 * https://gurumee92.tistory.com/128
 * malloc/free와 new/delete의 차이점 : https://wonjayk.tistory.com/252
 * Null 포인터로 객체의 함수가 호출되는 이유 : https://stdbc.tistory.com/124
 * 에러 : https://paranwater.tistory.com/138
 * 메모리 누수 : https://kldp.org/node/23920
 */