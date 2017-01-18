#include<bits/stdc++.h>
using namespace std;
class TheBrickTowerEasyDivOne
{
    public:
        int find(int a,int b,int c,int d){return min(a,c)*(2+(b!=d))+(a!=c);}
};
