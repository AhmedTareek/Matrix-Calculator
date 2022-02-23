#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ios>
#include <cstring>
using namespace std;


bool strtomat(char s[], float arr[][100], int* rownumber, int* colnumber);
void mattrans(float arr[][100], int rows, int cols);
double matdet(float arr[][100], int rows, int cols);
double matmindet(float arr[][100],float minors[][100], int rows, int cols);
void cofactors(float minors[][100],int n);
void adjucat(float cofacts[][100],float final[][100],int n);
void scamul(float arr[][100], float x, int arrrow, int arrcol);

int main() {

    int row1, col1;
    float arr[100][100] = { 0 };
    float arr2[100][100] = {0};
    float adj[100][100]={0};

    char s[1000001];
    cin.getline(s, 1000001);
    char op[2];
    cin.getline(op, 2);

    for (int  i =0 ;i < strlen(s)-1;i++){
        if ( ( (int)s[i] < 48 || (int)s[i] > 57)){
            if ((int)s[i]==45 ||(int) s[i] == 91 ||(int) s[i]==93 || (int)s[i]==32 || (int)s[i]==44){
                continue;
            }else{
                cout << "ERROR!";
                return 0;
            }
        }
    }
    if (op[0] == 'T') {
        cout << fixed << setprecision(2);
        strtomat(s, arr, &row1, &col1);
        mattrans(arr, row1, col1);
        return 0;
    }
    else if (op[0] == 'D') {
            strtomat(s, arr, &row1, &col1);
            cout << matdet(arr, row1, col1);
            return 0;

    }else if (op[0]=='I'){
        float deter = 0;
        strtomat(s, arr, &row1, &col1);
        matmindet(arr,arr2,row1,col1);
        cofactors(arr2,row1);
        adjucat(arr2,adj,row1);
        deter = matdet(arr, row1, col1);
        if (deter ==0){
            cout << "ERROR!";
            return 0;
        }
        scamul(adj,(1/deter),row1,col1);

    }






}
void scamul(float arr[][100], float x, int arrrow, int arrcol) {
    cout << '[';
    for (int i = 0; i < arrrow; i++) {
        for (int j = 0; j < arrcol; j++) {
            if (j != arrcol - 1) {
                if ((float)(arr[i][j] * x) == (int) (arr[i][j] * x)){
                cout << fixed << setprecision(2) <<  arr[i][j] * x << ' ';
                }else{
                  if (arr[i][j] * x < 0 ){
                        cout << fixed << setprecision(2) << (ceil(100*(arr[i][j] * x))/100) <<' ';
                    }else{
                        cout << fixed << setprecision(2) << (floor(100*(arr[i][j] * x))/100) <<' ';
                    }
                }
            }
            else {
                if ((float) (arr[i][j] * x) == (int) (arr[i][j] * x)){
                cout << fixed << setprecision(2) << arr[i][j] * x;
                }else{
                    if (arr[i][j] * x < 0 ){
                        cout << fixed << setprecision(2) << (ceil(100*(arr[i][j] * x))/100);
                    }else{
                        cout << fixed << setprecision(2) << (floor(100*(arr[i][j] * x))/100);
                    }
                }
            }
        }
        if (i != arrrow - 1)
            cout << ',' << ' ';
    }
    cout << ']';


}




void adjucat(float cofacts[][100],float final[][100],int n){
    for (int i =0;i<n;i++){
        for (int j =0;j<n;j++){
            final[i][j]=cofacts[j][i];
        }
    }
}
void cofactors(float minors[][100],int n){
    float sign;
    float bigsign=1;
    for (int i =0 ; i<n;i++){
        sign = bigsign;
        for (int j =0;j<n;j++){
            if (minors[i][j]==0){
                sign = sign *-1;
            }else{
            minors[i][j] = sign * minors[i][j];
            sign = sign *-1;
            }
        }
        bigsign=bigsign*-1;
    }

}



double matmindet(float arr[][100],float minors[][100], int rows, int cols){
    if (rows != cols) {
        cout << "ERROR!";
        return 0;
    }
    if (rows == 2) {
        return (arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0]);
    }
    else if (rows == 1) {
        return arr[0][0];
    }
    else {
        int minorsrowidx=0,minorscolidx=0;
        float d=0;
        for (int i = 0; i < rows; i++) {
            for (int i2 = 0;i2<rows;i2++){

            float mat[100][100];
            int colidx = 0, rowidx = 0;   //mat index
            for (int j = 0; j < rows; j++) {
                colidx = 0;
                for (int k = 0; k < rows; k++) {
                    if (j == i || k == i2){
                        continue;
                    }else {
                    mat[rowidx][colidx] = arr[j][k];
                    colidx++;
                    }
                }
           if (colidx != 0 )
                rowidx++;

            }
          /*  for (int f =0 ; f< rowidx;f++){
                for (int ff=0 ; ff<rowidx;ff++){
                    cout << mat[f][ff] << ' ';
                }
                cout << endl;
            } */

            d =  matdet(mat, rows - 1, cols - 1);
            minors[minorsrowidx][minorscolidx]=d;
            minorscolidx++;
            if (minorscolidx == cols){
                minorscolidx=0;
                minorsrowidx++;
            }
           // cout << " d is " << ' ' << d << endl;
        }
        }


        return d;
    }
}







double matdet(float arr[][100], int rows, int cols) {
    if (rows != cols) {
        cout << "ERROR!";
        return 0;
    }
    if (rows == 2) {
        return (arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0]);
    }
    else if (rows == 1) {
        return arr[0][0];
    }
    else {
        double d=0;
        int sign = 1;
        for (int i = 0; i < rows; i++) {

            float mat[100][100];
            int colidx = 0, rowidx = 0;   //mat index
            for (int j = 1; j < rows; j++) {
                colidx = 0;
                for (int k = 0; k < rows; k++) {
                    if (k != i) {
                    mat[rowidx][colidx] = arr[j][k];
                    colidx++;
                    }
                }
            rowidx++;

            }

            d+= sign * arr[0][i] * matdet(mat, rows - 1, cols - 1);
            sign *= -1;


        }


        return d;
    }






}
void mattrans(float arr[][100], int rows, int cols) {
    cout << '[';
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (i != rows - 1) {

                if (arr[i][j] - (int)arr[i][j] == 0) {
                    cout << fixed << setprecision(0) << arr[i][j] << ' ';
                }
                else
                {
                    cout << fixed << setprecision(2) << arr[i][j] << ' ';
                }
            }
            else
            {
                if (arr[i][j] - (int)arr[i][j] == 0) {
                    cout << fixed << setprecision(0) << arr[i][j];
                }
                else
                {
                    cout << fixed << setprecision(2) << arr[i][j];
                }







            }
        }
        if (j != cols - 1) {
            cout << ',' << ' ';
        }
    }

    cout << ']';



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
