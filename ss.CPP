
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "ss.h"
using namespace std;

ss::ss(){
	blockhead = NULL;
	current = NULL;
	//here = NULL;
	//availhead = NULL;
	
}


void ss::Split(int blockposition, int zip)//splits the block whose pointer was passed
{
	
	
	current = blockhead;
	
	for(int i = 1; i<blockposition; i++)//set current to the block we are splitting 
	{
		if(i == blockposition)
		{
			break;
		}
		current=current->next;
	}
	
	blockptr NextBLock = new block;
	blockptr temp = current->next;
	NextBLock->prev = current;
	current->next = NextBLock;
	NextBLock->next = temp;
	temp->prev = NextBLock;
	

	
	for(int i = 9; i<blocksize; i++)	// moeves everything from last half of old block to first hald of new block
	{
		for(int x = 0; x< blocksize; x++)
		{
			NextBLock->zip[x] = current->zip[i];
			NextBLock->placename[x] = current->placename[i];
			NextBLock->state[x] = current->state[i];
			NextBLock->county[x] = current->county[i];
			NextBLock->latitude[x] = current->latitude[i];
			NextBLock->longitude[x] = current->longitude[i];
		}
		
		
	}
	for(int i = 9; i<blocksize; i++)	//set last half of block = 0
	{
			NextBLock->zip[i] = 0;
			NextBLock->placename[i] = '0';
			NextBLock->state[i] = '0';
			NextBLock->county[i] = '0';
			NextBLock->latitude[i] = 0;
			NextBLock->longitude[i] = 0;
	}
	for(int i = 9; i<blocksize; i++)	//set last half of current = 0
	{
			current->zip[i] = 0;
			current->placename[i] = '0';
			current->state[i] = '0';
			current->county[i] = '0';
			current->latitude[i] = 0;
			current->longitude[i] = 0;
	}
	//search the block for iinsertion
	if(current->next->zip[0]<zip)
	{
		current=current->next;
	}

}

void ss::Merge(int blockposition)
{
	int prevfilled = 0, nextfilled = 0, ziptemp = 0;
	int tempzip[blocksize];
	string tempplacename[blocksize];
	string tempstate[blocksize];
	string tempcounty[blocksize];
	float templatitude[blocksize];
	float templongitude[blocksize];
	string placenametemp, statetemp, countytemp;
	float latitudetemp, longitudetemp;
	
	//set current to block that we are mergeing 
	for(int i = 1; i<blockposition; i++)
	{
		if(i == blockposition)
		{
			break;//will this cause a problem?
		}
		current=current->next;
	}
	
	//check to see if the previous or the next block has more data
	
	for(int i = 0; i<blocksize; i++)
	{
		//search current->prev for data spots filled 
		if(current->prev->zip[i] != 0)
		{
			prevfilled++;
		}
		//search current->next for data spots filled
		if(current->next->zip[i] != 0)
		{
			nextfilled++;
		}
	}
	
	
	
	
	//need to check to see how much we can take from previous and next nodes.
	//can have it automatically take a few from each		allways needs 1
	
	
	
	if(prevfilled>11)
	{
		//seearch for last item in previous block
		for(int i = 0; i<blocksize; i++)
		{
			if(current->prev->zip[i+1] == 0)
			{
				//take this item 
				ziptemp = current->prev->zip[i];
				placenametemp = current->prev->placename[i];
				countytemp = current->prev->county[i];
				statetemp	= current->prev->state[i];
				latitudetemp = current->prev->latitude[i];
				longitudetemp = current->prev->longitude[i];
				
				//clear the data that was taken
				current->prev->zip[i] = 0;
				current->prev->placename[i] = '0';
				current->prev->county[i] = '0';
				current->prev->state[i] = '0';
				current->prev->latitude[i] = 0;
				current->prev->longitude[i] = 0;
			}
		}
		// place everything into temp arrays
		for(int i = 0; i <blocksize; i++)
		{
			tempzip[i]=current->zip[i];
			tempplacename[i]=current->placename[i];
			tempstate[i]=current->state[i];
			tempcounty[i]=current->county[i];
			templongitude[i]=current->longitude[i];
			templatitude[i]=current->latitude[i];
		}
		
		//place item that was taken into the appropriate position
		for(int i = 0; i < blocksize; i++)
		{
				
				if(i==0)
				{	
					current->zip[i]=ziptemp;
					current->placename[i]=placenametemp;
					current->state[i]=statetemp;
					current-> county[i]=countytemp;
					current->latitude[i]=latitudetemp;
					current->longitude[i]=longitudetemp;
				}
				else 
				{
					current->zip[i]=tempzip[i-1];
					current->placename[i]=tempplacename[i-1];
					current->state[i]=tempstate[i-1];
					current-> county[i]=tempcounty[i-1];
					current->latitude[i]=templatitude[i-1];
					current->longitude[i]=templongitude[i-1];
				}
		}	
	}
	else 
	{
		//seearch for last item in nexxt block

		//take this item 
		ziptemp = current->next->zip[0];
		placenametemp = current->next->placename[0];
		countytemp = current->next->county[0];
		statetemp	= current->next->state[0];
		latitudetemp = current->next->latitude[0];
		longitudetemp = current->next->longitude[0];
		
				//clear the data that was taken
		current->next->zip[0] = 0;
		current->next->placename[0] = '0';
		current->next->county[0] = '0';
		current->next->state[0] = '0';
		current->next->latitude[0] = 0;
		current->next->longitude[0] = 0;
			
		// place everything into temp arrays
		for(int i = 0; i <blocksize; i++)
		{
			tempzip[i]=current->zip[i];
			tempplacename[i]=current->placename[i];
			tempstate[i]=current->state[i];
			tempcounty[i]=current->county[i];
			templongitude[i]=current->longitude[i];
			templatitude[i]=current->latitude[i];
		}
		
		//place item that was taken into the appropriate position
		for(int i = 0; i < blocksize; i++)
		{
				
			if(i==10)
			{	
				current->zip[i]=ziptemp;
				current->placename[i]=placenametemp;
				current->state[i]=statetemp;
				current-> county[i]=countytemp;
				current->latitude[i]=latitudetemp;
				current->longitude[i]=longitudetemp;
			}
			else 
			{
				current->zip[i]=tempzip[i-1];
				current->placename[i]=tempplacename[i-1];
				current->state[i]=tempstate[i-1];
				current-> county[i]=tempcounty[i-1];
				current->latitude[i]=templatitude[i-1];
				current->longitude[i]=templongitude[i-1];
			}
		}
	}
	
	
	
}

