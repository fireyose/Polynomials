// Author:          Youssef Almkari
// Course:          CSC136
// Assignment:      Project 2
// Filename:        poly_tst.cpp
// Purpose:         To construct a menu to deal with polynomials
//                  Evaluate, Multiply, Print, and Add a polynomial

#include "poly.h"
#include <iostream> 
#include <fstream>
#include <cmath>
#include <cctype>
using namespace std;

/** PROTOTYPES **/

bool openFile (ifstream &, string &, Polynomial &); // Opens input file stream
void printMenu ();                                  // Displays Menu
bool choiceIsX (char &);                            // Checks if user choice is 'X'
float evalPoly (Polynomial &);                      // Evaluates polynomial for user input 'X'
void multPoly (Polynomial &);                       // Multiplies polynomial by user input coefficient 
void addPoly (Polynomial &);                        // Adds term to the polynomial

int main() {
  Polynomial thePoly;    // Declare object 'thePoly' type Polynomial
  ifstream infile;       // Holds input file stream
  ofstream outfile;      // Holds output file stream
  string filename;       // Hold user input filename
  char choice;           // Holds user's menu choice

  // Check if file is successfully opened
  if (openFile (infile, filename, thePoly)) {
    printMenu (); 
    cin >> choice;

    // Menu displays after every choice
    // while user does exit
    while (toupper(choice) != 'X') {
      switch (toupper(choice)) {
      case 'E':
	cout << evalPoly(thePoly);
	break;
      case 'M':
	multPoly(thePoly);
	break;
      case 'P':
	cout << thePoly;
	break;
      case 'A':
	addPoly(thePoly);
	break;
      default:
	// User does not enter a menu option
	cout << endl;
	cout << "Entry not an option, try again." << endl;
	break;
      }
      printMenu ();
      cin >> choice;
    }

    // User chooses to exit
    if (choiceIsX (choice)) {
      char ans;
      cout << "Are you sure? (y or n): ";
      cin >> ans;
      while (toupper (ans) != 'Y' && toupper (ans) != 'N') {
	cout << "Please answer y or n: ";
	cin >> ans;
      }
      // User exists program
      if (toupper (ans) != 'Y') {
	return 0;
      }
      else if (toupper (ans) == 'Y') {
	char ans;
	cout << endl;
	cout << "Would you like to save your Polynomial? (y or n): ";
	cin >> ans;
	while (toupper (ans) != 'Y' && toupper (ans) != 'N') {
	  cout << "Please answer y or n: ";
	  cin >> ans;
	}
	if (toupper (ans) == 'N') {
	  return 0;
	}
	// Print polynomial data to 'newText.txt'
	else if (toupper (ans) == 'Y') {
	  string filename;
	  cout << "Name polynomial file:  ";
	  cin >> filename;
	  outfile.open(filename.c_str());
	  outfile << thePoly;
	  outfile.close();
	}
      }
    }
  }
  return 0;
}

/*
Functon:          openFile
Description:      opens input stream
                  checks if successful
Parameters:       ifstream inf    - input/output - holds input file stream
                  string filename - input/output - holds filename
		  Polynomial Poly - input        - holds object 
Returns:          True if file successfuly opened and read, else false
*/

bool openFile (ifstream &inf, string &fileName, Polynomial &Poly) {
  cout << "Enter file name: ";	         // Ask user for file name
  cin >> fileName;                       // Inserts name in string "fileName"
  cout << endl << endl;
  inf.open(fileName.c_str());            // Opens file
  
  // Checks if the file exists 
  if (inf.fail()) {
    cout << "FILE NOT FOUND" << endl << endl;     // File was not successfully found
    return false;                                 // Bool returns false, program exists 
  }
  else {
    cout << "FILE FOUND" << endl << endl;	  // File successfully streaming under "infile"
    Poly.readFile(inf);
    return true;                                  // Bool returns true, program continues
  }
}

/*
Function:         printMenu
Description:      prints menu
Parameters:       None
Returns:          void
 */

void printMenu () { 
  cout << endl << endl;
  cout << "*The Polynomial Program*" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "(E)valuate" << endl;
  cout << "(M)ultiply" << endl;
  cout << "(P)rint" << endl;
  cout << "(A)dd" << endl;
  cout << "e(X)it" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl << endl;
  cout << "Choose one, any one:  ";
}

/*
Function:       choiceIsX
Description:    checks if user choice is 'X'
Parameters:     char C - input - holds user's choice
Returns:        True is choice is 'X', else false
*/

bool choiceIsX (char &C) {
  if (toupper (C) == 'X')
    return true;
  else
    return false;
}

/*
Function:       evalPoly
Description:    Evaluates the polynomial for user input 'X'
Parameters:     Polynomial Poly - input - holds object
Returns:        evaluated polynomial total type float
*/

float evalPoly (Polynomial &Poly) {
  double X;
  cout << "Enter a value for 'X':  ";
  cin >> X;
  cout << endl;
  return Poly(X);
}

/*
Function:       multPoly
Description:    multiplies polynomial by the user's input
Parameter:      Polynomial Poly - input - holds object
Returns:        void
*/

void multPoly (Polynomial &Poly) {
  float factor;
  cout << "What number would you like to multiply the polynomial by?:  ";
  cin >> factor;
  Poly *= factor;
}

/*
Function:       addPoly
Description:    adds user input coefficient and exponent
                to Polynomial
Parameters:     Polynomial Poly - input - holds object
Returns:        void
*/

void addPoly (Polynomial &Poly) {
  float coeff;
  int expn;
  cout << endl << endl;
  cout << "Enter Coefficient:  ";
  cin >> coeff;
  cout << endl << endl;
  cout << "Enter Exponent:  ";
  cin >> expn;
  Poly.add(coeff, expn);
}
