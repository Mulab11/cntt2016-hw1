#include<bits/stdc++.h>
using namespace std;
class TheBrickTowerEasyDivOne
{
    public:
        int find(int redCount, int redHeight, int blueCount, int blueHeight)
        {
            return min(redCount,blueCount)*(2+(redHeight!=blueHeight))+(redCount!=blueCount);//直接计算 
        }
};