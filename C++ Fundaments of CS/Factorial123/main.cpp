#include <iostream>



//#include <iostream>

#include <ctime>

using namespace std;


int GCF(int x, int y) { // create GCF function with x and y parameters

    if (y == 0) { // compares if y is equal to 0
        return x; // if y = 0 , then return x
    } else //if y is not 0 it continues the if statement
    {
        return GCF(y, x % y); // Again call the GCF function but swap position x with y and y with x mod y unless y = 0


    }

}

int gcf(int x, int y) { // create gcf function with x and y parameters
    int z = 0; // declare int variable z with value 0;
    while (y != 0) { // check if value of y = 0 , if not it continues the loop
        z = y; // assign value of z with y
        y = x % y; // assign value of y with x mod y
        x = z; // assign value of x with z ,i.e y
    }
    return x; // once y = 0 it returns the x value
}

int time_taken_recurcisvely() { // create a function with no parameter
    ::clock_t t1 = ::clock(); // create a t1 variable and recording the time before loop.
    int res = 0; // create res variable with value 0
    ::srand(1); // intialise random no.
    for (int i = 0; i < 1000000; i++) { // looping for million times
        res += GCF(rand(), rand()); //finding GCF using recurcisve method of million value


    }
    clock_t t2 = ::clock(); // create a t2 variable and recording the time after loop.
    cout << res << "\n"; // print the last res = GCF value from loop
    cout << "Time taken by recursively  is " << t2 - t1 << "\n";// print the time taken for loop to finish

}

int time_taken_iteratively() { //create a function
    ::clock_t t1 = ::clock(); // create a t1 variable and recording the time before loop.
    int res = 0; // create res variable with value 0
    ::srand(1); //intialise random no.
    for (int i = 0; i < 1000000; i++) { // looping for million times
        res += gcf(rand(), rand()); //finding GCF using iterative method of million value


    }

    clock_t t2 = ::clock(); // create a t2 variable and recording the time after loop.
    cout << res << "\n";//print the last res = GCF value from loop
    cout << "Time taken by iteratively  is " << t2 - t1 << "\n"; // print the time taken for loop to finish

}


int main() {

    int a = 31, b = 01, c = 53, d = 52; // assigning value of a,b,c,d with refrence to my student ID

    cout << GCF(20, 12) << "\n" << gcf(20, 12)
         << "\n"; //print the GCF of 20 and 12 using recursive first and iterative method 2nd
    cout << "The GCF of (a*b,c) is " << GCF(a * b, c) << "\n"; // print the GCF of (a*b,c) using recursive method
    cout << "The GCF of (b*c,d) is " << GCF(b * c, d) << "\n";// print the GCF of (b*c,d) using recursive method
    cout << "The GCF of (c*d,a) is " << GCF(c * d, a) << "\n";// print the GCF of (c*d,a) using recursive method


    cout << "The GCF of (a*b,c) is " << gcf(a * b, c) << "\n";// print the GCF of (a*b,c) using iterative method
    cout << "The GCF of (b*c,d) is " << gcf(b * c, d) << "\n";// print the GCF of (b*c,d) using iterative method
    cout << "The GCF of (c*d,a) is " << gcf(c * d, a) << "\n";// print the GCF of (b*c,d) using iterative method

    time_taken_iteratively(); // calling time_taken_iteratively function
    time_taken_recurcisvely(); // calling  time_taken_recurcisvely function


}



