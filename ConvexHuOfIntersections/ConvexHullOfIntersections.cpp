// ConvexHuOfIntersections.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Set.h"
#include "IntersectionCalculator.h"

#include <iostream> 
#include <sstream>

using namespace std;
Set theSet;
void generateStressTest(int numPrimitives = 1000) {
    ofstream outfile;
    outfile.open("stressTest.dat");
    outfile << to_string(numPrimitives) << endl;
    const int width = 100;
    const int height = 100;
    const int maxRadius = 50;
    for (int i = 0; i < numPrimitives; i++) {
        stringstream ss;
        int rPrim = rand() % 2;
        switch (rPrim) {
            case 0:
            {
                int rX = rand() % width;
                int rY = rand() % height;
                int rR = rand() % maxRadius;
                ss << "C " << rX << " " << rY << " " << rR;
            }
            break;
            case 1:
            {
                int rX0 = rand() % width;
                int rY0 = rand() % height;
                int rX1 = rand() % width;
                int rY1 = rand() % height;
                ss << "L " << rX0 << " " << rY0 << " " << rX1 << " " << rY1;
            }
            break;
        }
        outfile << ss.str() << endl;
    }
    outfile.close();
}

int main()
{
    std::cout << "Convex Hull Of Intersections!\n";
    std::cout << "-----------------------------\n";
    //generateStressTest();
    if (IntersectionCalculator::test()) {
        theSet.getPrimitives();
        theSet.writeOutPrimitives(true);
        theSet.calcIntersections();
        theSet.writeOutPoints(true);
        //theSet.findHullPoints();
        theSet.findConvexHullJarvis();
        theSet.writeOutHullPoints(true);
        theSet.calcAreaOfTheConvexHull();
    }
    else
        cout << "Error! The algorithm test is unsucessfull.";
 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
