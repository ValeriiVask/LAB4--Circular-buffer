// CircularBufferApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include "../CircularBufferLib/CircularBuffer.h"

int main()
{
    CircularBuffer<int, 10> buf;

    std::cout << "Push: ";
    for (int i = 0; i < 15; i++)
    {
        if (buf.push(i))
            std::cout << std::setw(5) << i << ",";
        else
            std::cout << "full ,";
    }
    std::cout << std::endl;

    std::cout << "Pop:  ";
    for (int i = 0; i < 15; i++)
    {
        int v;
        if (buf.pop(v))
            std::cout << std::setw(5) << v << ",";
        else
            std::cout << "empty,";
    }
    std::cout << std::endl;
}