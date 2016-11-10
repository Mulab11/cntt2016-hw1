#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#include <set>
string s;
set<string> S;
int f[60][60];
int dp(int l, int r)
{
    if(f[l][r]) return f[l][r];
    int &ans = f[l][r];
    if(S.count(s.substr(l, r - l))) return ans = 1;
    ans = 10000;
    for(int k = l + 1; k != r; ++k)
    {
        int tmp = dp(l, k) + dp(k, r);
        if(tmp < ans) ans = tmp;
    }
    return ans;
}

class CuttingBitString
{
public:
    int getmin(string s)
    {
        ::s = s;
        S.insert("1");
        S.insert("101");
        S.insert("11001");
        S.insert("1111101");
        S.insert("1001110001");
        S.insert("110000110101");
        S.insert("11110100001001");
        S.insert("10011000100101101");
        S.insert("1011111010111100001");
        S.insert("111011100110101100101");
        S.insert("100101010000001011111001");
        S.insert("10111010010000111011011101");
        S.insert("1110100011010100101001010001");
        S.insert("1001000110000100111001110010101");
        S.insert("101101011110011000100000111101001");
        S.insert("11100011010111111010100100110001101");
        S.insert("10001110000110111100100110111111000001");
        S.insert("1011000110100010101111000010111011000101");
        S.insert("110111100000101101101011001110100111011001");
        S.insert("100010101100011100100011000001001000100111101");
        S.insert("10101101011110001110101111000101101011000110001");
        S.insert("1101100011010111001001101011011100010111011110101");
        S.insert("1000011110000110011110000011001001101110101011001001");
        int tmp = dp(0, s.size());
        if(tmp > 100) tmp = -1;
        return tmp;
    }
}	user;
