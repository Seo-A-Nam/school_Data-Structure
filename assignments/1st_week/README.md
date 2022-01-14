## 할 것
1. 문의한 내용 바탕으로 선택정렬 알고리즘 고치기 (강의 예제에 나온 것으로 고치기).

## 참고 자료
1. new 할당 실패 시 예외처리 https://psychoria.tistory.com/57
2. new 핟당 실패 시 예외처리	https://ju3un.github.io/c++-new-excepiton/
3. 공백 기준 문자열 자르기 : https://seoyeonkk.tistory.com/entry/C-%EA%B3%B5%EB%B0%B1-%EA%B8%B0%EC%A4%80-%EB%AC%B8%EC%9E%90%EC%97%B4-%EC%9E%90%EB%A5%B4%EA%B8%B0split

1. cin으로 입력받을 경우, 버퍼에 '\n'이 남는다.
2. cin 다음 입력을 cin으로 받을경우, 전 버퍼에 있던 공백 및 개행문자를 무시하기 때문에 버퍼를 굳이 비워줄 필요가 없다.
3. cin 다음 입력을 getline으로 받을경우, 전 버퍼에 있던 공백 및 개행문자를 포함해서 입력받기 때문에 버퍼를 지워주는 작업이 필요하다.
4. getline 다음 입력을 getline으로 받을경우, getline은 '\n' 문자를 버퍼에 포함시키기 않기때문에 버퍼를 비워줄 필요가 없다.
5. BOJ의 채점결과와 로컬의 실행결과가 일치하지 않는 이유는 다양하겠습니다만, Windows와 Linux의 개행 문자 차이, 컴파일러의 차이 등이 그 이유가 되지 않을까 생각합니다.
구름Ide에서는 위의 코드에서 cin.ignore()를 포함시킬경우 정상적으로 작동하였으나, ideone에서는 런타임 에러가 발생(https://ideone.com/vKz64B)
특히 문자열 문제에서 오답시, 다른 컴파일러를 사용해 보는것도 좋은 선택.
cin은 '\n'를 변수에 담지 않는다. (입력버퍼에 남겨둔다.)
getline은 '\n'를 변수에 담는다.
cin.ignore();는 버퍼 전체를 비우는것이 아니라 맨 앞의 문자하나를 지운다.
getline(읽어올 입력스트림, 저장할 문자열변수)
