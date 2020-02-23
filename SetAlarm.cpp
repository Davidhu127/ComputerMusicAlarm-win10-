#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
using namespace std;
// 設定鬧鐘UI：會根據現在時間計算還剩多少小時，具有記憶功能，並且能透過 schtasks 直接更改工作排程器的執行(喚醒)時間
// 1. You need to create a task called "runAlarm" in the Task Scheduler, under "MusicAlarm" folder. (or change line44 directly)
// 2. Please run this program by RUN WITH ADMIN, otherwise schtasks command won't work.

int main()
{
	time_t t;
	char tstr[20];
	time(&t);
	strftime( tstr, sizeof(tstr), "%Y %m %d %H %M", localtime(&t) ); // get current time
	int Y, Mth, D, H, M;
	stringstream ss;
	ss << tstr;
	ss >> Y >> Mth >> D >> H >> M;

	ifstream fin("D:\\David\\Program\\2016\\ComputerAlarm\\ringtime.txt"); // where prev settings stored
	int rD, rH, rM;
	fin >> rH >> rM;
	fin.close();
	int tmph = (rH >= H) ? rH-H : rH+24-H;
	int tmpm = ((rM >= M) ? rM-M : (tmph--, rM+60-M))/6;  // comma operator
	cout << "Current alarm: " << rH << ':' << rM << "   " << tmph <<'.'<< tmpm << " hours left\n";
	char c;
	do {
		cout << "\ncommand:  [HH]:[MM]\n";
		scanf("%d:%d", &rH, &rM);
		rD = (rH >= H) ? D : D+1;
		tmph = (rH >= H) ? rH-H : (rH+24-H);
		tmpm = ((rM > M) ? rM-M : (tmph--, rM+60-M))/6;
		cout << tmph <<'.'<< tmpm << " hours after [Y/N]";
		cin >> c;
	} while (c != 'Y');
	ofstream fout("D:\\David\\Program\\2016\\ComputerAlarm\\ringtime.txt");
	fout << rH << ' ' << rM;
	fout.close();
	ss.str(""); ss.clear();
	ss << "schtasks /Change /TN MusicAlarm\\runAlarm /SD "; // windows cmd command (the task is under "MusicAlarm" folder)
	char tmps[30];
	sprintf(tmps, "%d/%02d/%02d /ST %02d:%02d", Y, Mth, rD, rH, rM);
	ss << tmps;
	system(ss.str().c_str());
	system("pause");

	return 0;
}
