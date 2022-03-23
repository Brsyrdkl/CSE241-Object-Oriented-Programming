#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "HW1library.h"

const char Player[2] = {'X','O'};

char board_array[13][13]=		{{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'},
								{'.','.','.','.','.','.','.','.','.','.','.','.','.'}};


int asksize(){//To determine what should be the board size.(6x6-12x12)

	int board_size;

	cout <<"What should be the board size?(you should enter integer!)" << endl;
	cin >> board_size;

		if(board_size < 6 || board_size > 12){
			cerr << "!!Invalid Board Size!!" << endl;//Error for different board size
			asksize();
		}
		else{
			return board_size;
		}
}

int askhowtoplay(){

	int choice;

	cout << "Select how you want to play:\n"
		 << "1.Two Player Game\n"
		 << "2.User Vs. Computer Game" << endl;
	cin  >> choice;

	if(choice==1) return 1;
	if(choice==2) return 2;
	if(choice!=1 && choice!=2){
		cerr << "!Please choose one of them!" << endl;
		askhowtoplay();
	}
	return 0;
}



void displayboard(int board_size){

	string letter = "abcdefghijkl";
	string numbers = "123456789";
	string space = " ";


	for(int i=1;i<board_size+1;++i){
				cout << space << letter[i-1];
			}
	cout << endl;

	for(int i=0;i<board_size;++i){

		if(i>8){
			cout << i+1;
			for(int s=1;s<i+1;++s)
				cout << space;
		}
		else{
			cout << numbers[i];
			for(int s=0;s<i+1;++s)
				cout << space;
		}

		for(int j=0;j<board_size;++j)
			cout << board_array[i][j] << " ";

			cout << endl;

	}
}



int askmoveandplay(int oyuncusirasi,int board_size){

	string letter = "ABCDEFGHIJKL";
	int number,keep=-1;
	char character;
	int sira = oyuncusirasi % 2;
	int dotnum=0;

	//winnercontrol_X(board_array,board_size); //this 2 functions are checking who is winner but its now working well
	//winnercontrol_O(board_array,board_size);

	cout << "Please Make a Move(e.g. C5):";
	cin >> character >> number;
	cin.clear();
	cin.ignore(100,'\n');

	for(int i=0;i<12;i++){
		if(character==letter[i]) keep = i;
	}
	if(keep==-1) oyuncusirasi--;//if user enters wrong letter function turns again

	for(int k=0;k<board_size;k++){									//|	Checking
					for(int j=0;j<board_size;j++){				    //|	The
						if(board_array[k][j]=='.') dotnum++;		//|	Fullness
					}												//|	Of
				}													//|	The
																	//|	Board
				if(dotnum==0){										//|
					cout << "Table is full and game over" << endl;	//|
					return 0;										//|
				}




	if(board_array[number-1][keep]==Player[0] || board_array[number-1][keep]==Player[1]){
		cerr << "\nThere is already " << board_array[number-1][keep] << " here\n" << endl;
		displayboard(board_size);
		//scanning_array(board_array,board_size);
		askmoveandplay(oyuncusirasi,board_size);

	}
	else{
		board_array[number-1][keep]=Player[sira];
		displayboard(board_size);
		//scanning_array(board_array,board_size);
		askmoveandplay(oyuncusirasi+1,board_size);

	}

}


int playwithcomp(int oyuncusirasi,int board_size){

		string letter = "ABCDEFGHIJKL";
		int number,keep=-1;
		char character;
		int dotnum=0;
		srand (time(NULL));
		int random1 = rand() % board_size; // in range 0 to boardsize
		int random2 = rand() % board_size;
		//winnercontrol_X(board_array,board_size); //this 2 functions are checking who is winner but its now working well
		//winnercontrol_O(board_array,board_size);

		cout << "Please Make a Move(e.g. C5):";
		cin >> character >> number;
		cin.clear();
		cin.ignore(100,'\n');

		for(int i=0;i<12;i++){
			if(character==letter[i]) keep = i;
		}
		if(keep==-1) oyuncusirasi--;

		for(int k=0;k<board_size;k++){									//|	Checking
						for(int j=0;j<board_size;j++){				    //|	The
							if(board_array[k][j]=='.') dotnum++;		//|	Fullness
						}												//|	Of
					}													//|	The
																		//|	Board
					if(dotnum==0){										//|
						cout << "Table is full and game over" << endl;	//|
						return 0;										//|
					}




		if(board_array[number-1][keep]==Player[0] || board_array[number-1][keep]==Player[1]){ //checking if there is X or O in that box.
			cerr << "\nThere is already " << board_array[number-1][keep] << " here\n" << endl;
			displayboard(board_size);
				//scanning_array(board_array,board_size);
			playwithcomp(oyuncusirasi,board_size);

		}
		else{
			board_array[number-1][keep]=Player[0];

			while(board_array[random1][random2]!='.'){//computer plays here
				random1 = rand() % board_size;
				random2 = rand() % board_size;
			}
			board_array[random1][random2]=Player[1];

			displayboard(board_size);
				//scanning_array(board_array,board_size);
			playwithcomp(oyuncusirasi+2,board_size);

		}

}


int winnercontrol_X(char board[][13],int size){//something wrong

	int i=0,a=0;

	for(;i<size;i++){
		if(board[i][a]=='X'){
			if(board[i-1][a+1]=='X' || board[i][a+1]=='X' || board[i+1][a+1]=='X'){
				a++;
				i=0;
			}

		}
	}
	if(a==size){
		cout << "!Congratulations! Winner is X player" << endl;
		return 0;
	}
return 0;
}


int winnercontrol_O(char board[][13],int size){///something wrong
	int i=0,a=size;

		for(;a>0;a--){
			if(board[i][a]=='O'){
				if(board[i+1][a-1]='O' || board[i+1][a]=='O' || board[i+1][a+1]=='O'){
					a=size;
					i++;
				}
			}
		}
		if(i==size){
			cout << "!Congratulations! Winner is O player" << endl;
			return 0;
		}

return 0;
}

/*int scanning_array(char board[][13],int size){ // I tried to use scan for 0001 error but
												 // i can't find solution
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(board_array[i][j]!='X' && board_array[i][j]!='O' && board_array[i][j]!='.'){
				board_array[i][j]='.'; }
		}
	}

}*/


