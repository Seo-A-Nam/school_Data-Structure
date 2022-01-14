## 진행 현황
* 템플릿 함수 적용까지 끝넀다. (splited_files 폴더 안에 있음)
* assignment_original.cc 파일에는 템플릿 적용하지 않음
    - 코드가 너무너무 길어질 거 같아서
* 계절학기 시작 이후 수정한 것 첨부함. 수식의 계산 결과는 같으나 연산자 우선순위가 달라 후위변환식은 다소 다르게 나옴.

## 고려할 사항

1. 입력형식을 검사하는 예외처리를 넣을 것인가?
2. "pdf에 제시된 것 이외의 입/출력이 있을 경우 테스트케이스에 맞지 않는 것으로 처리해 감점이 발생합니다"라고 하는데 에러출력메시지는 어떻게 해야하는가 << 교수에게 문의해보자
    -> 근데 재입력 받기가 필수구현 사항인거 보면, 에러처리를 해야만 하는 것 같다.
    -> 일단 문의해보기.
3. Template 클래스를 쓸 것인가?
4. "제곱 연산자도 구현했는데 이 코드가 과제에서 감점받지는 않을까요?"라고 질문 올리기.
5. 닫는 괄호 연산자 만나면 모든 연산자가 pop되고 결과값 벡터에 들어가므로, 닫는 괄호 앞에 연산자가 나오는 상황도 예외처리해야한다.

    * ex)
    (23-)201
    23 - 201 
    [error] Stack Underflow
    [1]    61548 segmentation fault  ./a.out
6. 입력값에서는 띄어쓰기 없이, 0~9 자연수 입력이라고 되어있었는데
여러자리의 자연수를 입력해도 처리가 되도록 구현해버림... -> 교수님께 문의하기
7. 입력값은 자연수로 들어오기로 되어있으므로 자연수 입력이 아닌 경우는 별도로 예외처리 하지 않음 (- 연산자와 헷갈린다). (연산자 >= 피연산자) 개수 처리나 그냥 연산자가 여러개 겹치는 경우의 예외처리에 걸려서 wrong input이라고 나올 것임.


## 참고문헌

 * 템플릿? : https://blockdmask.tistory.com/43
 * 스택응용 - 수식 계산 : https://rpatm.tistory.com/43  (이게 짱)
 * https://monzeac.tistory.com/28
 * https://gurumee92.tistory.com/128
 * malloc/free와 new/delete의 차이점 : https://wonjayk.tistory.com/252
 * Null 포인터로 객체의 함수가 호출되는 이유 : https://stdbc.tistory.com/124
 * 에러 : https://paranwater.tistory.com/138
 * 메모리 누수 : https://kldp.org/node/23920
 * 스택을 이용해서 괄호 검사하는 알고리즘 : https://comdolidol-i.tistory.com/45
