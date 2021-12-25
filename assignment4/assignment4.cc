#include <iostream>
#include <string>
#include <list>
using namespace std;

class Polynomial {
private :
    list<int>   lt;
    string  input;
    string  output;
    string  result;
public :
    friend  ostream& operator<<(ostream&, string &input_);
    void    process_input(string input);
    string  make_output(string pair);
    void    addPoly(Polynomial c);
    void    sMultPoly(Polynomial c, Polynomial e);
    void    MultPoly(Polynomial c, Polynomial e);
    string  evalPoly(Polynomial c);
};


void    Polynomial::process_input(string input)
{
    int len = input.size();

    for (int i = 0; i < len; i++)
    {
        if 
    }
    for (int i = 0; i < len; i++)
    {

    }
}

int
     main()
{
    Polynomial a, b, c, d, t;
    int x;

    // cin >> a;
    // // cin >> b;
    // // cin >> c;
    // cout << "A(x) = "<<a;
    // // cout << "B(x) = "<<b<<endl <<"C(x)= "<<c;
    // // t = a * b;
    // // d = t + c;
    // // cout << "T(x) = "<<t;
    // // cout << "D(x) = "<<d;
    // // cin >> x;
    // // cout << "x = "<<x<<"-->"<<d.evalPoly(x);
    return (0);
}
/*
* 연산자 오버로딩 : https://yeolco.tistory.com/119
*
*/