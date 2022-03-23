#ifndef CATALOG_H
#define CATALOG_H

using namespace std;
const char denden = '\"';

class Catalog
{

  struct information
  {
    string title;
    string authors;
    string artists;
    string director;
    string year;
    string tags;
    string genre;
    string starring;
  };

	public:
		void SetCatalogRead(string CR) {catalogread = CR;}
		string GetCatalogRead(){return catalogread;}

		void SetSTRNG(string str) {STRNG = str;}
		string GetSTRNG(){return STRNG;}
		void SetFIELD(string fld) {FIELD = fld;}
		string GetFIELD(){return FIELD;}

    int GetUnique(){return unique_count;}
    void SetUnique(int unique){unique_count = unique;}

		int CheckDuplicateEntry(Catalog& OBJ);



	vector<information> INFO;
	vector<string> TEXT;
  vector<string> redZone;

  protected:
		string catalogread;
		string STRNG,FIELD;
    int unique_count;

};

void readData(string filename,Catalog& myOBJ);
void readComm(string filename,Catalog& myOBJ);
bool dendenCount(int dd,Catalog OBJ);
void writeOutput(string output_filename,Catalog myOBJ);

#endif

