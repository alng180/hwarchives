// ----------------------------------------------------------------------------
// Sort Student data (by their last name)
//
// Displays a list based on the last names of the students, sorted using
// insertion sort. Then display a histogram based on the grades of the 
// students in the class. Then, finally, display the average grade of the 
// class.
//
// The list will be displayed in the format of grade, last name,
// and then first name. An example of this is:
// 
// grade last first
// 50 duck donald
//
//
// Assumptions:
// 
//    -- Format of data is correct
//          * Order of data presented is always last, first, grade
//          * White space in between them
//          * One student per line
//          * Contains eof at the end of the file
//    -- All names are no more in length than MAXLENGTH
//    -- All grades are correctly sized as integers
//

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;            // maximum number of records in total
int const MAXLENGTH = 31;           // maximum string length 
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const GROUP = 10;               // group amount
int const HISTOGRAMSIZE = (MAXGRADE-LOWGRADE)/GROUP + 1;    // grouped by GROUP

struct StudentType  {               // information of one student
   int grade;                       // the grade of the student
   char last[MAXLENGTH];            // last name (MAXLENGTH-1 at most)
   char first[MAXLENGTH];           // first name (MAXLENGTH-1 at most)
};

// prototypes go here
bool sortInput(istream&, StudentType[], int&);  // read and sort class data
void displayList(StudentType[], int);           // print sorted list
void setHistogram(int[], StudentType[], int);   // calculate grade frequencies
void displayHistogram(int[]);                   // print histogram
int findAverage(StudentType[], int);            // calculate average grade

//-----------------------------------------------------------------------------
int main()  {
   StudentType students[MAXSIZE];   // list of MAXSIZE number of students
   int size = 0;                    // total number of students
   int histogram[HISTOGRAMSIZE];    // grades grouped by GROUP
   int average = 0;                 // average exam score, truncated

   // creates file object and opens the data file
   ifstream infile("data1.txt");
   if (!infile)  { 
      cout << "File could not be opened." << endl; 
      return 1;  
   }

   // read and sort input by last then first name
   bool successfulRead = sortInput(infile, students, size);              

   // display list, histogram, and class average 
   if (successfulRead)  {
      displayList(students, size);
      setHistogram(histogram, students, size);
      displayHistogram(histogram);
      average = findAverage(students, size);
      cout << "Average grade: " << average << endl << endl;
   }
   return 0;
}

//-----------------------------------------------------------------------------
// sortInput
//
// Reads student data from file (first parameter) for the class of students 
// and then sorts/inputs the read student data from the file in alphabetical 
// order based on last name into an array of StudentTypes (second parameter).
// Keeps tracks of the size (number of students) of the array using an int 
// (third parameter), which should never be greater than MAXSIZE

bool sortInput(istream& infile, StudentType students[], int& size) {
   
   StudentType temp;          // temp location for read data before insertion
   bool correctplace = false;        // if the correct place is found or not
   int place = 0;                    // current location within array
   
   // loop until all(or up to MAXSIZE) students are processed
   for(;;) {

      // read next student's data from data file
      infile >> temp.last >> temp.first >> temp.grade;

      // check if student's grade is legal or not
      // if not, skip and move onto next student
      while(temp.grade < 0 || temp.grade > 100) {
         infile >> temp.last >> temp.first >> temp.grade;
      }

      // check to see if done. If true, break out of infinite loop
      if (size >= MAXSIZE || infile.eof()) break;

      place = size;                 // move place to point to end of array
      correctplace = false;         // search for new correct location

      // for each student pulled from the file
      // loop until place reaches beginning of array (place = 0) or 
      // if the proper place is found in the array for the student
      while(place > 0 && !correctplace) {

         // use strcmp to compare the current and new last/first names
         int lastcmp = strcmp(temp.last, students[place-1].last);
         int firstcmp = strcmp(temp.first, students[place-1].first);
         
         // new last name is alphabetically ahead of current last name
         if(lastcmp < 0) {
            students[place] = students[place-1];
            place--;
         // new last/current last name are equal and 
         // new first name is alphabetically ahead of current first name
         } else if ((lastcmp == 0) && (firstcmp < 0)) {
            students[place] = students[place-1];
            place--;
         // correct sorted position found
         } else {
            correctplace = true;    // break out of loop 
         }
      }
      students[place] = temp;       // copy temp into correct sorted position
      size++;                        
   }
   
   return true;
}

//-----------------------------------------------------------------------------
// displayList
//
// outputs a list of students in grade/last name/first name format and sorted
// by last name from the presorted array of students (first parameter)

void displayList(StudentType students[], int size) {
   cout << "List of names sorted:" << endl;
   // for each student, display data in <grade> <last name> <first name> format
   for(int i=0; i < size; i++) {
      cout << setw(3) << students[i].grade << "  "
           << students[i].last << " "
           << students[i].first << endl;
   }
   cout << endl;
}

//-----------------------------------------------------------------------------
// setHistogram
//
// determines the frequency distribution for the grades per "group"/grade
// interval from the StudentType array filled and sorted in sortInput (second
// parameter); stores this information in an integer array (first parameter)

void setHistogram(int histogram[], StudentType students[], int size) {
   int temp = 0;              // temporary holder for grades

   // set all integers in histogram array to 0
   for (int i = 0; i < HISTOGRAMSIZE; i++) {
      histogram[i] = 0;
   }

   // for each grade in students, determine which group/grade interval the
   // grade belongs in and add one to corresponding spot in histogram[]
   for (int j = 0; j < size; j++) {
      temp = students[j].grade;
      histogram[temp/GROUP]++; 
   }
}

//-----------------------------------------------------------------------------
// displayHistogram
//
// outputs a histogram displaying the grade distribution of the class per grade
// interval/"group" using the histogram array (first parameter) set/filled in
// setHistogram

void displayHistogram(int histogram[]) {
   cout << "Histogram of grades:" << endl;

   // draw histogram for each "group"/grade interval
   for(int i = 0; i < GROUP+1; i++) {
      cout << setw(3) << (i*GROUP) << "-->" 
           << setw(4) << ((i*GROUP)+(GROUP-1)) << ": ";

      // output number of stars based on corresponding int in histogram array
      for(int j = 0; j < histogram[i]; j++) {
         cout << "*";
      }
      cout << endl;
   }
   cout << endl;
}

//-----------------------------------------------------------------------------
// findAverage
//
// calculate the arthimetic mean for the grades of the class (i.e. sum of all 
// grades in the class divided by the size/number of students)

int findAverage(StudentType students[], int size) {
   int sum = 0;

   // sum up all of the grades of the students in the class
   for(int i = 0; i < size; i++) {
      sum += students[i].grade;
   }

   // return the average
   return sum/size;
}