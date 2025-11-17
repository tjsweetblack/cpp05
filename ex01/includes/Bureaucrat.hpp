#pragma once
#include <iostream>
#include <exception>
#include <cstdlib>

class Form;

class Bureaucrat{
	
	private:
	const std::string name;
	int grade;
	
	public:
	//constructors
	Bureaucrat();
	Bureaucrat(const std::string _name, int _grade);
	Bureaucrat(const Bureaucrat &src);
	Bureaucrat &operator =(const Bureaucrat &src);
    //getters
    std::string getName() const;
    int getGrade() const;
    //setters
    void setGrade(int _grade);
    //member functions
    void incrementGrade();
    void decrementGrade();
    void signForm(Form &form);
    //exceptions
	class GradeTooHighException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

    class GradeTooLowException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

    ~Bureaucrat();
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& src);
