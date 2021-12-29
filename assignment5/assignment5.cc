#include <iostream>
using namespace std;

struct StackNode
{
    char  data;
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
    bool            pushLS(char element);
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

bool    Stack::pushLS(char element)
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
      	printf("[error] Cannot try peek() on emtpy stack\n");
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

bool    process_postfix(Stack a, string input, string output)
{
    char op[6] = {'/','*','-', '+', '(', ')'};
    int order[6] = {3, 3, 2, 2, 1, 1}; // 연산자의 순위를 임의의 숫자로 지정함.
    int size = input.size();
    int flag = 0;

    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < 6; j++)
      {
        if (input[i] == op[j])
        {
          a.pushLS(op[j]);
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
      {
        output.append((string)input[i]);
      }
    }
    return (true);
} // 중위표기로 입력받은 식을 후위표기로 변환해줌.

int     main()
{
    while (1)
    {
        Stack a, b; // a : 연산자를 뽑아서 후위 수식에 넣어줄 스택, b : 연산자를 뽑아서 
        string input, output;
    
        cin >> input;
        // ================ 중위 수식을 후위 수식으로 바꿈 ===============

        // ================ 후위 수식을 이용해서 연산함 ==================
        break;
    }
    return (0);
}
/*
 * 템플릿? : https://blockdmask.tistory.com/43
 * 스택응용 - 수식 계산 : https://rpatm.tistory.com/43
 * https://monzeac.tistory.com/28
 * https://gurumee92.tistory.com/128
 * malloc/free와 new/delete의 차이점 : https://wonjayk.tistory.com/252
 * Null 포인터로 객체의 함수가 호출되는 이유 : https://stdbc.tistory.com/124
 * 에러 : https://paranwater.tistory.com/138
 * 메모리 누수 : https://kldp.org/node/23920
 * /