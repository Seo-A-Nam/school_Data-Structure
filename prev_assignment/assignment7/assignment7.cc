#include <iostream>
using namespace std;

int     main()
{
    while (1)
    {
        string input;

        cin>>input;
        if (input.compare((string)".") == 0)
        {
            cout << "==================== Terminate The Program ===================="<<endl;
            break;
        }
    }
}