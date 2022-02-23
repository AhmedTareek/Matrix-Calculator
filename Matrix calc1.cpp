#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;


bool strtomat(char s[], float arr[][100], int* rownumber, int* colnumber);
void matadd(float arr[][100], float arr2[][100], int arrrow, int arrcol, int arr2row, int arr2col);
void matsub(float arr[][100], float arr2[][100], int arrrow, int arrcol, int arr2row, int arr2col);
void matmul(float arr[][100], float arr2[][100], int arrrow, int arrcol, int arr2row, int arr2col);
void scamul(float arr[][100], float x, int arrrow, int arrcol);
int main() {
    int row1, col1, row2, col2;
    float arr[100][100] = { 0 };
    float arr2[100][100] = { 0 };
    char s[100000];
    char s2[100000];
    cin.getline(s, 100000);
    char op[2];
    cin.getline(op, 10);
    cin.getline(s2, 100000);
    bool first = false;
    bool second = false;

    if (op[0] == '+') {

        first = strtomat(s, arr, &row1, &col1);
        second = strtomat(s2, arr2, &row2, &col2);
        if (first && second) {
            matadd(arr, arr2, row1, col1, row2, col2);
        }
        else {
            cout << "ERROR!";
            return 0;
        }
    }
    else if (op[0] == '-') {
        first = strtomat(s, arr, &row1, &col1);
        second = strtomat(s2, arr2, &row2, &col2);
        if (first && second) {
            matsub(arr, arr2, row1, col1, row2, col2);
        }
        else {
            cout << "ERROR!";
            return 0;

        }
    }
    else if (op[0] == '*') {
        if (s[0] == '[' && s2[0] == '[') {
            first = strtomat(s, arr, &row1, &col1);
            second = strtomat(s2, arr2, &row2, &col2);
            if (first && second) {
                matmul(arr, arr2, row1, col1, row2, col2);
            }
            else {
                cout << "ERROR!";
                return 0;

            }
        }
        else if (s[0] != '[') {
            first = strtomat(s2, arr2, &row2, &col2);
            if (first) {
                scamul(arr2, stof(&s[0]), row2, col2);
            }
            else {
                cout << "ERROR!";
                return 0;

            }
        }
        else if (s2[0] != '[') {
            first = strtomat(s, arr, &row1, &col1);
            if (first) {
                scamul(arr, stof(&s2[0]), row1, col1);
            }
            else {
                cout << "ERROR!";
                return 0;

            }
        }
        else {
            cout << "ERROR!";
            return 0;

        }
    }
    else {
        cout << "ERROR!";
        return 0;
    }

}
void scamul(float arr[][100], float x, int arrrow, int arrcol) {
    cout << '[';
    for (int i = 0; i < arrrow; i++) {
        for (int j = 0; j < arrcol; j++) {
            if (j != arrcol - 1) {
                cout << arr[i][j] * x << ' ';
            }
            else {
                cout << arr[i][j] * x;
            }
        }
        if (i != arrrow - 1)
            cout << ',' << ' ';
    }
    cout << ']';





}
void matmul(float arr[][100], float arr2[][100], int arrrow, int arrcol, int arr2row, int arr2col) {
    float sum = 0;
    if (arrcol == arr2row) {
        cout << '[';
        for (int i = 0; i < arrrow; i++) {
            for (int j = 0; j < arr2col; j++) {
                sum = 0;
                for (int k = 0; k < arr2row; k++) {
                    sum += arr[i][k] * arr2[k][j];
                }
                if (j != arr2col - 1) {
                    cout << sum << ' ';
                }
                else {
                    cout << sum;
                }
            }
            if (i != arrrow - 1)
                cout << ',' << ' ';

        }
        cout << ']';

    }
    else
    {
        cout << "ERROR!";
    }

}

void matsub(float arr[][100], float arr2[][100], int arrrow, int arrcol, int arr2row, int arr2col) {

    if (arr2row == arrrow && arr2col == arrcol) {
        cout << "[";
        for (int i = 0; i < arrrow; i++) {
            for (int j = 0; j < arrcol; j++) {
                cout << arr[i][j] - arr2[i][j];
                if (j != arrcol - 1)
                    cout << ' ';
            }
            if (i != arrrow - 1)
                cout << ',' << ' ';
        }
        cout << ']';
    }
    else
    {
        cout << "ERROR!";
    }

}

void matadd(float arr[][100], float arr2[][100], int arrrow, int arrcol, int arr2row, int arr2col) {

    if (arr2row == arrrow && arr2col == arrcol) {
        cout << "[";
        for (int i = 0; i < arrrow; i++) {
            for (int j = 0; j < arrcol; j++) {
                cout << arr[i][j] + arr2[i][j];
                if (j != arrcol - 1)
                    cout << ' ';
            }
            if (i != arrrow - 1)
                cout << ',' << ' ';
        }
        cout << ']';
    }
    else
    {
        cout << "ERROR!";
    }
}

bool strtomat(char s[], float arr[][100], int* rownumber, int* colnumber) {
    bool IsFirstTime = true;
    int count = 1;
    int count2 = 0;
    float x;
    s[strlen(s) - 1] = s[strlen(s)];  // remove last bracket

    for (unsigned int i = 0; i <= strlen(s); i++) {
        s[i] = s[i + 1];
    } // remove first bracket
    char* word = strtok(s, " "); //split the string by spaces

    int rowidx = 0, colidx = 0; //index for the float array (arr)
    int oldcol;
    int allcol = 1;
    int all = 0;
    while (word != NULL)
    {

        all++;
        x = stof(word);
        arr[rowidx][colidx] = x;
        colidx++;
        //cout << x << endl;
        //cout << word << endl;
        count2++;
        if ((word[strlen(word) - 1] == ',')) { //check if there , in the number
            allcol++;
            if (IsFirstTime) {
                oldcol = colidx;
                IsFirstTime = false;
            }
            if (oldcol == colidx) {
                count++;
                rowidx++;
                colidx = 0;
            }
            else {
                //cout << "ERORR!"<<endl;
                arr = { 0 };
                count2 = 0;
                all++;
                return false;
                break;

            }
        }
        word = strtok(NULL, " ");
    }
    //cout <<endl<< count2 << endl;
    //cout <<endl<< count << endl;
    //if (! IsFirstTime){
    //for(int i = 0;i<count;i++){
      //  for(int j =0;j<(count2/count);j++)
        //cout << arr[i][j] << ' ';
      //  cout << endl;
    //}
    //}
    //cout << "rows num : " << count << endl;
    //cout << "col num : " << count2/count;
    if (count * (count2 / count) != all)
        return false;
    *rownumber = count;
    *colnumber = count2 / count;
    return true;

}
