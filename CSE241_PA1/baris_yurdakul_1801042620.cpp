#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;


int us(int alt,int ust){
  int sonuc = 1;
  for(int i=1;i<=ust;++i){
    sonuc *= alt;
  }
  return sonuc;
}

string cnvrtToString(char** arr,int size){//converting to -r or -u to string
  string s = "";
  for(int i=0 ; i<2 ;++i){
    s += arr[size][i];
  }
  return s ;
}

int cnvrtToInt(char** arr,int size){//convert argv[2] to int
  int num=0,basamak;
  int count = 0,i=0;
  int count2;
  while(arr[size][count]!= NULL){
    count++;
  }
  count2 = count;
  while(count2>0){
  basamak = arr[size][count2-1] - '0';
  num += basamak*us(10,i);
  i++;
  count2--;
}
  return num;
}

void checkdigits(string s1,string s2 ){//printing first and second count
    int size = sizeof(s1);
    int firstcount = 0,secondcount = 0;
    int i = 0;
    while(s1[i]!=NULL){
      if(s1[i]==s2[i]) firstcount++;
      if(s1[i]!=s2[i]){
        for(int j=0;j<=size;j++){
          if(s1[i]==s2[j]) secondcount++;
        }
      }
      i++;
    }
cout << firstcount << " " << secondcount << endl;
}

bool checksamedigits(int secret){

      int basamak=0;
      int holdsecret ;
      holdsecret = secret;
      while(holdsecret != 0){
          basamak++;
          holdsecret = holdsecret/10;
      }
      for(int i = 0 ; i< basamak ; i++){
          holdsecret = secret/10;
          while(holdsecret != 0){
              if(secret%10 == holdsecret%10) return false;
              holdsecret = holdsecret/10;
          }
          secret = secret/10;
      }
      return true;
}

bool checkNotInteger(char** argv){

  bool check=false;
  int i=0;

  while(argv[2][i]!=NULL){
    if(argv[2][i]!='0' &&
       argv[2][i]!='1' &&
       argv[2][i]!='2' &&
       argv[2][i]!='3' &&
       argv[2][i]!='4' &&
       argv[2][i]!='5' &&
       argv[2][i]!='6' &&
       argv[2][i]!='7' &&
       argv[2][i]!='8' &&
       argv[2][i]!='9') check=true;
       i++;
  }
  return check;
}

bool checkNotInteger(string argv){

  bool check=false;
  int i=0;

  while(argv[i]!=NULL){
    if(argv[i]!='0' &&
       argv[i]!='1' &&
       argv[i]!='2' &&
       argv[i]!='3' &&
       argv[i]!='4' &&
       argv[i]!='5' &&
       argv[i]!='6' &&
       argv[i]!='7' &&
       argv[i]!='8' &&
       argv[i]!='9') check=true;
       i++;
  }
  return check;
}


int main(int argc, char** argv){

//ERRORS
    if(argc != 3){ // if program doesn't starts truly like ./mastermind 123abc
      cerr << "E0" << endl;
      exit(1);
  }
    if(argv[2][0]=='0'){//checks first digit is 0
      cerr << "E0" << endl;
      exit(1);
  }
    if(checkNotInteger(argv)){//works when like -r a123
      cerr << "E2" << endl;
      exit(1);
    }

//---------------



  srand(time(NULL));
  int secret_number;
  string guessnum;
  string sgv = cnvrtToString(argv,1); //converts to string -r of -u
  int igv = cnvrtToInt(argv,2);       //converts to int number after -r of -u

//ERROR
  if(!checksamedigits(igv)){
    cerr << "E0" << endl;
    exit(1);
  }
  //--------------


if(sgv == "-r"){
//ERROR
if(igv>=10 || igv<=0){
  cerr << "E0" << endl;
  exit(1);
}


  secret_number=0;
  bool check;
  int randnum,count=0;
  int holdrandzero;

  for(int i=0;i<igv;++i){

    if(randnum==0) holdrandzero=0;

      if(holdrandzero==0)randnum = rand() % 9+1;// blocks some 0 problems
      else randnum = rand() % 9;

    if(randnum==0 && i==igv-1){//for first digit will not be 0
        randnum = rand() % 9+1;
      }
    secret_number += us(10,i)*randnum;
    if(!checksamedigits(secret_number)){ // checking same digits and fix
      while(!checksamedigits(secret_number)){
         secret_number -= us(10,i)*randnum;

         if(holdrandzero==0)randnum = rand() % 9+1;// blocks some 0 problems
         else randnum = rand() % 9;

         if(randnum==0 && i==igv-1){//for first digit will not be 0
             randnum = rand() % 9+1;
             i--;
           }
         secret_number += us(10,i)*randnum;
      } // end of while
    }// end of if
  }//end of for
cout << secret_number << endl;
  string ssecret = to_string(secret_number);
  while(count<100){
  cin >> guessnum;
  if(guessnum.size()!=ssecret.size()){//comparing with digits size
    cerr << "E1" << endl;
    exit(1);
  }

  if(checkNotInteger(guessnum)){//check digits that not number
    cerr << "E0" << endl;
    exit(1);
  }

  if(!checksamedigits(stoi(guessnum))){
    cerr << "E0" << endl;
    exit(1);
  }
  if(guessnum==ssecret){
    cout << "FOUND " << count+1 << endl;
    exit(1);
  }
    checkdigits(ssecret,guessnum);
    count++;
  }
  cerr << "FAILED" << endl;
  exit(1);
}


else if(sgv == "-u"){

  if(igv<0){//error for negatives
    cerr << "E0" << endl;
    exit(1);
  }


  int count=0;
  secret_number=igv;
  string ssecret = to_string(secret_number);
  while(count<100){
  cin >> guessnum;

  if(guessnum.size()!=ssecret.size()){//size error
    cerr << "E1" << endl;
    exit(1);
  }

  if(!checksamedigits(stoi(guessnum))){//check same digits with returning string to int
    cerr << "E0" << endl;
    exit(1);
  }
  if(guessnum==ssecret){
    cout << "FOUND " << count+1 << endl;//prints if user find true argument
    exit(1);
  }
    checkdigits(ssecret,guessnum);
    count++;//count for 100 times and fail
}//end of while
  cerr << "FAILED" << endl; // fail after 100 timess
  exit(1);
}

else cerr << "E0" << endl;//error if comment is not -r or -u

return 0;
}
