#include <iostream>
#include <chrono>
#include <fstream>

typedef std::chrono::high_resolution_clock Clock;
using namespace std;


int fib_rec(int x)
{
    if (x == 0)
        return 0;
    else if (x == 1)
        return 1;
    else
        return fib_rec(x-1) + fib_rec(x-2);
}

int fib_itr(int x)
{
    int a;
    int b;
    int c;

    a = 0;
    b = 1;

    for (int i = 1; i < x; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main () {
    int n;
    n = 2000000;


    std::ofstream MyFile("Time.csv");

    MyFile << "n, 2n, A2(n), A2(2n), T'2(n), T'2(2n), r, \n";
    for (int i = 0; i < 1000; i++) {

        auto start_n = std::chrono::high_resolution_clock::now();
        fib_itr(n + i);
        auto finish_n = std::chrono::high_resolution_clock::now();
        cout << "T' (n) = " << chrono::duration_cast<chrono::microseconds>(finish_n - start_n).count() << " ms. (n = "
             << n + i << ")" << std::endl;
        auto start_2n = std::chrono::high_resolution_clock::now();
        fib_itr(2*n+2*i);
        auto finish_2n = std::chrono::high_resolution_clock::now();
        cout << "T' (2n) = " << chrono::duration_cast<chrono::microseconds>(finish_2n - start_2n).count() << " ms. (2n = "
             << 2*n + 2*i << ")" << std::endl;

        float t_1;
        t_1 = chrono::duration_cast<chrono::microseconds>(finish_n - start_n).count();

        float t_2;
        t_2 = chrono::duration_cast<chrono::microseconds>(finish_2n - start_2n).count();

        //MyFile << n+i << ',' << 2*n+2*i << ',' << fib_itr(n + i) << ',' << fib_itr(2*n+2*i) <<',' << chrono::duration_cast<chrono::microseconds>(finish_n - start_n).count() << ',' << chrono::duration_cast<chrono::microseconds>(finish_2n - start_2n).count() << ',' << t_1/t_2 << std::endl;
        MyFile << n+i << ',' << 2*n+2*i << ',' << fib_itr(n + i) << ',' << fib_itr(2*n+2*i) <<',' << t_1 << ',' << t_2 << ',' << t_2/t_1 << std::endl;


        //std::vector<std::pair<std::string, std::vector<int>>> vals = {{"One", vec1}, {"Two", vec2}, {"Three", vec3}};


    }

    MyFile.close();
    return 0;
    //cout << fib_itr(2000000);
}


    /*for (int i = 0; i<100; i++){
        auto start = std::chrono::high_resolution_clock::now();
        fib_itr(2*n+2*i);
        auto finish = std::chrono::high_resolution_clock::now();
        cout << "T' (2n) = " << chrono::duration_cast<chrono::microseconds>(finish - start).count()<<" ms. (n = " << 2*n+2*i << ")" <<std::endl;
        MyFile<< chrono::duration_cast<chrono::microseconds>(finish - start).count() << std::endl;
    }

    // Create a file stream object and check that it opened correctly

    // Write some stuff to the file


    close the file


}*/

