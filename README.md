# ComputerMusicAlarm (win10)
Wake up the computer and plays a music randomly in the morning!


## SetAlarm.cpp
**SetAlarm.cpp** is the top program, with which users can set up the desired alarm time.
 * It memorizes the previous alarm setting through writting/reading data to/from a file.
 * After getting the time from standard input, it runs a windows-cmd command `schtasks /Change` to set the invoking time of the task in Task Scheduler.
 * At the determined time, the PC will wake up and run **MusicAlarm.cpp**.
 * Please note that you have to create a new task "runAlarm" under the folder "MusicAlarm" in the Scheduler first. Also please ensure that this task can [wake the PC up](https://www.howtogeek.com/119028/how-to-make-your-pc-wake-from-sleep-automatically/).
 
![Snapshot 01](/01.png)


## MusicAlarm.cpp
This program would be called by the Task Scheduler at the specific time.
 * It gets the song list from the music folder by cmd command `dir/b > [path]`.
 * Among the list, it gets one of the song name randomly, and converts the file name to [Format 8.3](https://en.wikipedia.org/wiki/8.3_filename).
 * After that, NirCmd.exe will be called in order to set the system volumn to maximum. A registry will also been added in order to enable Loop Mode.
 * Finally, Windows Media Player will be called to play the music. 
 
*The reason why conversion is needed is that there usually exist blanks in the name of every files, and this is not accepted by cmd.*

![Snapshot 02](/02.png)
