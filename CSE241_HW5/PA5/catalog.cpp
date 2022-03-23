#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

#include "catalog.h"

using namespace std;

void readData(const string file_name,Catalog& myOBJ)
{
	int i=0;
	string line;
	string stemp;
	size_t pos;


	ifstream File("data.txt");


	    if(File.is_open())
    	{
			getline(File,line);
				 if(line == "book")  myOBJ.SetCatalogRead("book");
			else if(line == "music") myOBJ.SetCatalogRead("music");
			else if(line == "movie") myOBJ.SetCatalogRead("movie");
			else exit(0);
      //cout << "Catalog Read : " << myOBJ.GetCatalogRead() << endl;


	while(getline(File,line))
	{
		pos = line.find(denden);
		line = line.substr(pos+1);
		pos = line.find(denden);
		stemp =	line.substr(0,pos);
  //  cout << "1.stemp : " << stemp << endl;
    myOBJ.INFO.resize(sizeof(myOBJ.TEXT));
    myOBJ.INFO[i].title = stemp;

		line = line.substr(pos+2);

		pos = line.find(denden);
		line = line.substr(pos+1);
		pos = line.find(denden);
		stemp =	line.substr(0,pos);
    //cout << "2.stemp : " << stemp << endl;

		if(myOBJ.GetCatalogRead() == "book") myOBJ.INFO[i].authors = stemp;
		if(myOBJ.GetCatalogRead() == "music") myOBJ.INFO[i].artists = stemp;
		if(myOBJ.GetCatalogRead() == "movie") myOBJ.INFO[i].director = stemp;

		line = line.substr(pos+2);

		pos = line.find(denden);
		line = line.substr(pos+1);
		pos = line.find(denden);
		stemp =	line.substr(0,pos);
    //cout << "3.stemp : " << stemp << endl;

		myOBJ.INFO[i].year = stemp;

		line = line.substr(pos+2);

		pos = line.find(denden);
		line = line.substr(pos+1);
		pos = line.find(denden);
		stemp =	line.substr(0,pos);
    //cout << "4.stemp : " << stemp << endl;
		if(myOBJ.GetCatalogRead() == "book") myOBJ.INFO[i].tags = stemp;
	  if(myOBJ.GetCatalogRead() == "music") myOBJ.INFO[i].genre = stemp;
		if(myOBJ.GetCatalogRead() == "movie"){
      myOBJ.INFO[i].genre = stemp;
      if(dendenCount(10,myOBJ)){
	     line = line.substr(pos+2);

			pos = line.find(denden);
			line = line.substr(pos+1);
			pos = line.find(denden);
			stemp =	line.substr(0,pos);
      //cout << "5.stemp : " << stemp << endl;
      myOBJ.INFO[i].starring = stemp;
    }

		}
	i++;
	}
File.close();
File.open("data.txt");

	getline(File,line);

	while(getline(File,line))
	{
		myOBJ.TEXT.push_back(line);

	}
/*  for(int i=0;i< myOBJ.TEXT.size() ;i++)
  {
      cout << myOBJ.TEXT[i] << endl;
  }
cout << endl;*/
		}

		else cout << "Data file not opened" << endl;

File.close();

}


