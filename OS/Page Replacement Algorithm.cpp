#include <iostream> // input/output stream
#include <stack> // std::stack
#include <vector> //
#include <cstdlib> // for using c functions, exit(1) in this
using namespace std; // for using cin and cout from the std library
class pralgo {
    int frame[100], actualframe[100][2], pgnum[100], num, count, q, fsize;

public:
    void FifoAlgo();             // for fifo algorithm
    void OptimalAlgo();          // for optimal algorithm
    void LRUalgo();              // for LRU algorithm
    void defaultval();           // to initialise 
    void fetchdata();            // to get the data through input
    void copyStack(stack<int>& s, stack<int>& t, int element); // to copy stack for LRU
};


void pralgo::defaultval()
{
    int i;
    for (i = 0; i < fsize; i++) {   
    frame[i] = -1;
    }

    for (i = 0; i < fsize; i++) {
        actualframe[i][0] = -1;
        actualframe[i][1] = 0;
    }
    q = 0;
    count = 0;
}
void pralgo::fetchdata()
{
    cout << "\nEnter frame size and the number of pages (with space inbetween, Ex: 4 15): ";   // to get frame size and the number of pages
    cin >> fsize>>num;                      // storing frame size in fsize and number of pages in num
    cout << "\nEnter the reference string : ";  // to get reference string
    for (int i = 0; i < num; i++) {
        cin >> pgnum[i];					// to store the reference string 
    }
}

// algorithm for FIFO

void pralgo::FifoAlgo()
{
    defaultval();                            // using the values from the initialiser
    int a, b, c, fnum;                       
    int pgindex = 0, index = 0, fault = 0;   // initialising page index, index and fault
    q = 0;
    count = 0;
    for (a = 0; a < num; a++) {
        b = 0;
        if (index > fsize - 1)// Reset index when it exceeds the frame size
            index = 0;
        fault = 1;
        //loop to check if the current element is present in current frame
        while (b < fsize) {
            if (frame[b] == pgnum[pgindex]) {  // comparing frame with page number.
                fault = 0;                 // if element or page number found in anyone of the memory frame then fault = 0 /no fault/ hit
                goto loop1;
            }
            fnum = index;
            b++;
        }
        b = 0;
        //loop to check for empty slots available in current frame id so allocate it current page Number
        while (b < fsize) {
            if (frame[b] == -1) {
                fault = 1;
                fnum = b;
                goto loop1;
            }
            b++;
        }
        index++;
    loop1:
        if (fault == 1) {// If element is not allocated or is not present in current stack 
            frame[fnum] = pgnum[pgindex];// allocate element to index pos in current stack
            count++;
        }
        
        //Display the current frame elments
        cout <<"\n"; 
        cout << pgnum[pgindex] << "|| <";
         pgindex++;
        for (c = 0; c < fsize; c++) {
			if(c!=0)
			 cout<<",";
			if(frame[c]==-1)
			cout<<" ";
			else
            cout << frame[c];
           
        }
        if (fault == 1)
            cout << ">  *PF*";
        else
            cout << ">  *NPF*";
    }
    cout << "\nTotal number of page fault using FIFO algorithm: " << count;
}

// algorithm for optimal

