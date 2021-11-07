#include<iostream>
#include<fstream>
#define ARRAY_SIZE 10
using namespace std;
void input_arr(int** arr, int* n){
    ifstream inf("input.txt");
    if (!inf)return;
    inf >> *n;
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++)
            inf >> arr[i][j];
}
bool check_arr(int** arr, int n){
    bool checkPrime = false, checkColumn;
    int a,k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            k = 2;
            if (!checkPrime)
                while (k < arr[i][j]){
                    if (arr[i][j] % k == 0){
                        checkPrime = true;
                        k = arr[i][j];
                    }
                    k++;
                }
        }
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++){
                checkColumn = true;
                for (k = 0; k < n; k++) {
                    if (arr[k][i] != arr[k][j])checkColumn = false;
                }
                if (checkColumn)return true;
            }
    return false;
}
void process_arr(int** arr, int n){
    int absSumArr[ARRAY_SIZE][2],arrC[ARRAY_SIZE][ARRAY_SIZE];
    int bufI, bufS;
    for (int i = 0; i < n; i++){
        absSumArr[i][0] = i;
        absSumArr[i][1] = 0;
        for (int j = 0; j < n; j++){
            absSumArr[i][1] += abs(arr[i][j]);
            arrC[i][j] = arr[i][j];
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++){
            if (absSumArr[i][1] > absSumArr[j][1]){
                bufI = absSumArr[i][0];
                bufS = absSumArr[i][1];
                absSumArr[i][0] = absSumArr[j][0];
                absSumArr[i][1] = absSumArr[j][1];
                absSumArr[j][0] = bufI;
                absSumArr[j][1] = bufS;
            }
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = arrC[absSumArr[i][0]][j];
}
void output_arr(int** arr, int n){
    ofstream outf("output.txt");
    if (!outf)return;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            outf << arr[i][j] << " ";
        outf << endl;
    }
}
void main(){
    int** arr = new int* [ARRAY_SIZE];
    int n;
    for (int i = 0; i < ARRAY_SIZE; i++)
        arr[i] = new int[ARRAY_SIZE];
    input_arr(arr, &n);
    if (check_arr(arr, n))
        process_arr(arr, n);
    output_arr(arr, n);
    return;
}
