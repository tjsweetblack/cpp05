#pragma once
#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm {
private:
    std::string target;

public:
    // Constructors
    RobotomyRequestForm();
    RobotomyRequestForm(const std::string &target);
    RobotomyRequestForm(const RobotomyRequestForm &src);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &src);
    
    // Destructor
    virtual ~RobotomyRequestForm();
    
    // Getter
    std::string getTarget() const;
    
    // Execute implementation
    virtual void execute(Bureaucrat const &executor) const;
};
