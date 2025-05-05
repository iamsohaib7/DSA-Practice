// This program computes the length of the Shortest Common Supersequence (SCS)

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Naive recursive approach: exponential time
int naiveSCS(const string &s, const string &t, int n, int m) {
    // If one string is empty, SCS is just the length of the other
    if (n == 0 || m == 0) {
        return max(n, m);
    }
    // If last characters match, include it once and recurse on both
    if (s[n - 1] == t[m - 1]) {
        return 1 + naiveSCS(s, t, n - 1, m - 1);
    } else {
        // Else, take 1 plus the min of dropping one char from either string
        return 1 + min(
            naiveSCS(s, t, n - 1, m),  // drop last of s
            naiveSCS(s, t, n, m - 1)   // drop last of t
        );
    }
}

// Memoized top-down DP: caches results in dp
int memoSCS(const string &s, const string &t, int n, int m, vector<vector<int>> &dp) {
    // Base case
    if (n == 0 || m == 0) {
        return max(n, m);
    }
    int &res = dp[n][m];
    // Return cached if available
    if (res != -1) {
        return res;
    }
    // Compute and cache
    if (s[n - 1] == t[m - 1]) {
        res = 1 + memoSCS(s, t, n - 1, m - 1, dp);
    } else {
        res = 1 + min(
            memoSCS(s, t, n - 1, m, dp),  // skip last of s
            memoSCS(s, t, n, m - 1, dp)   // skip last of t
        );
    }
    return res;
}

// Bottom-up DP (tabulation): O(n*m) time and space
int tabSCS(const string &s, const string &t, int n, int m, vector<vector<int>> &dp) {
    // Fill base cases: SCS of empty and prefix
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = max(i, j);
            } else if (s[i - 1] == t[j - 1]) {
                // Matching chars: extend diagonal
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                // Else take 1 + min of left or top
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// Alternative SCS via LCS length
int lcsWay(const string &s, const string &t, int n, int m, vector<vector<int>> &dp) {
    // Build LCS table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s[i - 1] == t[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    // SCS length = n + m - LCS
    return n + m - dp[n][m];
}

int main() {
    const string s1 = "AGGTAB", s2 = "GXTXAYB";
    int n = s1.size(), m = s2.size();

    // Prepare dp table for memoization (init -1)
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    cout << "Naive Way: " << naiveSCS(s1, s2, n, m) << endl;
    cout << "Memoized Way: " << memoSCS(s1, s2, n, m, dp) << endl;

    // Reinitialize dp for tabulation
    for (auto &row : dp) fill(row.begin(), row.end(), 0);
    cout << "Tabulation Way: " << tabSCS(s1, s2, n, m, dp) << endl;

    // Reinitialize dp for LCS method
    for (auto &row : dp) fill(row.begin(), row.end(), 0);
    cout << "LCS Way: " << lcsWay(s1, s2, n, m, dp) << endl;

    return 0;
}
