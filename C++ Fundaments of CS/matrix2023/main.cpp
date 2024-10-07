// MyMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>

using namespace std;


// matlib.cpp : A simple matrix library program.
// Written by Prof Richard Mitchell    6/12/22
// Adapted by
//

const int maxM = 16;    // allows for matrices up to size 4*4

struct myMat {            // structure to store a matrix
    int numRows;        // number of rows
    int numCols;        // number of columns
    int data[maxM];        // data are stored in row order
};


myMat zeroMat(int r, int c) {
    // create a matrix with r rows and c columns, filled with zeros
    myMat m;            // define matrix
    m.numRows = r;        // set size
    m.numCols = c;
    for (int ct = 0; ct < maxM; ct++) m.data[ct] = 0;// set elems to 0

    return m;            // return matrix
}

int getIndex(myMat m, int r, int c) {
    // returm index of element in row r, col c of matrix m
    return r * m.numCols + c;
}

myMat mFromStr(string s) {
    // create a matrix from string s
    // string of form "1,2;3,4;5,6"   ; separates rows and , separates columns ... No error check
    int ms;
    if (s.length() > 0) ms = 1; else ms = 0;
    myMat m = zeroMat(ms, ms);                        // is s empty create 0*0 matrix, else start with 1*1 matrix
    int mndx = 0;                                    // used to index into array
    string sub = "";                                // sub string - numbers between , or ; set empty
    for (int ct = 0; ct < s.length(); ct++) {        // each char in turn
        if ((s[ct] == ',') || (s[ct] == ';')) {    // if , or ; then sub contains number
            m.data[mndx++] = stoi(sub);                // convert number to integer, put in data array
            sub = "";                                // clear sub string
            if (s[ct] == ';') m.numRows++;            // if found ; indicates an extra row
            else if (m.numRows == 1) m.numCols++;    // if , then (if in row 1) increase count of columns
        } else sub = sub + s[ct];                        // add character to sub string
    }
    if (sub.length() > 0) m.data[mndx++] = stoi(sub);// add last sub string
    return m;
}

myMat mGetRow(myMat m, int row) {
    // create a matrix from m, having one row
    myMat res = zeroMat(1, m.numCols);        // create a matrix of 1 row
    for (int col = 0; col < m.numCols; col++)// for each element in row

        res.data[col] = m.data[getIndex(m, row, col)];        // copy col element to res
    return res;
}

myMat mGetCol(myMat m, int col) {
    // create a matrix from m, having one column
    myMat col_res = zeroMat(m.numRows, 1);        // create a matrix of 1 column
    for (int row = 0; row < m.numRows; row++)// for each element in column

        col_res.data[row] = m.data[getIndex(m, row, col)];        // copy row element to res
    return col_res;
}


int dotProd(myMat v1, myMat v2) { // create dotProd function
    int prod = 0; // create prod variable
    for (int m = 0; m < v1.numCols; m++) // creating boundry
        prod += v1.data[getIndex(v1, 0, m)] * v2.data[getIndex(v2, m, 0)]; // multiplying alternative row and column


    return prod;
}


myMat mTranspose(myMat m) { // mTranspose function is created with a matrix parameter

    myMat res = zeroMat(m.numCols, m.numRows);        // create a matrix of 1 row

    for (int col = 0; col < m.numCols; col++)// for each element in column
        for (int row = 0; row < m.numRows; row++)// for each element in rows

            res.data[getIndex(res, col, row)] = m.data[getIndex(m, row, col)]; // swaping the element of rows and column
    return res;

}

myMat mAdd(myMat m1, myMat m2) { //mAdd function created with parameter m1 and m2
    myMat res = zeroMat(m1.numRows, m1.numCols);        // create res zero matrix of same no. of rows and column of m1

    for (int row = 0; row < m1.numRows; row++) // do each row of m1
        for (int col = 0; col < m1.numCols; col++)// do each column of m1.

            res.data[getIndex(res, row, col)] =
                    m1.data[getIndex(m1, row, col)] + m2.data[getIndex(m2, row, col)];
    //adding each same position element of m1 and m2 matrix and assigning to res matrix.
    return res;
}

myMat mMult(myMat m1, myMat m2) { // multiply 2 matrixes

    myMat res = zeroMat(m1.numRows, m2.numCols); //create res matrix with mith m1 rows and m2 column size.


    for (int row = 0; row < m1.numRows; row++) // do each row of m1
        for (int col = 0; col < m2.numCols; col++) // do each column of m2
            res.data[getIndex(res, row, col)] = dotProd(mGetRow(m1, row), mGetCol(m2, col));
//assigning res.data value with dot product of m1 rows with m2 columns
    return res; //return value of res
}

myMat mScalar(myMat m1, myMat m2) { // scalar task to be perfomed
    myMat res = zeroMat(m1.numRows, m1.numCols); // creating res matrix with m1 matrix size

    for (int row = 0; row < m1.numRows; row++) // foe each element of row of m1
        for (int col = 0; col < m1.numCols; col++)// for each element column of m1

            res.data[getIndex(res, row, col)] = 9 * m1.data[getIndex(m1, row, col)] -
                                                7 * m2.data[getIndex(m2, row, col)];
    //carry out scalar operation with constant and matrix and assign the value to res
    return res; // return final res value
}

myMat mMagic(myMat m) { //adjoint matrix to be found
    myMat magic = zeroMat(m.numRows, m.numCols); // same parameter size matrix to be formed

    magic.data[0] = m.data[getIndex(m, 1, 1)]; // assigning 1st value of magic matrix with last element of m
    magic.data[1] = -m.data[getIndex(m, 0, 1)]; // swaping the 2nd element wiht 3rd and make it negative
    magic.data[2] = -m.data[getIndex(m, 1, 0)]; // swaping the 3rd element wiht 2nd and make it negative
    magic.data[3] = m.data[getIndex(m, 0, 0)];// assigning last value of magic matrix with firs element of m

    return magic;
}

