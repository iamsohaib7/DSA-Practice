#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    Function: makeLcs
    Purpose: Build the LCS (Longest Common Subsequence) DP table using bottom-up dynamic programming.
    Parameters:
        - s1, s2: Input strings
        - dp: 2D vector to store LCS lengths at each (i, j)
        - n, m: Lengths of s1 and s2
*/
void makeLcs(const string &s1, const string &s2, vector<vector<int>> &dp, int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // If characters match, increment the length of LCS by 1
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } 
            // Else, take the maximum LCS length from the top or left cell
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
}

/*
    Function: printLcs
    Purpose: Reconstruct and return one LCS string using the filled DP table.
    Logic: Start from dp[n][m] and move backwards to trace the LCS.
*/
string printLcs(const string &s1, const string &s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); // Initialize DP table with zeros

    makeLcs(s1, s2, dp, n, m); // Fill DP table using tabulation

    string res;
    int i = n, j = m;

    // Trace back from bottom-right to top-left to reconstruct LCS
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            // If characters match, they are part of LCS
            res.push_back(s1[i - 1]);
            i--;
            j--;
        } 
        // Move in the direction of the larger value
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // LCS is built in reverse, so reverse it before returning
    reverse(res.begin(), res.end());
    return res;
}

/*
    Main function: Demonstrates the usage of the LCS logic.
*/
int main() {
    const string s1 = "acbcf";
    const string s2 = "abcdaf";

    string res = printLcs(s1, s2); // Get one LCS
    cout << "LCS: " << res << endl;

    return 0;
}
