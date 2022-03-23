#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

#include "catalog.h"

using namespace std;


int main()
{
int unique;
Catalog OBJ;
readData("data.txt",OBJ);
writeOutput("output.txt",OBJ);
unique = OBJ.CheckDuplicateEntry(OBJ);

fstream oFile;
oFile.open("output.txt",ios::out | ios::app);
oFile << unique << " unique entries" << endl;


readComm("command.txt",OBJ);

return 0;
}
