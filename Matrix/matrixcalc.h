/*
Both the functions are interdependent.
The cofactor function removes the r-th row and c-th column from arr and then 
uses determinant function to calculate it's determinant.
Then it multiplies resulting value with appropiate sign and returns the value.
The determinat function calculate determinat of a matrix by
summing up first row elements multiplied by their respective cofactors.
It uses cofactor function to calculate the cofactors.
*/

double determinant(unsigned int n, double arr[n][n]);
/*
The determinant fuction takes two arguments: n - order of matrix, arr[n][n] - 2D Array containing the matrix elements
All indexing are zero based.
This function returns the determinant of the matrix.
*/

double cofactor(unsigned int n, unsigned int r, unsigned int c, double arr[n][n]);
/*
The cofactor function has following parameters n - order of matrix, (r,c) - denoting a particular element, arr[n][n] - The matrix elements.
Again all indexing is zero based.
The function returns the co-factor of (r,c) element.
*/
