#include "assignment6.h"

LinkedList* List::get_pList()
{
    return (this->pList);
}

List::List()
{
    this->pList = (LinkedList *)malloc(sizeof(LinkedList));
	if (pList == NULL)
        cout<<"[error] malloc failure : pList"<<endl;
	this->pList->count = 0;
	this->pList->headerNode->pLink = NULL;
}

bool List::addLLE(int position, ListNode element)
{
    ListNode    *head = this->pList->headerNode;
    ListNode    *prev;
    ListNode    *node;
    int         i;

    i = 0;
    cout<<"!"<<endl;
    if (this->pList == NULL)
    {
        cout<<"[error] pList is Null"<<endl;
        return (false);
    }
    cout<<"!"<<endl;
    if (this->pList->count + 1 < position || position < 0)
    {
        cout<<"[error] Invalid position value"<<endl;
        return (false);
    }
    cout<<"!"<<endl;
    node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL)
    {
        cout<<"[error] malloc failure : node"<<endl;
        return (false);
    }
    cout<<"!"<<endl;
    *node = element;
    if (this->pList->count == 0) // 리스트에 노드가 없을 떄
    {
        cout<<"!"<<endl;
        head->pLink = node;
        node->pLink = node;
    }
    else if (position == 0) // 노드가 여러 개일 때 맨 앞에 새로운 노드를 넣어주는 경우
    {
        cout<<"!"<<endl;
        ListNode *tail;
        ListNode *ptr;
        node->pLink = head->pLink->pLink;
        //head->pLink = node;
        //head->pLink = node;
        tail = node->pLink;
        while (tail->pLink != head->pLink)
        {
            tail = tail->pLink;
        }
        tail->pLink = node;
        head->pLink = node;
    }
    else // 리스트의 중간에 노드를 넣는 경우
    {
        cout<<"!"<<endl;
        node->deg = element.deg;
        node->coef = element.coef;
        prev = this->pList->headerNode->pLink;
        while(i < position && prev->pLink != head->pLink)
        {
            prev = prev->pLink;
            i++;
        }
        node->pLink = prev->pLink;
        prev->pLink = node;
    }
    cout<<"!"<<endl;
    this->get_pList()->count++;
    return (true);
}
// 첫 노드를 0번째로 하는가? 헤더 노드를 0번쨰로 하는 가?
// (전자를 택함. 실제로 헤더는 스택이고...어디 영역에 저장되는 지 모르니까)


bool List::removeLLE(int position)
{
    ListNode    *head = this->pList->headerNode;
    ListNode    *curr;
    ListNode    *tmp;
    ListNode    *tail = this->pList->headerNode->pLink;
    int          i;

    if (position >= this->pList->count || position < 0)
    {
        cout<<"[error] Invalid Position value"<<endl;
        return (false);
    }
    // 현재 존재하는 개수 이상인 인덱스에서 노드를 삭제할 수 없다. 따라서 false 반환.
    if (this->pList == NULL)
    {
        cout<<"[error] There is no LinkedList existing"<<endl;
        return (false);
    }
    else
    {
        tmp = this->pList->headerNode->pLink;
        if (this->pList->count == 1) // 노드가 하나뿐인 경우
        {
            this->pList->headerNode = NULL;
            free(tmp);
            tmp = 0;
            return (true);
        }
        else if (position == 0) // 여러 개 노드가 있을 때 첫번째 노드(헤더노드의 다음노드)를 제거하려는 경우
        {
            while (tail->pLink != head->pLink)
                tail = tail->pLink;
            this->pList->headerNode->pLink = tmp->pLink;
            tail->pLink = tmp->pLink;
            free(tmp);
            tmp = 0;
            this->pList->count--;
            return (true);
        }
        else // 리스트의 중간에 있는 노드를 제거하는 경우
        {
            i = 0;
            while (++i < position && tmp->pLink != head)  
                tmp = tmp->pLink;
            //해당 position의 직전 노드까지 이동. (tmp)
            curr = tmp->pLink; // curr - 해당 포지션의 노드
            tmp->pLink = curr->pLink;  // getALElement()를 통해 직전 노드의 주소를 받아와서 하는 방법도 있더라. (발표자 코드 참고)
            free(curr);
            curr = 0;
        }
    }
    this->pList->count--;
    // 중간에 노드를 삭제하는 경우 (해당 position노드의 연결을 끊어주고 free()한 뒤, 그 뒤에 있던 노드를 현재 노드의 pLink에 연결)
    return (true);
}

ListNode* List::getLLE(int position)
{
    ListNode    *node;

   if (position > this->pList->count)
   {
       cout<<"[error] Invalid Position value"<<endl;
       return (NULL);
   }
   if (this->pList == NULL)
   {
       cout<<"[error] There is no LinkedList existing"<<endl;
       return (NULL);
   }
   node = this->pList->headerNode->pLink;
   while (position--)
       node = node->pLink;
   return (node);
}

void List::clearLinkedList()
{
    ListNode    *ls;
    int     index;

    if (this->pList == NULL)
    {
        cout<<"[error] There is no LinkedList existing"<<endl;
        return ;
    }
    index = this->pList->count;
    ls = this->pList->headerNode->pLink;
    while (index--)
    {
        ls->coef = 0;
        ls->deg = 0;
        ls = ls->pLink;
    }
}

int List::getLLsize()
{
    if (this->pList == NULL)
        return (0);
    return (this->pList->count);
}

List::~List()
{
    ListNode  *curr;
    ListNode  *tmp;
    
    // 메모리 free() 과정 전에, clearLinkedList()를 쓴 사람들이 있었음. 우리도 그걸 추가하는 게 더 바람직할지도 모름. 
    curr = this->pList->headerNode->pLink;
 	if (this->pList == NULL)
	 	printf("there is no LinkedList existing\n");
	 else
     {
        while(curr) 
        {
            tmp = curr;
            curr = curr->pLink;
            free(tmp);
            tmp = 0;
        }
        free(this->pList);
        this->pList = 0;
    }
}