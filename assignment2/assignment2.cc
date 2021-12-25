#include <iostream>
#include <stdbool.h>
#include <string>
#include <cstdlib>
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
            age--; // 월이 더 일찍일 때, 또는 월이 같지만 일 수에서 더 일찍일 때.
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

int     err_terminate()
{
    cout<<"[error] Terminate the program"<<endl;
    return (1);
}

bool    check_num(const char *s)
{
    int i = 0;
    int len = strlen(s);

    while (i < len)
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (0);
        i++;
    }
    return (true);
} // 학번은 10자리 숫자이므로 atoi 쓸 수 없다. (atoi - int 최대값 (8자리)까지만 작동). 따라서 함수 따로 만듬

bool    check_inputFormat(string *s)
{
    int slash = 0;
    int flag = 0;
    
    try {
        for (int i = 0; i < 3; i++)
        {
            flag = 0;
            for (int j = s[i].size() - 1; j > 0; j--) // string의 뒤에서부터 쉼표 찾기
            {
                if (s[i][j] == ',')
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                throw ("comma");
        }
        for (int i = 0; i < s[3].size(); i++)
        {
            if (s[3][i] == '/')
                slash++;
        }
        if (slash != 2)
            throw ("slash");
    }
    catch (const char *err) {
        cout << "[error] Incorrect input format of " <<err<<endl;
        return (false);
    }
    return (true);
} // 입력된 형식이 올바른 지 쉼표(,)와 슬래시(/) 개수를 세서 판별

bool    check_birthFormat(string *birth, Date date)
{
    try {
        int end_days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 말일 - 윤년 2월은 따로 처리해줄 것
        int byear = atoi(birth[0].c_str()), bmonth = atoi(birth[1].c_str()), bday = atoi(birth[2].c_str());

        if (byear < 0 || byear > date.year)
            throw("Birth : year");
        if (bmonth < 1 || bmonth > 12)
            throw("Birth : month");
        if (bday < 0 || bday > 31) // 기본 적인 일 범위 초과
            throw ("Birth : day");
        if ((byear % 4 != 0) && (bmonth == 2 && bday > 28)) // 윤년이 아닌데 2월에 29일 이상이면 오류
            throw("Birth : day");
        if (bday > end_days[bmonth - 1])
            throw("Birth : day");
    } // 생일 체크 (음수여선 안됨. 월(1~12), 일(1~31 또는 1~30)의 범위에 있어야함. 현재 시간 보다 늦으면 안됨)
    catch (const char *err) {
        cout << "[error] invalid range of "<<err<<endl;
        return (false);
    }
    return (true);
}

int     check_infoFomat(string *s, string *birth)
{
    try { // 문자열이면 atoi가 0 나온다.
        if (atoi(s[0].c_str()) != 0) 
            throw ("Major");
        if (check_num(s[1].c_str()) == 0) 
            throw ("Student number");
        if (atoi(s[2].c_str()) != 0)
            throw ("Name");
        for (int i = 0; i < 3; i++)
        {
            if (atoi(birth[i].c_str()) == 0)
                throw ("Birth");
        }
    }  // 인자 format을 체크 (학과(문자열) -> 학번(숫자) -> 이름(문자열) -> 생일(숫자))
    catch (const char *err) {
        cout << "[error] Wrong format : "<<err<<endl;
        return (0);
    }
    return (1);
}

int     main()
{
    //string info = "소프트웨어학과, 2019125021, 남서아, 2000/09/01";
    string info[4];
    string birth[3];
    Date date;
    int age;
    
    cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)를 입력하세요>" << endl;
    // =======================  입력   ===============================
    for (int i = 0; i < 4; i++)
        cin >> info[i]; // cin으로 문자를 받을 시 : 모든 whitespace는 무시하고 저장한다.
    if (!check_inputFormat(info)) // 입력값 형식 (쉼표, /)를 체크함
        return (err_terminate());
    //  =======================  처리   ===============================
    trim_info(info); // 입력된 값 다듬기 (공백과 쉼표 제거) 
    parse_birth(info[3], birth); // 생일 정보(연도-월-일)를 각각 문자 배열에 넣기. 
    if (!(check_infoFomat(info, birth) || check_birthFormat(birth, date))) // 입력된 정보값이 유효한 지 확인.
        return (err_terminate());
    // =======================   출력  ===============================
    cout << info[0]<<" "<<info[1]<<" "<<info[2]<<"님";
    cout<< birth[0]<<"년"<<birth[1]<<"월"<<birth[2]<<"일생"<<" ";
    date.show();
    age = calculate_age(birth, date);
    cout<< " 현재" << age <<"세입니다." <<endl;
    return (0);
}

/* 참고 : 
* https://blockdmask.tistory.com/55
*/