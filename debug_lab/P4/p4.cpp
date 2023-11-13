#include <iostream>
#include <vector>
#include "solution.h"

using namespace std;

void Solution::dfs(vector<vector<int>> &matrix, int remain, int used, int n, int m, int &best){
    int this_k_unavailable;
    int i, j;
    int x, y;
    int a, b;
    if (used >= best)
        return;

    if (remain == 0){
        best = min(best, used);
        return;
    }

    for (a=0; a < n; a++)
        for (b=0; b < m; b++)
            // 找到一个空格子，尝试填入一个正方形
            if (matrix[a][b] == 0){
                for (int k = min(n - a, m - b); k >= 1; k--){
                    this_k_unavailable = 0;
                    x = a;
                    y = b;

                    for (i = 0; i < k; i++)
                        for (j = 0; j < k; j++)
                            if (matrix[x + i][y + j])
                                this_k_unavailable = 1;

                    if (this_k_unavailable)
                        continue;

                    for (i = 0; i < k; i++)
                        for (j = 0; j < k; j++)
                            matrix[x + i][y + j] = 1;

                    remain -= k * k;
                    used++;
                    dfs(matrix, remain, used, n, m, best) ;
                    used--;
                    remain += k * k;

                    for (i = 0; i < k; i++)
                        for (int j = 0; j < k; j++)
                            matrix[x + i][y + j] = 0;
                }

                return;
            }
}

int Solution::tilingRectangle(int n, int m) {
    int best = n * m;

    vector<vector<int>> matrix(n, vector<int> (m));

    dfs(matrix, n * m, 0, n, m, best);

    return best;
}