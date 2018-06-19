                                     Project 1 – Multi-Level Feedback Queue Scheduler 

Contents
**************************
1. Introduction
3. About, Limitations and observations
4. Sample Output
------------------------------------------------------------------------------------------------------
Introduction:
*******************
This program is to implement a multi-level feedback queue schedular, with first two queue based on the round robin algorithm of quantums 8 and 16 respectively and last queue based on first come first server algorithm. Based on the CPU usage time, processes will be moved to next queues. One of the advantage of using such a multi-level feedback queue schedular is that any process with low burst times will get a chance to execute using round robin algorithm and hence the complete response time will be improved.

The project is implemented used C++ programming.
------------------------------------------------------------------------------------------------------------------


Limitations and observations:
*****************************

1. Used arrays to input process IDs, arrival time, burst time and priorites. To be entered manually in the main function of the source code.
2. Code executed on command line.
3. Results are completely based on the values at the main function.
4. Output shows the calculated waiting time, response time, turn around time, average wait time, average response time, average total response time.
5. In output, PID is the process ID, WT is waiting time, RT is response time and TAT is turn around time.
------------------------------------------------------------------------------------------------------------------

Sample Output:  For 20 processes.
*****************           
** Multi-Level Feedback Queue Scheduler  **                                                                                                                                             
------------------------                                                                                                                                             
------------------------                                                                                                                                             
PID1 WT: 123     RT: 0   TAT: 135                                                                                                                                    
PID2 WT: 216     RT: 6   TAT: 239                                                                                                                                    
PID3 WT: 217     RT: 28  TAT: 247                                                                                                                                    
PID4 WT: 109     RT: 101         TAT: 103                                                                                                                            
PID5 WT: 201     RT: 86  TAT: 217                                                                                                                                    
PID6 WT: 190     RT: 72  TAT: 196                                                                                                                                    
PID7 WT: 226     RT: 36  TAT: 276                                                                                                                                    
PID8 WT: 255     RT: 94  TAT: 282                                                                                                                                    
PID9 WT: 124     RT: 112         TAT: 116  

PID10 WT: 111    RT: 103         TAT: 109                                                                                                                            
PID11 WT: 47     RT: 44  TAT: 52                                                                                                                                     
PID12 WT: 128    RT: 111         TAT: 114                                                                                                                            
PID13 WT: 189    RT: 59  TAT: 194                                                                                                                                    
PID14 WT: 117    RT: 109         TAT: 116                                                                                                                            
PID15 WT: 186    RT: 52  TAT: 194                                                                                                                                    
PID16 WT: 193    RT: 79  TAT: 203                                                                                                                                    
PID17 WT: 143    RT: 14  TAT: 160                                                                                                                                    
PID18 WT: 71     RT: 67  TAT: 72                                                                                                                                     
PID19 WT: 24     RT: 22  TAT: 29                                                                                                                                     
PID20 WT: 76     RT: 72  TAT: 73                                                                                                                                     
                                                                                                                                                                     
Average Turn around time : 156.35                                                                                                                                    
Average Waiting Time : 147.3                                                                                                                                         
Average Response Time : 63.35   
