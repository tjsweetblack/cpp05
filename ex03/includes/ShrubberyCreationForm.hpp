#pragma once
#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm {
private:
    std::string target;

public:
    // Constructors
    ShrubberyCreationForm();
    ShrubberyCreationForm(const std::string &target);
    ShrubberyCreationForm(const ShrubberyCreationForm &src);
    ShrubberyCreationForm &operator=(const ShrubberyCreationForm &src);
    
    // Destructor
    virtual ~ShrubberyCreationForm();
    
    // Getter
    std::string getTarget() const;
    
    // Execute implementation
    virtual void execute(Bureaucrat const &executor) const;
};
