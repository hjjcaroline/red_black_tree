#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include <iostream>

using namespace std;

bool cal_next(const string& str,int* next)
{
	if (next == NULL)
	{
		return false;
	}
	int k = -1;
	int size = str.size();
	next[0] = -1;
	for (int i = 1; i < size; ++i)
	{
		while(k > -1 && str[i] != str[k+1])
		{
			k = next[k];
		}
		if (str[i] == str[k+1])
		{
			++k;
		}
		next[i] = k;
	}
	return true;
}


int cal_substr(const string &str,const string &ptr)
{
	int slen = str.size();
	int plen = ptr.size();
	int *next = new int[plen];
	cal_next(ptr,next);
	int k = -1;
	for (int i = 0; i < slen; ++i)
	{
		while (k > -1 && str[i] != ptr[k+1])
		{
			k = next[k];
		}
		if (str[i] == ptr[k+1])
		{
			++k;
		}
		if (k == plen - 1)
		{
			return i - k;
		}
	}
	return -1;
}

std::vector<int> cal_substrs(const string &str,const string &ptr)
{
	std::vector<int> res;
	int slen = str.size();
	int plen = ptr.size();
	int *next = new int[plen];
	cal_next(ptr,next);
	int k = -1;
	for (int i = 0; i < slen; ++i)
	{
		while (k > -1 && str[i] != ptr[k+1])
		{
			k = next[k];
		}
		if (str[i] == ptr[k+1])
		{
			++k;
		}
		if (k == plen - 1)
		{
			res.push_back(i - k);
		}
	}
	return res;
}

int main(int argc, char const *argv[])
{
	string str,ptr;
	cout << "please inpt a string:\n";
	cin >> str;
	cout << "please inpt a short string:\n";
	cin >> ptr;
	int pos = cal_substr(str,ptr);
	cout << "result is " << pos << endl;
	return 0;
}
