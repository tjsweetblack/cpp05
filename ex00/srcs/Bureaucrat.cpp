/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <badriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:35:14 by badriano          #+#    #+#             */
/*   Updated: 2025/10/16 14:11:26 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat():name("none"), grade(150)
{
    
};

Bureaucrat::Bureaucrat(const std::string _name, int _grade): name(_name)
{
        setGrade(_grade);
};

Bureaucrat::Bureaucrat(const Bureaucrat &src): name(src.name){
    //try to set grade in a copy constructor to verify if copy class does not have invalid grade
    int tmp;
    
    tmp = src.getGrade();
    this->setGrade(tmp);
};

Bureaucrat& Bureaucrat::operator =(const Bureaucrat &src)
{
    if (this == &src)
		return *this;

    //try to set grade in a copy constructor to verify if copy class does not have invalid grade
    int tmp;

    tmp = src.getGrade();
    this->setGrade(tmp);
    return (*this);
}

void Bureaucrat::setGrade(int _grade)
{
    if( _grade > 149)
    {
        throw Bureaucrat::GradeTooLowException();
    }

    if( _grade < 2)
    {
        throw Bureaucrat::GradeTooHighException();
    }

    grade = _grade;
}

std::ostream& operator <<(std::ostream &out,const Bureaucrat &src)
{
    return (out << src.name << ", " << "bureaucrat grade " << src.grade << std::endl);
}

Bureaucrat::~Bureaucrat()
{
  std::cout << name << ": default deconstructor called"<< std::endl;  
};

std::string Bureaucrat::getName() const
{
    return name;
};

int Bureaucrat::getGrade() const
{
    return grade;
};

const char * Bureaucrat::GradeTooHighException::what() const throw()
{
    return "grade too high";
}

const char * Bureaucrat::GradeTooLowException::what() const throw()
{
    return "grade too low";
}