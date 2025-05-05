// This program computes the Longest Common Subsequence (LCS) of two strings

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Naive recursive approach: O(2^{min(n,m)}) time due to overlapping subproblems
int naiveLCS(const string &s1, const string &s2, int n, int m)
{
    // Base case: if either string length is zero, no common subsequence
    if (n == 0 || m == 0)
    {
        return 0;
    }
    // If last characters match, include it and recurse on remaining prefixes
    if (s1[n - 1] == s2[m - 1])
    {
        return 1 + naiveLCS(s1, s2, n - 1, m - 1);
    }
    // Otherwise, consider dropping one character from either string
    return max(
        naiveLCS(s1, s2, n - 1, m), // drop last of s1
        naiveLCS(s1, s2, n, m - 1)  // drop last of s2
    );
}

// Top-down DP (memoization): caches results in dp to achieve O(n*m) time
int memoLCS(const string &s1, const string &s2, int n, int m, vector<vector<int>> &dp)
{
    // Base case
    if (n == 0 || m == 0)
    {
        return 0;
    }
    // If already computed, return cached value
    if (dp[n][m] != -1)
    {
        return dp[n][m];
    }
    // Compute and cache result
    if (s1[n - 1] == s2[m - 1])
    {
        dp[n][m] = 1 + memoLCS(s1, s2, n - 1, m - 1, dp);
    }
    else
    {
        dp[n][m] = max(
            memoLCS(s1, s2, n - 1, m, dp), // skip last of s1
            memoLCS(s1, s2, n, m - 1, dp)  // skip last of s2
        );
    }
    return dp[n][m];
}

// Bottom-up DP (tabulation): builds table iteratively in O(n*m) time
int tabLCS(const string &s1, const string &s2, int n, int m, vector<vector<int>> &dp)
{
    // Initialize base cases: first row and column to 0
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            dp[i][j] = 0;
        }
    }
    // Fill DP table
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                // match: extend subsequence
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                // no match: take max of adjacent states
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

int main()
{
    const string s1 = "acbcf";
    const string s2 = "abcdaf";
    int n = s1.size(), m = s2.size();

    // Memoization table initialized to -1
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    // Compute LCS with three methods
    int naiveRes = naiveLCS(s1, s2, n, m);
    int memoRes = memoLCS(s1, s2, n, m, dp);

    // Reinitialize for tabulation
    for (auto &row : dp)
        fill(row.begin(), row.end(), 0);
    int tabRes = tabLCS(s1, s2, n, m, dp);

    // Output results
    cout << "Naive Way: " << naiveRes << endl;
    cout << "Memoized Way: " << memoRes << endl;
    cout << "Tabulation Way: " << tabRes << endl;

    return 0;
}
