#include "Roster.h"

#include <cstdlib>
#include <fstream>
#include <cassert>
#include <iostream>
using namespace std;

Roster::Roster() {
  // initialize to empty array

  this->numStudents = 0;
  for (int i=0; i<ROSTER_MAX; i++) {
    this->students[i] = NULL;
  }

}

void Roster::resetRoster() {
 // To avoid memory leaks:
  //  Recycle memory for all allocated students on roster
  
  while (this->numStudents > 0) {
    delete this->students[this->numStudents - 1];
    this->numStudents --;
  }

}

void Roster::addStudentsFromFile(std::string filename) {
  std::ifstream ifs; // the stream we will use for the input file
  ifs.open(filename);
  
  if (ifs.fail()) {
    std::cerr << "Could not open input file: "
	      << filename << std::endl;
    exit(2); 
  }

  // ifs is an instance of ifstream
  // ifstream inherits from istream, 
  //   i.e. ifs is-a istream

  this->addStudentsFromStream(ifs);

}

void Roster::addStudentsFromStream(std::istream &is) {

  this->resetRoster();

  std::string thisLine;
  // Try to read past the header line.
  getline(is,thisLine);
  if ( is.eof() || is.fail() ) {
    std::cerr << "Unable to read first line of input stream" << std::endl;
    exit(3);
  }

  getline(is,thisLine);
  while (  !is.eof() && !is.fail() ) {
    // If we get here, it means the most recent attempt to read succeeded!
    // So do something with thisLine
    
    Student *sPtr = new Student(thisLine);
    this->students[this->numStudents] = sPtr;
    this->numStudents++;
    
    // try to read another line
    getline(is,thisLine);
  } // end while

}

int Roster::getNumStudents() const { 
  return numStudents;
}

Student Roster::getStudentAt(int index) const { 
  //MOST LIKELY NEED TO DEREFERENCE (MAY NOT THO FOR SOME REASON)
  return *(students[index]); 
}

std::string Roster::toString() const {
  std::string result = "{\n";
  //Student s;

  for (int i = 0; i < numStudents; i++){
    //cout << "index: " << i << endl;
    //cout << (*students[i]).toString() << endl;
    //THE ISSUE IS WITH the student class toString() function
    //s = getStudentAt(i);
    result+=(getStudentAt(i).toString());
    // result+=(students[i]->toString());
    //cout << "after" << endl;
    if (i != numStudents - 1){
      result+=",";
    }
    result+="\n";
  }

  result += "}\n";
  return result;

}

void Roster::sortByPerm() {
  // SELECTION SORT
  // stub does nothing
  // int maxVal;
  // int maxValIndex;

  // for (int i = 0; i < numStudents; i++){
  //   maxVal = students[i]->perm;
  //   for (int j = i; j < numStudents; j++){
  //     if (students[j]->perm > maxVal){
  //       maxVal = students[j]->perm;
  //       maxValIndex = j;
  //     }
  //   }
  //   //swap here
  //   Student *tempStudent = students[maxValIndex];
  //   students[maxValIndex] = students[i];
  //   students[i] = tempStudent;
  // }

  for (int i = numStudents - 1; i > 0; i--){
    //cout << "index: " << i << endl;
    sortByPermHelper(i);
  }
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
  int maxPerm = students[0]->getPerm();
  int maxPermIndex = 0;

  for (int i = 0; i < k; i++){
    if (students[i]->getPerm() > maxPerm){
      maxPerm = students[i]->getPerm();
      maxPermIndex = i;
    }
  }
  return maxPermIndex;
}

void Roster::sortByPermHelper(int k) {
  // swaps max perm from [0..k-1] with elem [k-1]

  int im = indexOfMaxPermAmongFirstKStudents(k);
  int swapIndex = k - 1;

  Student *tempStudent = students[im];
  students[im] = students[swapIndex];
  students[swapIndex] = tempStudent;

  // for (int i = 0; i < numStudents; i++){
  //   cout << getStudentAt(i).toString() << " ";
  // }
  // cout << endl << endl;
  

  // now swap the pointers between index im and index k-1

  // THIS IS STILL A STUB !!!
  
}
