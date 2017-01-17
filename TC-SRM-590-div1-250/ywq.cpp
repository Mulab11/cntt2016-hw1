#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

class FoxAndChess {
    public:
    string ableToMove(string begin, string target) {
        int n=begin.size();
        int k=0;
        for (int i=0;i<n;i++)
            if (begin[i]!='.')
            {
                while (k<n&&target[k]=='.') k++;
                if (k>=n||begin[i]!=target[k]) return "Impossible";
                k++;
            }
        k=0;
        for (int i=0;i<n;i++)
            if (target[i]!='.')
            {
                while (k<n&&begin[k]=='.') k++;
                if (k>=n||begin[k]!=target[i]) return "Impossible";
                k++;
            }
        k=0;
        for (int i=0;i<n;i++)
            if (begin[i]=='R')
            {
                while (target[k]!='R') k++;
                if (k<i) return "Impossible";
                k++;
            }
        k=0;
        for (int i=0;i<n;i++)
            if (begin[i]=='L')
            {
                while (target[k]!='L') k++;
                if (k>i) return "Impossible";
                k++;
            }
        return "Possible";
    }
};

