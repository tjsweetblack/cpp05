#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat():name("none"), grade(150)
{
    
};

Bureaucrat::Bureaucrat(const std::string _name, int _grade): name(_name)
{
    setGrade(_grade);
};

Bureaucrat::Bureaucrat(const Bureaucrat &src): name(src.name)
{
    setGrade(src.getGrade());
}

Bureaucrat& Bureaucrat::operator =(const Bureaucrat &src)
{
    if (this == &src)
		return *this;

    setGrade(src.getGrade());
    return (*this);
}

void Bureaucrat::setGrade(int _grade)
{
    if (_grade < 1)
    {
        throw Bureaucrat::GradeTooHighException();
    }

    if (_grade > 150)
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

void Bureaucrat::incrementGrade()
{
    if (grade - 1 < 1)
        throw Bureaucrat::GradeTooHighException();
    grade--;
}

void Bureaucrat::decrementGrade()
{
    if (grade + 1 > 150)
        throw Bureaucrat::GradeTooLowException();
    grade++;
}

void Bureaucrat::signForm(Form &form)
{
    try
    {
        form.beSigned(*this);
        std::cout << this->name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << this->name << " couldn't sign " << form.getName() 
                  << " because " << e.what() << std::endl;
    }
}

const char * Bureaucrat::GradeTooHighException::what() const throw()
{
    return "grade too high";
}

const char * Bureaucrat::GradeTooLowException::what() const throw()
{
    return "grade too low";
}

