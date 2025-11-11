#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

// Default constructor
RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequestForm", 72, 45), target("default") {
}

// Parameterized constructor
RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("RobotomyRequestForm", 72, 45), target(target) {
}

// Copy constructor
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src)
    : AForm(src), target(src.target) {
}

// Assignment operator
RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &src) {
    if (this == &src)
        return *this;
    
    AForm::operator=(src);
    this->target = src.target;
    return *this;
}

// Destructor
RobotomyRequestForm::~RobotomyRequestForm() {
    std::cout << "RobotomyRequestForm destructor called" << std::endl;
}

// Getter
std::string RobotomyRequestForm::getTarget() const {
    return target;
}

// Execute implementation
void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
    // Check execution requirements (signed and grade)
    checkExecution(executor);
    
    // Make drilling noises
    std::cout << "* DRILLING NOISES * BZZZzzzzZZZZ... WHIRRRRR... BZZZZZZ..." << std::endl;
    
    // 50% success rate
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(NULL));
        seeded = true;
    }
    
    if (std::rand() % 2 == 0) {
        std::cout << target << " has been robotomized successfully!" << std::endl;
    } else {
        std::cout << "Robotomy of " << target << " failed!" << std::endl;
    }
}
