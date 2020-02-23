#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>
#include <time.h>
using namespace std;
/*
	A Music Alarm that will pick a song randomly from the Music Folder and play
		it with Windows Media Player. Written by davidhcefx, 2016.12.02, revised in 2020.02.

	* Please ensure that:
	  - There is no non-music files under the Music Folder.
	  - There is no sub-directories within the Music Folder.

	* In order to close it, PLEASE CLOSE MEDIA PLAYER FIRST!!
	  This app will close up itself after that. (otherwise, system volumn wouldn't restore)
*/


string Music_Folder = "C:\\Users\\David\\Music\\Songs";
string Windows_Media_Player = "C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe";
// Optional: If you have installed nircmd, then we could turn the volume to maximum!
string Nircmd = "C:\\OtherPrograms\\nircmd-x64\\nircmd.exe";

string format_8_3(const string& addr);

int main()
{
	// Get music list
	system("CD %TEMP%");
	system(("DIR /B \"" + Music_Folder + "\"> .\\music.list").c_str());
	ifstream fin(".\\music.list");
	vector<string> musiclist;
	string line;
	while (getline(fin, line)){
		musiclist.push_back(line);
	}
	fin.close();
	// Pick one randomly
	mt19937 mt(time(NULL));
	if (Music_Folder.back() != '\\') {
		Music_Folder.push_back('\\');
	}
	string cmd = format_8_3(Windows_Media_Player);
	cmd += " \"" + Music_Folder + musiclist[ mt() % (musiclist.size()) ] + "\"";
	// Turn the volume to maximum
	bool hasNir = (system(format_8_3(Nircmd).c_str()) == 0) ? true : false;
	if (hasNir) {
		system((Nircmd + " setsysvolume 65535").c_str());
	}
	// Enable Loop Mode
	system("reg add \"HKCU\\Software\\Microsoft\\MediaPlayer\\Preferences\" /v \"ModeLoop\" /t REG_DWORD /d 1 /f");
	cout << "PLEASE CLOSE THE MEDIA PLAYER FIRST!!\nThis window will close up itself.\n";
	system(cmd.c_str());
	if (hasNir) {
		system((Nircmd + " setsysvolume 6553").c_str());
	}
	// Disable Loop Mode
	system("reg add \"HKCU\\Software\\Microsoft\\MediaPlayer\\Preferences\" /v \"ModeLoop\" /t REG_DWORD /d 0 /f");
	system("DEL .\\music.list");
	return 0;
}

string format_8_3(const string& addr){
	/*
		Format 8.3 Converter (v2) by davidhcefx, 2020.2.24.
	*/
	system("CD %TEMP%");
	ofstream fout("fmt83.bat");
	fout << "@echo off\n";
	fout << "echo %~s1%\n";
	fout.close();
	system(("fmt83.bat \"" + addr + "\"> result.fmt83").c_str());

	string line;
	ifstream fin("result.fmt83");
	getline(fin, line);
	fin.close();
	return line;
}
