/* 
 * File:        main.cpp
 * 
 * Authors:     Brent Lewis
 *              Jacob Jenkins
 *              Shreya Nirmalan
 *              Nicola Frachesen
 *              Elaine Del Rosario
 * 
 * 
 */
#include "Calculator.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    Calculator *calculator;
    char menuChoice;
    bool keepGoing;
    string expr;
    
    cout << "*** Welcome to the Calculator Program! ***\n" << endl;
    
    //this do-while loop represents the main menu
    do
    {
        cout << "\nWhat do you want to do?\n" << endl;
        
        cout << "(1) Compute a new expression." << endl;
        cout << "(2) Review previous expressions and answers." << endl;
        cout << "(3) Help." << endl;
        cout << "(4) Quit." << endl;
        cout << "\nEnter your choice: ";
        
        cin >> menuChoice;
        cin.ignore();
        cout << endl;
        
        switch(menuChoice)
        {
        	case '1':
        		keepGoing = true;
        		while(keepGoing)
        		{
                	cout << "Enter your expression: ";
                	getline(cin, expr);
                	if(expr == "back" || expr == "quit")
                		keepGoing = false;
                	else
                		calculator = new Calculator(expr);
                }
                break;
            case '2':
                cout << "Here are the previous inputs: " << endl;
                break;
            case '3':
                //this do-while loop represents the help menu
                do
                {
                    cout << "What do you need help with?\n" << endl;

                    cout << "(1) Entering an expression" << endl;
                    cout << "(2) Exponents" << endl;
                    cout << "(3) Square/Nth roots" << endl;
                    cout << "(4) Logarithms" << endl;
                    cout << "(5) Fractions" << endl;
                    cout << "(6) How your answer will be displayed" << endl;
                    cout << "(7) Return to main menu" << endl;
                    cout << "\nEnter your choice: ";
                    
                    cin >> menuChoice;
                    cin.ignore();
                    cout << endl;

                    switch(menuChoice) 
                    {
                        case '1':
                            cout << "To enter your expression, type in your first value followed by an operator, and then your second value. \n Ex: 4*5 \t (3 + 5) / 2 \nApproved Operators: +, -, *, /, ^ \nTranscedental Numbers: PI/pi, e \n" << endl;
                            break;
                        case '2':
                            cout << "To write out an exponent, use the ^ key and the following format: a^x \nThis will be read as 'a raised to the power of x', where a and x are replaced by your chosen coefficients. \n" << endl;
                            break;
                        case '3':
                            cout << "To write out a square root or nth root, use the following format: sqrt:x for a square root and x^(1/n) \nThis will read as 'the square root of x' or 'the nth root of x', where x is the coefficient \nyou wish to take the root of. \n" << endl;
                            break;
                        case '4':
                            cout << "To write out a logarithm, use the following format: log_b:x \nThis will read as 'log base b of x', where b and x are replaced by your chosen coefficients. \n" << endl;
                            break;
                        case '5':
                            cout << "To write out a fraction, use the following formats: a/b \nWhere a and b are replaced by your chosen coeffiecients. If you wish to write expressions for the numerator, \ndenominator, or both, then use the following format: (a+b)/(c*d) \nWhere a, b, c, and d are your given coefficients and you can use any of the approved operators in your expressions. \nRemember to enclose your expressions before and after the / in () ! \n" << endl;
                            break;
                        case '6':
                            cout << "Please keep in mind that your answers will be returned in their simplest forms as \nintegers (i.e. 2 + 2 = 4), fractions (i.e. 2/6 = 1/3), logarithms (i.e. log_10:6 = log_10:2 + log_10:3), \n or expressions (i.e. 2 + 2 + pi^2 = 4 + pi^2). /nIf you wish to receive decimal answers, please (INSERT DESCRIPTION HERE!!!)." << endl;
                            break;
                        case '7':
                            cout << "Returning back to the main menu..." << endl;
                            break;
                        default:
                            cout << "Invalid selection! Choose 1, 2, 3, 4, 5, 6, or 7.\n" << endl;
                    }
                }while(menuChoice != '7');
                
                menuChoice = 1;
                break;
            case '4':
                break;
            default:
                cout << "Invalid selection! Choose 1, 2, 3, or 4!\n" << endl;
        }
        
    }while(menuChoice != '4' && expr != "quit");
    
    return 0;
}
