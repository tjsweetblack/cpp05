#pragma once
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <string>

class Intern {
private:
    // Private helper methods for form creation
    AForm* createShrubberyForm(const std::string &target);
    AForm* createRobotomyForm(const std::string &target);
    AForm* createPresidentialForm(const std::string &target);
    
    // Structure to map form names to creation functions
    struct FormType {
        std::string name;
        AForm* (Intern::*creator)(const std::string &target);
    };

public:
    // Constructors
    Intern();
    Intern(const Intern &src);
    Intern &operator=(const Intern &src);
    
    // Destructor
    ~Intern();
    
    // Main method - Factory pattern implementation
    AForm* makeForm(const std::string &formName, const std::string &target);
    
    // Exception for unknown form types
    class FormNotFoundException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};
