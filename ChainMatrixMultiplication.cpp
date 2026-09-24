#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

// Recursive function to print the optimal parenthesization
void printOptimalParens(const std::vector<std::vector<int>>& s, int i, int j) {
    if (i == j) {
        std::cout << "A" << i;
    } else {
        std::cout << "(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        std::cout << ")";
    }
}

int main() {
    // Example dimensions: 4 matrices
    // A1: 40x20, A2: 20x30, A3: 30x10, A4: 10x30
    std::vector<int> p = {40, 20, 30, 10, 30};
    int n = p.size() - 1; // Number of matrices

    // 1-indexed DP tables of size (n+1) x (n+1)
    std::vector<std::vector<int>> m(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> s(n + 1, std::vector<int>(n + 1, 0));

    // L is chain length (from 2 up to n)
    for (int L = 2; L <= n; ++L) {
        for (int i = 1; i <= n - L + 1; ++i) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k; // Store optimal split point
                }
            }
        }
    }

    // Display m-table (Minimum Multiplication Costs)
    std::cout << "--- Cost Table (m-table) ---\n";
    std::cout << "  i\\j";
    for (int j = 1; j <= n; ++j) std::cout << std::setw(8) << j;
    std::cout << "\n";

    for (int i = 1; i <= n; ++i) {
        std::cout << std::setw(5) << i;
        for (int j = 1; j <= n; ++j) {
            if (i > j) {
                std::cout << std::setw(8) << "-";
            } else {
                std::cout << std::setw(8) << m[i][j];
            }
        }
        std::cout << "\n";
    }

    // Display s-table (Split/K points)
    std::cout << "\n--- Split Table (s-table) ---\n";
    std::cout << "  i\\j";
    for (int j = 1; j <= n; ++j) std::cout << std::setw(6) << j;
    std::cout << "\n";

    for (int i = 1; i <= n; ++i) {
        std::cout << std::setw(5) << i;
        for (int j = 1; j <= n; ++j) {
            if (i >= j) {
                std::cout << std::setw(6) << "-";
            } else {
                std::cout << std::setw(6) << s[i][j];
            }
        }
        std::cout << "\n";
    }

    // Output optimal result
    std::cout << "\nMinimum operations required: " << m[1][n] << "\n";
    std::cout << "Optimal Parenthesization: ";
    printOptimalParens(s, 1, n);
    std::cout << "\n";

    return 0;
}
