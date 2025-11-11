#pragma once
#include <iostream>
#include <exception>
#include <cstdlib>

class Bureaucrat;

class Form{

	private:
	const std::string name;
    bool is_signed;
	const int grade_to_sign;
    const int grade_to_execute;

	public:
	//constructors
	Form();
	Form(const std::string _name, int _grade_to_sign, int _grade_to_execute);
	Form(const Form &src);
	Form &operator =(const Form &src);
    //getters
    std::string getName() const;
	bool getIsSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;

    //member functions
	void beSigned(const Bureaucrat &bureaucrat);
	
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

    ~Form();
};

std::ostream& operator<<(std::ostream& out, const Form& src);
