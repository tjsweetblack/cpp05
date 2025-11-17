#pragma once
#include <iostream>
#include <exception>
#include <string>

class AForm;

class Bureaucrat {
public:
    const std::string name;
    int grade;
    
    // Constructors
    Bureaucrat();
    Bureaucrat(const std::string _name, int _grade);
    Bureaucrat(const Bureaucrat &src);
    Bureaucrat &operator=(const Bureaucrat &src);
    
    // Destructor
    ~Bureaucrat();
    
    // Getters
    std::string getName() const;
    int getGrade() const;
    
    // Setters
    void setGrade(int _grade);
    
    // Member functions
    void incrementGrade();
    void decrementGrade();
    void signForm(AForm &form);
    void executeForm(AForm const &form) const;
    
    // Exceptions
    class GradeTooHighException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
    
    class GradeTooLowException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &src);
