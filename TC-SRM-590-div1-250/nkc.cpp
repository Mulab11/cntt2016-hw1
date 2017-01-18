#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define NO return "Impossible"
#define YES return "Possible"
using namespace std;
struct FoxAndChess
{
	string ableToMove(string begin, string target)
	{
		int n=begin.size();
		int i,j=0;
		for(i=0;i<n;i++)
		{
			if(target[i]=='.') continue;
			while(j<n&&begin[j]=='.') j++;
			if(j==n) NO;//棋子数量对不上 
			if(target[i]!=begin[j]) NO;//棋子种类对不上 
			if(target[i]=='L'&&j<i) NO;
			if(target[i]=='R'&&j>i) NO;//棋子位置对不上 
			j++;
		}
		for(i=j;i<n;i++)
		if(begin[i]!='.') NO;//棋子数量对不上 
		YES;//全对 
	}
};