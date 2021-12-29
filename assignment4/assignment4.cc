#include <iostream> // bool, cin, cout, ... 
#include <string>
#include <algorithm> // sort()
#include <vector>
#include <utility> // pair 함수 있음
#include <cmath> // pow()

using namespace std;


bool    comp(pair<int, int> a, pair<int, int> b)
{
    return (a.second > b.second);
}

class Polynomial {
private :
    vector<pair<int,int> > poly; // pair = <계수, 차수> : 입력값을 다듬어 다항식 만든 것.
    // 1 + x + x^2 같이 순차적으로 들어오는 경우면 ㄱㅊ지만 1 + x^2와 같이 차수를 건너뛰는 경우를 대비해서 계수 정보까지 넣어줌.
    string  input; // ( , )( , ) 이런 형태로 입력받은 입력값 그 자체.
    string  output; // poly를 통해 완성한 다항식 수식 문자열.
public :
    bool    process_input();
    bool    process_output();
    void    addPoly(vector<pair<int, int> > poly1, vector<pair<int, int> > poly2);
    void    sMultPoly(Polynomial c, Polynomial e); // 다항식의 단항 곱셈
    void    MultPoly(Polynomial c, Polynomial e);
    string  evalPoly(int x); // x = c 일 때 다항식의 값을 계산
    void    removeZeros();
    vector<pair<int,int> >  get_poly();
    string                  get_output();
    string                  get_input();
    friend std::istream&    operator>>(istream& inputStream, Polynomial& c);
    friend Polynomial       operator+(Polynomial &a, Polynomial &b);
    friend std::ostream&    operator<<(ostream& outputStream, Polynomial& c);
};

void    Polynomial::removeZeros()
{
    for (int i = 0; i < this->poly.size(); i++) 
    {
        if (this->poly[i].first == 0)
            this->poly.pop_back();
    }
    if (this->poly.size() == 0)
        this->poly.push_back(make_pair(0, 0));
} // 0 제거 처리 (0만 있을 경우는 보존).   
/*
* 다항식에 0만 있는 경우 제외하고, 두번째 항으로도 쭉 0(차수 상관없이 계수가 0)이 들어왔다면 그걸 다 제거함. 
* 이거 안해주면 2x^2에 0을 곱한 경우 0x^2 이렇게 된게 그대로 출력될 수도 있음.
*/
vector<pair<int,int> > Polynomial::get_poly()
{
    return (poly);
}

string Polynomial::get_output()
{
    return (output);
}

string Polynomial::get_input()
{
    return (input);
}

void    Polynomial::addPoly(vector<pair<int, int> > poly1, vector<pair<int, int> > poly2)
{
    vector<pair<int, int> > poly3;
    int size1 = poly1.size(), size2 = poly2.size();
    int coef1, coef2, deg1, deg2;
    int index = 0, i = 0, j = 0, end = 0;

    while (1)
    {
        coef1 = poly1[i].first;
        deg1 = poly1[i].second;
        coef2 = poly2[j].first;
        deg2 = poly2[j].second;
        if (i == size1 && j == size2)
            break;
        if (i == size1) // 만약 1번 다항식을 다 돌았다면, 2번 다항식의 항을 결과 다항식에 추가한다.
        {
            poly3.push_back(make_pair(coef2, deg2));
            j++;
        }
        else if (j == size2) // 만약 2번 다항식을 다 돌았다면, 1번 다항식의 항을 결과 다항식에 추가한다.
        {
            poly3.push_back(make_pair(coef1, deg1));
            i++;
        }
        else if (deg1 == deg2)
        {
            if ((coef1 + coef2) != 0) // 두 항의 합이 0이 아닐 경우에만 다항식에 넣어줌.
                poly3.push_back(make_pair(coef1 + coef2, deg1));
            i++;
            j++;
        }
        else if (deg1 > deg2)
        {
            poly3.push_back(make_pair(coef1, deg1));
            i++;
        }
        else // deg1 < deg2 인 경우.
        {
            poly3.push_back(make_pair(coef2, deg2));
            j++;
        }
    }
    this->poly = poly3;
    this->removeZeros();
    this->process_output();
} // vector<<pair<int,int>> 타입의 poly 멤버변수를 돌면서 차수와 계수를 비교. 다항식 덧셈을 수행함

