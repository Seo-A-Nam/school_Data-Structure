#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <cstdbool>
using namespace std;

bool    err_terminate()
{
    cout << "[error] Terminate the program"<<endl;
    return (false);
} // 에러 발생 시 프로그램 종료.

void    display_txt(vector<string> s)
{
    int len = s.size();

    cout <<endl;
    for (int i = 0; i < len; i++)
    {
        cout << "index ["<< i + 1<< "] : "<< s[i] << endl;
    }
    cout <<endl;
} // 문자열의 인덱스 : 문자열 쌍으로 모든 단어들을 출력.

int     binarySearch_recursion(vector<string> s, string input, int left, int right)
{ // 여기서 s를 포인터로 안보내는 이유 : 여기서는 문자열 비교-확인만 하고 직접적인 삭제/수정 등은 하지 않기 때문에.
    int mid;

    if (left <= right)
    {
        mid = (left + right) / 2;
        if (s[mid] == input)
            return (mid);
        if (s[mid] < input)
            return (binarySearch_recursion(s, input, mid + 1, right));
        if (s[mid] > input)
            return (binarySearch_recursion(s, input, left, mid - 1));
    }
    return (-1);
}
/*
* 재귀적 binary Search(이진 탐색)을 사용하여 단어 리스트 속 단어의 위치를 검색한다.
* 주어진 문자list에서 input이라는 문자를 찾아 그 인덱스를 반환한다.
* 찾지 못한다면 -1 반환.
*/

void    removeDup_txt(vector<string> *s)
{
    string pre = (*s)[0];
    int i = 1;

    while (i < (*s).size()) // 매번 size를 받아와야함. 중복삭제를 해가면서 계속 배열 사이즈가 줄어들기 때문.
    {
        if ((*s)[i] == pre)
            (*s).erase((*s).begin() + i);
        pre = (*s)[i];
        i++;
    }
} // 읽어온 단어들이 정렬된 상태일 때, 그 중에서 중복된 걸 제거

void    sort_txt(vector<string> *s)
{
    string tmp;
    int len = (*s).size();

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if ((*s)[i] > (*s)[j])
            {
                tmp = (*s)[i];
                (*s)[i] = (*s)[j];
                (*s)[j] = tmp;
            }
            
        }
    }
} // 읽어온 단어들을 사전 순으로 정렬.

void    trim_txt(vector<string> *s)
{
    char punct[9] = {'\'', '"', '.', ',', '!', '?', ':', ';', '-'};
    int len = (*s).size();

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 9;j++)
        {
            (*s)[i].erase(remove((*s)[i].begin(), (*s)[i].end(), punct[j]), (*s)[i].end());
        }
    }
} // 읽어온 단어들에서 구두점을 제거.

bool    get_fileString(vector<string> *words)
{
    string filename("input.txt");
    string word;
    ifstream input_file(filename); // 파일 열어줌.

    if (!input_file.is_open())
    {
        cerr << "[error] Could not open the file - '" << filename << "'" << endl;
        return (false);
    } // 파일이 열리지 않았을 경우 오류처리
    cout << "----------------------- File Content -------------------------" << endl << endl;
    while (input_file >> word) 
    {
        cout << word <<" ";
        (*words).push_back(word);
    } 
    cout << endl << endl; // 여기 while() 돌면서 파일 내용도 전부 출력함.
    /* 
    * 추출 연산자(>>) 호출. 
    * 첫번째 공백 문자를 만나기 전에 자동으로 첫 번째 단어를 읽는 문자열 변수로 리디렉션 
    */
    input_file.close(); // 파일 닫아줌
    return (true);
} // 파일로부터 단어들을 읽어옴.
/*
* 주의! : ifstream으로 열면 cin처럼 공백, 엔터 등으로 입력을 구분한다. 
* 따라서 여러 개 공백을 읽어올 수 없고 단어만 하나씩 받아온다... (교수님께 문의하기)
*/

void    search_txt(vector<string> *s)
{
    string  input;
    int     ret = 0;

    while (1)
    {
        cout << "================= Type the word you wanna find ================"<<endl;
        cout << "(Type dot(.) to end the program)" << endl << endl;
        cin >> input; // 입력 + (space) + (엔터). 혹은 입력 + (엔터 두번)
        if (input.compare(".") == 0)
        {
            cout << "____________________ Terminate the Program ____________________"<<endl <<endl;
            break;
        }
        ret = binarySearch_recursion((*s), input, 0, (*s).size() - 1);
        if (ret == -1)
        {
            cout << "The string doesn't exsit in a file!" << endl; // 삭제 가능 (불필요)
            cout << "Position of the word : " << -1 <<endl <<endl; // 중요
        }
        else
            cout << "Position of the word : " << ret + 1 <<endl <<endl;
    }
}

int     main()
{
    vector<string> words;
    string input;
    if (!(get_fileString(&words)))
        return (err_terminate());
    trim_txt(&words);
    sort_txt(&words);
    cout << "------------------------ After Sort --------------------------" << endl;
    display_txt(words);
    removeDup_txt(&words);
    cout << "----------------- After Removing Duplication ------------------" << endl;
    display_txt(words);
    search_txt(&words);
    return (0);
}

/*
* https://www.delftstack.com/ko/howto/cpp/cpp-read-file-word-by-word/
* https://www.maybugs.com/news/articleView.html?idxno=562025
* https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=sang9151&logNo=221092559183
* https://supermemi.tistory.com/53
* https://popawaw.tistory.com/39
*/
