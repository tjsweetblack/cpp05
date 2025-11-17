#include "AForm.hpp"
#include "Bureaucrat.hpp"

// Default constructor
AForm::AForm() : name("default"), is_signed(false), grade_to_sign(150), grade_to_execute(150) {
}

// Parameterized constructor
AForm::AForm(const std::string _name, int _grade_to_sign, int _grade_to_execute)
    : name(_name), is_signed(false), grade_to_sign(_grade_to_sign), grade_to_execute(_grade_to_execute) {
    if (_grade_to_sign < 1 || _grade_to_execute < 1)
        throw AForm::GradeTooHighException();
    if (_grade_to_sign > 150 || _grade_to_execute > 150)
        throw AForm::GradeTooLowException();
}

// Copy constructor
AForm::AForm(const AForm &src)
    : name(src.name), is_signed(src.is_signed), grade_to_sign(src.grade_to_sign), grade_to_execute(src.grade_to_execute) {
}

// Assignment operator
AForm &AForm::operator=(const AForm &src) {
    if (this == &src)
        return *this;
    
    // Only copy non-const member
    this->is_signed = src.is_signed;
    return (*this);
}

// Destructor
AForm::~AForm() {
    std::cout << name << ": AForm destructor called" << std::endl;
}

// Getters
std::string AForm::getName() const {
    return name;
}

bool AForm::getIsSigned() const {
    return is_signed;
}

int AForm::getGradeToSign() const {
    return grade_to_sign;
}

int AForm::getGradeToExecute() const {
    return grade_to_execute;
}

// Member function to sign the form
void AForm::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() > this->grade_to_sign)
        throw AForm::GradeTooLowException();
    this->is_signed = true;
}

// Protected method to check execution requirements
void AForm::checkExecution(const Bureaucrat &executor) const {
    if (!this->is_signed)
        throw AForm::FormNotSignedException();
    if (executor.getGrade() > this->grade_to_execute)
        throw AForm::GradeTooLowException();
}

// Exception implementations
const char *AForm::GradeTooHighException::what() const throw() {
    return "AForm grade is too high!";
}

const char *AForm::GradeTooLowException::what() const throw() {
    return "AForm grade is too low!";
}

const char *AForm::FormNotSignedException::what() const throw() {
    return "Form is not signed!";
}

// Insertion operator overload
std::ostream &operator<<(std::ostream &out, const AForm &src) {
    out << "AForm " << src.getName()
        << ", signed: " << (src.getIsSigned() ? "yes" : "no")
        << ", grade required to sign: " << src.getGradeToSign()
        << ", grade required to execute: " << src.getGradeToExecute();
    return out;
}
