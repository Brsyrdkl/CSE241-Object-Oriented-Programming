#ifndef HW1library
#define HW1library
using namespace std;

int asksize();
int askhowtoplay();
void displayboard(int board_size);
int askmoveandplay(int oyuncusirasi,int board_size);
int playwithcomp(int oyuncusirasi,int board_size);
int winnercontrol_X(char board[][13],int size);
int winnercontrol_O(char board[][13],int size);
//int scanning_array(char board[][13],int size);


#endif
