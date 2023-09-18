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
    if (ch == '(')
    {
        return;
    }
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
    p[')'] = 0;
    p['+'] = 1;
    p['-'] = 1;
    p['*'] = 2;
    p['/'] = 2;
    p['('] = 3;

    bool flag = false;
    for (int i = 0; i < len; ++i)
    {
        if (str[i] - '0' >= 0 && str[i] - '0' <= 9)
        {
            int temp = 0;
            while (i < len && str[i] - '0' >= 0 && str[i] - '0' <= 9)
            {
                temp = temp * 10 + (str[i] - '0');
                ++i;
            }
            stk.push(temp);
        }
        if (i >= len)
        {
            break;
        }
        while (opt.size() > 0)
        {
            char ch = opt.top();
            int ta = p[str[i]];
            int tb = p[ch];
            if (flag && ch == '(')
            {
                ta += p['('];
                 
            }
            else if (flag && str[i] != ')')
            {
                ta += p['('];
                tb += p['('];
            }

            if (ta <= tb)
            {
                MyFunc(stk, opt);
            }
            else
            {
                break;
            }
        }
        if (str[i] == ')')
        {
            flag = false;
            continue;
        }
        if (str[i] == '(')
        {
            flag = true;
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