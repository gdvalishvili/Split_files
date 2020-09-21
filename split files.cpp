#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int main() {
	//ifstream ifs;
	ofstream ofs;

	//Enter File Name
	cout << "\nEnter File Name: \t";
	string fname;						//save file name
	getline(cin, fname);				//enter file name

	//Enter Delimiter
	cout << "Enter Delimiter: \t";
	string delimiter;					//save delimiter
	getline(cin, delimiter);			//enter delimiter

	//Output File(s) Description
	string base(".txt");
	string FileName = "file_";
	char delimiter_char;			//convert vector to char
	string delimiter_string;		//convert vector to string
	int file_count = 1;				//numbers of created file

	//vector of char for save delimiter
	vector<char> vc;
	for (int i = 0; i < delimiter.length(); i++) {
		vc.push_back(delimiter[i]);
	}

	//vector for save text (temporary)
	vector<char> text;

	//vector for save compare text (temporary)
	vector<char> temp;

	//Save text file in buffer
	ifstream ifs(fname, ifstream::binary);
	if (ifs) {

		ifs.seekg(0, ifs.end);
		int length = ifs.tellg();
		ifs.seekg(0, ifs.beg);

		char* buffer = new char[length];

		cout << "\nReading " << length << " characters ... " << endl;

		ifs.read(buffer, length);

		if (ifs)
			cout << "All characters read successfully." << endl;
		else
			cout << "error: only " << ifs.gcount() << " could be read" << endl;
		ifs.close();



		//when delimiter is one symbol
		if (delimiter.length() == 1) {
			delimiter_char = vc[0];

			for (int i = 0; i < length; i++) {

				if (buffer[i] != delimiter_char) {
					text.push_back(buffer[i]);
				}
				else {
					ofs = ofstream(FileName + to_string(file_count) + base);
					for (int i = 0; i < text.size(); i++) {
						ofs << text[i];
					}
					text.clear();
					text.push_back(buffer[i]);
					file_count++;
				}
			}
			ofs = ofstream(FileName + to_string(file_count) + base);
			for (int i = 0; i < text.size(); i++) {
				ofs << text[i];
			}
			text.clear();
		}



		//when delimiter are two or more symbols
		else {
			string str(vc.begin(), vc.end());

			for (int i = 0; i < length; i++) {
				for (int j = i; j < delimiter.length() + i; j++) {
					temp.push_back(buffer[j]);

					string com_str(temp.begin(), temp.end());

					if (str == com_str) {
						ofs = ofstream(FileName + to_string(file_count) + base);
						for (int i = 0; i < text.size(); i++) {
							ofs << text[i];
						}
						text.clear();
						file_count++;
					}
				}
				text.push_back(buffer[i]);
				temp.clear();
			}	
			ofs = ofstream(FileName + to_string(file_count) + base);
			for (int i = 0; i < text.size(); i++) {
				ofs << text[i];
			}
			text.clear();
		}
		delete[] buffer;

		cout << endl;
		cout << "File Name : " << fname << endl;
		cout << "Delimiter : " << delimiter << endl;
		cout << "Number of created files : " << file_count << endl;
	}
	else
		cout << "\nUnable to open file: " << fname << endl;
	
	
	system("pause");
	return 0;
}