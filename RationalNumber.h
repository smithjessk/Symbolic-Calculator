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

class RationalNumber : public Number {

public:
  RationalNumber(Number numerator, Number denominator);
  ~RationalNumber();
  void simplify();
  int findGCD(int a, int b);
  
private:
  Number* numerator;
  Number* denominator;
};

#endif	/* RATIONALNUMBER_H */
