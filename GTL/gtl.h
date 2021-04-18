#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;
class gtl
{
	vector<string> fileNames;
	unordered_map<string, vector<pair<string, int>>> word;
	string pathF;
public:
	vector<string> userWords; 
	gtl();
	int loadFiles(vector<string>& );
	char* lowerC(char* );
	bool IS_StopWords(string);
	void ReadFiles(unordered_map<string, vector<pair<string, int>>>&, vector<string> );
	void intersection(unordered_map<string,vector<pair<string,int>>>,vector<string>);
	void inputU();
};