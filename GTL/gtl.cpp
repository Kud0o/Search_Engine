#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include "gtl.h"
#include "dirent.h"
#include <algorithm>
#include <stdlib.h>
using namespace std;
//unordered_map <  string ,  list<  pair  <string  ,  vector <long long> > > >//

gtl::gtl()
{
	pathF = "Files\\";
	loadFiles(fileNames);
	ReadFiles(word, fileNames);
	intersection(word, userWords);
}


void gtl::inputU(){
	char ch[1000];
	char delimiters[]=" \"\',.;()!-+=/*<>{}[]&%#@?_$";
	char* c;
	cin.getline(ch, 1000);
	c = strtok(ch, delimiters);
	while(c != NULL){
	userWords.push_back(c);
	c = strtok(NULL, delimiters);
	}
}

int gtl::loadFiles(vector<string>& fileN){
	DIR* DS = NULL;						//Directory Stream.
	dirent* entry = NULL;				//Used to read Directory.
	DS = opendir(pathF.c_str());			//Open The Folder(Directory)
	if(DS == NULL)
		return -1;				   //(path) Folder Or files doesn't exist.
	entry = readdir(DS);			   //Read first file.(Read Directory).
	while(entry != NULL){
		if(entry->d_name[0] != '.')
		fileN.push_back(entry->d_name);     //Append fileName in vector.
		entry = readdir(DS);				//Read the next file.
	}
	closedir(DS);						//Close Directory
	return fileN.size();	
}

//Convert the word to lowerCase.
char* gtl::lowerC(char* str){
	unsigned char *word = (unsigned char*)str;
	while(*word){
		*word = tolower(*word);
		word++;
	}
	return str;
}

//Don't store this word, if it true.
bool gtl::IS_StopWords(string word){
	if(word.size() < 3 || word == "the" || word == "this" || word == "they" || word == "was"
		 || word == "and" || word == "has" || word == "have" || word == "their"
		  || word == "our" || word == "for" || word == "that" || word == "can"
		   || word == "off" || word == "into" || word == "else" || word == "could")
		return true;
	return false;
}

void gtl::ReadFiles(unordered_map<string, vector<pair<string, int>>>& word, vector<string> FileNames){
		char line[1000];
	    char delimiters[]=" \"\',.;()!-+=/*<>{}[]&%#@?_$";
		char* toc;
		unordered_map<string, unordered_map<string, int>> temp;
	for(int i=0;i<FileNames.size();i++)
	{
		ifstream file(("Files\\"+FileNames[i]).c_str());
		if(!file.is_open()){
			file.open(("Files\\"+FileNames[i]).c_str());
			cout<<"Files\\"+FileNames[i]<<endl;
		}
	
		while(file.good()){
			file.getline(line, 1000);
			toc = strtok(line, delimiters);
			while(toc != NULL && !IS_StopWords(toc)){
			toc = lowerC(toc);
			(temp[toc])[FileNames[i].c_str()]++;
//			cout<<toc<<" "<<(temp[toc])[FileNames[i].c_str()]<<endl;
			toc = strtok(NULL, delimiters);
			}
		}
		file.close();
		file.open(("Files\\"+FileNames[i]).c_str());
		while(file.good()){
			file.getline(line, 1000);
			toc = strtok(line, delimiters);
			while(toc != NULL && !IS_StopWords(toc)){
			toc = lowerC(toc);
			pair<string, int> p = make_pair(FileNames[i], temp[toc][FileNames[i].c_str()]);
			word[toc].push_back(p);	
			//cout<<toc<<" "<<FileNames[i]<<" "<<temp[toc][FileNames[i].c_str()]<<endl;
			toc = strtok(NULL, delimiters);
			}
		}
		file.close();
	}
}


void gtl::intersection(unordered_map<string,vector<pair<string,int>>> all_words, vector<string> words_search2)
{
	int size = words_search2.size();
	string words_search[20];
	/*for(vector<string>::iterator i = words_search2.begin(),int y=0; i!=words_search2.end();y++, ++i){
		words_search[y]=*i;
	}*/
	for(int i = 0; i < size; ++i){
		words_search[i] = words_search2[i];
	}
    int counter=0;
    vector <pair<string,int> > words[10];
    unordered_map<string,vector<pair<string,int> > >::iterator _search;
	for (int i=0;i<words_search2.size();i++)
    {
        _search=all_words.find(words_search[i]);
        if (_search == all_words.end())
        {
            std::cout<<"Sorry,the word that you search dose not exist.\n";
        }
        else
        {
            for (vector<pair<string,int> >::iterator input=_search->second.begin();input!=_search->second.end();input++)
            {
                words[i].push_back(make_pair(input->first,input->second));
            }
        }
        for (vector<pair<string,int> >::iterator compare=words[i].begin();compare!=words[i].end();compare++)
        {
            for (vector<pair<string,int> >::iterator compare2=words[i].begin();compare2!=words[i].end();compare2++)
            {
                if (compare2->second > compare->second)
                {
                    swap(*compare2,*compare);
                }
            }

        }
    }
    
    vector<pair<string,int>> path;
    /*if (size_of_words_search==1)
    {
		for (int i=0;i<words[0].size();i++)
        {
            path.push_back(words[0][i]);
        }
    }
    else 
    {*/
        unordered_map<string,int > mp;
        for (int k=0;k<words_search2.size();k++)
        {
			for (int i=0;i<words[k].size();i++)
            {
				mp[words[k][i].first]++;
            }
        }
        for (unordered_map<string,int >::iterator it=mp.begin();it!=mp.end();it++)
        {
            if (it->second==words_search2.size())
            {
				path.push_back(make_pair(it->first,it->second));
                
            }
        }
    //}
    
		for (vector<pair<string,int>>::iterator i=path.begin();i<=path.begin()+10;i++)
    {
		int n=1;
        ifstream file;
		string s=i->first;
	    const char * c = s.c_str();
		file.open(c);
        if (file.is_open())
        {
			cout<<"file ("<<n<<"):\n";
			n++;
            string line;
            for (int u=1;!file.eof();u++)
            {
                if (u<=3)
                {
                    getline(file,line);
                    cout<<"\t"<<line<<endl;
                }
            }
            file.close();
        }
        else cout<<"sorry ,unable to open the file.\n";
        cout<<"\n\n\n\t\t\t--------------------------------------------------------------\n\n\n";
    }
	char p;
	cout<<"Do you want show the all file (y/n) : ";
	cin>>p;
	if (p=='y')
	{
	   int num,o=1;
	   cout<<"Please enter your option : ";
	   cin>>num;
	   vector<pair<string,int>>::iterator i;
	   for (i=path.begin();o!=0&&i!=path.end();o--,i++);
	   string s=i->first;
	   const char * c = s.c_str();
	   system(c);
	}
}