/*
аргументы строки
1-имя входного файла
2-разделители
3-доступная память
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <locale>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <ctime>

using namespace std;


void merge(char* filename1, char* filename2, char* resultFile) {
	ifstream fin[2];
	ofstream fout(resultFile);
	fin[0].open(filename1);
	fin[1].open(filename2);
	string buffer[2];
	fin[0] >> buffer[0];
	fin[1] >> buffer[1];
	int minimalBuffer = 0;
	do {
		if (buffer[0] < buffer[1]) {
			minimalBuffer = 0;
		}
		else {
			minimalBuffer = 1;
		}
		fout << buffer[minimalBuffer] << endl;
		fin[minimalBuffer] >> buffer[minimalBuffer];
	} while (!fin[minimalBuffer].eof());

	while (!fin[minimalBuffer ^ 1].eof()) {
		fout << buffer[minimalBuffer ^ 1] << endl;
		fin[minimalBuffer ^ 1] >> buffer[minimalBuffer ^ 1];
	}
	fin[0].close();
	fin[1].close();
	fout.close();
}



void externalSort(char* input, char* output, size_t availableMemory) {
	int32_t countChunks = 0;
	size_t usedMemory = 0;
	char buffer1[20], buffer2[20];
	ifstream fin(input);
	string current;
	do {
		vector<string> chunk;
		while (usedMemory < availableMemory && !fin.eof()) {
			int8_t nextByte = fin.get();
			if (nextByte == '\n') {
				chunk.push_back(current);
				current.clear();
			}
			else {
				current += nextByte;
				usedMemory++;
			}
		}
		sort(chunk.begin(), chunk.end());
		_itoa(countChunks, buffer1, 10);
		ofstream fout(buffer1);
		for (int i = 0; i < chunk.size(); ++i) {
			fout << chunk[i] << endl;
		}
		usedMemory = current.size();
		countChunks++;
	} while (!fin.eof());
	while (countChunks > 1) {
		for (int i = 0; i < countChunks; i += 2) {
			if (i + 1 == countChunks) {
				_itoa(i, buffer1, 10);
				_itoa(i/2, buffer2, 10);
				rename(buffer1,buffer2);
			}
			else {
				_itoa(i, buffer1, 10);
				_itoa(i + 1, buffer2, 10);
				merge(buffer1, buffer2, "result.txt");
				remove(buffer1);
				remove(buffer2);
				_itoa(i / 2, buffer1, 10);
				rename("result.txt", buffer1);
			}
		}
		countChunks=(countChunks+1)/2;
	}
	remove(output);
	rename("0",output);
}

size_t parse(char* input, char* output, char* delimiters) {
	set<char> setOfDelimeters;
	for (int i = 0; i < strlen(delimiters); ++i) {
		setOfDelimeters.insert(delimiters[i]);
	}
	ifstream fin(input);
	ofstream fout(output);
	size_t stringSize = 0;
	size_t maxStringSize = 0;
	bool wasDelimiter = true;
	while (true) {
		char nextByte = fin.get();
		if (fin.eof()) break;
		if (setOfDelimeters.count(nextByte)) {
			if (!wasDelimiter) {
				fout << endl;
				if (maxStringSize < stringSize) {
					maxStringSize = stringSize;
				}
				wasDelimiter = true;
				stringSize = 0;
			}
			
		}
		else {
			fout << nextByte;
			stringSize++;
			wasDelimiter = false;
		}
	}
	return maxStringSize;
}

void genRand(char* input, char* delimiters) {
	ofstream fout(input);
	for (int i = 0; i < 1000; ++i) {
		int sz = rand() % 10000 + 1;
		for (int i = 0; i < sz; ++i) {
			fout << (char)(rand() % 26 + 'a');
		}
		fout << delimiters[rand() % strlen(delimiters)];
	}
	fout.close();
}

bool check() {
	vector<string> v[2];
	ifstream fin1("temp.txt");
	ifstream fin2("output.txt");
	string s;
	while (fin1 >> s) {
		v[0].push_back(s);
	}
	while (fin2 >> s) {
		v[1].push_back(s);
	}
	sort(v[0].begin(), v[0].end());
	cerr << "CHECK = ";
	return v[0] == v[1];
}

int main(int argc, char* argv[]) {
	//genRand(argv[1], argv[2]);
	size_t fileSize = 0;
	srand(time(NULL));
	size_t availableMemory = atoi(argv[3]);
	cerr << "target:" << argv[1] << endl;
	cerr << "delimiters:" << argv[2] << endl;
	cerr << "available memory(bytes) = " << availableMemory << endl;
	size_t maxStringSize = parse(argv[1], "temp.txt", argv[2]);
	cerr << "maxStringSize = " << maxStringSize << endl;
	if (maxStringSize > availableMemory) {
		cerr << "string size > available memory";
		remove("temp.txt");
		return 1;
	}
	externalSort("temp.txt", "output.txt", availableMemory);
	bool correctSort = check();
	remove("temp.txt");
	if (correctSort) {
		cerr << "OK";
		return 0;
	}
	else{
		cerr << "FAULT";
		return 1;
	}
}
