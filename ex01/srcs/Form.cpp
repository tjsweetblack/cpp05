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
#include "Bureaucrat.hpp"

// Default constructor
Form::Form() : name("default"), is_signed(false), grade_to_sign(150), grade_to_execute(150)
{
}

// Parameterized constructor
Form::Form(const std::string _name, int _grade_to_sign, int _grade_to_execute)
    : name(_name), is_signed(false), grade_to_sign(_grade_to_sign), grade_to_execute(_grade_to_execute)
{
    if (_grade_to_sign < 1 || _grade_to_execute < 1)
        throw Form::GradeTooHighException();
    if (_grade_to_sign > 150 || _grade_to_execute > 150)
        throw Form::GradeTooLowException();
}

// Copy constructor
Form::Form(const Form &src)
    : name(src.name), is_signed(src.is_signed), grade_to_sign(src.grade_to_sign), grade_to_execute(src.grade_to_execute)
{
}

// Assignment operator
Form& Form::operator=(const Form &src)
{
    if (this == &src)
        return *this;
    
    // Only copy the non-const member
    this->is_signed = src.is_signed;
    return (*this);
}

// Destructor
Form::~Form()
{
    std::cout << name << ": Form destructor called" << std::endl;
}

// Getters
std::string Form::getName() const
{
    return name;
}

bool Form::getIsSigned() const
{
    return is_signed;
}

int Form::getGradeToSign() const
{
    return grade_to_sign;
}

int Form::getGradeToExecute() const
{
    return grade_to_execute;
}

// Member function to sign the form
void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > this->grade_to_sign)
        throw Form::GradeTooLowException();
    this->is_signed = true;
}

// Exception implementations
const char* Form::GradeTooHighException::what() const throw()
{
    return "Form grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Form grade is too low!";
}

// Insertion operator overload
std::ostream& operator<<(std::ostream &out, const Form &src)
{
    out << "Form " << src.getName() 
        << ", signed: " << (src.getIsSigned() ? "yes" : "no")
        << ", grade required to sign: " << src.getGradeToSign()
        << ", grade required to execute: " << src.getGradeToExecute();
    return out;
}