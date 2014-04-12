/*
	This file tests the Calculator class
*/

#include "Calculator.h"

int main()
{
	Calculator calculator;
	vector<string> inputs, answers;
	
	//addition test cases
	calculator.addInput("1+2");
	calculator.calculate();
	
	calculator.addInput("(1+2)");
	calculator.calculate();
	
	calculator.addInput("1+2+3");
	calculator.calculate();
	
	calculator.addInput("(1+2)+3");
	calculator.calculate();

	calculator.addInput("(1+2+3)");
	calculator.calculate();
	
	calculator.addInput("1+(2+3)");
	calculator.calculate();
	
	calculator.addInput("-1+2");
	calculator.calculate();
	
	calculator.addInput("1+(-2)");
	calculator.calculate();
	
	/*//subtraction test cases
	calculator.addInput("(3 * 5)");
	calculator.calculate();
	
	//multiplication test cases
	calculator.addInput("(3 * 5)");
	calculator.calculate();
	
	//division test cases
	calculator.addInput("(3 * 5)");
	calculator.calculate();*/
	
	
	inputs = calculator.getPreviousInputs();
	answers = calculator.getPreviousAnswers();
	for(int i = 0; i < inputs.size();i++)
	{
		cout << "Expression: " << inputs[i] << endl;
		cout << endl;
		cout << "Answer: " << answers[i] << endl;
	}
	return 0;
}
