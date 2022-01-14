#include "assigment5.h"

int     main()
{
  string input;
  cout <<endl<< "=================================================================="<<endl;
  cout << "                Welcome to our stack calculater!" << endl;
  cout<< "               (press .(dot) to terminte program)" << endl <<endl;
  while (1)
  {
      cout << "> Type any infix math expression to calculate."<<endl<<" (without any whitespace)"<<endl<<endl;
      cout << "Infix : ";
      cin >> input; // input 값에 띄어쓰기 포함되었는지 예외처리할 수 없음 (cin은 공백 나오면 입력 끝냄) 
      // 조건 : 띄어쓰기 없이, 0~9 자연수 입력.
      if (input.compare((string)".") == 0)
      {
        cout << "==================== Terminate The Program ===================="<<endl;
        break;
      }
      else if (check_inputFormat(input) == false)
      {
        cout << "[error] Wrong input format"<<endl<<endl;
        cout << "Try again !" <<endl;
        // 다음 루프로 넘어가서 처음부터 다시할 수 있도록 함
      }
      else
      {
        Stack<char> *a = new Stack<char>;
        Stack<int> *b = new Stack<int>;
        vector<string> output; // 입력된 요소를 띄어쓰기 넣어 출력해야하기 때문에 이렇게 선언함.
        // ================ 중위 수식을 후위 수식으로 바꿈 ===============
        if (process_postfix(a, &input, &output) == false) // int overflow 일어나는 경우 (아직 코드 안넣음!)
        {
          delete a;
          delete b;
          cout << "Try again !" <<endl;
          continue; // 다음 루프로 넘어가서 처음부터 다시할 수 있도록 함
        }
        cout << "Postfix : ";
        for (int i = 0; i < output.size(); i++)
        {
          cout << output[i];
          if (i < output.size() - 1)
            cout << ",";
        }
        cout <<endl;
        // ================ 후위 수식을 이용해서 연산함 ==================
        if (calculate_postfix(b, output) == false)
        {
          delete a;
          delete b;
          continue;
        }
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