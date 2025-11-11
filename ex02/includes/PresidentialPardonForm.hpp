#pragma once
#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
private:
    std::string target;

public:
    // Constructors
    PresidentialPardonForm();
    PresidentialPardonForm(const std::string &target);
    PresidentialPardonForm(const PresidentialPardonForm &src);
    PresidentialPardonForm &operator=(const PresidentialPardonForm &src);
    
    // Destructor
    virtual ~PresidentialPardonForm();
    
    // Getter
    std::string getTarget() const;
    
    // Execute implementation
    virtual void execute(Bureaucrat const &executor) const;
};
