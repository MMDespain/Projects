#include <iostream> // IOSTREAM is the standard library that gives access to the cin and cout objects
#include <string>
#include <functional>

struct Operator{
	char operator_char;
	std::function<double(double,double)> operator_function;
};


double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double get_operand();
Operator get_operator();


int main() {
	std::cout << "Welcome to Mason's Calculator\n"; /*This is equivalent to a print function
	the '<<' is an insertion operator, 'std' is to indicate the library that 'cout' is from.*/
	std::cout << "Please type first operand:\n";
	double op1 = get_operand();
	std::cout << "Please enter one of the following operators {+,-,*,/}:\n";
	Operator op = get_operator();

	std::cout << "Please type the second operand:\n";
	double op2 = get_operand();
	std::cout << op1 << op.operator_char << op2 << "=\n";
	op1 = op.operator_function(op1, op2);
	std::cout << op1 << std::endl;
	std::cout << "Press enter to close program.\n";
	std::cin.ignore();
	std::cin.clear();
	std::cin.get();

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

double get_operand(){
	double num;
	while (!(std::cin >> num)){
		std::cin.clear();
		std::cin.ignore();
	}
	return num;
}

Operator get_operator(){
	char op;
	bool op_validated = false;
	Operator obj;
	while (!op_validated){
		op_validated = true;
		std::cin >> op;
		std::cin.ignore();
		switch (op){
			case '+':
				obj.operator_function = add;
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
			default:
				op_validated = false;
				continue;
		}
	}
	
	obj.operator_char = op;
	return obj;
}