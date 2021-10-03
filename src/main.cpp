#include "helper.h"

class Solution {
public:
    string longestCommonPrefix(vector<string> strs) {
        int len = std::min_element(strs.begin(), strs.end(), []
            (const string& str1, const string& str2) {
                return str1.size() < str2.size();
            })->size();
        
        if (len == 0) return "";
        
        string result = "";
        char c;
        for (int i = 0; i < len; ++i) {
            c = strs[0][i];
            for (int j = 1; j != strs.size(); ++j) {
                if (strs[j][i] != c) return result;
            }
            result += c;
        }
        
        return result;
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{	
	Solution sol;
	std::cout << std::boolalpha;
	std::cout << sol.longestCommonPrefix({"dog","racecar","car4","23","kjlfdsal;kf", "carkdljsl", "racelkdsaj"}) << std::endl;
	std::cout << sol.longestCommonPrefix({"flower","flow","flight"}) << std::endl;
	return 0;
}