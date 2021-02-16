#include <iostream>


using namespace std;

bool isPowerOfTwo(unsigned n) {
    return n && (!(n & (n-1)));
}
/*
Got it!
GeeksforGeeks
Skip to content
Tutorialskeyboard_arrow_down Studentskeyboard_arrow_down Courses ContriButE
Custom Search
*/

bool isIdentityMatrix(int mat[][10], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j && mat[i][j] != 1){
                return false;
            }
            if (i != j && mat[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    // cout << sizeof(long double **[10][12]) << endl;
    // printf("%lu", sizeof(long double **[10][12]));
    // int x, y;
    // cin >> x >> y;
    // while (true) {
    //     if (isPowerOfTwo(x)) {
    //         cout << x << endl;
    //     }
    //     x++, y++;
    // }
    // int n;
    // scanf("%d", &n);
    // int mat[10][10];
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         scanf("%d", &mat[i][j]);
    //     }
    // }
    // cout << isIdentityMatrix(mat, n) << endl;

	// contribute
    for (int i = 0; i < 32; i = (-(~i))) {
        cout << i << endl;
    }

    return 0;
}
