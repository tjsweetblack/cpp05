/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <badriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:41:25 by badriano          #+#    #+#             */
/*   Updated: 2025/10/16 14:35:49 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

/*
private:
	const std::string name;
    bool is_signed;
	const int grade_to_sign;
    const int grade_to_execute;
*/

Form::Form():name("none"), is_signed(false), grade_to_sign(150), grade_to_execute(150)
{
    
};

Form::Form(const std::string _name, int _grade_to_sign, int _grade_to_execute, bool _is_signed): name(_name)
{

};

Form::Form(const Form &src): name(src.name){

}

Form& Form::operator =(const Form &src)
{
    if (this == &src)
		return *this;

    //try to set grade in a copy constructor to verify if copy class does not have invalid grade
    this->set_grade_to_sing(src.get_to_sing());
    this->set_grade_to_execute(src.get_to_execute());
    return (*this);
}

std::ostream& operator <<(std::ostream &out,const Form &src)
{
    return (out << src.getName() << ", " << "Form grade to sign " << src.get_to_sing() << "Form grade to execute " << src.get_to_execute() << std::endl);
}

Form::~Form()
{
  std::cout << name << ": default deconstructor called"<< std::endl;  
};

std::string Form::getName() const
{
    return name;
};

void Form::set_grade_to_sing(int grade)
{
    if ( grade > 149)
    {
        throw Form::GradeTooLowException();
    }
    if ( grade < 2)
    {
        throw Form::GradeTooHighException();
    }
};

void Form::set_grade_to_execute(int grade)
{
    if ( grade > 149)
    {
        throw Form::GradeTooLowException();
    }
    if ( grade < 2)
    {
        throw Form::GradeTooHighException();
    }
    grade_to_execute = grade;
};


const char * Form::GradeTooHighException::what() throw()
{
    return "grade too high";
}

const char * Form::GradeTooLowException::what() throw()
{
    return "grade too low";
}