myMat mMagicToFindX(myMat m1, myMat m2) { // x to be found using Magic function
    myMat x = zeroMat(m2.numRows, m2.numCols); // setting the size of x
    myMat prod_of_A_and_Magic = zeroMat(m1.numRows, m1.numCols); // setting the size of product of A and Magic matrix


    myMat prod_of_b_and_Magic = zeroMat(m2.numRows, m2.numCols); // setting the size of product of A and Magic matrix

    prod_of_A_and_Magic = mMult(mMagic(m1), m1); // multiplying matrix A with magic matrix
    prod_of_b_and_Magic = mMult(mMagic(m1), m2); // multiplying matrix b with magic matrix


    x.data[0] = (prod_of_b_and_Magic.data[getIndex(prod_of_b_and_Magic, 0, 0)]) /
                (prod_of_A_and_Magic.data[getIndex(prod_of_A_and_Magic, 0, 0)]);
    //setting first element of x

    x.data[1] = (prod_of_b_and_Magic.data[getIndex(prod_of_b_and_Magic, 1, 0)]) /
                (prod_of_A_and_Magic.data[getIndex(prod_of_A_and_Magic, 1, 1)]);
//setting second element of x
    return x;
}

int mDeter(myMat m) { // to find determinant of a matrix
    int deter = 0;
    deter = m.data[getIndex(m, 0, 0)] * m.data[getIndex(m, 1, 1)] -
            m.data[getIndex(m, 1, 0)] * m.data[getIndex(m, 0, 1)];
    //deter = product 1st and last element - product of 2nd and 3rd element
    return deter;

}

myMat mCarmer(myMat m1, myMat m2) { //to find x using carmer method
    myMat x = zeroMat(m2.numRows, m2.numCols);


    x.data[0] = ((m2.data[getIndex(m2, 0, 0)]) * (m1.data[getIndex(m1, 1, 1)]) -
                 m2.data[getIndex(m2, 1, 0)] * (m1.data[getIndex(m1, 0, 1)])) / mDeter(m1);
//setting 1st element using carmer method
    x.data[1] = ((m2.data[getIndex(m2, 1, 0)]) * (m1.data[getIndex(m1, 0, 0)]) -
                 m2.data[getIndex(m2, 0, 0)] * (m1.data[getIndex(m1, 1, 0)])) / mDeter(m1);
    //setting 2nd element using carmer method
    return x;
}

void printMat(const char *mess, myMat m) {
    // mess is string to be printed, followed by matrix m
    cout << mess << " = " << "\n";                // print message
    for (int row = 0; row < m.numRows; row++) {        // do each row
        for (int col = 0; col < m.numCols; col++)        // do each column
            cout << m.data[getIndex(m, row, col)] << "\t";    // outputing the element then tab
        cout << "\n";                            // output new line at end of row
    }
    cout << "\n";                                // and end of Matrix
}

void testVecs(myMat m1, myMat m3) {
    // test vector routines ... get row from m1, col from m2, do dot product of these
    cout << "Testing Vector routines" << "\n";
    printMat("m1(A) row 0", mGetRow(m1, 0));    // display row 0 of m1
    printMat("m3(C) col 1", mGetCol(m3, 1));
    cout << "Dot prod of these is " << dotProd(mGetRow(m1, 0), mGetCol(m3, 1)) << "\n\n";
}

void testMatOps(myMat m1, myMat m2, myMat m3, myMat m5, myMat m6, myMat m7, myMat m8) {
    // test matrix operations m1 + m2; m1 + m3'; m1 * m3; m3 * m2
    cout << "Testing Add, Transpose, Multiply routines" << "\n";

    printMat("m1 + m2", mAdd(m1, m2));
    printMat("m1 + m3'", mAdd(m1, mTranspose(m3)));


    printMat("m1*m3", mMult(m1, m3));
    printMat("m3*m2", mMult(m3, m2));

    printMat("9m1 - 7m3'", mScalar(m1, mTranspose(m3)));
    cout << "Determinant of m5 = " << mDeter(m5) << "\n" << "\n";
    printMat("The value of x if A and b given with carmer law is ", mCarmer(m5, m6));

    printMat("Magic matrix of A (m7)", mMagic(m7));

    printMat("The value of x if A and b given with magic matrix is ", mMagicToFindX(m7, m8));

}

int main() {
    cout << "31015352 matrixes \n";    // change to your student number
    myMat m1, m2, m3, m5, m6, m7, m8;                        // create three matrices

    m1 = mFromStr("5,5,9;7,9,10");            // change numbers to those from the web page, as specified on the sheet
    m2 = mFromStr("10,5,5;9,9,8");            // ditto
    m3 = mFromStr("8,7;7,9;8,9");            // ditto
    m5 = mFromStr("9,7;10,5");      //ditto
    m6 = mFromStr("125;125");       //ditto

    m7 = mFromStr("9,10;5,5");  //ditto
    m8 = mFromStr("161;85");    //ditto

    printMat("m1", m1);                        // display m1
    printMat("m2", m2);                        // display m2
    printMat("m3", m3);                  // display m3
    printMat("Carmer rule A(m5) ", m5); //display m5
    printMat("Carmer rule b(m6)", m6); //display m6
    printMat("Magic matrix A(m7) ", m7);//display m7
    printMat("Magic matrix b(m8) ", m8);//display m8
    testVecs(m1, m3);                        // test the vector routines
    testMatOps(m1, m2, m3, m5, m6, m7, m8);                    // test the add, transpose and multiply


    return 0;
}