// This Code is for Printing the Shortest Common Supersequence
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string printSCS(const string &s, const string &t, int n, int m, vector<vector<int>> &dp) {
    // 1. Build DP table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = max(i, j);
            } else if (s[i - 1] == t[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // 2. Backtrack to build result
    int i = n, j = m;
    string res;
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            res.push_back(s[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] < dp[i][j - 1]) {
            res.push_back(s[i - 1]);
            i--;
        } else {
            res.push_back(t[j - 1]);
            j--;
        }
    }
    // 3. Append any remaining prefix
    while (i > 0) { res.push_back(s[i - 1]); i--; }
    while (j > 0) { res.push_back(t[j - 1]); j--; }

    // 4. Reverse the constructed string
    reverse(res.begin(), res.end());
    return res;
}
int main()
{

    const string s1 = "AGGTAB", s2 = "GXTXAYB";
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    cout << "SCS: " << printSCS(s1, s2, n, m, dp) << endl;
    return 0;
}