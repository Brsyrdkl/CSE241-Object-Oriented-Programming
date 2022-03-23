#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;

class Gate
{
  public:
      int eval() = 0;
  private:
      string s_gate;
}
class ANDGate : public Gate
{
  private:
      Gate* inputL;
      Gate* inputR;
  public:
      ANDGate(Gate* in1,Gate* in2) : inputL(in1) ,inputR(in2)
      {
      }

      int eval()
      {
          return inputL->eval() & inputR->eval();
      }


}


class ORGate : public Gate
{
  private:
      Gate* inputL;
      Gate* inputR;
  public:
      ORGate(Gate* in1,Gate* in2) : inputL(in1) ,inputR(in2)
      {
      }

      int eval()
      {
          return inputL->eval() | inputR->eval();
      }
}

class NOTGate : public Gate
{
  private:
      Gate* inputN;
  public:
      NOTGate(Gate* in) : inputN(in)
      {
      }

      int eval()
      {
          if(inputN==1) return 0;
          else return 1;
      }
}
int readingInput(string txtfile, int** inArr);
int readingCircuit(const string txtfile,string *ssArr);

int main()
{
    string *ssArr;
    int** inArr;
    readingCircuit("circuit.txt",ssArr);
    readingInput("input.txt",inArr);

}










Gate readingCircuit(const string txtfile,string *ssArr)
{
  ifstream File(txtfile);
  int i=0,j=0;
  string *ssInput;
  string *ssOutput;
  int inCount = 0, outCount = 0 ,satırCount = 0,satırCount2 = 0;
  int andCount = 0, orCount = 0 , notCount = 0 , ffCount = 0;
  int ssArrLength;
  if(File.is_open())
{


      while(!File.eof())
        {
          string satır;
          getline(File,satır);
          satırCount++;
        }

        ssArr = new string [satırCount+1];

      File.seekg(0);

      int i=0;

            while(!File.eof())
            {
                File >> ssArr[i];
                i++;
            }

      ssArrLength = i;

      File.seekg(0);

      if(ssArr[0][0] != 'I' || ssArr[0][1] != 'N' || ssArr[0][2] != 'P' ||
        ssArr[0][3] != 'U' || ssArr[0][4] != 'T'){
          cerr << "First line is not INPUT.Please check your txt file!" << endl;
          exit(0);
        }
      else
          for(int i = 5 ; i < ssArr[0].length-4 ; i++)
              if(ssArr[0][i] == ' '){
                  inCount++;
                  if(ssArr[0][i+1] == ' '){
                      cerr << "Wrong input check your txt" << endl;
                      exit(0)
                  }
              }

      if(ssArr[1][0] != 'O' || ssArr[1][1] != 'U' || ssArr[1][2] != 'T' ||
        ssArr[1][3] != 'P' || ssArr[1][4] != 'U' || ssArr[1][5] != 'T' ||){}
          cerr << "Second line is not OUTPUT.Please check your txt file!" << endl;
          exit(0);
        }
      else
          for(int i = 6 ; i < ssArr[1].length-6 ; i++)
              if(ssArr[1][i] == ' '){
                  outCount++;
                  if(ssArr[1][i+1] == ' '){
                      cerr << "Wrong output check your txt" << endl;
                      exit(0)
                  }
              }

      string *ArrInput = new string[inCount+ssArrLength-1];
      string *ArrOutput = new string[outCount];


      for(int i = 2; i < ssArrLength ; i++){

          if(ssArr[i][0] == 'A' && ssArr[i][1] == 'N' && ssArr[i][2] == 'D')
          {
              andCount++;
          }
          else if(ssArr[i][0] == 'O' && ssArr[i][1] == 'R' ssArr[i][2] == ' ')
          {
              orCount++;
          }
          else if(ssArr[i][0] == 'N' && ssArr[i][1] == 'O' && ssArr[i][2] == 'T')
          {
              notCount++;
          }
          else if(ssArr[i][0] == 'F' && ssArr[i][1] == 'L' && ssArr[i][2] == 'I' &&
            ssArr[i][3] == 'P' && ssArr[i][4] == 'F' && ssArr[i][5] == 'L' &&
            ssArr[i][6] == 'O' && ssArr[i][7] == '7')
          {
              ffCount++;
          }
          else if(ssArr[i][0] == 'F' && ssArr[i][1] == 'L' && ssArr[i][2] == 'I' &&
            ssArr[i][3] == 'P' && ssArr[i][4] == 'F' && ssArr[i][5] == 'L' &&
            ssArr[i][6] == 'O')
          {
              dCount++;
          }
    }



}
  else
  {
    cerr << "Cannot open file try again" << endl;
    exit(0);
  }
}


int readingInput(string txtfile, int** inArr){

    ifstream File(txtfile);
    int number;
    int b=0;
    if(File.is_open())
    {
        while(!File.eof())
        {
            string satır;
            getline(File,satır);
            satırCount2++;
        }

      File.seekg(0);

      inArr = new int*[satırCount2];      //DYNAMIC ALLOCATION
      for(int i=0 ; i < satırCount2 ; i++)
          inArr[i] = new int[satır.length/2];


      for(int i=0;i<satırCount2;i++){
        for(int j=0;j<satır.length;j++){
            File >> number;
            if(number = 1 || number = 0){
              inArr[i][b] = number;
              b++;
            }
          }
        }

    return inArr;
    }

    else
    {
        cerr << "Cannot open file" << endl;
        exit(0);
    }
}
