#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void    swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
} // 두 주소값의 데이터를 swap

void    sort(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = i; // min 값의 인덱스
        for (int k = i + 1; k < n; k++)
        {
            if (arr[k] > arr[j])
                j = k;
        }
        swap(&arr[i], &arr[j]);
    }
} // 선택 정렬

int binary_serach(int *arr, int value, int left, int right)
{
    int mid = 0;
    int flag = 0;
    int key_index = 0;
    
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (arr[mid] < value)
            right = mid - 1;
        if (arr[mid] == value)
        {
            if (arr[mid] == value)
            {
                flag = 1;
                key_index = mid;
                right = mid - 1;
            }
        }
        if (arr[mid] > value)
            left = mid + 1;
    }
    if (flag != 0)
        return (key_index); // 중복 처리를 위해 이렇게 함. 중복값 중에서는 가장 처음 나오는 것의 인덱스를 반환함. 
    return (-1);
} // 이원 탐색 기법을 사용한 탐색 함수

bool    check_numstr(string a)
{
    int i = 0;

    if (a[0] == '-')
        i++;
    while (i < (int)a.size())
    {
        if (!(a[i] >= '0' && a[i] <= '9'))
            return (false);
        i++;
    }
    return (true);
}

void    do_binSearch(int *arr, int n)
{
    string key;
    int ret = 0;

    cout << "Key> ";
    cin >> key;
    if (check_numstr(key) == false)
    {
        cout << "[error] key input : Wrong format."<<endl;
        return ;
    }
    ret = binary_serach(arr, stoi(key), 0, n - 1);
    if (ret == -1)
        cout<<"Not found"<<endl;
    else
        cout<<ret<<endl;
} // 과제에 정해진 형식대로 보이게끔 binary_search()를 호출하는 함수

void    get_check_input(int n, string *input, int *arr)
{
    string temp;

    try{
        for (int i = 0; i < n; i++)
        {
            if (check_numstr(input[i]) == false) // 숫자가 아닌 문자일 경우
                throw ("Input error : Wrong input Format!\n");
            arr[i] = stoi(input[i]);
        }
    }
    catch (const char *err)
    {
        delete[] input;
        delete[] arr;
        cout<<"[error] "<<err<<endl;
        exit(EXIT_FAILURE);
    }
}
/* 
에러 처리 : 입력값을 string 형식으로 받아 체크
char로 받으면 아스키값 65인지 A가 입력된 것인지 구분할 방법이 없기 때문이다.
이 방법을 통해 숫자가 아닌 문자가 입력되었을 때를 예외 처리해주었다
*/

void   get_input(int *n, string **input, int *arr)
{
    int count = 0;
    string s;
    string word;

    getline(cin, s);
    istringstream ss(s);
    ss.str(s);
    try {
        if (s.empty())
            throw ("Input error : empty input");
        while (ss >> word)
        {
            if (count == 0) // 첫번째 값은 n(입력받을 숫자의 개수)에 넣어준다.
            {
                if (check_numstr(word) == true)
                    *n = stoi(word);
                if (*n <= 0)
                    throw ("Input error : invalid range of input number"); // 개수 입력 범위 예외처리.)
                count++;
                continue;
            }
            else if (count > *n)
            {
                throw ("Input error : exceeded input values");
                break;
            }
            else
                (*input)[count - 1] = word;
            count++;
        }
        if (count <= *n)
            throw ("Input error : more input values needed");
    }
    catch (const char *err)
    {
        delete[] arr;
        delete[] (*input);
        cout<<"[error] "<<err<<endl;
        exit(EXIT_FAILURE);
    }
}

int     memory_alloc(int **arr, string **input, int n)
{
    try
    {
        (*arr) = new int [n];
    }
    catch (bad_alloc ex) // new 를 통한 메모리 할당 실패 시 예외처리
    {
        cout << ex.what()<<endl;
        return (0);
    }
    try
    {
        (*input) = new string [n];
    }
    catch (bad_alloc ex) // new 를 통한 메모리 할당 실패 시 예외처리
    {
        cout << ex.what() <<endl;
        delete (arr);
        return (0);
    }
    return (1);
} // arr과 input이라는 포인터에 메모리 할당. 메모리 할당 실패 시 0, 할당 성공 시 1을 반환하는 함수

int     main()
{
    int n;
    string option;
    int *arr = NULL;
    string *input = NULL;

    // ======== 숫자 입력 후 출력 ==========
    cout << "Put the number of integer and those integers in sequence"<<endl;
    if (!(memory_alloc(&arr, &input, n))) // 메모리 할당과 동시에, 할당 실패 시 예외처리 해줌
        return (1);
    get_input(&n, &input, arr);
    get_check_input(n, input, arr); // 입력과 동시에 입력 형식 에러 체크
    cout <<"--------------- input array ---------------"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout <<arr[i]<<" ";
    }
    cout<<endl;
    // =========== 정렬 후 출력 ============
    sort(arr, n);
    cout<<"--------------- after sort ---------------"<<endl;
    for (int i = 0; i < n; i ++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    // =========== 이원 탐색 ==============
    cout <<"------------- Binary Search ---------------"<<endl;
    do_binSearch(arr, n);
    while (1)
    {
        cout << "Continue(Y/N)?> ";
        cin >> option;
        if (option.compare((string)"Y") == 0)
            do_binSearch(arr, n);
        if (option.compare((string)"N") == 0)
        {
            cout << "Bye..."<<endl;
            break;
        }
    }
    delete[] arr;
    delete[] input;
    return (0);
}