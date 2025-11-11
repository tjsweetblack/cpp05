#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

// Default constructor
PresidentialPardonForm::PresidentialPardonForm()
    : AForm("PresidentialPardonForm", 25, 5), target("default") {
}

// Parameterized constructor
PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
    : AForm("PresidentialPardonForm", 25, 5), target(target) {
}

// Copy constructor
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &src)
    : AForm(src), target(src.target) {
}

// Assignment operator
PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &src) {
    if (this == &src)
        return *this;
    
    AForm::operator=(src);
    this->target = src.target;
    return *this;
}

// Destructor
PresidentialPardonForm::~PresidentialPardonForm() {
    std::cout << "PresidentialPardonForm destructor called" << std::endl;
}

// Getter
std::string PresidentialPardonForm::getTarget() const {
    return target;
}

// Execute implementation
void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
    // Check execution requirements (signed and grade)
    checkExecution(executor);
    
    // Inform about the pardon
    std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