void readComm(const string file_name,Catalog& myOBJ)
{


	ifstream File("command.txt");


	    if(File.is_open())
    	{
			list<string> myList;
      list<string>::iterator itr;
      vector<string> TEMP_V;
			size_t pos=-1,tpos;
			string temp,totemp;
			string command;
			int i = 0,redcount=0,redcount2=0;

			while(getline(File,temp))
			{
				myList.push_back(temp);
			}

      itr = myList.begin();
      ;
			while(itr != myList.end())
			{
			//--------------------------------------------------------------
				temp = *itr;

        fstream oFile;
        oFile.open("output.txt",ios::out | ios::app);
        oFile << temp << endl;
        oFile.close();

				pos = temp.find("search");
				if(pos == -1)
				{
        pos = temp.find("sort");
				command = "sort";
				temp = temp.substr(pos+4);
				pos = temp.find(denden);
				temp = temp.substr(pos+1);
				pos = temp.find(denden);
				myOBJ.SetFIELD(temp.substr(0,pos));
				}
				else{
				command = "search";
				temp = temp.substr(pos+6);
				pos = temp.find(denden);
				temp = temp.substr(pos+1);
				pos = temp.find(denden);
				tpos = pos;
				myOBJ.SetSTRNG(temp.substr(0,pos));
        temp = temp.substr(pos+1);
				pos = temp.find("in");
				if(tpos==pos) cerr << "there is no 'in' " << endl;
				pos = temp.find(denden);
        //cout << "pos : " << pos << endl;
				temp = temp.substr(pos+1);
				pos = temp.find(denden);
				myOBJ.SetFIELD(temp.substr(0,pos));
				}
        //cout << "command : " << command << endl;
      //cout << "getstrng : " << myOBJ.GetSTRNG() << endl;
        //cout << "getfield : " << myOBJ.GetFIEAlanLD() << endl;
			//---------------------------------------------------------------
			if(command == "search")
			{
				if(myOBJ.GetFIELD() == "title")
				{
					for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					{
						if(myOBJ.INFO[i].title.find(myOBJ.GetSTRNG()) != string::npos)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              for(int j=0;j<myOBJ.redZone.size();j++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[j])
                  {
                      redcount++;
                  }
              }
              if(redcount == 0) oFile << myOBJ.TEXT[i] << endl;
              redcount=0;
              oFile.close();
            }

					}
				}
				if(myOBJ.GetFIELD() == "authors")
				{
					for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					{
						if(myOBJ.INFO[i].authors.find(myOBJ.GetSTRNG()) != string::npos)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              for(int j=0;j<myOBJ.redZone.size();j++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[j])
                  {
                      redcount++;
                  }
              }
              if(redcount == 0) oFile << myOBJ.TEXT[i] << endl;
              redcount=0;
              oFile.close();
            }
					}
				}
				if(myOBJ.GetFIELD() == "artists")
				{
					for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					{
						if(myOBJ.INFO[i].artists.find(myOBJ.GetSTRNG()) != string::npos)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              for(int j=0;j<myOBJ.redZone.size();j++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[j])
                  {
                      redcount++;
                  }
              }
              if(redcount == 0) oFile << myOBJ.TEXT[i] << endl;
              redcount=0;
              oFile.close();
            }
					}
				}
				if(myOBJ.GetFIELD() == "director")
				{
					for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					{
						if(myOBJ.INFO[i].director.find(myOBJ.GetSTRNG()) != string::npos)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              for(int j=0;j<myOBJ.redZone.size();j++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[j])
                  {
                      redcount++;
                  }
              }
              if(redcount == 0) oFile << myOBJ.TEXT[i] << endl;
              redcount=0;
              oFile.close();
            }
					}
				}
				if(myOBJ.GetFIELD() == "year")
				{
					for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					{
						if(myOBJ.INFO[i].year.find(myOBJ.GetSTRNG()) != string::npos)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              for(int j=0;j<myOBJ.redZone.size();j++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[j])
                  {
                      redcount++;
                  }
              }
              if(redcount == 0) oFile << myOBJ.TEXT[i] << endl;
              redcount=0;
              oFile.close();
            }
					}
				}
				if(myOBJ.GetFIELD() == "tags")
				{
					for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					{
						if(myOBJ.INFO[i].tags.find(myOBJ.GetSTRNG()) != string::npos)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              for(int j=0;j<myOBJ.redZone.size();j++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[j])
                  {
                      redcount++;
                  }
              }
              if(redcount == 0) oFile << myOBJ.TEXT[i] << endl;
              redcount=0;
              oFile.close();
            }
					}
				}
				if(myOBJ.GetFIELD() == "genre")
				{
					for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					{
						if(myOBJ.INFO[i].genre.find(myOBJ.GetSTRNG()) != string::npos)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              for(int j=0;j<myOBJ.redZone.size();j++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[j])
                  {
                      redcount++;
                  }
              }
              if(redcount == 0) oFile << myOBJ.TEXT[i] << endl;
              redcount=0;
              oFile.close();
            }
					}
				}
				if(myOBJ.GetFIELD() == "starring")
				{
					for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					{
						if(myOBJ.INFO[i].starring.find(myOBJ.GetSTRNG()) != string::npos)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              for(int j=0;j<myOBJ.redZone.size();j++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[j])
                  {
                      redcount++;
                  }
              }
              if(redcount == 0) oFile << myOBJ.TEXT[i] << endl;
              redcount=0;
              oFile.close();
            }
					}
				}
			}
    //  ---------------------------------------------------------------------------
			if(command == "sort")
			{
        if(myOBJ.GetFIELD() == "title")
        {
          fstream oFile;
          oFile.open("output.txt",ios::out | ios::app);
              for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
					          {
                      TEMP_V.push_back(myOBJ.INFO[i].title);
                    }
                      sort(TEMP_V.begin(),TEMP_V.end());

          for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
          {
            for(int j = 0 ; j < myOBJ.TEXT.size() ; j++)
            {
              if(myOBJ.INFO[i].title.find(TEMP_V[j]) != string::npos && TEMP_V[j] != "")
              {
                for(int k=0 ; k < myOBJ.redZone.size();k++)
                {
                    if(myOBJ.TEXT[i] == myOBJ.redZone[k])
                    {
                        redcount2++;
                    }

                }
                if(redcount2 == 0) oFile << myOBJ.TEXT[i] << endl;
                else redcount2 = 0;
              }
            }
          }

        oFile.close();
        }
        if(myOBJ.GetFIELD() == "authors")
        {
          fstream oFile;
          oFile.open("output.txt",ios::out | ios::app);
              for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
                    {
                      TEMP_V.push_back(myOBJ.INFO[i].authors);
                    }
                      sort(TEMP_V.begin(),TEMP_V.end());

          for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
          {
            for(int j = 0 ; j < myOBJ.TEXT.size() ; j++)
            {
              if(myOBJ.INFO[i].authors.find(TEMP_V[j]) != string::npos && TEMP_V[j] != "")
              {
                for(int k=0 ; k < myOBJ.redZone.size();k++)
                {
                    if(myOBJ.TEXT[i] == myOBJ.redZone[k])
                    {
                        redcount2++;
                    }

                }
                if(redcount2 == 0) oFile << myOBJ.TEXT[i] << endl;
                else redcount2 = 0;
              }
            }
          }

        oFile.close();
        }
        if(myOBJ.GetFIELD() == "artists")
        {
          fstream oFile;
          oFile.open("output.txt",ios::out | ios::app);
              for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
                    {
                      TEMP_V.push_back(myOBJ.INFO[i].artists);
                    }
                      sort(TEMP_V.begin(),TEMP_V.end());

          for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
          {
            for(int j = 0 ; j < myOBJ.TEXT.size() ; j++)
            {
              if(myOBJ.INFO[i].artists.find(TEMP_V[j]) != string::npos && TEMP_V[j] != "")
              {
                for(int k=0 ; k < myOBJ.redZone.size();k++)
                {
                    if(myOBJ.TEXT[i] == myOBJ.redZone[k])
                    {
                        redcount2++;
                    }

                }
                if(redcount2 == 0) oFile << myOBJ.TEXT[i] << endl;
                else redcount2 = 0;
              }
            }
          }

        oFile.close();
        }
        if(myOBJ.GetFIELD() == "director")
        {
          fstream oFile;
          oFile.open("output.txt",ios::out | ios::app);
              for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
                    {
                      TEMP_V.push_back(myOBJ.INFO[i].director);
                    }
                      sort(TEMP_V.begin(),TEMP_V.end());

          for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
          {
            for(int j = 0 ; j < myOBJ.TEXT.size() ; j++)
            {
              if(myOBJ.INFO[i].director.find(TEMP_V[j]) != string::npos && TEMP_V[j] != "")
              {
                for(int k=0 ; k < myOBJ.redZone.size();k++)
                {
                    if(myOBJ.TEXT[i] == myOBJ.redZone[k])
                    {
                        redcount2++;
                    }

                }
                if(redcount2 == 0) oFile << myOBJ.TEXT[i] << endl;
                else redcount2 = 0;
              }
            }
          }

        oFile.close();
        }
        if(myOBJ.GetFIELD() == "year")
        {
          fstream oFile;
          oFile.open("output.txt",ios::out | ios::app);
              for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
                    {
                      TEMP_V.push_back(myOBJ.INFO[i].year);
                    }
                      sort(TEMP_V.begin(),TEMP_V.end());

          for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
          {
            for(int j = 0 ; j < myOBJ.TEXT.size() ; j++)
            {
              if(myOBJ.INFO[i].year.find(TEMP_V[j]) != string::npos && TEMP_V[j] != "")
              {
                for(int k = 0 ; k < myOBJ.redZone.size();k++)
                {
                    if(myOBJ.TEXT[i] == myOBJ.redZone[k])
                    {
                        redcount2++;
                    }

                }
                if(redcount2 == 0) oFile << myOBJ.TEXT[i] << endl;
                else redcount2 = 0;
              }
            }
          }

        oFile.close();
        }
        if(myOBJ.GetFIELD() == "tags")
        {
          fstream oFile;
          oFile.open("output.txt",ios::out | ios::app);
              for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
                    {
                      TEMP_V.push_back(myOBJ.INFO[i].tags);
                    }
                      sort(TEMP_V.begin(),TEMP_V.end());

          for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
          {
            for(int j = 0 ; j < myOBJ.TEXT.size() ; j++)
            {
              if(myOBJ.INFO[i].tags.find(TEMP_V[j]) != string::npos && TEMP_V[j] != "")
              {
                for(int k=0 ; k < myOBJ.redZone.size();k++)
                {
                    if(myOBJ.TEXT[i] == myOBJ.redZone[k])
                    {
                        redcount2++;
                    }

                }
                if(redcount2 == 0) oFile << myOBJ.TEXT[i] << endl;
                else redcount2 = 0;
              }
            }
          }

        oFile.close();
        }
        if(myOBJ.GetFIELD() == "genre")
        {
          fstream oFile;
          oFile.open("output.txt",ios::out | ios::app);
              for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
                    {
                      TEMP_V.push_back(myOBJ.INFO[i].genre);
                    }
                      sort(TEMP_V.begin(),TEMP_V.end());

          for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
          {
            for(int j = 0 ; j < myOBJ.TEXT.size() ; j++)
            {
              if(myOBJ.INFO[i].genre.find(TEMP_V[j]) != string::npos && TEMP_V[j] != "")
              {
                for(int k=0 ; k < myOBJ.redZone.size();k++)
                {
                    if(myOBJ.TEXT[i] == myOBJ.redZone[k])
                    {
                        redcount2++;
                    }

                }
                if(redcount2 == 0) oFile << myOBJ.TEXT[i] << endl;
                else redcount2 = 0;
              }
            }
          }

        oFile.close();
        }
        if(myOBJ.GetFIELD() == "starring")
        {fstream oFile;
        oFile.open("output.txt",ios::out | ios::app);
            for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
                  {
                    TEMP_V.push_back(myOBJ.INFO[i].starring);
                  }
                    sort(TEMP_V.begin(),TEMP_V.end());

        for(int i = 0 ; i < myOBJ.TEXT.size() ; i++)
        {
          for(int j = 0 ; j < myOBJ.TEXT.size() ; j++)
          {
            if(myOBJ.INFO[i].starring.find(TEMP_V[j]) != string::npos && TEMP_V[j] != "")
            {
              for(int k=0 ; k < myOBJ.redZone.size();k++)
              {
                  if(myOBJ.TEXT[i] == myOBJ.redZone[k])
                  {
                      redcount2++;
                  }

              }
              if(redcount2 == 0) oFile << myOBJ.TEXT[i] << endl;
              else redcount2 = 0;
            }
          }
        }

      oFile.close();
      }
		}



