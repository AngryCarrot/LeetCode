#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <cstdio>

using namespace std;

freopen("../input.txt", "r", stdin);

// qsrot比较函数
int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

// line with space
vector<int> getInput(string line)
{
    string buf;
    stringstream ss;
    ss << line;
    vector<int> nums1;
    while (ss >> buf)
    {
        nums1.push_back(atoi(buf.c_str()));
    }
    return nums1;
}

vector<string> split(string data, string token)
{
    vector<string> output;
    size_t pos = string::npos; // size_t to avoid improbable overflowe
    do
    {
        pos = data.find(token);
        output.push_back(data.substr(0, pos));
        if (string::npos != pos)
            data = data.substr(pos + token.size());
    } while (string::npos != pos);
    return output;
}


#endif // UTILS_H