void ss::update()
{
	ofstream outss;
	outss.open("ss.txt");
	current=blockhead;   //setting current to the start of the list
	do{
		for(int i = 0; i< blocksize; i++)
		{
			if(current->zip[i]!=0)
			{
				outss<<setw(6)<<current->zip[i]
			   	<<setw(30)<<current->placename[i]
				<<setw(7)<<current->state[i]
				<<setw(35)<<current->county[i]
				<<setw(8)<<current->latitude[i]
				<<setw(9)<<current->longitude[i]<<endl;
			}
				
			
		}
		current=current->next;
	}while(current->next!=NULL);
	outss.close();
}

void ss::insert()
{
	ifstream index;
	index.open("index.txt");
	int datafromindex = 0;
	int zip = 0;
	int tempzip[20];
	string templace[20];
	string tempstate[20];
	string tempcounty[20];
	float templat[20];
	float templong[20];
	string place;	
	string state;	
	string county;
	string temp;
	float lat;
	float lon;
	int blockposition = 0;
	int recordpos = 0;
	current=blockhead;
	blockptr s;
	
	
	
	
	
	
	while(zip<100){
		cout<<"Please enter the zip."<<endl<<"Zip: ";
		cin>>zip;
	};
	cout<<endl;
	cout<<"Please enter the placename."<<endl<<"placename: ";
		cin>>place;
		cout<<endl;
		
	cout<<"Please enter the state."<<endl<<"state: ";
		cin>>state;
		cout<<endl;
	cout<<"Please enter the county."<<endl<<"county: ";
		cin>>county;
		cout<<endl;
	cout<<"Please enter the latitude."<<endl<<"latitude: ";
		cin>>lat;
		cout<<endl;
	cout<<"Please enter the longitude."<<endl<<"longitude: ";
		cin>>lon;
		cout<<endl;

	
		
	//search for the block to insert	
	
	while(datafromindex<zip){
		
		if(datafromindex<zip)
		{
			getline(index,temp);		
			stringstream data(temp); 
			data>>datafromindex;
			blockposition++;
		}
		else if(datafromindex>zip)
		{
			blockposition--;
			break;
		}
	}
	blockposition--;
	blockposition--;
	
	//advance the current pointer to the block that we searched the index for
	

	//search the block zip field for insertion position

		int j = 0;
		while(current->zip[j]<=zip && j<blocksize)		//if we find the searched zip
		{
			recordpos=j;
			j++;
		}
		recordpos++;
	bool full = false;
	for(int i=0;i<blocksize;i++)
	{
		if(current->zip[i]==0)
		{
			full = false;
			break;
		}
		else
		{
			full=true;
			
		}
	}
	
	
	//full if full     half if half
	
	if(full == true)
	{
		Split(blockposition, zip);
		
	}
	
	//search spot to insert 
	int recrodposition;
	for(int x = 0; x<zip; x++)
	{
		if(current->zip[x]>zip)
		{
			recrodposition = x;
			break;
		}
		
	}
	
			for(int i =0; i<blocksize ;i++)
			{
				tempzip[i]=current->zip[i];
				templace[i]=current->placename[i];
				tempstate[i]=current->state[i];
				tempcounty[i]=current->county[i];
				templat[i]=current->latitude[i];
				templong[i]=current->longitude[i];
			}		
			for(int m = 0; m<blocksize ;m++)
			{
				
				if(current->zip[m]<zip)
				{
					
					current->zip[m]=tempzip[m];
					current->placename[m]=templace[m];
					current->state[m]=tempstate[m];
					current->county[m]=tempcounty[m];
					current->latitude[m]=templat[m];
					current->longitude[m]=templong[m];
				}
				if(current->zip[m]>zip&&m!=recordpos)
				{	
					current->zip[m]=tempzip[m-1];
					current->placename[m]=templace[m];
					current->state[m]=tempstate[m];
					current->county[m]=tempcounty[m];
					current->latitude[m]=templat[m];
					current->longitude[m]=templong[m];
					
					
				}
				else if(m==recordpos)
				{	
					current->zip[m]=zip;
					current->placename[m]=place;
					current->state[m]=state;
					current-> county[m]=county;
					current->latitude[m]=lat;
					current->longitude[m]=lon;
				}
			
			
	index.close();
}
}
void ss::del()
{
	bool found = false;
	int size = 0;
	int zip;
	cout<<"Please enter the zip of the record you would like to delete!"<<endl<<"Zip: ";
	cin>>zip;
	cout<<"Deleteing record with zip: "<<zip<<endl;;
	current = blockhead;
	int k = 0;
	
	
	int blockpos;
	
	while(current->next != NULL )
	{
		if(current->zip[k]!=zip)
		{
			if(k==blocksize)
			{
				current=current->next;
				blockpos++;	
				k=0;
			}
			else
				k++;
			
		}
		else if(current->zip[k]==zip)
		{
			current->zip[k]=0;
			current->placename[k]="";
			current->state[k]="";
			current->county[k]="";
			current->latitude[k]=0;
			current->longitude[k]=0;
			
			cout<<"deleted!"<<endl;
			break;
		}
		else
		{
			cout<<"The record you are looking for does not exist!"<<endl;
		}
		
	}
	
	int halfcount = 0;
	for(int i = 0; i<blocksize; i++)
	{
		if(current->zip[i]!=0)
		{
			halfcount++;
		}
	}
	if (halfcount<10)
	{
		Merge(blockpos);
	}
	
	
	//add in condtion for merge
	
}

