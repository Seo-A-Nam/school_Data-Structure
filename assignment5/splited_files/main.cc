#include "assigment5.h"

int     main()
{
  string input;
  while (1)
  { 
      cin >> input; // input 값에 띄어쓰기 포함되었는지 예외처리할 수 없음 (cin은 공백 나오면 입력 끝냄) 
      // 조건 : 띄어쓰기 없이, 0~9 자연수 입력.
      if (input.compare((string)".") == 0)
      {
        cout << "==================== Terminate The Program ===================="<<endl;
        break;
      }
      else if (check_inputFormat(input) == false)
      {
        cout << "[error] Wrong input format"<<endl;
      }
      else
      {
        Stack<string> *a = new Stack<string>;
        Stack<int> *b = new Stack<int>;
        vector<string> output; // 입력된 요소를 띄어쓰기 넣어 출력해야하기 때문에 이렇게 선언함.
        // ================ 중위 수식을 후위 수식으로 바꿈 ===============
        process_postfix(a, &input, &output);
        for (int i = 0; i < output.size(); i++)
        {
          cout << output[i] << " ";
        }
        cout <<endl;
        // ================ 후위 수식을 이용해서 연산함 ==================
        calculate_postfix(b, output);
        delete a;
        delete b;
        break;
      }
  }
  return (0);
}

//  int main()
// {
//    test(); // 기존 main의 이름을 test로 바꾸어 돌린다.
//    system("leaks a.out"); // 메모리 누수 체크
//    return (0);
//  }