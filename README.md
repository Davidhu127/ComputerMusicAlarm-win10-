# ComputerMusicAlarm (win10)
Wake up the computer and plays a music randomly in the morning!


## SetAlarm.cpp
**SetAlarm.cpp** is the top program, with which users can set up the desired alarm time.
 * It memorizes the previous alarm setting through writting/reading data to/from a file.
 * After getting the time from standard input, it runs a windows-cmd command `schtasks /Change` to set the invoking time of the task in Task Scheduler.
 * At the determined time, the PC will wake up and run **MusicAlarm.cpp**.
 * Please note that you have to create a new task "runAlarm" under the folder "MusicAlarm" in the Scheduler first. This task must have the [highest admin power](https://davidhu0903ex3.pixnet.net/blog/post/453551861-%5b%e9%99%a4%e9%8c%af%5d-%e5%b7%a5%e4%bd%9c%e6%8e%92%e7%a8%8b%e5%99%a8---%e8%87%aa%e5%8b%95%e5%96%9a%e9%86%92%e5%9f%b7%e8%a1%8c-%280x41301%29%280x80) in order to wake PC up.
 
![Snapshot 01](/01.png)


## MusicAlarm.cpp
This program would be called by the Task Scheduler at the specific time.
 * It gets the song list from the music folder by cmd command `dir/b > [path]`.
 * Among the list, it gets one of the song name randomly, and converts the file name to [Format 8.3](https://en.wikipedia.org/wiki/8.3_filename).
 * After that, NirCmd.exe will be called in order to set the system volumn to maximum. A registry will also been added in order to enable Loop Mode.
 * Finally, Windows Media Player will be called to play the music. 
 
*The reason why conversion is needed is that there usually exist blanks in the name of every files, and this is not accepted by cmd.*

![Snapshot 02](/02.png)
