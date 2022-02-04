/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:20:05 by jabenjam          #+#    #+#             */
/*   Updated: 2022/02/04 18:25:11 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
	std::cout << "Default constructor for Bureaucrat called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string const name, int const grade) : _name(name), _grade(grade)
{
	std::cout << "Parametric constructor for Bureaucrat called" << std::endl;
	try
	{
		if (this->_grade > 150)
			throw Bureaucrat::GradeTooLowException();
		else if (this->_grade < 1)
			throw Bureaucrat::GradeTooHighException();
	}
	catch (GradeTooLowException low)
	{
		std::cout << this->getName() << "'s " << low.getMessage() << std::endl;
	}
	catch (GradeTooHighException high)
	{
		std::cout << this->getName() << "'s " << high.getMessage() << std::endl;
	}
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor for Bureaucrat called" << std::endl;
}

Bureaucrat & Bureaucrat::operator=(Bureaucrat & bureaucrat)
{
	this->_grade = bureaucrat.getGrade();
	return (*this);
}

std::ostream & operator<<(std::ostream & COUT, Bureaucrat & bureaucrat)
{
	COUT << bureaucrat.getName() << "'s grade is " << bureaucrat.getGrade() << ".";
	return (COUT);
}

void Bureaucrat::operator++(int)
{
	try
	{
		if (this->_grade > 1)
			this->_grade--;
		else
			throw Bureaucrat::GradeTooHighException();
	}
	catch (GradeTooHighException high)
	{
		std::cout << this->getName() << "'s " << high.getMessage() << std::endl;
	}
}

void Bureaucrat::operator--(int)
{
	try
	{
		if (this->_grade < 150)
			this->_grade++;
		else
			throw Bureaucrat::GradeTooLowException();
	}
	catch (GradeTooLowException low)
	{
		std::cout << this->getName() << "'s " << low.getMessage() << std::endl;
	}
}

std::string const Bureaucrat::getName() const
{
	return (this->_name);
}

int Bureaucrat::getGrade() const
{
	return (this->_grade);
}

void Bureaucrat::signForm(Form & form)
{
	try
	{
		if (this->_grade > form.getSignLvl())
			throw Bureaucrat::GradeTooLowException();
		else
			std::cout << this->getName() << " signed " << form.getName() << std::endl;
	}
	catch (GradeTooLowException low)
	{
		std::cout << this->getName() << " couldn't sign " << form.getName() << " because their " << low.getMessage() << std::endl;
	}
}

void Bureaucrat::executeForm(Form const & form)
{
	try
	{
		if (this->_grade > form.getExecLvl())
			throw Bureaucrat::GradeTooLowException();
		else if (form.getSigned() == false)
			throw Bureaucrat::NotSignedException();
		else
			std::cout << this->getName() << " executed " << form.getName() << std::endl;
	}
	catch (GradeTooLowException low)
	{
		std::cout << this->getName() << " couldn't execute " << form.getName() << " because their " << low.getMessage() << std::endl;
	}
	catch (NotSignedException nosign)
	{
		std::cout << this->getName() << " couldn't execute " << form.getName() << " because their " << nosign.getMessage() << std::endl;
	}
}

Bureaucrat::GradeTooHighException::GradeTooHighException()
{
	this->_msg = "grade is too high!";
}

Bureaucrat::GradeTooHighException::~GradeTooHighException()
{
	
}

std::string Bureaucrat::GradeTooHighException::getMessage()
{
	return (this->_msg);
}

Bureaucrat::GradeTooLowException::GradeTooLowException()
{
	this->_msg = "grade is too low...";
}

Bureaucrat::GradeTooLowException::~GradeTooLowException()
{
	
}

std::string Bureaucrat::GradeTooLowException::getMessage()
{
	return (this->_msg);
}

Bureaucrat::NotSignedException::NotSignedException()
{
	this->_msg = "form is not signed.";
}

Bureaucrat::NotSignedException::~NotSignedException()
{
	
}

std::string Bureaucrat::NotSignedException::getMessage()
{
	return (this->_msg);
}