void pralgo::OptimalAlgo()
{
    defaultval();
    int x, y, z, fnum, m = 0, index = 0;
    int pgindex1 = 0, pgindex = 0, fault = 0, flag = 0, flag1 = 0;
    count = 0, q = 0;
    for (x = 0; x < num; x++) {
        y = 0;
        if (index > fsize - 1) //Reset index when it exceeds the frame size
            index = 0;
        fault = 1;
        m = 0;
        while (y < fsize) { //loop to check if the current element is present in current frame
			if(frame[y] == pgnum[pgindex])
			{
				fault=0;
			 goto loop1;
		 }
            if (frame[y] == -1) {// if slot is available then allocate element to the frame 
                fault = 1;
                fnum = y;
                goto loop1;
            }
            y++;
        }
        y = 0;
        while (y < fsize) {// Check if this element is occuring in next elements 
            z = 0;
            while (z < fsize) {
                if ((frame[z] == pgnum[pgindex])) {
                    fault = 0;
                    goto loop1;
                }
                z++;
            }
            flag = 0;
            flag1 = 0;
            pgindex1 = pgindex;
            while (pgindex1 < num) {
                if (frame[y] == pgnum[pgindex1 + 1] && pgindex1 + 1 < m) {
                    break;
                }
                if (frame[y] == pgnum[pgindex1 + 1] && pgindex1 + 1 > m) {
                    m = pgindex1 + 1;
                    fnum = y;
                    flag1 = 1;
                    break;
                }
                pgindex1++;
            }
            pgindex1 = pgindex;
            if (flag1 == 0) {
                pgindex1 = pgindex;
                while (pgindex1 < num) {
                    if (frame[y] == pgnum[pgindex1 + 1]) {
                        flag = 1;
                        break;
                    }
                    pgindex1++;
                }
                if (flag == 0) {
                    fnum = y;
                    goto loop1;
                }
            }
            y++;
        }
    loop1:
        if (fault == 1) {// If PageNumber is not present in current stack replace with fnum pointer 
            frame[fnum] = pgnum[pgindex];
            count++;
        }
        cout <<"\n"<< pgnum[pgindex] << "|| <";
        pgindex++;
     
      for (z = 0; z < fsize; z++) {
	if(z!=0)
			 cout<<",";
	if(frame[z]==-1)
	  cout<<" ";
	else
            cout << frame[z];
	 
        }
        if (fault == 1)                                         
            cout <<">  *PF*";
        else
            cout <<">  *NPF*";                                  // if the elements in the frame doesn't change, no page fault or referenced 
    }
    cout << "\nTotal number of page faults using Optimal Algorithm is : " << count;   // output for optimal algorithm
}

//algorithm for LRU
void pralgo::LRUalgo()
{
    int npfault = 0;
    //declaring a class templet which holds a Stack,  
    //printstack is for printing the stack, 
    //aStack is to store the current status of LRU, contains is to check the incoming page number in the stack
    stack<int> printStack, aStack, contains;   
   // loop to read page numbers from the reference string
    for (int i = 0; i < num; i++) {         
        cout << '\n' << pgnum[i] << "||";
        contains = aStack;
        int localcount = 0;
 // to check if the page number is present in the existing stack
        while (!contains.empty() && localcount < fsize) {
            if (contains.top() == pgnum[i]) {
                cout << "NPF";
                npfault++;
            }
            contains.pop();
            localcount++;
        } 
        copyStack(aStack, printStack, pgnum[i]); // copies the astack to printstack without the current element [pgnum[i]]
        printStack.push(pgnum[i]);  // current element is been added to the stack(print)
        aStack = printStack; 
        int counter = 0;
   // loop to print the stack     
        
        while (!printStack.empty() && counter < fsize) {
            counter++;
            cout << ' '<<'\t' << printStack.top();
            printStack.pop();
        }
      
    }

    cout << "\n Total Page Fault using LRU algorithm is : " << ((((num - npfault - fsize) > 0) ? num - npfault - fsize : 0) + ((fsize <= num) ? fsize : num)); //total page numbers-framesize(default page fault) - not page faults  = pagefaults.
}
// recurrsive function to copy astack to printstack
void pralgo::copyStack(stack<int>& s, stack<int>& t, int element)
{
    if (!s.empty()) {
        int item = s.top();         
        s.pop();
        copyStack(s, t, element);
        if (item != element)    // condition to check wheather element is present in the current stack, if so skip
            t.push(item);
    }
}

int main()
{
 pralgo a;                           // using 'a' as object to call 'pralgo'
 int selection;                      // to strore selection from the menu
 a.fetchdata();                      // to get the data from fetchdata to object 'a'
 do
 {                                   // Menu selection
  cout<< "\n#### Menu ####\n";
  cout<< "1. FIFO Algorithm \n";
  cout<< "2. OPTIMAL Algorithm \n";
  cout<< "3. LRU Algorithm \n";
  cout<< "4. Exit application\n";
  cout<< "\nSelect from the above menu: ";
  cin >> selection;                           // input selection
 
                                           // if and elseif loop to call the functions as per selection
 if(selection==1)
  a.FifoAlgo();
 else if(selection==2)
  a.OptimalAlgo();
 else if(selection==3)
  a.LRUalgo();
 else if (selection==4)
  {
  exit(1);                      //to terminate program
 }
 else
  cout<<"\n Invalid Choice! Try again with (1,2,3,4) !!\n";  // in case of wronge selction input
 
 } while(selection!=1 || selection!=2 || selection!=3 || selection!=4); // to enter into the loop again and display the menu
 return 1;
}
