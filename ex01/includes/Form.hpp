#pragma once
#include <iostream>
#include <exception>
#include <cstdlib>


class Form{

	private:
	const std::string name;
    bool is_signed;
	const int grade_to_sign;
    const int grade_to_execute;

	public:
	//constructors
	Form();
	Form(const std::string _name, int _grade_to_sign, int _grade_to_execute, bool _is_signed);
	Form(const Form &src);
	Form &operator =(const Form &src);
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

    ~Form();
};

std::ostream& operator<<(std::ostream& out, const Form& src);
