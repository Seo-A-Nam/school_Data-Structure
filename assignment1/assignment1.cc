#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class   Date {
public :
    int year, month, day;
    Date();
    void    show(void);
};

void Date::show()
{
    cout <<year<<"년"<<month<<"월"<<day<<"일";
}

Date::Date()
{
    time_t t; // rawtime
    struct tm *pTimeinfo;

    t = time(NULL);
    pTimeinfo = localtime(&t);
    year = pTimeinfo->tm_year + 1900;
    month = pTimeinfo->tm_mon + 1;
    day = pTimeinfo->tm_mday;
}

int     calculate_age(string *birth, Date date) // 만 나이를 계산.
{
    int age = 0;

    age = date.year - stoi(birth[0]);
    if ((stoi(birth[1]) > date.month) || ((stoi(birth[1]) == date.month) && stoi(birth[2]) > date.day)) 
            age--; // 월이 더 일찍일 때, 월이 같지만 일 수에서 더 일찍일 때.
    return (age);
}

void    parse_birth(string s, string *birth)
{
    int     index = 0;
    int     cnt = 0;

    while ((index = s.find('/')) != string::npos)
    {
        birth[cnt] = s.substr(0, index);
        cnt++;
        s.erase(0, index + 1);
    }
    birth[cnt] = s;
}

void    trim_info(string *s)
{
    for (int i  = 0; i < 3; i++)
    {
        s[i].erase(remove(s[i].begin(), s[i].end(), ' '), s[i].end()); // 이거 안하면 ~님 앞에 공백 하나 생김
        s[i].erase(remove(s[i].begin(), s[i].end(), ','), s[i].end()); // 쉼표 제거
    }
}

int     main()
{
    //string sentence = "소프트웨어학과, 2019125021, 남서아, 2000/09/01";
    string info[4];
    string birth[3];
    Date date;
    int age;
    
    cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)를 입력하세요>" << endl;
    //  =======================  입력  ===============================
    for (int i = 0; i < 4; i++)
        cin >> info[i]; // cin으로 문자를 받을 시 : 모든 whitespace는 무시하고 저장한다.
    // =======================  처리  ===============================
    trim_info(info); // 입력된 값에서 공백과 쉼표 제거 
    parse_birth(info[3], birth);
    // =======================  출력  ===============================
    cout << info[0]<<" "<<info[1]<<" "<<info[2]<<"님";
    cout<< birth[0]<<"년"<<birth[1]<<"월"<<birth[2]<<"일생"<<" ";
    date.show();
    age = calculate_age(birth, date);
    cout<< " 현재" << age <<"세입니다." <<endl;
    return (0);
}

/* 참고 : 
* https://numerok.tistory.com/29
* https://reakwon.tistory.com/66
* https://blockdmask.tistory.com/417
* https://blossoming-man.tistory.com/entry/cin%EA%B3%BC-scanf%EB%8A%94-%EA%B3%B5%EB%B0%B1-%EB%AC%B8%EC%9E%90%EB%A5%BC-%EC%96%B4%EB%96%BB%EA%B2%8C-%EC%9D%B8%EC%8B%9D%ED%95%98%EB%8A%94%EA%B0%80
*/