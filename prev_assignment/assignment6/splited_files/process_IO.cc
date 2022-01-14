#include "assignment6.h"


// void    Polynomial::removeZeros()
// {
//     LinkedList *pList = this->poly->get_pList();
//     ListNode *ptr = pList->headerNode->pLink;
//     for (int i = 0; i < pList->count; i++) 
//     {
//         if (ptr->coef == 0)
//             this->poly->removeLLE(pList->count - 1);
//     }
//     if (pList->count == 0)
//     {
//         ListNode ele;
//         memset(&ele, 0, sizeof(ele));
//         this->poly->addLLE(0, ele);
//     }
// } // 0 제거 처리 (0만 있을 경우는 (0,0)을 다시 넣어주어 보존).   
// /*
// * 다항식에 0만 있는 경우 제외하고, 두번째 항으로도 쭉 0(차수 상관없이 계수가 0)이 들어왔다면 그걸 다 제거함. 
// * 이거 안해주면 2x^2에 0을 곱한 경우 0x^2 이렇게 된게 그대로 출력될 수도 있음.
// */

// bool    Polynomial::process_output()
// {
//     string output;
//     LinkedList *pList = this->poly->get_pList();
//     ListNode *poly = pList->headerNode->pLink;
//     string tmp;

//     this->removeZeros(); // 0 관련 예외처리.
//     for (int i = 0; i < pList->count; i++)
//     {
//         // =========================== 계수 표시 ===============================
//         if (poly->coef == 1 && poly->deg == 0) // 상수항일 경우에 1이 출력되도록 함.
//             tmp = to_string(poly->coef);
//         else if (poly->coef == 1 && poly->deg != 0); // 상수항이 아닌데 계수가 1일 경우는 1이 나오지 않도록 함 (ex : 1x (x), x (o))
//         else if (poly->coef < 0)
//         {
//             tmp.append((string)"("); // 캐스팅 이유 : "" 이거는 보통 (const char *)형이라서.
//             tmp.append((to_string(poly->coef)));
//             tmp.append((string)")");
//         } // 계수가 음수일 때 괄호로 묶어줌 
//         else
//             tmp = to_string(poly->coef); // 그 외의 경우. 계수의 숫자를 출력.
//         // ======================= 차수 (차수, 제곱표시) =========================
//         output.append(tmp);
//         if (poly->deg == 0); // 차수가 0일 때 (상수일 때)는 아무것도 안함. (뒤에 x 안 붙여줌.)
//         else if (poly->deg == 1) // 계수가 1차일때는 x 뒤에 제곱 안붙임
//         {
//             output.append((string)"x");
//         }
//         else
//         {
//             output.append((string)"x");
//             output.append((string)"^");
//             output.append(to_string(poly->deg));
//         }
//         // ========== 덧셈 표시
//         if (i != pList->count - 1) // 식의 맨 끝이 아니라면 + 연산자를 뒤에 붙여줌.
//             output.append((string)"+");
//         tmp = ""; // 다음에 output에 잘못된 값 들어가지 않게 매번 쓸때마다 초기화해줌.
//         poly = poly->pLink;
//     }
//     this->output = output;
//     return (true);
// } // vector<<pair<int,int>> 타입의 poly 멤버변수를 처리하여 다항식의 문자열 형태로 변환해줌.

// bool    Polynomial::process_input() // 지수 음수 경우 이외에도 다른 부분도 예외처리해도 되는 지 문의하기.
// {
//     LinkedList *pList = this->poly->get_pList();
//     ListNode *poly = pList->headerNode->pLink; 
//     ListNode ele;
//     //vector<pair <int, int> > poly;
//     string input = this->get_input();
//     int     flag = 0; // 이 플래그로 ( , ) 입력 형식 체크.
//     int     flag2 = 0;  // 이 플래그로 ( , ) 입력 형식 체크.
//     int     coef = -1;
//     int     degree = -1;
//     int     prev = 0;

//     for (int i = 0; i < input.size(); i++)
//     {
//         if (input[i] == '(')
//         {
//             flag++;
//             coef = atoi(input.c_str() + i + 1);
//         }
//         if (input[i] == ',')
//         {
//             flag++;
//             degree = atoi(input.c_str() + i + 1);
//             if (degree < 0) // 지수 음수 입력 시 프로그램 처음으로 돌아가도록 예외처리.
//             {
//                 cout << "[error] negative degree!" <<endl;
//                 return (false);
//             }
//         }
//         if (input[i] == ')')
//         {
//             if (flag != 2) // 이 플래그로 ( , ) 입력 형식 체크.
//             {
//                 cout << "[error] Wrong input format!"<<endl;
//                 return (false);
//             }
//             flag = 0;
//             flag2 = 1;
//             if (coef == 0 && degree != 0) //차수가 0이 아닌데 계수가 0이면 그 항은 결국 0이 된다. 예외처리 해줌. 
//             {
//                 cout <<"[error] Incorrect coefficient value!"<<endl;
//                 return (false);
//             }
//             ele.coef = coef;
//             ele.deg = degree;
//             ele.pLink = NULL;
//             this->poly->addLLE(i, ele);
//         }
//     }
//     if (flag2 == 0) // 이 플래그로 ( , ) 입력 형식 체크.
//     {
//         cout << "[error] Wrong input format!"<<endl;
//         return (false);
//     }
//     sort_poly(this->get_poly()); // 만약에 addLLE 함수에 자동정렬 기능을 넣었다면 더 좋았겠지만 그건 더 귀찮아서 이렇게만듬 ㅠㅠ
//     //sort(poly, poly.end(), comp); // 계수가 내림차순이 되도록 정렬함. (지시 상, 정렬 안된 상태로 입력 받았어도 따로 에러처리 해주지 않는다).
//     for (int i = 0; i < pList->count; i++)
//     {
//         if (i > 0 && (poly->deg == prev))
//         {
//             cout << "[error] duplicated homogenious"<<endl;
//         }
//         prev = poly->deg;
//         poly = poly->pLink;
//     } // 동차항 반복 오류처리 
//     // 항들이 내림차순으로 정렬되어있는 상태인데, 저번 차수와 이번 차수가 같으면 동차항이 반복되어 입력된 것이므로 오류이다.
//     this->removeZeros(); // 0 제거 처리 (0만 있을 경우는 보존). 
//     return (true);
// } // input된 string을 파싱 처리하여 vector<<pair<int,int>> 타입의 poly 멤버변수에 넣어줌.
