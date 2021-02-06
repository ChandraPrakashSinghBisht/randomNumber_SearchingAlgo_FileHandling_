/*
    Task 1: Random number generation - Create a random number generator to create a list of unique integers (each number must appear only once).
    It must be able to generate at least 300 integers (no repeated numbers)

    Task 2: Searching Implementation - Implement linear search, interpolation search and binary search to search an integer from a list of integers from task 1.

    Task 3: Testing - Create a main function which is able to call the number generator and all algorithms. Apply the testing procedure:
    Searching
    By using the function from Task 1, generate 100 unique integers. Output the list in a 100data.txt or 100data.csv file. 
    Get the last integer in the list as k.

    Read the integers from the file in an array or linked list. Apply the algorithms in Task 2 to find k from the list.
*/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

//Function definitions for all algorithms

//generate and write random numbers to a file
void generateWrite(int array[], int size){
    //create a write stream object
    ofstream fout("100data.txt");

    //If file cannot be created then return
    if(!fout){
        cout<<"\nUnable to create the file.";
        return;
    }
    //else proceed futher

    //seed random number generator
    srand(time(0)); 

    for(int i=0; i<size; i++){
        //generate random numbers and store in array
	    array[i] = rand();

        //write to the file
        fout<<array[i]<<" ";
    }

    //close the file object
    fout.close();
}

//linear search
int linearSearch(int arr[], int n, int x) 
{ 
    int i; 
    for (i = 0; i < n; i++) 
        if (arr[i] == x) 
            return i;   //return thr position of element
    return -1; //if element not present
} 

//binary search: a recursive binary search function. 
//It returns location of x in given array if present, 
// otherwise -1 
int binarySearch(int arr[], int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle itself 
        if (arr[mid] == x) 
            return mid; 
  
        // If element is smaller than mid, then move to left subarray 
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x); 
  
        // Else the element can only be present in right subarray 
        return binarySearch(arr, mid + 1, r, x); 
    } 
  
    // We reach here if the element is not present in array 
    return -1; 
} 

//Read numbers from a text file
void readNumbers(int array[], int size){
    //open the file
    ifstream fin;
    fin.open("100data.txt");

    //check for opening error
    if(!fin){
        cout<<"\nUnable to open file!!!";
        return;
    }

    //loop counter
    int count = 0;

    //read numbers into the array
    while(fin >> array[count]){
        count++;
    }

    //close the file
    fin.close();
}

//Interpolation search: if x is present in arr[0..n-1], then returns
// index of it, else returns -1.
int interpolationSearch(int arr[], int lo, int hi, int x)
{
    int pos;
 
    // Since array is sorted, an element present
    // in array must be in range defined by corner
    if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
 
        // Probing the position with keeping
        // uniform distribution in mind.
        pos = lo
              + (((double)(hi - lo) / (arr[hi] - arr[lo]))
                 * (x - arr[lo]));
 
        // Condition of target found
        if (arr[pos] == x)
            return pos;
 
        // If x is larger, x is in right sub array
        if (arr[pos] < x)
            return interpolationSearch(arr, pos + 1, hi, x);
 
        // If x is smaller, x is in left sub array
        if (arr[pos] > x)
            return interpolationSearch(arr, lo, pos - 1, x);
    }
    return -1;  //if not present
}


//Driver program
int main(){
    //declare the array with max size as 300
    int rnums[300];

    //loop choice variable
    int ch;

    do{
        //Menu for the program
        cout<<"\n\n----------------MENU FOR PROGRAM--------------------\n";
        cout<<"\n1. Generate Random Numbers";
        cout<<"\n2. Search for a number";
        cout<<"\n3. Reset the values of array";
        cout<<"\n4. Quit from whole program";  
        cout<<"\nEnter your choice : ";
        cin>>ch;

        //Proceed as per the input received
        //and call appropriate methods
        switch(ch){ //write random values to the file
            case 1:
                cout<<"\nEnter the size of array : ";
                int size;
                cin>>size;
                generateWrite(rnums, size);
                break;
            case 2:  //Search for an integer
                //first read the numbers from the file 
                readNumbers(rnums, size);

                //The array needs to be sorted before searching
                sort(rnums, rnums+size);

                //variable to store presence of element
                //-1 if not present, else its index value
                int ele;

                int ch2;  //loop variable
                do{
                    cout<<"\n\nEnter number to be searched for: ";
                    int search;
                    cin>>search;

                    //Menu for Searching algorithms
                    cout<<"\n****MENU FOR SEARCHING***\n";
                    cout<<"\n1. Linear Search";
                    cout<<"\n2. Binary Search";
                    cout<<"\n3. Interpolation Search";
                    cout<<"\n4. Done with Searching";
                    cout<<"\nEnter your choice : ";
                    cin>>ch2;

                    //proceed as input  received
                    //and call appropriate methods
                    switch(ch2){
                        case 1:
                            //call and store the position of 'search
                            //if -1, it means element not present
                            ele = linearSearch(rnums, size, search);
                            if(ele == -1){
                                cout<<"\n"<<search<<" is not in the file";
                            }
                            else{
                                cout<<"\n"<<search<<" is present in the file";
                            }
                            break;
                        case 2:
                            //call and store the position of 'search
                            //if -1, it means element not present
                            ele = binarySearch(rnums, 0, size-1, search);
                            if(ele == -1){
                                cout<<"\n"<<search<<" is not in the file";
                            }
                            else{
                                cout<<"\n"<<search<<" is present in the file";
                            }
                            break;
                        case 3:
                            //call and store the position of 'search
                            //if -1, it means element not present
                            ele = interpolationSearch(rnums, 0, size-1, search);
                            if(ele == -1){
                                cout<<"\n"<<search<<" is not in the file";
                            }
                            else{
                                cout<<"\n"<<search<<" is present in the file";
                            }
                            break;
                        case 4:
                            cout<<"\nExiting the search portal";
                            break;
                        default:
                            cout<<"\nWrong choice!!!";
                    }
                }while(ch2 != 4);

                break;
            case 3:  //Reset the array
                for(int i=0; i<size; i++){
                    rnums[i] = 0; //All values set to 0
                }
                cout<<"\n\nValues reset successful.";
                break;
            case 4:  //Quit the program
                cout<<"\n\nExiting the program.";
                break;
            default:
                cout<<"\nWrong choice!!!";
        }
    }while(ch != 4);  //do-while ends here

    cout<<"\n\nGoodbye...\n";
    return 0;
}  //end of main
