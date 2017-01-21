#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<ctime>
#include<iostream>
#include<string>
#include<cctype>
#include<queue>
#include<stack>
#include<list>

using namespace std;

string f[60][60][3];

int cmp(int a,int b)
{
    if (a<b) return 0;
    if (a==b) return 1;
    return 2;
}

class LeftRightDigitsGame2
{
    public:
        string minNumber(string s1, string s2)
        {
            int l=s1.size();
            for (int a=0;a<l;a++)
                for (int b=0;b<l;b++)
                    for (int c=0;c<3;c++)
                        f[a][b][c]="A";
            for (int a=0;a<l;a++)
                f[0][a][cmp(s1[0],s2[a])]=s1[0];
            for (int a=0;a<l-1;a++)
                for (int b=0;b<l-a;b++)
                    for (int c=0;c<3;c++)
                        if (f[a][b][c]!="A")
                        {
                            if (b!=0)
                            {
                                if (s1[a+1]<s2[b-1]) f[a+1][b-1][0]=min(f[a+1][b-1][0],s1[a+1]+f[a][b][c]);
                                if (s1[a+1]==s2[b-1]) f[a+1][b-1][c]=min(f[a+1][b-1][c],s1[a+1]+f[a][b][c]);
                                if (s1[a+1]>s2[b-1]) f[a+1][b-1][2]=min(f[a+1][b-1][2],s1[a+1]+f[a][b][c]);
                            }
                            if (b+a!=l-1)
                            {
                                if (s1[a+1]>s2[b+a+1]) f[a+1][b][(c==0) ? 0 : 2]=min(f[a+1][b][(c==0) ? 0 : 2],f[a][b][c]+s1[a+1]);
                                if (s1[a+1]==s2[b+a+1]) f[a+1][b][c]=min(f[a+1][b][c],f[a][b][c]+s1[a+1]);
                                if (s1[a+1]<s2[b+a+1]) f[a+1][b][(c==2) ? 2 : 0]=min(f[a+1][b][(c==2) ? 2 : 0],f[a][b][c]+s1[a+1]);
                            }
                        }
            if (f[l-1][0][1]=="A" && f[l-1][0][2]=="A") return "";
            return min(f[l-1][0][1],f[l-1][0][2]);
        }
};