bool    Polynomial::process_output()
{
    string output;
    vector<pair<int, int> > poly;
    string tmp;

    this->removeZeros(); // 0 관련 예외처리.
    poly = this->get_poly();
    for (int i = 0; i < poly.size(); i++)
    {
        // =========================== 계수 표시 ===============================
        if (poly[i].first == 1 && poly[i].second == 0) // 상수항일 경우에 1이 출력되도록 함.
            tmp = to_string(poly[i].first);
        else if (poly[i].first == 1 && poly[i].second != 0); // 상수항이 아닌데 계수가 1일 경우는 1이 나오지 않도록 함 (ex : 1x (x), x (o))
        else if (poly[i].first < 0)
        {
            tmp.append((string)"("); // 캐스팅 이유 : "" 이거는 보통 (const char *)형이라서.
            tmp.append((to_string(poly[i].first)));
            tmp.append((string)")");
        } // 계수가 음수일 때 괄호로 묶어줌 
        else
            tmp = to_string(poly[i].first); // 그 외의 경우. 계수의 숫자를 출력.
        // ======================= 차수 (차수, 제곱표시) =========================
        output.append(tmp);
        if (poly[i].second == 0); // 차수가 0일 때 (상수일 때)는 아무것도 안함. (뒤에 x 안 붙여줌.)
        else if (poly[i].second == 1) // 계수가 1차일때는 x 뒤에 제곱 안붙임
        {
            output.append((string)"x");
        }
        else
        {
            output.append((string)"x");
            output.append((string)"^");
            output.append(to_string(poly[i].second));
        }
        // ========== 덧셈 표시
        if (i != poly.size() - 1)
            output.append((string)"+");
        tmp = ""; // 다음에 output에 잘못된 값 들어가지 않게 매번 쓸때마다 초기화해줌.
    }
    this->output = output;
    return (true);
} // vector<<pair<int,int>> 타입의 poly 멤버변수를 처리하여 다항식의 문자열 형태로 변환해줌.

bool    Polynomial::process_input() // 지수 음수 경우 이외에도 다른 부분도 예외처리해도 되는 지 문의하기.
{
    vector<pair <int, int> > poly;
    string input = this->get_input();
    int     flag = 0; // 이 플래그로 ( , ) 입력 형식 체크.
    int     flag2 = 0;  // 이 플래그로 ( , ) 입력 형식 체크.
    int     coef = -1;
    int     degree = -1;
    int     prev = 0;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(')
        {
            flag++;
            coef = atoi(input.c_str() + i + 1);
        }
        if (input[i] == ',')
        {
            flag++;
            degree = atoi(input.c_str() + i + 1);
            if (degree < 0) // 지수 음수 입력 시 프로그램 처음으로 돌아가도록 예외처리.
            {
                cout << "[error] negative degree!" <<endl;
                return (false);
            }
        }
        if (input[i] == ')')
        {
            if (flag != 2) // 이 플래그로 ( , ) 입력 형식 체크.
            {
                cout << "[error] Wrong input format!"<<endl;
                return (false);
            }
            flag = 0;
            flag2 = 1;
            if (coef == 0 && degree != 0) //차수가 0이 아닌데 계수가 0이면 그 항은 결국 0이 된다. 예외처리 해줌. 
            {
                cout <<"[error] Incorrect coefficient value!"<<endl;
                return (false);
            }
            poly.push_back(make_pair(coef, degree));
        }
    }
    if (flag2 == 0) // 이 플래그로 ( , ) 입력 형식 체크.
    {
        cout << "[error] Wrong input format!"<<endl;
        return (false);
    }
    sort(poly.begin(), poly.end(), comp); // 계수가 내림차순이 되도록 정렬함. (지시 상, 정렬 안된 상태로 입력 받았어도 따로 에러처리 해주지 않는다).
    for (int i = 0; i < poly.size(); i++)
    {
        if (i > 0 && (poly[i].second == prev))
        {
            cout << "[error] duplicated homogenious"<<endl;
        }
        prev = poly[i].second;
    } // 동차항 반복 오류처리 
    // 항들이 내림차순으로 정렬되어있는 상태인데, 저번 차수와 이번 차수가 같으면 동차항이 반복되어 입력된 것이므로 오류이다.
    this->poly = poly;
    this->removeZeros(); // 0 제거 처리 (0만 있을 경우는 보존). 
    return (true);
} // input된 string을 파싱 처리하여 vector<<pair<int,int>> 타입의 poly 멤버변수에 넣어줌.

