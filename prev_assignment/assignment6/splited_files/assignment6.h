#ifndef _ASSIGNMENT6_H_
#define _ASSIGNMENT6_H_

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

// ====================== process_IO.cc ========================
void    splitHeads(List *list, List *list_a, List *list_b);
List  *sort_Merge(List *merge_a, List *merge_b);
List  *mergeSort(List *List);
void    sort_poly(List *poly);

// ======================  main.cc =============================
istream& operator>>(istream& inputStream, Polynomial& c);
ostream& operator<<(ostream& outputStream, Polynomial& c);
Polynomial operator+(Polynomial &a, Polynomial &b);
Polynomial operator*(Polynomial &a, Polynomial &b);

#endif