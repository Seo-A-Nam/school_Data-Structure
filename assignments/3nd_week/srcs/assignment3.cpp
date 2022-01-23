#include <iostream>
#include <climits> // int_max, int_min 때문에 호출.
using namespace std;

long long sum; // 전역변수로 트리 내 정수의 합 저장.

// ====================  STACK  =========================

template <typename T>
struct StackNode
{
    T data;
    struct StackNode* pLink;
}; // 연결리스트 스택의 노드.

template <typename T>
struct LinkedStack
{
    int currentElementCount;
    StackNode<T>* pTopElement;
}; // 연결리스트 스택 구조체.

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
}; // 스택 클래스.

// ======================  BST  =========================

template <class T> class BST;
template <class T>
class Node {
	friend class BST<T>;
	private :
		Node<T>     *leftChild;
		T           key; 
			// 원래는 키와 노드 별도의 값을 가지지만, 여기서는 키만 가지는 것으로 가정.
		Node<T>     *rightChild;
}; // BST의 노드

template <class T>
class BST {
	private :
		Node<T> *root;
		int     nodeCount;
	public :
		BST();
		~BST();
		void    deleteBST(Node<T> *node);
		bool    IsEmpty(); // 공백이면 true를 반환
		void    Insert(const T&); // 키를 삽입. 키가 중복되면 관련 원소를 갱신
		void    inorder_traverse();
		Node<T> *getRoot();
}; // BST (이진 탐색 트리)


// =================  스택 멤버 함수  =====================

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

// =================  BST 멤버 함수  =====================
template <class T>
bool        BST<T>::IsEmpty()
{
	if (nodeCount == 0)
		return (true);
	return (false);
} // bst에 노드가 없다면 true, 있다면 false 반환

template <class T>
BST<T>::    BST()
{
	root = new Node<T>;
	nodeCount = 0;
} // 생성자

template <class T>
BST<T>::    ~BST()
{
	deleteBST(root);
} // 파괴자

template <class T>
void        BST<T>::deleteBST(Node<T> *node)
{
	if (!node)  return ;
	deleteBST(node->leftChild);
	deleteBST(node->rightChild);
	delete (node);
	nodeCount--;
} // 재귀를 통한 메모리 해제를 수행

template <class T>
void        BST<T>::inorder_traverse()
{
	Node<T> *ptr = root;
	Stack<Node<T> *> s;
	// 스택을 이용해서 반복적 중위순회 (시스템 스택이 아닌 외부 스택 이용)

	if (!root)
		return ;
	while (1)
	{
		while (ptr) // 왼쪽 자식 필드로 이동
		{
			s.pushLS(ptr); // 스택에 삽입
			ptr = ptr->leftChild;
		}
		if (s.isLinkedStackEmpty())
			return ;
		ptr = s.peekLS()->data; // 스택에서의 삭제.
		cout << ptr->key << " ";
		sum += ptr->key;	
		StackNode<Node<T> *> *tmp = s.popLS();
		delete tmp;
		ptr = ptr->rightChild;
	}
} 

template <class T>
void        BST<T>::Insert(const T& newNode)
{
	Node<T> *p = root, *pp = 0, *ptr; // pp는 p의 부모

	if (IsEmpty())
	{
		root->key = newNode;
		nodeCount++;
		return ;
	}
	while (p) // 위치 찾아가기. (만약 이미 있는 노드라면 갱신 수행)
	{
		pp = p;
		if (newNode < p->key) p = p->leftChild;
		else if (newNode > p->key) p = p->rightChild;
		else // 원소를 갱신
		{ p->key = newNode; return ; }
	}
	// 삽입을 수행
	ptr = new Node<T>;
	ptr->key = newNode;
	if (root)
		if (newNode < pp->key) pp->leftChild = ptr;
		else pp->rightChild = ptr;
	else root = ptr;
	nodeCount++;
} // BST에 key를 삽입 (이 프로그램에서는 key와 value를 구분하지 않는다)

template <class T>
Node<T>     *BST<T>::getRoot()
{
	return (root);
} // 루트 노드의 포인터를 반환.


// ===================================================

bool    check_numstr(string a)
{
    int i = 0;

    if (a[0] == '-' || a[0] == '+')
        i++;
    while (i < (int)a.size())
    {
        if (!(a[i] >= '0' && a[i] <= '9'))
            return (false);
        i++;
    }
    return (true);
} // 주어진 문자열이 숫자로만 이루어져있는 지 검사.

bool    check_numRange(string a)
{
	long long nb;
	
	if (a.size() > 11)
		return (false);
	nb = stoll(a);
	if (nb > INT_MAX || nb < INT_MIN)
		return (false);
	return (true);
} // 주어진 문자열의 숫자가 정수 범위 이내인 지 검사.

int     main()
{
	BST<int> bst;
	string temp;
	
	sum = 0;
	//  ==================    BST에 넣을 원소 입력 받기     ======================
	cout << "____ Type a row of integers to insert in this BST. _____" <<endl;
	cout << "       (finish your input with '#' terminator)"<<endl<<endl;
	while (1)
	{
		cin >> temp;
		if (temp.compare("#") == 0)
			break;
		try {
			if (check_numstr(temp) == false)
				throw "[error] Input : Value should only contain numbers.";
			if (check_numRange(temp) == false)
				throw "[error] Input : Out of Integer range.";
		}
		catch (const char *err) {
			cout << err <<endl;
			return (1);
		}
		bst.Insert(stoi(temp));
	} // bst에 넣을 원소를 입력 받는다 ('#'으로 입력이 끝나게 된다)
	//  ====================      결과값 출력       ========================
	cout << endl <<"Result ================================================" << endl << endl;
	cout << "AO LIST : ";
	bst.inorder_traverse(); // 중위 순회로 방문한 노드 출력
	cout << "#" << endl;
	cout << "SUM : "<<sum<<endl; // bst를 순회하며 방문한 노드 키 값의 합을 출력
	return (0);
}