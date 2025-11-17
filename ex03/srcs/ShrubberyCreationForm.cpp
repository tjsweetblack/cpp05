#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

// Default constructor
ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreationForm", 145, 137), target("default") {
}

// Parameterized constructor
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), target(target) {
}

// Copy constructor
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src)
    : AForm(src), target(src.target) {
}

// Assignment operator
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &src) {
    if (this == &src)
        return *this;
    
    AForm::operator=(src);
    this->target = src.target;
    return *this;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm() {
    std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

// Getter
std::string ShrubberyCreationForm::getTarget() const {
    return target;
}

// Execute implementation
void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
    // Check execution requirements (signed and grade)
    checkExecution(executor);
    
    // Create file and write ASCII trees
    std::string filename = target + "_shrubbery";
    std::ofstream file(filename.c_str());
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }
    
    // Write ASCII trees
    file << "       ###" << std::endl;
    file << "      #o###" << std::endl;
    file << "    #####o###" << std::endl;
    file << "   #o#\\#|#/###" << std::endl;
    file << "    ###\\|/#o#" << std::endl;
    file << "     # }|{  #" << std::endl;
    file << "       }|{" << std::endl;
    file << std::endl;
    file << "      ^" << std::endl;
    file << "     ^^^" << std::endl;
    file << "    ^^^^^" << std::endl;
    file << "   ^^^^^^^" << std::endl;
    file << "  ^^^^^^^^^" << std::endl;
    file << " ^^^^^^^^^^^" << std::endl;
    file << "^^^^^^^^^^^^^" << std::endl;
    file << "     |||" << std::endl;
    file << "     |||" << std::endl;
    file << std::endl;
    file << "   .''." << std::endl;
    file << "  /    \\" << std::endl;
    file << " /      \\" << std::endl;
    file << ".        ." << std::endl;
    file << "|        |" << std::endl;
    file << "|  ____  |" << std::endl;
    file << ".  \\  /  ." << std::endl;
    file << " \\  \\/  /" << std::endl;
    file << "  \\____/" << std::endl;
    
    file.close();
    std::cout << "Created shrubbery file: " << filename << std::endl;
}
