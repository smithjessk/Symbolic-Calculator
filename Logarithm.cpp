#include "Logarithm.h"

using namespace std;

/*
 * TODO: Write a little bit about what this class does in relation to Expression
 */

Logarithm::Logarithm(Number* coefficient, Number* value, Number* base) {
	this->values["coefficient"] = coefficient;
	this->values["value"] = value;
	this->values["base"] = base;
    this->values["integer"] = 0;
}

Logarithm::Logarithm(string expression) {
    Number* coefficient; Number* value; Number* base;
    int pos = expression.find_first_of("l");
    int pos2;
    if(pos == -1) {
		string exception = "ERROR! This isn't a log! \n";
		throw exception;
	}
    // First deal with the coefficient
    if(expression.substr(0, pos).find_first_of("pe") != -1) {
        coefficient = new TranscendentalNumber(expression.substr(0, pos));
    }
    else {
        coefficient = new Integer(expression.substr(0, pos));
    }
    pos = expression.find_first_of("_");
    pos2 = expression.find_first_of(":");
    // Next deal with the base...
    if(expression.substr(pos + 1, pos2).find_first_of("pe") != -1) {
        base = new TranscendentalNumber(expression.substr(0, pos));
    }
    else {
        base = new Integer(expression.substr(0, pos));
    }
    if(expression.substr(pos2).find_first_of("pe") != -1) {
        value = new TranscendentalNumber(expression.substr(pos2, expression.size()));
    }
    else {
        value = new Integer(expression.substr(pos2, expression.size()));
    }
    this->values["coefficient"] = coefficient;
    this->values["value"] = value;
    this->values["base"] = base;
    this->values["integer"] = 0;
}

Logarithm::~Logarithm() {
    delete values["coefficient"];
    delete values["value"];
    delete values["base"];
    delete values["integer"];
}

// Get and Set Methods
map<string, Number*> Logarithm::getValues() {
    return values;
}

void Logarithm::setValues(string key, Number* val) {
    values[key] = val;
}

/*
vector<Number*> Logarithm::getLogValues() {
    return LogValues;
}

void Logarithm::setLogValues(vector<Number*> LogValues) {
    this->LogValues = LogValues;
}
*/

double Logarithm::toDouble(){
	// Uses log() from cmath which gives the natural logarithm.
    return values["coefficient"]->toDouble() * (log(values["value"]->toDouble()) / 
                                                log(values["base"]->toDouble())) + values["integer"]->toDouble();
}

// Needs to be changed.
string Logarithm::toString(){
	stringstream valueStream;
	valueStream << values["coefficient"]->toString() << "log_" << values["base"]->toString() << ":" << values["value"]->toString();
    if (values["integer"]->getValue() != 0) {
        valueStream << "+" << values["integer"]->toString();
    }
	/* Not needed any longer...
    for (int i = 0; i >= LogValues.size(); i++){
		if (i == LogValues.size()-1){
			valueStream << "log_" << values["base"]->toString() << ":" << LogValues[i]->toString();
		}
		else if (smoothOperator == '+'){
			valueStream << "log_" << values["base"]->toString() << ":" << LogValues[i]->toString() << "+";
		}
		else{
			valueStream << "log_" << values["base"]->toString() << ":" << LogValues[i]->toString() << "-";
		}
	}
    */
	string str = valueStream.str();
	return str;
}

// Only simplifies Integers to integer bases with Integer coefficients ATM.
void Logarithm::simplify() {
    // If the base is an Integer,
    if (typeid(*values["base"]) == typeid(Integer)) {
        // and the last value in logValues is also an Integer,
        if (typeid(*values["value"]) == typeid(Integer)) {
            // See what power of base can be pulled out of the value,
            long multiplier = logBaseN(values["value"]->getValue(), values["base"]->getValue(), 0);
            // If the coefficient is an Integer.
            if (typeid(*values["coefficient"]) == typeid(Integer)) {
                // Set the value of the Integer to the coefficient times the multiplier.
                values["integer"]->setValue(multiplier * values["coefficient"]->getValue());
                // Set the value equal to the result of the value divided by the base^multiplier,
                values["value"]->setValue(values["value"]->getValue() / ((long)pow(values["base"]->getValue(), multiplier)));
                // Get all the twos out.
                long coefficientMultiplier = logBaseN(values["value"]->getValue(), 2, 0);
                // Set the value of the coefficient equal to itself times the coefficient multiplier,
                values["coefficient"]->setValue(values["coefficient"]->getValue() * coefficientMultiplier);
                // Set the value of value to the value divided by 2^coefficient multiplier.
                values["value"]->setValue(values["value"]->getValue() / ((long)pow(2, coefficientMultiplier)));
            }
        }
    }
}