bool ss::is_empty()
{
	if(blockhead == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ss::display_ss()
{
	ifstream infile;
	infile.open("SequenceSet.txt");
	bool end = false;
	string infilestring;
	cout<<endl<<"-----------------------------------------------------------------------------------------------"<<endl<<endl;

	while(end!=true)
	{
		
		getline(infile, infilestring);
		if(infilestring == "~")
		{
			cout<<endl<<"-----------------------------------------------------------------------------------------------"<<endl<<endl;

		}
		else
		{
			cout<<infilestring<<endl;
		}
		
		if(infile.eof())
		{
			end = true;
			break;
		}
		
		
		
		
		
	}
	
	infile.close();
}

void ss::displayfield()
{
	ifstream index;	//name of file to open
	index.open("index.txt");			//open the index file
	int recordpos = 0;				//holds positiong in array if record
	int zipsearch = 0;				//user entered zip to search
	string temp ;					//string holdiing line from index
	int blockposition = -2;			//postion of block
	int datafromindex = 0; 			//index of block
	current=blockhead;				//sets current pointer to the head of block list
	int fieldchoice=0;				//the field choice from the user
	
	cout<<"-----------------------------------------------------"<<endl;
	cout<<"Enter the zip of the record you would like displayed!"<<endl;
	cout<<"Zip to search: ";
	cin>>zipsearch;
	cout<<endl;
	
	
	while(datafromindex<=zipsearch&& !index.eof())
	{
		getline(index,temp);
		stringstream data(temp); 
		data>>datafromindex;		
		blockposition++;
	}
	
	
	//advance the current pointer to the block that we searched the index for
	for(int i = 0; i<blockposition;i++)
	{
		current=current->next;
	}
	if(current->next->next==NULL)
	{
		current= current->next;
	}
	/*Searched the given blocks zip array for the zip if not found let the user know it does not exist */
	
	for(int i = 0; i<blocksize; i++)
	{
		if(current->zip[i]==zipsearch)		//if we find the searched zip
		{
			recordpos=i;
		}
	}
	
	if(current->zip[recordpos] != 0 &&current->zip[recordpos] == zipsearch )
	{
		cout<<"What field would you like displayed?"<<endl;
		cout<<"-----------------------------------------------------"<<endl;
		cout<<"(1)"<<setw(8)<<"Zip"<<endl;
		cout<<"(2)"<<setw(15)<<"Place Name"<<endl;
		cout<<"(3)"<<setw(11)<<"State "<<endl;
		cout<<"(4)"<<setw(12)<<"County "<<endl;
		cout<<"(5)"<<setw(14)<<"Latitude "<<endl;
		cout<<"(6)"<<setw(15)<<"Longitude "<<endl;
		cout<<"(7)"<<setw(27)<<"Zip, Placename, State "<<endl;
		cout<<"(8)"<<setw(11)<<"Block "<<endl;
		cout<<"-----------------------------------------------------"<<endl;
		cout<<"Choice: ";
		cin>>fieldchoice;
		cout<<endl;
		if(fieldchoice==1)
		{
			cout<<"Zip: "<<setw(5)<<current->zip[recordpos]<<endl;
		}
		else if(fieldchoice==2)
		{
			cout<<"Placename: "<<current->placename[recordpos]<<endl;
		}
		else if(fieldchoice==3)
		{
			cout<<"State: "<<current->state[recordpos]<<endl;
		}
		else if(fieldchoice==4)
		{
			cout<<"County: "<<current->county[recordpos]<<endl;
		}
		else if(fieldchoice==5)
		{
			cout<<"Latitude: "<<current->latitude[recordpos]<<endl;
		}
		else if(fieldchoice==6)
		{
			cout<<"Longitude: "<<current->longitude[recordpos]<<endl;
		}
		else if(fieldchoice==7)
		{
			cout<<"Zip:"<<current->zip[recordpos]<<endl<<"Placename: "<<current->placename[recordpos]<<endl<<"State: "<<current->state[recordpos]<<endl;
		}
		else
		{
			int width = 20;
			
			for(int i = 0; i<blocksize; i++)
			{
				if(current->zip[i]!=0)
				{
					cout<<setw(6)<<current->zip[i]
					<<setw(20)<<current->placename[i]
					<<setw(3)<<current->state[i]
					<<setw(17)<<current->county[i]
					<<setw(10)<<current->latitude[i]
					<<setw(11)<<current->longitude[i]<<endl;
				}
				
			}
		}
	}
	else
	{
		cout<<"The record you are looking for does not exist!"<<endl;
	}
	
	
	index.close();
}

void ss::displayrecord()
{
	ifstream index;
	index.open("index.txt");			//open the index file
	int recordpos = 0;				//holds positiong in array if record
	int zipsearch = 0;				//user entered zip to search
	string temp ;				//string holdiing line from index
	int blockposition = -2;			//postion of block
	int datafromindex = 0; 			//index of block
	current=blockhead;				//sets current pointer to the head of block list
	
	cout<<"Enter the zip of the record you would like displayed!"<<endl;
	cin>>zipsearch;
	
	/*Reads the index file and increments the blockpos int when we read in a new line.
	We read a new line when the string from the index file is larger than the user enetered value*/
	
	while(datafromindex<=zipsearch&& !index.eof())
	{
		getline(index,temp);
		stringstream data(temp); 
		data>>datafromindex;	
		blockposition++;
	}
	
	
	//advance the current pointer to the block that we searched the index for
	for(int i = 0; i<blockposition;i++)
	{
		current=current->next;
	}
	if(current->next->next==NULL)
	{
		current= current->next;
	}
	/*Searched the given blocks zip array for the zip if not found let the user know it does not exist */
	
	for(int i = 0; i<blocksize; i++)
	{
		if(current->zip[i]==zipsearch)		//if we find the searched zip
		{
			recordpos=i;
		}
	}
	/*Returnes the record that the user has requested*/
	if(current->zip[recordpos] != 0 &&current->zip[recordpos] == zipsearch )
	{
		cout<<current->zip[recordpos]<<" "
		<<current->placename[recordpos]<<" "
		<<current->state[recordpos]<<" "
		<<current->county[recordpos]<<" "
		<<current->latitude[recordpos]<<" "
		<<current->longitude[recordpos]<<endl;
	}
	else
	{
		cout<<"The record you are looking for does not exist!"<<endl;
	}

	index.close();			//close file1
	
}

void ss::createindex()
{
	
	ofstream outindex;
	outindex.open("index.txt");
	current=blockhead;   //setting current to the start of the list
	do{
		
		outindex<<current->zip[0]<<endl;
		current=current->next;
	}while(current->next!=NULL);
	outindex.close();
}

void ss::createSS()
{
	ss s;
	ifstream file;
	ofstream outfile;
	outfile.open("SequenceSet.txt");
	string line;
	file.open("ss.txt");
	bool end = false;
		
	blockptr temp= new block;	
	
	blockhead=temp;
	blockhead->next=NULL;
	blockhead->prev=NULL;
	temp=NULL;
	current=blockhead;	
	
	while(end != true)//create a new block and read in data
	{	
		for(int k = 0; k <= blocksize;k++)
		{
			if(k<=blocksize-6)
			{	//load first part of bloack into file
				getline(file,line);
				outfile <<line<<endl;	
				
			}	
			else if(k == blocksize-1)
			{
				outfile<<"~"<<endl;
		
			}
		}
		if(file.eof())
		{
			end = true;
		}
		
	}

	
	
	outfile.close();
	file.close();
}

void ss::load(int blockposition)
{
	ss s;
	ifstream file;
	file.open("SequenceSet.txt");
	string line;
	
		
	blockptr temp= new block;	
	
	blockhead=temp;
	blockhead->next=NULL;
	blockhead->prev=NULL;
	temp=NULL;
	current=blockhead;	
	
	for(int i = 0; i<=5; i++)//create a new block and read in data
	{
		if(i>0)
		{
			temp = new block;
			temp->prev=current;
			current->next=temp;
			current=temp;
			current->next=NULL;
		}
		
	
		for(int j = 0; j<blocksize; j++)
		{
			if(j<=blocksize-6)
			{
			getline(file,line);	
			buffer(line,current,j);
			}
			else
			{
				addzip(0,j,current);
				addplace("",j,current);
				addstate("",j,current);
				addcounty("",j,current);
				addlat(0,j,current);
				addlong(0,j,current);
			}
			

		}
		
	}
	
}


void ss::buffer(string itext, blockptr thisone,int spot){
	
	int 	size=94,
			zip=0,
	/*There are some zips that are two short and require different 
	runs. So we can keep track of how long the zip is and calculate it
	at the end. The zip will never be longer than 5.*/
			zipcount=0,	
	/*for latitude and longitude, we aren't sure how many 
	values are before the decimal. So we will keep track of 
	the index values with these. There are a few bool values
	to keep track of if it is negative or if we hit the decimal.*/
			placeLat=0,		//Values before decimal.
			placeLon=0;		
	string 	city="",
			state="",
			county="";
	char 	buffer[size];
	float	latitude=0,
			longitude=0;
	bool	lat= false,		//Is it negative?
			latdec=false,	//Have we "hit" the decimal?
			lon= false,
			londec=false;

	
		for(int i=0; i< itext.size(); i++){
			buffer[i]=itext[i];
			
			/*Zip, 0-5 of buffer. Sometimes 0-4. This will count the number of 
			digits for a zip. We gauge this by checking if the current character
			is a number or not.*/
			if(i<=6&&buffer[i]-'0'<10&&buffer[i]-'0'>=0)
				zipcount++;
			//City,5-36 of buffer. Add the character to the string.
			else if(i<37){
				if(buffer[i]!=' ')
					city+=buffer[i];
			}
			//State, 37,38 of buffer. Add the character to the string.
			else if(i<39){
				if(buffer[i]!=' ')
					state+=buffer[i];
			}
			//County, 39-75 of buffer. Add the character to the string.
			else if(i<76){
				if(buffer[i]!=' ')
					county+=buffer[i];
			}
			//Latitude, 76-85 of buffer.
			else if(i<86){
				int temp=0;
				if(buffer[i]=='-')	//Is it negative?
					lat=true;
				if(buffer[i]=='.')	//Did we find the decimal?
					latdec=true;
				if(i==85){			//Lastly, we calculate the latitude.
					for(int x=0;x<placeLat;x++){
						/*Subtract one because placeLat increases for the decimal.
						pow() determines which digit the number belongs in number*(10^x).*/
						if(buffer[x+76]!=' '&&buffer[x+76]!='-')
							temp+=(buffer[x+76]-'0')*pow(10,placeLat-1-x);
					}
					latitude+=temp;
				}
				if(buffer[i]!=' '&&buffer[i]!='.'&&latdec==true&&buffer[i]!='-')
					latitude+=(buffer[i]-'0')*pow(10,-(i-(placeLat+76)));
				if(latdec==false)
					placeLat++;
			}
			//Longitude, 86-93 of buffer, same as latitude algorithm, but with longitude.
			else{
				int temp=0;
				if(buffer[i]=='-')	//Is it negative?
					lon=true;
				if(buffer[i]=='.')	//Did we find the decimal?
					londec=true;
				if(i==93){			//Lastly, we calculate the longitude
					for(int x=0;x<placeLon;x++){
						/*subtract one because placeLon increases for the decimal.
						pow() determines which digit the number belongs in number*(10^x).*/
						if(buffer[x+86]!=' '&&buffer[x+86]!='-')							
							temp+=(buffer[x+86]-'0')*pow(10,placeLon-1-x);
					}
					longitude+=temp;					
				}
				//Same as previous pow(), but for after the decimal.
				if(buffer[i]!=' '&&buffer[i]!='.'&&londec==true&&buffer[i]!='-')
					longitude+=(buffer[i]-'0')*pow(10,-(i-(placeLon+86)));
				if(londec==false)
					placeLon++;
			}
		}
		
		int index = 0;
		while(zipcount>0)
		{
  			 if(buffer[index]!=' '){
   				 int temp=buffer[index]-'0';
   				 zip+=temp*pow(10,zipcount-1);
  				  zipcount--;
  				 }
   			index++;
 		 }
		if(lon==true)
			longitude=0-longitude;
		if(lat==true)
			latitude=0-latitude;
		addzip(zip,spot,thisone);            //adds zip
        addplace(city,spot,thisone);    //adds placename
        addstate(state,spot,thisone);        //adds state
        addcounty(county,spot,thisone);        //adds county
        addlong(longitude,spot,thisone);        //adds longitude
        addlat(latitude,spot,thisone);        //adds latitude*/
        
		zip=0;
		zipcount=0;
		city="";
		state="";
		county="";
		latitude=0;
		longitude=0;
		placeLat=0;
		placeLon=0;
		latdec=false;
		londec=false;
	}

void ss::addzip(int z, int pos, blockptr po){
	po->zip[pos]=z;
	
}

void ss::addplace(string p, int pos, blockptr po){
	po->placename[pos]=p;
}

void ss::addstate(string s, int pos, blockptr po){
	po->state[pos]=s;
}

void ss::addcounty(string c, int pos, blockptr po){
	po->county[pos]=c;
}

void ss::addlat(float lat, int pos, blockptr po){
	po->latitude[pos]=lat;
}

void ss::addlong(float lon, int pos, blockptr po){
	po->longitude[pos]=lon;
}
