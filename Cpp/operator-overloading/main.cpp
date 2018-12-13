#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix
{
    public:
        vector<vector<int>> a;
        Matrix() {
            a.clear();
        }
};

Matrix operator+ (Matrix matA, Matrix matB)
{
    Matrix sum = matA;

    /* Check sizes. */
    if (matA.a.size() != matB.a.size()) {
        throw "Cannot sum differently sized matrices.";
    }

    for (unsigned int x = 0; x < sum.a.size(); x++) {
        /* Check sizes. */
        if (matA.a[x].size() != matB.a[x].size()) {
            throw "Cannot sum differently sized matrices.";
        }
        for (unsigned int y = 0; y < sum.a[x].size(); y++) {
            /* Sum the elements. */
            sum.a[x][y] += matB.a[x][y];
        }
    }

    return sum;
}

int main () {
   int cases,k;
   cin >> cases;
   for(k=0;k<cases;k++) {
      Matrix x;
      Matrix y;
      Matrix result;
      int n,m,i,j;
      cin >> n >> m;
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         x.a.push_back(b);
      }
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         y.a.push_back(b);
      }
      result = x+y;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }
   }  
   return 0;
}
