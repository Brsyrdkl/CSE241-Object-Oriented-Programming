
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "HW1library.h"

int main() {
	int oyuncusirasi=0;
	int x=asksize();
	int y=askhowtoplay();

		if(y==1){
			cout << "Playing Two Player Game" << endl;
				displayboard(x);
				askmoveandplay(oyuncusirasi,x);
	}
		if(y==2){
			cout << "Playing User Vs. Computer Game" << endl;
				displayboard(x);
				playwithcomp(oyuncusirasi,x);
	}
	return 0;
}






