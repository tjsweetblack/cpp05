#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat():name("none"), grade(150)
{
    
};

Bureaucrat::Bureaucrat(const std::string _name, int _grade): name(_name)
{
    try
    {
        setGrade(_grade);
    }
    catch(Bureaucrat::GradeTooHighException &e)
    {
        std::cerr<<e.what()<< std::endl;
    }
    catch(Bureaucrat::GradeTooLowException &e)
    {
        std::cerr<<e.what()<< std::endl;
    }
};

Bureaucrat::Bureaucrat(const Bureaucrat &src): name(src.name){
    //try to set grade in a copy constructor to verify if copy clas does not have invalid grade
    int tmp;

    try
    {
        tmp = src.getGrade();
        this->setGrade(tmp);
    }
    catch(Bureaucrat::GradeTooHighException &e)
    {
        std::cerr<<e.what()<< std::endl;
    }
    catch(Bureaucrat::GradeTooLowException &e)
    {
        std::cerr<<e.what()<< std::endl;
    }
}

Bureaucrat& Bureaucrat::operator =(const Bureaucrat &src)
{
    if (this == &src)
		return *this;

    //try to set grade in a copy constructor to verify if copy clas does not have invalid grade
    int tmp;
    try
    {
        tmp = src.getGrade();
        this->setGrade(tmp);
    }
    catch(Bureaucrat::GradeTooHighException &e)
    {
        std::cerr<<e.what()<< std::endl;
    }
    catch(Bureaucrat::GradeTooLowException &e)
    {
        std::cerr<<e.what()<< std::endl;
    }
    return (*this);
}

void Bureaucrat::setGrade(int _grade)
{
    if( _grade > 149)
    {
        throw Bureaucrat::GradeTooHighException();
    }

    if( _grade < 2)
    {
        throw Bureaucrat::GradeTooLowException();
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

const char * Bureaucrat::GradeTooHighException::what() throw()
{
    return "grade too high";
}

const char * Bureaucrat::GradeTooLowException::what() throw()
{
    return "grade too low";
}

