#include <iostream> // IOSTREAM is the standard library that gives access to the cin and cout objects
#include <functional> // Used to allow the function to be assignable to a variable

struct Operator{ //Format for structs in C++, same as C I believe
	char operator_char;
	std::function<double(double,double)> operator_function;
};


double add(double a, double b);//function header declarations
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double get_operand();
Operator get_operator();


int main() {
	std::cout << "Welcome to Mason's Calculator\n"; // std:: is to indicate that the thing on the right side of the :: is from a library
	std::cout << "Please type first operand:\n"; // cout is the c++ object to control output. << tells the compiler to feed the data into cout, cout handles the formatting.
	double op1 = get_operand(); // cin object is for retrieving user input, I describe my understanding in the function
	std::cout << "Please enter one of the following operators {+,-,*,/}:\n";
	Operator op = get_operator();

	std::cout << "Please type the second operand:\n";
	double op2 = get_operand();
	std::cout << op1 << op.operator_char << op2 << "=\n"; // multiple objects can be fed into cout with << in one line. 
	op1 = op.operator_function(op1, op2); // op is an instance of the Operator struct, using . accesses its properties, this line is accessing the function and calling it
	std::cout << op1 << std::endl; // std::endl functions the same as '\n', but takes more keystrokes.
	std::cout << "Press enter to close program.\n";
	std::cin.ignore();
	std::cin.clear();
	std::cin.get(); //cin.get() returns the first character in the buffer, the previous two lines are to clear the buffer so that it has to wait for user input before closing the program.

	return 0;
}

double add(double a, double b){
	return a + b;
}

double subtract(double a, double b){
	return a - b;
}

double multiply(double a, double b){
	return a * b;
}

double divide(double a, double b){
	return a / b;
}

double get_operand(){			//cin >> extracts data from the input buffer to the object. It starts after(?) and ends at the first instance of white space in the user input, it is also aware of what it is writing to
	double num;
	while (!(std::cin >> num)){ // I don't know why this works, but it will continue to prompt the user for input until a valid input (for a double) is read
		std::cin.clear();		// clear and ignore are used to stop cin from checking erroneous user input
		std::cin.ignore();
	}
	return num;
}

Operator get_operator(){
	char op;
	bool op_validated = false;
	Operator obj;				// creates an operator object
	while (!op_validated){
		op_validated = true;
		std::cin >> op; //gets a single character from user input, since it knows its writing to a character it won't feed more than one character
		std::cin.ignore(); //to clear out the next characters in the buffer
		switch (op){
			case '+':
				obj.operator_function = add; //these are the function names
				break;
			case '-':
				obj.operator_function = subtract;
				break;
			case '*':
				obj.operator_function = multiply;
				break;
			case '/':
				obj.operator_function = divide;
				break;
			default: 					// if op doesn't match any of the operators, the default case will reset the while loop
				op_validated = false;
				continue;
		}
	}
	
	obj.operator_char = op; //assigns the attribute of the struct
	return obj;
}