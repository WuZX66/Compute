#include <iostream>
#include <vector>
#include "algorithm"
#include <stack>
#include "unordered_map"
using namespace std;

void MyFunc(stack<int> &stk, stack<char> &opt)
{
    char ch = opt.top();
    opt.pop();
    int b = stk.top();
    stk.pop();
    int a = stk.top();
    stk.pop();
    switch (ch)
    {
    case /* constant-expression */ '+':
        stk.push(a + b);
        /* code */
        break;
    case '-':
        stk.push(a - b);
        break;
    case '*':
        stk.push(a * b);
        break;
    case '/':
        if (b == 0)
        {
            fprintf(stderr, "Zero Exception\n");
            exit(-1);
        }
        stk.push(a / b);
        break;
    default:
        break;
    }
}

int evalRPN(string str)
{
    int len = str.size();
    stack<int> stk;
    stack<char> opt;
    unordered_map<char, int> p;
    p['+'] = 0;
    p['-'] = 0;
    p['*'] = 1;
    p['/'] = 1;
    for (int i = 0; i < len; ++i)
    {
        int temp = 0;
        while (i < len && str[i] - '0' < 0 || str[i] - '0' > 9)
        {
            ++i;
        }
        while (i < len && str[i] - '0' >= 0 && str[i] - '0' <= 9)
        {
            temp = temp * 10 + (str[i] - '0');
            ++i;
        }
        stk.push(temp);
        if (i >= len)
        {
            break;
        }
        while (opt.size() > 0)
        {
            char ch = opt.top();
            if (p[ch] >= p[str[i]])
            {
                MyFunc(stk, opt);
            } 
            else
            {
                break;
            }
        }
        opt.push(str[i]);
    }
    while (stk.size() > 1 && opt.size() > 0)
    {
        MyFunc(stk, opt);
    }
    return stk.top();
}
int main()
{
    string s;
    cin >> s;
    int res = evalRPN(s);
    cout << res << endl;
    return 0;
}