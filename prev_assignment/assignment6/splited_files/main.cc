//#include "assignment6.h"


#include <iostream> // bool, cin, cout, ... 
#include <string>
#include <algorithm> // sort()
#include <vector>
#include <utility> // pair 함수 있음
#include <cmath> // pow()
using namespace std;

struct ListNode
{
    int coef; // 계수
    int deg; // 차수
    struct ListNode* pLink;
};
struct LinkedList
{
    int count;	// 현재 인덱스의 개수
    ListNode *headerNode;		// data와 다음 주소를 가르키는 포인터
};

class List {
    private : 
        LinkedList *pList;
    public : 
        List();
        bool addLLE(int position, ListNode element);
        bool removeLLE(int position);
        ListNode* getLLE(int position);
        void clearLinkedList(); // 링크드리스트의 요소들을 전부 0으로 초기화함.
        int getLLsize();
        ~List();
        LinkedList* get_pList();
};

class Polynomial {
private :
    List *poly; // <계수, 차수> : 입력값을 다듬어 다항식 만든 것.
    string  input; // ( , )( , ) 이런 형태로 입력받은 입력값 그 자체.
    string  output; // poly를 통해 완성한 다항식 수식 문자열.
public :
    // bool    process_input();
    // bool    process_output();
    // void    addPoly(List* poly1, List* poly2);
    // void    sMultPoly(Polynomial c, Polynomial e); // 다항식의 단항 곱셈
    // void    MultPoly(Polynomial c, Polynomial e);
    // string  evalPoly(int x); // x = c 일 때 다항식의 값을 계산
    // void    removeZeros();
     List  *get_poly();
    // string                  get_output();
    // string                  get_input();
    // friend std::istream&    operator>>(istream& inputStream, Polynomial& c);
    // friend Polynomial       operator+(Polynomial &a, Polynomial &b);
    // friend std::ostream&    operator<<(ostream& outputStream, Polynomial& c);
};

void    splitHeads(List *list, List *list_a, List *list_b)
{
    LinkedList *pList = list->get_pList();
    LinkedList *pList_a = list_a->get_pList();
    LinkedList *pList_b = list_b->get_pList();

    if (pList == NULL || pList_a == NULL || pList_b == NULL)
    {
        printf("[error] There is no LinkedList existing.\n");
        return ;
    }
	int len = pList->count;
    ListNode *node = pList->headerNode->pLink;
    for (int i = 0; i < (len / 2); i++)
    {
        list_a->addLLE(i, *node);
        node = node->pLink;
    }
    for (int i = 0; i < len - (len / 2); i++)
    {
        list_b->addLLE(i, *node);
        node = node->pLink;
    }
    delete list;
} // 주어진 리스트를 반으로 쪼갬.

List  *sort_Merge(List *merge_a, List *merge_b)
{
    List  *ls = new List;
    ListNode  *ptr_a = merge_a->get_pList()->headerNode->pLink;
    ListNode  *ptr_b = merge_b->get_pList()->headerNode->pLink;
    ListNode *head1 = merge_a->get_pList()->headerNode;
    ListNode *head2 = merge_b->get_pList()->headerNode;
    int count = merge_a->get_pList()->count + merge_b->get_pList()->count;
    int i = 0;

    while (i < count)
    {
        if (ptr_a == head1->pLink) // 아래 elif 문과 합치지 말 것. segfault 남. 
        {
            ls->addLLE(i, *ptr_b);
            ptr_b = ptr_b->pLink;
        }
        else if (ptr_b == head2->pLink) // 아래 elif 문과 합치지 말 것. segfault 남.
        {
            ls->addLLE(i, *ptr_a);
            ptr_a = ptr_a->pLink;
        }
        else if (ptr_a->deg > ptr_b->deg)
        {
            ls->addLLE(i, *ptr_b);
            ptr_b = ptr_b->pLink;
        }
        else
		{
            ls->addLLE(i, *ptr_a);
			ptr_a = ptr_a->pLink;
		}
        i++;
    }
    delete merge_a;
    delete merge_b;
	return (ls);
} // 2개의 리스트를 정렬해가며 합침

