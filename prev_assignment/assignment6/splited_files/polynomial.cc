 #include "assignment6.h"

// List    *Polynomial::get_poly()
// {
//     return (poly);
// }

// string Polynomial::get_output()
// {
//     return (output);
// }

// string Polynomial::get_input()
// {
//     return (input);
// }

// void    Polynomial::addPoly(List* list1, List* list2)
// {
//     List list;
//     ListNode *ptr1 = (list1->get_pList()->headerNode->pLink), *ptr2 = (list2->get_pList()->headerNode->pLink); 
//     int coef1, coef2, deg1, deg2;
//     int index = 0;

//     while (1)
//     {
//         coef1 = ptr1->coef;
//         deg1 = ptr1->deg;
//         coef2 = ptr2->coef;
//         deg2 = ptr2->deg;
//         if (ptr1 == NULL && ptr2 == NULL)
//             break;
//         if (ptr1 == NULL) // 만약 1번 다항식을 다 돌았다면, 2번 다항식의 항을 결과 다항식에 추가한다.
//         {
//             ListNode ele = {coef2, deg2, 0};
//             list.addLLE(index, ele);
//             ptr2 = ptr2->pLink;
//         }
//         else if (ptr2 == NULL) // 만약 2번 다항식을 다 돌았다면, 1번 다항식의 항을 결과 다항식에 추가한다.
//         {
//             ListNode ele = {coef1, deg1, 0};
//             list.addLLE(index, ele);
//             ptr1 = ptr1->pLink;
//         }
//         else if (deg1 == deg2)
//         {
//             if ((coef1 + coef2) != 0) // 두 항의 합이 0이 아닐 경우에만 다항식에 넣어줌.
//             {
//                 ListNode ele = {coef1 + coef2, deg1 + deg2, 0};
//                 list.addLLE(index, ele);
//                 ptr1 = ptr1->pLink;
//                 ptr2 = ptr2->pLink;
//             }
//         }
//         else if (deg1 > deg2)
//         {
//             ListNode ele = {coef1, deg1, 0};
//             list.addLLE(index, ele);
//             ptr1 = ptr1->pLink;
//         }
//         else // deg1 < deg2 인 경우.
//         {
//             ListNode ele = {coef2, deg2, 0};
//             list.addLLE(index, ele);
//             ptr2 = ptr2->pLink;
//             j++;
//         }
//         index++;
//     }
//     this->poly->get_pList() = list.get_pList();
//     this->removeZeros();
//     this->process_output();
// } // vector<<pair<int,int>> 타입의 poly 멤버변수를 돌면서 차수와 계수를 비교. 다항식 덧셈을 수행함

// void    Polynomial::sMultPoly(List *a, LinkedNode b)
// {
//     List list;
//     ListNode *ptr1 = a->get_pList()->headerNode->pLink;
//     ListNode *ptr2 = b;
//     int size1, size2, coef, deg;
    
//     size1 = ptr1->count;
//     size2 = ptr2->count;
//     // if (size1 != 1 && size2 != 1) // 하나가 단항식이여야 한다. 따라서 둘 다 다항식일 경우를 예외처리.
//     // {
//     //     cout << "[error] There is no match with monomial"<<endl;
//     //     return ;
//     // }
//     if (size1 == 1)
//     {
//         for (int i = 0; i < size2; i++)
//         {
//             coef = ptr1-> * a.poly[0].first;
//             deg = b.poly[i].second + a.poly[0].second;
//             poly.push_back(make_pair(coef, deg));
//         }
//     }
//     else if (size2 == 1)
//     {
//         for (int i = 0; i < size1; i++)
//         {
//             coef = a.poly[i].first * b.poly[0].first;
//             deg = a.poly[i].second + b.poly[0].second;
//             poly.push_back(make_pair(coef, deg));
//         }
//     }
//     if (this->poly.size() == 0)
//     {
//         this->poly = poly;
//         this->process_output();
//     }
//     else
//         this->addPoly(this->poly, poly); // 기존에 저장된 식이 있던 경우에는 이번에 곱한 값이랑 더해준다.
// }

// void    Polynomial::MultPoly(Polynomial a, Polynomial b) // 자기 자신을 인자로 넣어준 경우, 처리해줘야하는가? - 아직은 안함.
// {
//     int size;

//     size = b.poly.size();
//     for (int i = 0; i < size; i++) // b의 모든 항을 돈다.
//     {
//         Polynomial tmp;
//         tmp.poly.push_back(b.poly[i]);
//         this->sMultPoly(a, tmp); // b의 모든 항을 하나씩 가져와서, a에 단항식 곱셈을 수행함
//     }
//     this->removeZeros();
// }

// string  Polynomial::evalPoly(int x) // 다항식에 x의 값을 대입해서 계산.
// {
//     List poly = get_poly(); // this 없어도 돌아가나?
//     int coef = 0, deg = 0, sum = 0;

//     for (int i = 0; i < poly.size(); i++)
//     {
//         coef = poly[i].first;
//         deg = poly[i].second;
//         sum += coef * pow(x, deg);
//     }
//     return (to_string(sum));
// }
