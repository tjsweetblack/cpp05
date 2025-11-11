#include "Bureaucrat.hpp"
#include "AForm.hpp"

// Default constructor
Bureaucrat::Bureaucrat() : name("none"), grade(150) {
}

// Parameterized constructor
Bureaucrat::Bureaucrat(const std::string _name, int _grade) : name(_name) {
    setGrade(_grade);
}

// Copy constructor
Bureaucrat::Bureaucrat(const Bureaucrat &src) : name(src.name) {
    setGrade(src.getGrade());
}

// Assignment operator
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src) {
    if (this == &src)
        return *this;
    
    setGrade(src.getGrade());
    return (*this);
}

// Destructor
Bureaucrat::~Bureaucrat() {
    std::cout << name << ": Bureaucrat destructor called" << std::endl;
}

// Getters
std::string Bureaucrat::getName() const {
    return name;
}

int Bureaucrat::getGrade() const {
    return grade;
}

// Setters
void Bureaucrat::setGrade(int _grade) {
    if (_grade < 1)
        throw Bureaucrat::GradeTooHighException();
    if (_grade > 150)
        throw Bureaucrat::GradeTooLowException();
    
    grade = _grade;
}

// Increment grade (decrease number)
void Bureaucrat::incrementGrade() {
    if (grade - 1 < 1)
        throw Bureaucrat::GradeTooHighException();
    grade--;
}

// Decrement grade (increase number)
void Bureaucrat::decrementGrade() {
    if (grade + 1 > 150)
        throw Bureaucrat::GradeTooLowException();
    grade++;
}

// Sign a form
void Bureaucrat::signForm(AForm &form) {
    try {
        form.beSigned(*this);
        std::cout << this->name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << this->name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}

// Execute a form
void Bureaucrat::executeForm(AForm const &form) const {
    try {
        form.execute(*this);
        std::cout << this->name << " executed " << form.getName() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << this->name << " couldn't execute " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}

// Exception implementations
const char *Bureaucrat::GradeTooHighException::what() const throw() {
    return "Bureaucrat grade is too high!";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
    return "Bureaucrat grade is too low!";
}

// Insertion operator overload
std::ostream &operator<<(std::ostream &out, const Bureaucrat &src) {
    out << src.name << ", bureaucrat grade " << src.grade;
    return out;
}
