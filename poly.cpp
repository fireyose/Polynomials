// Author:              Youssef Almkari
// Filename:            poly.cpp
// Purpose:             Implementation of Class poly
//                      Produce an interface that handles polynomials

#include "poly.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*
Function: 	constructor
Member Type:	Mutator
Description: 	Sets the number of Terms in the polynomial to 0
Parameters: 	none
Returns:      	N/A
*/

Polynomial::Polynomial()
{ setSize(0); }
  
/*
Function: 	setTerm
Member Type:	Mutator
Description: 	Sets the term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
		float co 	- input 	- the coefficient
		int ex 		- input 	- the exponent 
Returns:      	true if the value is set, false if not
*/ 
void Polynomial::setTerm(int index, float co, int ex) {
  setCoeff (index, co);
  setExponent (index, ex);
}
  
/*  
Function: 	setCoeff
Member Type:	Mutator
Description: 	Sets the coefficient for a term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
		float co 	- input 	- the coefficient for the user
Returns:      	true if the value is set, false if not
*/ 
void Polynomial::setCoeff(int index, float co)
{ termList[index].coeff = co; }
  
/*
Function: 	setExponent
Member Type:	Mutator
Description: 	Sets the exponent for the term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
		int ex 		- input 	- the exponent for the user
Returns:      	true if the value is set, false if not
*/
void Polynomial::setExponent(int index, int ex)
{ termList[index].expn = ex; }


/*
Function: 	getTerm
Member Type:	Inspector
Description: 	Gives the user the values associated with the terms at the index
Parameters: 	int index	- input - the index at which the values are stored
Returns:        The requested Term
Precondition:	index is an in use (active) index
*/
Term Polynomial::getTerm(int index) const
{ return (termList[index]); }
  
/*
Function: 	getSize
Member Type:	Inspector
Description: 	Furnishes the number of Terms in the Polynomial
Parameters: 	none
Returns:        the number of Terms in the Polynomial
*/
int Polynomial::getSize() const
{ return (size); }

/*
Function: 	getCoeff
Member Type:	Inspector
Description: 	Gets the user the coefficient at a certain index
Parameters: 	int index	- input - the index at which the values are stored
Returns:        The requested coefficient
Precondition:	index is an in use (active) index
*/
float Polynomial::getCoeff(int index) const
{ return (termList[index].coeff); }

/*
Function: 	getExponent
Member Type:	Inspector
Description:  	Gets the user the exponent for a certain index
Parameters: 	int index	- input - the index at which the values are stored
Returns:      	The requested exponent
Precondition:	index is an in use (active) index
*/
int Polynomial::getExponent(int index) const
{ return (termList[index].expn); }
  
/*
Function: 	operator ()
Member Type:	Facilitator
Description: 	Evaluate the polynomial for variable x
Parameters: 	x  - input - variable that is standing for value of x
Returns:      	The polynomial evaluated for x
*/
double Polynomial::operator()(double x) const {
  double total = 0;
  for (int i = 0; i < getSize(); i++)
    total = total + (pow(x, getExponent(i)) * getCoeff(i));
  return total;
}
  
/*
Function: 	multiply
Member Type:	Mutator
Description: 	Multiply each coefficient by the scalar arg factor
Parameters: 	fact  - input - variable that is multiplying against all the coefficents
Returns:      	void
*/
void Polynomial::operator *=(float factor) {
  for (int i = 0; i < getSize(); i++)
    setCoeff (i, getCoeff (i) * factor);
}
  
/*
Function: 	add
Member Type:	Mutator
Description: 	Add a term to the polynomial
Parameters: 	coefficent  - input - the coefficent of the term being added
		exponent    - input - the exponent of the term being added
Returns:      	true if the term is added, false otherwise
*/
bool Polynomial::add(float coefficient, int exponent) {
  int dupLoc = 0;
  for (int i = 0; i < getSize(); i++)
    if (getExponent(i) == exponent)
      dupLoc = i;
    // Matching Exponents
    if (dupLoc > 0)
      setCoeff (dupLoc, getCoeff(dupLoc) + coefficient);
    // Add term to the end of array
    else if (getSize() < 10) {
      setTerm (getSize(), coefficient, exponent);
      setSize (getSize() + 1);
      sort();
    }
    // No match or room
    else 
      return false;
  return true;
}

/*
Function: 	add
Member Type:	Mutator
Description: 	Add a term to the polynomial
Parameters: 	T  - input - the Term being added
Returns:      	true if the term is added, false otherwise
*/
bool Polynomial::add(const Term &T)
{ return (add(T.coeff,T.expn)); }
  
/*
Function: 	readFile
Member Type:	Mutator
Description: 	Loads up the terms from a user declared filename
Parameters: 	file - input/output - stream variable 
Returns:      	void
*/
void Polynomial::readFile(ifstream &file) {
  Term T;
  while(file >> T)
    add(T);
  file.close();
}

void Polynomial::sort() { // sorts all of the terms in the factor array
  int idxMax = 0;
  for (int spot = getSize()-1; spot > 0; spot--) {
    idxMax = spot;
    for (int idx = 0; idx < spot; idx++) {
      if (getExponent(idxMax) > getExponent(idx))
	idxMax = idx;
      if (idxMax != spot) {
      	int tempExpn = getExponent(idxMax);
	float tempCoeff = getCoeff(idxMax);
	setTerm (idxMax, getCoeff(spot), getExponent(spot));
	setTerm (spot, tempCoeff, tempExpn); 
      }
    }
  }
}
  
/*
Function: 	setSize
Member Type:	Mutator
Description: 	Sets the term in the variable at a specific index. Private because the application 
		programmer shouldn't be messing with this;  # terms is a function of adding terms.
Parameters: 	int s	- input	- the index of the last value in the term array
Returns:      	N/A
*/ 
void Polynomial::setSize(int s)
{ size = s; }
  
/*
Function: 	operator >>
Description: 	Reads in a Term from a file
Parameters: 	ifstream file	- input/output - the input stream
		Term T		- output only  - the Term that will hold the data read in
Returns:      	ifstream 
*/
ifstream &operator >>(ifstream &file, Term &T) {
  file >> T.coeff >> T.expn;
  return file;
}

/*
Function: 	operator <<
Description: 	Print a Polynomial to the screen
Parameters: 	out - input/output - output stream
		P   - input        - The Polynomial to print
Returns:        void
*/
ostream &operator <<(ostream &out,const Polynomial &P) {
  for (int i = 0; i < P.getSize(); i++) {
    if (i == P.getSize()-1)
      out << P.getCoeff(i) << "x^" << P.getExponent(i);
    else
      out << P.getCoeff(i) << "x^" << P.getExponent(i) << " + ";
  } 
  return out;
}

/*
Function: 	operator <<
Description: 	Write the Polynomial to a File
Parameters: 	ofstream &out  - 	input/output - The output file stream
		const Polynomial &P	input	     - Polynomial to save
Returns:        ofstream - the output file stream
*/
ofstream &operator <<(ofstream &out,const Polynomial &P) {
  for (int i = 0; i < P.getSize(); i++)
    out << P.getCoeff (i) << " " <<  P.getExponent (i) << endl;
  return out;
}