//toDouble and toString currently give you the log at the position in the vector
//you want. This certainly needs tweaking, along with better interaction with
//how log splitting will work. Just getting the basic implementation done.



/*
void Logarithm::splitLog(vector<long> primes) {
    // Not the best way to do this, will be overhauled later. -- Well, seems good.
    LogValues.clear();
    for (int i = 0; i < primes.size(); i++) {
        LogValues.push_back(primes[i]);
        smoothOperator = '+';
    }
}
*/

int Logarithm::logBaseN(int value, int n, int counter) {
    if (value % n != 0) {
        return counter;
    } else {
        return logBaseN(value % n, n, counter++);
    }
}

/*
vector<long> Logarithm::findPrimeFactors(long number, long i, vector<long> prime) {
    if (number < i) {
        return primeFactors;
    } else if (number % i == 0) {
        primeFactors.push_back(i);
        return findPrimeFactors(number / i, 2, primeFactors);
    } else {
        return findPrimeFactors(number, i++, primeFactors);
    }
}
*/

// Operation methods -- not sure exactly what goes in these methods just yet
Number* Logarithm::add(Number* val) {
    if (typeid(*val) == typeid(Logarithm)) {
        if (typeid(*values["value"]) == typeid(Integer) &&
            typeid(*val->getValues()["value"]) == typeid(Integer)) {
            if (values["value"]->getValue() == val->getValues()["value"]->getValue()) {
                if (typeid(*values["base"]) == typeid(Integer) &&
                    typeid(*val->getValues()["base"]) == typeid(Integer)) {
                    if (values["base"]->getValue() == val->getValues()["base"]->getValue()) {
                        Number* result = new Logarithm(values["coefficient"]->add(val->getValues()["coefficient"]),
                                                       values["value"], values["base"]);
                        return result;
                    }
                }
                else if (typeid(*values["base"]) == typeid(TranscendentalNumber) &&
                    typeid(*val->getValues()["base"]) == typeid(TranscendentalNumber)) {
                    if (values["base"]->getTranscendentalValue() == val->getValues()["base"]->getTranscendentalValue()) {
                        Number* result = new Logarithm(values["coefficient"]->add(val->getValues()["coefficient"]),
                                                       values["value"], values["base"]);
                        return result;
                    }
                }
            }
        }
        else if (typeid(*values["value"]) == typeid(TranscendentalNumber) &&
            typeid(*val->getValues()["value"]) == typeid(TranscendentalNumber)) {
            if (values["value"]->getTranscendentalValue() == val->getValues()["value"]->getTranscendentalValue()) {
                if (typeid(*values["base"]) == typeid(Integer) &&
                    typeid(*val->getValues()["base"]) == typeid(Integer)) {
                    if (values["base"]->getValue() == val->getValues()["base"]->getValue()) {
                        Number* result = new Logarithm(values["coefficient"]->add(val->getValues()["coefficient"]),
                                                       values["value"], values["base"]);
                        return result;
                    }
                }
                else if (typeid(*values["base"]) == typeid(TranscendentalNumber) &&
                         typeid(*val->getValues()["base"]) == typeid(TranscendentalNumber)) {
                    if (values["base"]->getTranscendentalValue() == val->getValues()["base"]->getTranscendentalValue()) {
                        Number* result = new Logarithm(values["coefficient"]->add(val->getValues()["coefficient"]),
                                                       values["value"], values["base"]);
                        return result;
                    }
                }
            }
        }
    }
}

