#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>
#include <time.h>
using namespace std;
// 隨機播放音樂程式，會根據資料夾(D:\\David\\Music\\folderA) 裡面歌單，隨機取出一首播放
// If your folder's name has blanks in it, then you will need to convert them to format 8.3 also. Use DIR/X command to view their 8.3 format.

// convert file name to format 8.3
string format_8_3(const string& addr);

int main()
{
	system("DIR /B D:\\David\\Music\\folderA > D:\\namelist.selfdef"); // cmd command: get namelist
	ifstream fin("D:\\namelist.selfdef");
	vector<string> namelist;
	string line;
	while (getline(fin, line)){
		namelist.push_back(line);
	}
	mt19937 mt(time(NULL));
	string cmd = "C:\\PROGRA~2\\WINDOW~3\\wmplayer.exe "; // windows media player exe
	string name = namelist[ mt() % (namelist.size()) ];
	cmd.append(format_8_3("D:\\David\\Music\\folderA\\" + name));
	// NirCmd is a powerful tool (google to download it)
	system("D:\\David\\OtherProgram\\nircmd-x64\\nircmd.exe setsysvolume 65535"); // set system volume to maximum
	system(cmd.c_str());
	system("D:\\David\\OtherProgram\\nircmd-x64\\nircmd.exe setsysvolume 6553");
	fin.close();
	system("DEL D:\\namelist.selfdef");
	return 0;
}

string format_8_3(const string& addr){
	/*
		Format 8.3 converter
		2016.12.02
		Davidhu127
		Please #include <fstream>, <cstdlib>
		Please provide absolute file path, eg. "D:\\folder\\the file.pdf"
	*/
	if (addr[1]!=':' || addr[2]!='\\'){
		cerr << "Error: please provide absolute file path\n";
		return "";
	}
	int pos1 = addr.rfind('\\') +1;
	int pos2 = addr.find(' ', pos1);
	if (pos2 == -1){  // no need to transform to format 8.3
		return addr;
	}
	string purepath {addr.substr(0, pos1)};
	string str = "DIR /X ";
	str.append(purepath);
	str.append(addr.substr(pos1, pos2-pos1)); // first part of the name
	str.append("* > D:\\result.r83fmt");
	system(str.c_str());

	ifstream fin("D:\\result.r83fmt");
	string name = addr.substr(pos1, addr.size()-pos1);
	pos2 = -1;
	while (getline(fin, str)){
		if ((pos2 = str.rfind(name)) != -1) break;
	}
	if (pos2 == -1){
		cerr << "Error while: DIR/X [path] > D:\\result.r83fmt, please check the address: "<<addr<<"\n";
		return "";
	}
	pos2--;  // at ' '
	pos1 = str.rfind(' ', pos2-1);
	pos1++;  // at first word
	purepath.append(str.substr(pos1, pos2-pos1));
	fin.close();
	system("DEL /Q D:\\result.r83fmt");
    	return purepath;
}
