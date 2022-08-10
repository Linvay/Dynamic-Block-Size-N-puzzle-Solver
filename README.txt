/* -------------------------------------------------------------------
// 2022 SPRING ARTIFICIAL INTELLIGENCE HOMEWORK 2: SLIDING PUZZLE
// Author: Ting-Wei, Lin
// Student number: 40847038S
// Last update: 2022, April 28
// Environment: Windows 10
// Language: C++11
// Contact info:
// - e-mail: 40847038S@gapps.ntnu.edu.tw
// - phone: 0984313471
// ------------------------------------------------------------------ */

===COMPILE===
make
    compile all .cpp files
make clean
    delete all .o files

===EXECUTE PROGRAM===
.\main_IDS
    find sliding game solution with IDS
.\main_IDS t
    find sliding game solution with IDS, the program will also print out the time when finish searching a depth
.\main_IDAStar
    find sliding game solution with IDA*
.\main_IDAStar t
    find sliding game solution with IDA*, the program will also print out the time when finish searching a limit
IMPORTANT NOTE: Depending on the input, it might take the program a VERY long time to complete a search, 
                use CRTL+C to terminate the program if needed

===INPUT/OUTPUT===
After running either main_IDS or main_IDAStar, the program will ask you to enter the path to your input and output file
For example:
    input.txt
    output.txt
The program will search for "input.txt" in this current folder, and generate "output.txt" within this folder as well
the results of the program will be shown on the terminal, you can also find the result in the chosen output file
Should you choose to give a file path outside of this folder, make sure it is (1) an absolute path (2) the reverse-slash
is typed twice (e.g., C:\\input.txt)
IMPORTANT NOTE:
    (1) Some file reading/writing require administration access, you should execute the program as admin if file action is blocked
    (2) Anti-virus program might also block file action, you might want to disable it while executing the programs

===TEST CASES===
Test cases provided by the author is within these .txt files:
    input.txt
    input_ids.txt
    input_idastar.txt
Both main_IDS abd main_IDAStar is able to run input.txt, while input_ids.txt are test cases meant for main_IDS, 
and input_idastar are test cases meant for main_IDAStar