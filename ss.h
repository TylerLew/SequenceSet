#ifndef ss_h
#define ss_h
#include <iostream>
#include <string>
using namespace std;
class ss{
	private:
		static const int blocksize = 50;
		struct block
		{
			block* next;
			block* prev;
			int zip[blocksize];
			string placename[blocksize];
			string state[blocksize];
			string county[blocksize];
			float latitude[blocksize];
			float longitude[blocksize];
		}typedef *blockptr;
		blockptr blockhead;
		blockptr current;
	
	public:
	ss();
	void Split(int blockposition, int zip);
	void Merge(int blockposition);
	void update();
	void verfify();
	void createindex();
	void displayfield();
	void displayrecord();
	void display_ss();
	bool is_empty();
	void insert();	//find the area for insertion and add
	void del(); // search for record and set the arrays in that location to 0
	void createSS();
	void load(int blockposition);
	void buffer(string, blockptr, int);
	void addzip(int, int, blockptr);
	void addplace(string, int, blockptr);
	void addstate(string , int, blockptr);
	void addcounty(string, int, blockptr);
	void addlat(float, int, blockptr);
	void addlong(float, int, blockptr);
		
};

#endif
