#pragma once
#include <iostream>
#include <exception>
#include <string>

class Bureaucrat;

class AForm {
private:
    const std::string name;
    bool is_signed;
    const int grade_to_sign;
    const int grade_to_execute;

public:
    // Constructors
    AForm();
    AForm(const std::string _name, int _grade_to_sign, int _grade_to_execute);
    AForm(const AForm &src);
    AForm &operator=(const AForm &src);
    
    // Destructor - virtual for proper polymorphism
    virtual ~AForm();
    
    // Getters
    std::string getName() const;
    bool getIsSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;
    
    // Member functions
    void beSigned(const Bureaucrat &bureaucrat);
    
    // Pure virtual function - makes this an abstract class
    virtual void execute(Bureaucrat const &executor) const = 0;
    
    // Exceptions
    class GradeTooHighException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
    
    class GradeTooLowException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
    
    class FormNotSignedException : public std::exception {
    public:
        virtual const char *what() const throw();
    };

protected:
    // Protected method to check execution requirements
    void checkExecution(const Bureaucrat &executor) const;
};

std::ostream &operator<<(std::ostream &out, const AForm &src);