Number* Logarithm::subtract(Number* val) {
    if (typeid(*val) == typeid(Logarithm)) {
        // Makes sure the integer is at zero, forget foiling.
        if (val->getValues()["integer"]->getValue() == 0 && values["integer"]->getValue() == 0) {
            if (typeid(*values["value"]) == typeid(Integer) &&
                typeid(*val->getValues()["value"]) == typeid(Integer)) {
                if (values["value"]->getValue() == val->getValues()["value"]->getValue()) {
                    if (typeid(*values["base"]) == typeid(Integer) &&
                        typeid(*val->getValues()["base"]) == typeid(Integer)) {
                        if (values["base"]->getValue() == val->getValues()["base"]->getValue()) {
                            Number* result = new Logarithm(values["coefficient"]->subtract(val->getValues()["coefficient"]),
                                                           values["value"], values["base"]);
                            return result;
                        }
                    }
                    else if (typeid(*values["base"]) == typeid(TranscendentalNumber) &&
                             typeid(*val->getValues()["base"]) == typeid(TranscendentalNumber)) {
                        if (values["base"]->getTranscendentalValue() == val->getValues()["base"]->getTranscendentalValue()) {
                            Number* result = new Logarithm(values["coefficient"]->subtract(val->getValues()["coefficient"]),
                                                           values["value"], values["base"]);
                            return result;
                        }
                    }
                }
            }
            else if (typeid(*values["value"]) == typeid(TranscendentalNumber) &&
                     typeid(*val->getValues()["value"]) == typeid(TranscendentalNumber)) {
                if (values["value"]->getTranscendentalValue() == val->getValues()["value"]->getTranscendentalValue()) {
                    if (typeid(*values["base"]) == typeid(Integer) &&
                        typeid(*val->getValues()["base"]) == typeid(Integer)) {
                        if (values["base"]->getValue() == val->getValues()["base"]->getValue()) {
                            Number* result = new Logarithm(values["coefficient"]->subtract(val->getValues()["coefficient"]),
                                                           values["value"], values["base"]);
                            return result;
                        }
                    }
                    else if (typeid(*values["base"]) == typeid(TranscendentalNumber) &&
                             typeid(*val->getValues()["base"]) == typeid(TranscendentalNumber)) {
                        if (values["base"]->getTranscendentalValue() == val->getValues()["base"]->getTranscendentalValue()) {
                            Number* result = new Logarithm(values["coefficient"]->subtract(val->getValues()["coefficient"]),
                                                           values["value"], values["base"]);
                            return result;
                        }
                    }
                }
            }
        }
    }
}

Number* Logarithm::multiply(Number* val) {
    if (typeid(*val) == typeid(Logarithm)) {
        // forget foiling atm...
        if (val->getValues()["integer"]->getValue() == 0 && values["integer"]->getValue() == 0) {    
            if (typeid(*values["value"]) == typeid(Integer) &&
                typeid(*val->getValues()["value"]) == typeid(Integer)) {
                if (values["value"]->getValue() == val->getValues()["value"]->getValue()) {
                    if (typeid(*values["base"]) == typeid(Integer) &&
                        typeid(*val->getValues()["base"]) == typeid(Integer)) {
                        if (values["base"]->getValue() == val->getValues()["base"]->getValue()) {
                            Number* result = new Logarithm(values["coefficient"]->multiply(val->getValues()["coefficient"]),
                                                           values["value"], values["base"]);
                            return result;
                        }
                    }
                    else if (typeid(*values["base"]) == typeid(TranscendentalNumber) &&
                             typeid(*val->getValues()["base"]) == typeid(TranscendentalNumber)) {
                        if (values["base"]->getTranscendentalValue() == val->getValues()["base"]->getTranscendentalValue()) {
                            Number* result =  new Logarithm(values["coefficient"]->multiply(val->getValues()["coefficient"]),
                                                            values["value"], values["base"]);
                            return result;
                        }
                    }
                }
            }
            else if (typeid(*values["value"]) == typeid(TranscendentalNumber) &&
                     typeid(*val->getValues()["value"]) == typeid(TranscendentalNumber)) {
                if (values["value"]->getTranscendentalValue() == val->getValues()["value"]->getTranscendentalValue()) {
                    if (typeid(*values["base"]) == typeid(Integer) &&
                        typeid(*val->getValues()["base"]) == typeid(Integer)) {
                        if (values["base"]->getValue() == val->getValues()["base"]->getValue()) {
                            Number* result =  new Logarithm(values["coefficient"]->multiply(val->getValues()["coefficient"]),
                                                            values["value"], values["base"]);
                            return result;
                        }
                    }
                    else if (typeid(*values["base"]) == typeid(TranscendentalNumber) &&
                             typeid(*val->getValues()["base"]) == typeid(TranscendentalNumber)) {
                        if (values["base"]->getTranscendentalValue() == val->getValues()["base"]->getTranscendentalValue()) {
                            Number* result = new Logarithm(values["coefficient"]->multiply(val->getValues()["coefficient"]),
                                                           values["value"], values["base"]);
                            return result;
                        }
                    }
                }
            }
        }
    }
    else {
        // What should this do? I firmly think it should just return the number passed so we can check if the reference is the same.
        // If it is we know they were not able to be added.
    }
}

Number* Logarithm::divide(Number* val) {
    // We need to make sure we make a generic Number pointer to self.
    Number* numerator = this;
    Number* result = new RationalNumber(numerator, val);
    return result;
}

Number* Logarithm::exponentiate(Number* val) {
    return 0;
}

// Satisfying our love of maps
string Logarithm::getTranscendentalValue() {
    return "";
}

void Logarithm::setTranscendentalValue(string value) {
    return;
}
long Logarithm::getValue() {
    return 1;
}
void Logarithm::setValue(long value) {
	return;
}

void Logarithm::display()
{

}
