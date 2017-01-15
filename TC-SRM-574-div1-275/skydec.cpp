#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int a[N],b[N];
int n,m;
class TheNumberGame{
public:
    string determineOutcome(int A, int B){
        //预处理出数组
        while(A){
            a[++n]=A%10;
            A/=10;
        }
        while(B){
            b[++m]=B%10;
            B/=10;
        }
        if(m>n)return "Manao loses";
        //可以证明，只要A是B的子串就一定是Manao赢
        rep(i,1,n-m+1){
            bool ok=1;
            //枚举子串位置
            rep(j,1,m)ok&=(b[j]==a[i+j-1]);
            if(ok)return "Manao wins";
        }
        rep(i,1,n-m+1){
            bool ok=1;
            //枚举子串位置
            rep(j,1,m)ok&=(b[m+1-j]==a[i+j-1]);
            if(ok)return "Manao wins";
        }
        return "Manao loses";
    }
};