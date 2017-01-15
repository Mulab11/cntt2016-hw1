#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
class TheNumberGameDivOne{
public:
    string find(long long n){
        //打表可得，只有n是奇数或者2^{2*k+1}时，Brus才能赢
        if(n&1)return "Brus";
        int ji=0;
        while(n%2==0){
            n/=2;ji++;
        }
        if(n==1){
            //ji表示log2(n)的值
            if(ji&1)return "Brus";
            else return "John";
        }
        return "John";
    }
};