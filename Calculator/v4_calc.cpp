#include <string> // strings
#include <iostream> //cin, cout
#include <cctype> //std::istspace
#include <algorithm> //remove_if()
#include <vector> //dynamic arrays
#include <sstream> //double to string chicanery


struct Math_Operation { //Math Operation Node, contains a numeric value, pointer to the Node it intends to work on, and a 'superceeding' post operation pointer to redirect other nodes which intend to act upon it to the 'most resolved' value.
    double value;
    Math_Operation* target_MO;
    Math_Operation* post_operation_MO;
};

enum PEMDAS { //enum that contains each available operation, were more operations added they would need to be added here, and updated in the math_op_generator func.
    MULT = 0,
    DIV,
    ADD,
    NO_OP,
    COUNT, //On a zero-indexed enum, the final entry will be the quantity of entries in the enum not including the count as an entry.
}; 


void math_op_generator_assigner(std::string u_input, std::vector<Math_Operation*> proceedures[PEMDAS::COUNT]); // Parses the sanitized user input and generates/links the Math_Operation structs appropriately.
std::string get_sanitized_user_input(); // Gets the user input and sanitizes it, Removing whitespace and '?' (reserved character for program)
// It'd be prudent to have this make sure user-input is syntatically valid as well, either reprompting or deleting invalid characters to avoid crashes that occur from std::stod() recieving invalid input.
double  process_MO_array(std::vector<Math_Operation*> proceedures[PEMDAS::COUNT]); // Takes the Proceedures array and processes them in order of operations, returning the final value and deleting the Math_Operation structs from memory.

int main() {
    double* alias_value_ptr = NULL; // Used on the second pass of main loop, to track the value of the answer from the previous solution.
    std::ostringstream ss; // object that allows easy conversion of double to strings, for reinsertion back into user_input (so that math_op_generator_assigner() doesn't recieve an 'A' in input.)
    while (true) {
        std::string user_input = get_sanitized_user_input();
        if (!(alias_value_ptr == NULL)) {
            ss << *alias_value_ptr;
            std::string alias_value_str = ss.str();
            while (user_input.find('A') != std::string::npos){
                int i = user_input.find('A');
                user_input.erase(i, 1);
                user_input.insert(i, alias_value_str);
            }
            delete alias_value_ptr;
            alias_value_ptr = NULL;
            ss.str("");
            ss.clear();
        }
        std::vector<Math_Operation*> proceedures[PEMDAS::COUNT];
        math_op_generator_assigner(user_input, proceedures);
        alias_value_ptr = new double; // new double here just allocates memory for a double, it is used like this so that alias_value_ptr can be assigned a value in the next line, but must be deleted before reassignment to avoid memory leaks (see line 43)
        *alias_value_ptr = process_MO_array(proceedures);
        std::cout << "The answer is:\n" << *alias_value_ptr << "\n" << "If you would like to continue using the previous result, you can use a capital A as a variable.\n";
}}


void remove_whitespace(std::string& str) {
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) { return std::isspace(x); }), str.end()); // ripped from https://en.cppreference.com/w/cpp/algorithm/remove.html
    str.erase(std::remove(str.begin(), str.end(), '?'), str.end());
}

std::string get_sanitized_user_input() {
    std::string raw_input;
    std::cout << "Please enter equation to compute.\n";
    std::getline(std::cin, raw_input);
    remove_whitespace(raw_input);
    raw_input += '?'; // '?' is the special character I am using to indicate the end of user_input, to allow math_op_generator_assigner() to make the final value in a chain a 'no-op' type.
    return raw_input;
}

void process_MO(int op_code, Math_Operation& current_MO) {
    Math_Operation* other_MO = current_MO.target_MO;
    while (other_MO->post_operation_MO != NULL) {
        other_MO = other_MO->post_operation_MO;
    }
    //above gets the actual target
    switch (op_code) {
        case PEMDAS::MULT:
            other_MO->value = current_MO.value * other_MO->value;
            break;
        case PEMDAS::DIV:
            other_MO->value = current_MO.value / other_MO->value;
            break;
        case PEMDAS::ADD:
            other_MO->value = current_MO.value + other_MO->value;
            break;
        default:
            std::cout << "Unexpected op_code of: " << op_code << "in process_MO function.\n";
    }
    current_MO.post_operation_MO = other_MO;
}

double  process_MO_array(std::vector<Math_Operation*> proceedures[PEMDAS::COUNT]) {
    for (int i = 0; i < PEMDAS::COUNT-1; i++) {
        for(Math_Operation* current_MO: proceedures[i]) {
            process_MO(i, *current_MO);
        }
    }
    double solution = proceedures[PEMDAS::NO_OP].front()->value;
    for (int i = 0; i < PEMDAS::COUNT; i++) {
        for(Math_Operation* current_MO: proceedures[i]) {
            delete current_MO;
        }
    }
    return solution;
}

/* Uses two loops, one to track the beginning of a double and one to track the end of the double, when it hits a designated op-code it creates a substring from those indices and runs it through std::stod()
   for '-' operators, it will treat it like an add, but shift the index of the beginning once to the left, so that the next number generated become a negative number.
*/

void math_op_generator_assigner(std::string u_input, std::vector<Math_Operation*> proceedures[PEMDAS::COUNT]) {
    Math_Operation* previous_MO = NULL;
    for (unsigned int number_beginning = 0; number_beginning <= u_input.size(); number_beginning++) {
        bool decimal_present = false;
        std::string raw_number = "";
        for (unsigned int number_end = number_beginning; number_end <= u_input.size(); number_end++) {
            if ((number_end == number_beginning) && (u_input[number_end] == '-')) {
                //accept negative here if exists
                continue;
            }
            else if ((u_input[number_end] >= '0') && (u_input[number_end] <= '9')) { //can do < and > operations with chars because of ascii numbering, should be quicker than find function (i hope)
                continue;
            }
            else if (u_input[number_end] == '.'){
                if (!decimal_present) {decimal_present = !decimal_present;}
                else {std::cout << "Too many decimals in input! Exiting Program.\n"; std::exit(1);} // If a number has two decimal places it will cause std::stod() to fail, but this could be handled more gracefully than a program termination, likely while getting user input.
                continue;
            }
            else if (number_end-number_beginning >= 1){ //we have left the number now
                Math_Operation* new_MO = new Math_Operation;

                raw_number = u_input.substr(number_beginning, (number_end-number_beginning));
                new_MO->value = std::stod(raw_number);

                if (previous_MO != NULL) {previous_MO->target_MO = new_MO;}
                new_MO->post_operation_MO = NULL;
                
                // std::cout << new_MO->value << u_input[number_end] << number_end << '\n';
                switch (u_input[number_end]) {
                    case '*':
                        proceedures[PEMDAS::MULT].push_back(new_MO);
                        break;
                    case '/':
                        proceedures[PEMDAS::DIV].push_back(new_MO);
                        break;
                    case '+':
                        proceedures[PEMDAS::ADD].push_back(new_MO);
                        break;
                    case '-':
                        proceedures[PEMDAS::ADD].push_back(new_MO);
                        number_end --; //subtract opertions become adds, number_end is moved back one space so that the following number becomes negative.
                        break;
                    case '?':
                        proceedures[PEMDAS::NO_OP].push_back(new_MO);
                        break;
                    default:
                        std::cout << "Unexpected Character: " << u_input[number_end] << " in equation. Ending Program. \n";
                        std::exit(1);
                }
                number_beginning = number_end;
                previous_MO = new_MO;
                break;
            }
            else if (u_input[number_end] == '\0') {return;}
        }
    }
}