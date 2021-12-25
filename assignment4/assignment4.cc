#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <utility>
using namespace std;

// 1 + x + x^2 같이 순차적으로 들어오는 경우면 ㄱㅊ지만 1 + x^2와 같이 차수를 건너뛰는 경우를 대비해서 계수 정보까지 넣어줌.

class Polynomial {
public :
    list<pair<int, int>> lt;
    string  input;
    string  output;
    string  result;
    friend std::istream& operator>>(istream& inputStream, Polynomial& c);
    friend std::ostream& operator<<(ostream& outputStream, Polynomial& c);
    bool    process_input(string s);
    // string  make_output(string pair);
    // void    addPoly(Polynomial c);
    // void    sMultPoly(Polynomial c, Polynomial e); // 다항식의 단항 곱셈
    // void    MultPoly(Polynomial c, Polynomial e);
    // string  evalPoly(Polynomial c); // x = c 일 때 다항식의 값을 계산
};

istream& operator>>(istream& inputStream, Polynomial& c)
{
    inputStream >> c.input;
    return (inputStream);
}

ostream& operator<<(ostream& outputStream, Polynomial& c)
{
    outputStream << c.input << endl;
    return (outputStream);
}


bool    process_input(string s)
{
    list<pair<int, int>> lt; 
    int     flag = 0; // 이 플래그로 ( , ) 입력 형식 체크.
    int     coef = -1;
    int     degree = -1;

    cout<<"!!!"<<endl;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            flag = 1;
            coef = atoi(s.c_str() + i + 1);
        }
        if (s[i] == ',')
        {
            flag++;
            degree = atoi(s.c_str() + i + 1);
            if (degree < 0)
            {
                cout << "[error] negative degree!" <<endl;
                return (false);
            }
        }
        if (s[i] == ')')
        {
            if (flag != 2)
            {
                cout << "[error] Wrong input format!"<<endl;
                return (false);
            }
            lt.push_back({coef, degree});
        }
    }
    list<pair<int, int>>::iterator iter;
    for(iter = lt.begin(); iter != lt.end(); iter++){
        cout << "[" << iter->first << "," << iter->second << "]" << endl;
    }

    return (true);
} // 일단 ( , ) 형식 체크는 생략해둠. 나중에 보완하기.
// 만약 (계수, 차수)의 순서가 뒤죽박죽이면 어떡할까? 오름차순이 아니라면
// 정렬해서 그냥 그대로 쓰기? 아니면 원래꺼와 정렬된 거 비교 후 에러 출력?

int     main()
{
    Polynomial a, b, c, d, t;
    int x;
    
    cin >> a; // a에 점(.) 입력 시 함수 종료되도록 해야함.
    //cout<<a;
    //string s = "(2,2)(1,2)(3, 3)(1,0)";
    //cout<<s<<endl;
    process_input(a.input);
    // cin >> b;
    // cin >> c;
    // cout << "A(x) = "<<a;
    // cout << "B(x) = "<<b<<endl <<"C(x)= "<<c;
    // t = a * b;
    // d = t + c;
    // cout << "T(x) = "<<t;
    // cout << "D(x) = "<<d;
    // cin >> x;
    // cout << "x = "<<x<<"-->"<<d.evalPoly(x);
    return (0);
}
/*
* 연산자 오버로딩 : https://yeolco.tistory.com/119
* https://movahws.tistory.com/15
* 리스트 컨테이너 : https://blockdmask.tistory.com/76
*/