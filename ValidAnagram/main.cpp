#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void printVector(vector<int> v);

class Solution {
public:    
    /** 438. Find All Anagrams in a String
     * @brief findAnagrams
     * @param s
     * @param p
     * @return
     */
    vector<int> findAnagrams(string s, string p)
    {
        vector<int> result;
        int lengthS = s.length();
        int lengthP = p.length();
        if (lengthS < lengthP)
        {
            return result;
        }
        for (int i = 0; i != lengthS - lengthP + 1; ++i)
        {
            cout << s.substr(i, lengthP) << endl;
            if (isAnagram(s.substr(i, lengthP), p))
            {
                result.push_back(i);
            }
        }
        return result;
    }
    vector<int> findAnagramsNBS(string s, string p)
    {
        int lengthP = p.size();
        int lengthS = s.size();
        vector<int> result;
        if (s.size() < p.size())
        {
            return result;
        }
        if (0 == lengthP && lengthP == lengthS)
        {
            result.push_back(0);
            return result;
        }
        const int SIZE = 26;
        vector<int> smap(SIZE, 0);
        vector<int> pmap(SIZE, 0);
        for (unsigned int i = 0; i != lengthP; ++i)
        {
            ++smap[s[i] - 'a'];
            ++pmap[p[i] - 'a'];
        }

        for (unsigned int b = 0, e = b + lengthP - 1; e < s.size(); ++b, ++e)
        {
            if (b)
            {
                --smap[s[b - 1] - 'a'];
                ++smap[s[e] - 'a'];
            }
            if (smap == pmap)
            {
                result.push_back(b);
            }
        }
        return result;
    }
    /* Sliding window approach to cover all substrings in s of length p.size() *
         * Time Complexity = O(s), where s = s.size()                              */
    std::vector<int> findAnagramsNB(std::string s, std::string p)
    {
        std::vector<int> smap(26, 0), pmap(26, 0); /* since only a-z allowed   */
        std::vector<int> ans;                      /* output vector            */
        /* Handle corner cases first */
        if(s.size() == 0 || p.size() == 0 || s.size() < p.size())
        {
            return ans;
        }
        /* Add all chars in p and first p.size() chars of s into a table */
        for(size_t i = 0; i < p.size(); ++i)
        {
            pmap[p[i] - 'a']++;
            smap[s[i] - 'a']++;
        }
        /* Sliding window to cover all substrings in s of size p           */
        for(size_t b = 0, e = b + p.size() - 1; e < s.size(); ++b, ++e)
        {
            if(b != 0)
            { /* If not first window, remove prev b and add e   */
                smap[s[b-1] - 'a']--;
                smap[s[e]   - 'a']++;
            }
            if(smap == pmap)
            {
                ans.push_back(b); /* found anagram, add to ans */
            }
        }
        return ans;
    }
    /** 242. Valid Anagram 相同字母异序词
     * @brief isAnagram s = "anagram", t = "nagaram", return true.
     *                  s = "rat", t = "car", return false.
     * @param s
     * @param t
     * @return
     */
    bool isAnagram(string s, string t)
    {
        int length = s.length();
        int length2 = t.length();
        if (length != length2)
        {
            return false;
        }
        if (0 == length)
        {
            return true;
        }
        int *counts = new int[26];
        memset(counts, 0, sizeof(int) * 26);


        for (int i = 0; i != length; ++i)
        {
            ++counts[s[i] - 'a'];
            --counts[t[i] - 'a'];
        }

        bool result = true;
        for (int i = 0; i != 26; ++i)
        {
            if (counts[i])
            {
                result = false;
                break;
            }
        }

        delete []counts;
        return result;
    }
};

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    string s = "";
    string t = "";
    Solution ss;
    vector<int> v = ss.findAnagramsNBS(s, t);
    printVector(v);
    return 0;
}

void printVector(vector<int> v)
{
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}