//------------------------------------------------------------------------------------
      i++;
			itr++;
			}//end of while


		}

		else cout << "Commands file not opened" << endl;


    File.close();

}

void writeOutput(string output_filename,Catalog myOBJ)
{
    ofstream oFile("output.txt");

    if(oFile.is_open())
    {

        oFile << "Catalog Read : " << myOBJ.GetCatalogRead() << endl;

        for(int i=0;i< myOBJ.TEXT.size() ;i++){
            oFile << myOBJ.TEXT[i] << endl;
          }
    }

    else cout << "Output file cannot opened" << endl;

    oFile.close();

}


int Catalog::CheckDuplicateEntry(Catalog& OBJ)
{
    OBJ.SetUnique(0);
    int unique_count = OBJ.GetUnique();
    int sizeINFO = OBJ.TEXT.size();
    int a = 1,i;
    size_t dendencount;

    for(i = 0 ; i < sizeINFO; i++)
    {
      for(int j = i+1 ; j < sizeINFO ; j++){
        if(OBJ.INFO[i].title == OBJ.INFO[j].title)
        {
           //outputa yaz
           unique_count++;
           fstream oFile;
           oFile.open("output.txt",ios::out | ios::app);
           oFile << "Exception : duplicate entry" << endl;
           oFile << OBJ.TEXT[j] << endl;
           oFile.close();
           OBJ.redZone.push_back(OBJ.TEXT[j]);
           i = j;
        }
    }
  } //end of for

      if(OBJ.GetCatalogRead()=="book" || OBJ.GetCatalogRead()=="music")
      {
          for(int i = 0;i < OBJ.TEXT.size() ; i++)
          {
              dendencount = count(OBJ.TEXT[i].begin(),OBJ.TEXT[i].end(),denden);
              if(dendencount < 8)
              {
                  fstream oFile;
                  oFile.open("output.txt",ios::out | ios::app);
                  oFile << "Exception : missing field" << endl;
                  oFile << OBJ.TEXT[i] << endl;
                  oFile.close();
                  OBJ.redZone.push_back(OBJ.TEXT[i]);
                  unique_count++;
              }
              if(dendencount > 8)
              {
                  fstream oFile;
                  oFile.open("output.txt",ios::out | ios::app);
                  oFile << "Exception : command is wrong" << endl;
                  oFile << OBJ.TEXT[i] << endl;
                  oFile.close();
                  OBJ.redZone.push_back(OBJ.TEXT[i]);
                  unique_count++;
              }

          }
      }

      if(OBJ.GetCatalogRead()=="movie")
      {
        for(int i = 0;i < OBJ.TEXT.size() ; i++)
        {
            dendencount = count(OBJ.TEXT[i].begin(),OBJ.TEXT[i].end(),denden);
            if(dendencount < 10)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              oFile << "Exception : missing field" << endl;
              oFile << OBJ.TEXT[i] << endl;
              oFile.close();
              OBJ.redZone.push_back(OBJ.TEXT[i]);
              unique_count++;
            }
            if(dendencount > 10)
            {
              fstream oFile;
              oFile.open("output.txt",ios::out | ios::app);
              oFile << "Exception : command is wrong" << endl;
              oFile << OBJ.TEXT[i] << endl;
              oFile.close();
              OBJ.redZone.push_back(OBJ.TEXT[i]);
              unique_count++;
            }


        }
      }





    SetUnique(unique_count);
    return unique_count;
}

bool dendenCount(int dd,Catalog OBJ)
{
  int dendencount;

  for(int i = 0;i < OBJ.TEXT.size() ; i++)
  {
      dendencount = count(OBJ.TEXT[i].begin(),OBJ.TEXT[i].end(),denden);
      if(dendencount != dd)
      {
          return false;
      }
      else return true;
  }

}

