#include "proj5.h"

int main(int argc, char* argv[]) {

    string inputtxt = "";  
    string outputtxt = argv[argc-1];

    if (argc < 3) {
        cout << "Incorrect execution format"  << endl;

    }

    // Read through input args and assign to the correct variable of proj4 class
    for (int i = 1; i < argc-1; i++) {

        if (string(argv[i]) == "input.txt") {
            inputtxt = argv[i];
            cout << inputtxt << endl;

        }
    }
    


    ofstream outFile;
    outFile.open(outputtxt);

    Proj5 hw;
    hw.q1read(inputtxt);

    // Execute Question 1
    auto start = chrono::high_resolution_clock::now();

    hw.q1(outFile);
     
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    outFile << endl << "# Running Time: " << endl << duration.count() << " microseconds." << endl; ;

    outFile << endl << "-------------------------- " << endl << endl;

    // Execute Question 2
    hw.q2read(inputtxt);

    // Part A
    start = chrono::high_resolution_clock::now();

    hw.q2a(outFile);
     
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    outFile << "# Running Time: " << endl << duration.count() << " microseconds." << endl; ;

    outFile << endl << "-------------------------- " << endl << endl;

    // Part B
    // start = chrono::high_resolution_clock::now();

    // hw.q2(outFile); 
     
    // end = chrono::high_resolution_clock::now();
    // duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // outFile << endl << "# Running Time: " << endl << duration.count() << " microseconds." << endl; ;

    // outFile << endl << "-------------------------- " << endl << endl;
    return 0;

}