List  *mergeSort(List *ls)
{
    if (ls->get_pList()->count == 1)
        return (ls); // 리턴 조건
    List *pList_a = new class List;
	List *pList_b = new class List;
    List *merge_a;
    List *merge_b;
    List *list;

    splitHeads(ls, pList_a, pList_b);
    merge_a = mergeSort(pList_a);
    merge_b = mergeSort(pList_b);
    list = sort_Merge(merge_a, merge_b);
    return (list);
}

void    sort_poly(List *poly)
{
    poly = mergeSort(poly);
}
// istream& operator>>(istream& inputStream, Polynomial& c)
// {
//     inputStream >> c.input;
//     if (c.input == (string)".") // 점(.) 입력 시 프로그램을 종료.
//     {
//         cout << "================ Terminate the program ================"<<endl;
//         exit(0);
//     }
//     return (inputStream);
// }

// ostream& operator<<(ostream& outputStream, Polynomial& c)
// {
//     outputStream << c.output;
//     return (outputStream);
// }

// Polynomial operator+(Polynomial &a, Polynomial &b) // a + b 만 가능. 3개 이상의 다항식은 덧셈 불가.
// {
//     Polynomial result;
//     LinkedList *poly1 = a.get_poly();
//     LinkedList *poly2 = b.get_poly();

//     result.addPoly(poly1, poly2);
//     return (result);
// } // 자기 자신을 인자 중 하나로 넣는 경우에도 잘 작동함!

// Polynomial operator*(Polynomial &a, Polynomial &b) // a * b 만 가능. 3개 이상의 다항식은 곱셈 불가.
// {
//     Polynomial result;

//     result.MultPoly(a, b);
//     return (result);
// } // 자기 자신을 인자 중 하나로 넣는 경우에도 잘 작동함!

int     main()
{
    // 주의 : 입력 값에서 3x^2 + 0 이렇게 받아도 따로 예외처리 안하고 0만 제거해서 3x^2 이렇게 들어가게 해줌.
    // while (1)
    // {
    //     Polynomial a, b, c, d, t;
    //     int x;
    //     bool check1, check2, check3;

    //     cin >> a;
    //     cin >> b;
    //     cin >> c;  // a에 점(.) 입력 시 함수 종료되도록 해야함.
    //     if ((check1 = a.process_input()) == false || (check2 = b.process_input()) == false
    //         || (check3 = c.process_input()) == false) 
    //     {
    //         cout <<endl <<"============= Restart the program ================" <<endl <<endl;
    //         continue;
    //     } // 지수 음수 입력 시 프로그램 처음으로 돌아가도록 예외처리
    //     a.process_output();
    //     b.process_output();
    //     c.process_output();
    //     cout << "A(x) = "<< a << endl;
    //     cout << "B(x) = "<<b << endl;
    //     cout<<"C(x) = "<<c<<endl;
    //     t = a * b;
    //     d = t + c;
    //     cout << "T(x) = "<<t<<endl;
    //     cout << "D(x) = "<<d<<endl;
    //     cin >> x;
    //     cout << "x = "<<x<<"-->"<<d.evalPoly(x);
    //     break; // 프로그램 끝까지 정상적으로 왔으면 끝남.
    // }
    // Polynomial poly;
    ListNode ele;
    List *list = new List;
    memset(&ele, 0, sizeof(ele));
    ele.deg = 10;
    cout<<"1"<<endl;
    list->addLLE(0,ele);
    cout<<"1"<<endl;
    ele.deg = 30;
    list->addLLE(1,ele);
    cout<<"1"<<endl;
    ele.deg = 20;
    list->addLLE(2`ele);
    cout<<"1"<<endl;
    ele.deg = 40;
    list->addLLE(3,ele);
    cout<<"1"<<endl;
    sort_poly(list);
    ListNode *head = list->get_pList()->headerNode;
    for (ListNode *ptr = head; ptr->pLink != head; ptr = ptr->pLink)
    {
        cout<<ptr->deg<<endl;
    }
    delete list;
    return (0);
}
