#pragma once
#include <iostream>
#include <exception>
#include <cstdlib>


class Bureaucrat{
	public:
	const std::string name;
	int grade;
	//constructors
	Bureaucrat();
	Bureaucrat(const std::string _name, int _grade);
	Bureaucrat(const Bureaucrat &src);
	Bureaucrat &operator =(const Bureaucrat &src);
    //geters
    std::string getName() const;
    int getGrade() const;
    //seters
    void setGrade(int _grade);
    //member functios
    void incrementGrade();
    void decrementGrade();
    //exceptions
	class GradeTooHighException : public std::exception
	{
		public:
		virtual const char *what() throw();
	};

    class GradeTooLowException : public std::exception
	{
		public:
		virtual const char *what() throw();
	};

    ~Bureaucrat();
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& src);
