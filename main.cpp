#include <iostream>
#include <string>
#include "ss.cpp"
using namespace std;

void menu(){
	cout<<"----------------Sequence Set Generator---------------"<<endl<<endl;
	cout<<"-----------------------------------------------------"<<endl;
	cout<<"d: Delete Record." << endl;
	cout<<"i: Insert Record." << endl;
	cout<<"s: Displays Sequence Set." << endl;
	cout<<"r: Displays record." << endl;
	cout<<"f: Displays fields." << endl;
	cout<<"m: Menu." << endl;
	cout<<"x: Exit" << endl;
	
}

int main()
{
	ss s;
	char choice =' ';
	
	s.createSS();
	s.load(0);
	menu();
	while(choice!='x'){
		cout<<"-----------------------------------------------------"<<endl;
		cout<<"Enter Choice"<<endl;
		cin >> choice;
		switch(choice){
			case 'd':	s.del(),
						s.createindex();
						s.update();
						break;
			case 'm':	menu();
						break;
			case 'r': 	s.displayrecord();
						break;
			case 'f': 	s.displayfield();
						break;
			case 's': 	s.display_ss();
						break;
			case 'i': 	s.insert(),
						s.createindex();
						s.update();
						break;
			case 'x': 	cout << "Exiting" << endl;
						exit;
		}
	}
	cout<<"-----------------------------------------------------"<<endl<<endl;
	
}
