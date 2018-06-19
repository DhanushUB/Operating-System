                                     Project 0 – online Quiz system

Contents
**************************
1. Introduction
2. To run the program
3. About, Limitations and observations
4. Example Output

Introduction:
**************************

 This program is to implement a simple online Quiz system by understanding the multiple process creation, interprocess communication and terminating the process. For interprocess communication share memory concept is been used.  

 Limitations and observations
*************************************

 1. Number of questions are limit to three and answers for all the questions is 2.
 2. To make a little more exciting a timer of 15 seconds is been used, where each student gets 15 seconds to enter the name and answer three question. Second player get the chance to start with his name and question only after the first player finishes his 15 seconds.
 3. Answers to the question asked has to be manually entered by the player and are not system generated.
 4. End results doesnot display the name of the student, however, it validated the points earned by each student and positions from highest points to lowest, as shown below:
1 Rank goes to the player with 3 Correct answers                                                                           2 Rank goes to the player with 2 Correct answers 
3 Rank goes to the player with 1 Correct answers 

5. Terminates the child processes as per the ranks.
6. In the output, play's name followed with a number can be noticed. That number is the child's PID.
7. Ranking is not valid if the number of correct answers are same for all the players. 
8. If the answers entered is alphanumeric then the quiz ends for that player.
--------------------------------------------------------------------------------------------------------------------------------
*********************************************
Example Output
*********************************************

This is Main process 3605
Enter the count of the participants: 3

                  ---------------- This Quiz will have 3 Questions and to be answered in (15 Seconds) ---------------- 

Timer starts for Player: 3606

Please enter the name of the player:John

John: 3606

Please enter the answers:        2*1= 2

Please enter the answers:        4/2= 2

Please enter the answers:        3-1= 2

Answer1: 2
Answer2: 2
Answer3: 2
                         ---------------- This Quiz will have 3 Questions and to be answered in (15 Seconds) ---------------- 

Timer starts for Player: 3609

Please enter the name of the player: Sam

Sam: 3609

Please enter the answers:        2*1= 3

Please enter the answers:        4/2= 2

Please enter the answers:        3-1= 2

Answer1: 3
Answer2: 2
Answer3: 2
                         ---------------- This Quiz will have 3 Questions and to be answered in (15 Seconds) ---------------- 

Timer starts for Player: 3611

Please enter the name of the player: Kite

Kite: 3611

Please enter the answers:        2*1= 2

Please enter the answers:        4/2= 3

Please enter the answers:        3-1= 4

Answer1: 2
Answer2: 3
Answer3: 4
1 Rank goes to the player with 3 Correct answers 
2 Rank goes to the player with 2 Correct answers 
3 Rank goes to the player with 1 Correct answers 
Terminating: 3606
Terminating: 3609
Terminating: 3611
