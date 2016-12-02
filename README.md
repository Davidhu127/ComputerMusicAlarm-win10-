# ComputerMusicAlarm (win10)
Wake up the computer and plays a music randomly in the morning!


## SetAlarm.cpp
**SetAlarm.cpp** is the top program, with which users can set up the desired alarm time.
 * It memorizes the previous alarm setting through writting/reading data to/from a file.
 * After getting the time from standard input, it runs a windows-cmd-command `schtasks /Change` to modify task's execution time in Task Scheduler.
 * At the specific time, the PC will wake up and run **MusicAlarm.cpp**. (To wake PC up, Scheduler must have the highest admin power) 
 
![Snapshot 01](/01.png)


## MusicAlarm.cpp
This program would be called by the Task Scheduler at the specific time.
 * It gets the namelist from the music folder by cmd-command `dir/b > [path]`.
 * Among the list, it gets one of the song name by random, and convert the file name to 8.3 format. <br>
 * After that, NirCmd.exe has been called, in order to set system volumn max, and then Windows Media Player has been called to play the music. <br><br>
*The reason why conversion is needed is that there usually exist blanks in the name of every files, and this is not accepted by cmd. (If your folder's name also has blanks in it, then you will need to fix them too.)* <br>

![Snapshot 02](/02.png)
