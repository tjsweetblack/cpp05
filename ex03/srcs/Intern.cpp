#include "Intern.hpp"
#include <iostream>

// Default constructor
Intern::Intern() {
    std::cout << "Intern hired" << std::endl;
}

// Copy constructor
Intern::Intern(const Intern &src) {
    (void)src;  // Nothing to copy, intern has no state
    std::cout << "Intern copy created" << std::endl;
}

// Assignment operator
Intern &Intern::operator=(const Intern &src) {
    (void)src;  // Nothing to assign, intern has no state
    return *this;
}

// Destructor
Intern::~Intern() {
    std::cout << "Intern fired" << std::endl;
}

// Private form creation methods
AForm* Intern::createShrubberyForm(const std::string &target) {
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(const std::string &target) {
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialForm(const std::string &target) {
    return new PresidentialPardonForm(target);
}

// Main factory method - elegant implementation without if/else chain
AForm* Intern::makeForm(const std::string &formName, const std::string &target) {
    // Array of form types with their names and creation functions
    // This is the elegant way to avoid if/else/elseif chains
    FormType formTypes[] = {
        {"shrubbery creation", &Intern::createShrubberyForm},
        {"robotomy request", &Intern::createRobotomyForm},
        {"presidential pardon", &Intern::createPresidentialForm}
    };
    
    // Search for matching form type
    for (int i = 0; i < 3; i++) {
        if (formTypes[i].name == formName) {
            // Call the appropriate creation function using member function pointer
            AForm *form = (this->*(formTypes[i].creator))(target);
            std::cout << "Intern creates " << formName << std::endl;
            return form;
        }
    }
    
    // Form not found
    std::cout << "Intern cannot create form: \"" << formName 
              << "\" does not exist" << std::endl;
    throw Intern::FormNotFoundException();
}

// Exception implementation
const char* Intern::FormNotFoundException::what() const throw() {
    return "Form type not found!";
}