void    Polynomial::sMultPoly(Polynomial a, Polynomial b)
{
    vector<pair <int, int> > poly;
    int size1, size2, coef, deg;
    
    size1 = a.poly.size();
    size2 = b.poly.size();
    if (size1 != 1 && size2 != 1) // 하나가 단항식이여야 한다. 따라서 둘 다 다항식일 경우를 예외처리.
    {
        cout << "[error] There is no match with monomial"<<endl;
        return ;
    }
    if (size1 == 1)
    {
        for (int i = 0; i < size2; i++)
        {
            coef = b.poly[i].first * a.poly[0].first;
            deg = b.poly[i].second + a.poly[0].second;
            poly.push_back(make_pair(coef, deg));
        }
    }
    else if (size2 == 1)
    {
        for (int i = 0; i < size1; i++)
        {
            coef = a.poly[i].first * b.poly[0].first;
            deg = a.poly[i].second + b.poly[0].second;
            poly.push_back(make_pair(coef, deg));
        }
    }
    if (this->poly.size() == 0)
    {
        this->poly = poly;
        this->process_output();
    }
    else
        this->addPoly(this->poly, poly); // 기존에 저장된 식이 있던 경우에는 이번에 곱한 값이랑 더해준다.
}

void    Polynomial::MultPoly(Polynomial a, Polynomial b) // 자기 자신을 인자로 넣어준 경우, 처리해줘야하는가? - 아직은 안함.
{
    int size;

    size = b.poly.size();
    for (int i = 0; i < size; i++) // b의 모든 항을 돈다.
    {
        Polynomial tmp;
        tmp.poly.push_back(b.poly[i]);
        this->sMultPoly(a, tmp); // b의 모든 항을 하나씩 가져와서, a에 단항식 곱셈을 수행함
    }
    this->removeZeros();
}

string  Polynomial::evalPoly(int x) // 다항식에 x의 값을 대입해서 계산.
{
    vector<pair<int, int> > poly = get_poly(); // this 없어도 돌아가나?
    int coef = 0, deg = 0, sum = 0;

    for (int i = 0; i < poly.size(); i++)
    {
        coef = poly[i].first;
        deg = poly[i].second;
        sum += coef * pow(x, deg);
    }
    return (to_string(sum));
}

istream& operator>>(istream& inputStream, Polynomial& c)
{
    inputStream >> c.input;
    if (c.input == (string)".") // 점(.) 입력 시 프로그램을 종료.
    {
        cout << "================ Terminate the program ================"<<endl;
        exit(0);
    }
    return (inputStream);
}

ostream& operator<<(ostream& outputStream, Polynomial& c)
{
    outputStream << c.output;
    return (outputStream);
}

Polynomial operator+(Polynomial &a, Polynomial &b) // a + b 만 가능. 3개 이상의 다항식은 덧셈 불가.
{
    Polynomial result;
    vector<pair<int, int> > poly1 = a.get_poly();
    vector<pair<int, int> > poly2 = b.get_poly();

    result.addPoly(poly1, poly2);
    return (result);
} // 자기 자신을 인자 중 하나로 넣는 경우에도 잘 작동함!

Polynomial operator*(Polynomial &a, Polynomial &b) // a * b 만 가능. 3개 이상의 다항식은 곱셈 불가.
{
    Polynomial result;

    result.MultPoly(a, b);
    return (result);
} // 자기 자신을 인자 중 하나로 넣는 경우에도 잘 작동함!

int     main()
{
    // 주의 : 입력 값에서 3x^2 + 0 이렇게 받아도 따로 예외처리 안하고 0만 제거해서 3x^2 이렇게 들어가게 해줌.
    while (1)
    {
        Polynomial a, b, c, d, t;
        int x;
        bool check1, check2, check3;

        cin >> a;
        cin >> b;
        cin >> c;  // a에 점(.) 입력 시 함수 종료되도록 해야함.
        if ((check1 = a.process_input()) == false || (check2 = b.process_input()) == false
            || (check3 = c.process_input()) == false) 
        {
            cout <<endl <<"============= Restart the program ================" <<endl <<endl;
            continue;
        } // 지수 음수 입력 시 프로그램 처음으로 돌아가도록 예외처리
        a.process_output();
        b.process_output();
        c.process_output();
        cout << "A(x) = "<< a << endl;
        cout << "B(x) = "<<b << endl;
        cout<<"C(x) = "<<c<<endl;
        t = a * b;
        d = t + c;
        cout << "T(x) = "<<t<<endl;
        cout << "D(x) = "<<d<<endl;
        cin >> x;
        cout << "x = "<<x<<"-->"<<d.evalPoly(x);
        break; // 프로그램 끝까지 정상적으로 왔으면 끝남.
    }
    return (0);
}
/*
* 연산자 오버로딩 : https://yeolco.tistory.com/119
* https://movahws.tistory.com/15
* https://musket-ade.tistory.com/entry/C-%EC%97%B0%EC%82%B0%EC%9E%90-%EC%98%A4%EB%B2%84%EB%A1%9C%EB%94%A9
* 삼항연산자 : http://dev-bear.com/archives/96
* 다항식 계산기 : https://ko.numberempire.com/expressioncalculator.php
*/