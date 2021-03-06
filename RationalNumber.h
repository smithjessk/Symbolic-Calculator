/* 
 * File:        RationalNumber.h
 * 
 * Authors:     Brent Lewis
 *              Jacob Jenkins
 *              Shreya Nirmalan
 *              Nicola Frachesen
 *              Elaine Del Rosario
 * 
 * 
 */

#ifndef RATIONALNUMBER_H
#define	RATIONALNUMBER_H

#include "Number.h"
#include "Integer.h"
#include "Exponential.h"
#include "Expression.h"
#include "TranscendentalNumber.h"
#include "Logarithm.h"

class RationalNumber : public Number {
private:
    map<string, Number*> values;

public:
    RationalNumber(Number* numerator, Number* denominator);
	RationalNumber(string expression);
    ~RationalNumber();
    void simplify();
    void display();
    double toDouble();
    string toString();
    map<string, Number*> getValues();
    void setValues(string key, Number* val);
    
    //Operation Methods
    Number* add(Number*);
    Number* subtract(Number*);
    Number* multiply(Number*);
    Number* divide(Number*);
    Number* exponentiate(Number*);

    // Only used in RationalNumber
    int findGCD(int a, int b);
    
    // Used to satisfy Number.h
    long getValue();
    void setValue(long value);
    string getTranscendentalValue();
    void setTranscendentalValue(string value); 

};

#endif	/* RATIONALNUMBER_H */
