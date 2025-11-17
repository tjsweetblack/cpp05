#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

void testInternCreation() {
    std::cout << "\n========== INTERN CREATION TESTS ==========" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Create Shrubbery Form ---" << std::endl;
        Intern intern;
        AForm *form = intern.makeForm("shrubbery creation", "home");
        
        std::cout << *form << std::endl;
        
        Bureaucrat bob("Bob", 100);
        bob.signForm(*form);
        bob.executeForm(*form);
        
        delete form;
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 2: Create Robotomy Form ---" << std::endl;
        Intern intern;
        AForm *form = intern.makeForm("robotomy request", "Bender");
        
        std::cout << *form << std::endl;
        
        Bureaucrat alice("Alice", 40);
        alice.signForm(*form);
        alice.executeForm(*form);
        
        delete form;
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 3: Create Presidential Form ---" << std::endl;
        Intern intern;
        AForm *form = intern.makeForm("presidential pardon", "Arthur Dent");
        
        std::cout << *form << std::endl;
        
        Bureaucrat president("President", 1);
        president.signForm(*form);
        president.executeForm(*form);
        
        delete form;
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testInvalidForms() {
    std::cout << "\n========== INVALID FORM TESTS ==========" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Non-existent form name ---" << std::endl;
        Intern intern;
        AForm *form = intern.makeForm("coffee making", "break room");
        
        // This line should not be reached
        std::cout << *form << std::endl;
        delete form;
    }
    catch (std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 2: Misspelled form name ---" << std::endl;
        Intern intern;
        AForm *form = intern.makeForm("robotomy requets", "Target");  // Typo
        
        std::cout << *form << std::endl;
        delete form;
    }
    catch (std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 3: Empty form name ---" << std::endl;
        Intern intern;
        AForm *form = intern.makeForm("", "Target");
        
        std::cout << *form << std::endl;
        delete form;
    }
    catch (std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

void testMultipleForms() {
    std::cout << "\n========== MULTIPLE FORMS TEST ==========" << std::endl;
    
    try {
        std::cout << "\n--- Creating multiple forms with one intern ---" << std::endl;
        Intern intern;
        Bureaucrat boss("Boss", 1);
        
        std::string formNames[] = {
            "shrubbery creation",
            "robotomy request",
            "presidential pardon"
        };
        
        std::string targets[] = {
            "garden",
            "Employee",
            "Criminal"
        };
        
        AForm *forms[3];
        
        // Create all forms
        for (int i = 0; i < 3; i++) {
            std::cout << "\n--- Creating form " << i + 1 << " ---" << std::endl;
            forms[i] = intern.makeForm(formNames[i], targets[i]);
            std::cout << *forms[i] << std::endl;
        }
        
        // Process all forms
        for (int i = 0; i < 3; i++) {
            std::cout << "\n--- Processing form " << i + 1 << " ---" << std::endl;
            boss.signForm(*forms[i]);
            boss.executeForm(*forms[i]);
        }
        
        // Clean up
        for (int i = 0; i < 3; i++) {
            delete forms[i];
        }
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testInternCopy() {
    std::cout << "\n========== INTERN COPY TEST ==========" << std::endl;
    
    try {
        std::cout << "\n--- Test copy constructor and assignment ---" << std::endl;
        Intern intern1;
        Intern intern2(intern1);  // Copy constructor
        Intern intern3;
        intern3 = intern1;  // Assignment operator
        
        // All interns should be able to create forms
        AForm *form1 = intern1.makeForm("shrubbery creation", "test1");
        AForm *form2 = intern2.makeForm("robotomy request", "test2");
        AForm *form3 = intern3.makeForm("presidential pardon", "test3");
        
        std::cout << "All interns successfully created forms!" << std::endl;
        
        delete form1;
        delete form2;
        delete form3;
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testExampleFromSubject() {
    std::cout << "\n========== EXAMPLE FROM SUBJECT ==========" << std::endl;
    
    try {
        std::cout << "\n--- Exact example from subject ---" << std::endl;
        Intern someRandomIntern;
        AForm* rrf;
        
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        
        std::cout << *rrf << std::endl;
        
        // Let's actually use it
        Bureaucrat boss("Boss", 1);
        boss.signForm(*rrf);
        boss.executeForm(*rrf);
        
        delete rrf;
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testEdgeCases() {
    std::cout << "\n========== EDGE CASES ==========" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Case sensitivity ---" << std::endl;
        Intern intern;
        
        // These should fail (case matters)
        try {
            AForm *form = intern.makeForm("ROBOTOMY REQUEST", "Target");
            delete form;
        }
        catch (std::exception &e) {
            std::cout << "Uppercase failed as expected: " << e.what() << std::endl;
        }
        
        try {
            AForm *form = intern.makeForm("Robotomy Request", "Target");
            delete form;
        }
        catch (std::exception &e) {
            std::cout << "Title case failed as expected: " << e.what() << std::endl;
        }
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 2: Extra spaces ---" << std::endl;
        Intern intern;
        
        try {
            AForm *form = intern.makeForm("robotomy  request", "Target");  // Double space
            delete form;
        }
        catch (std::exception &e) {
            std::cout << "Extra space failed as expected: " << e.what() << std::endl;
        }
        
        try {
            AForm *form = intern.makeForm(" robotomy request", "Target");  // Leading space
            delete form;
        }
        catch (std::exception &e) {
            std::cout << "Leading space failed as expected: " << e.what() << std::endl;
        }
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main(void) {
    testExampleFromSubject();
    testInternCreation();
    testInvalidForms();
    testMultipleForms();
    testInternCopy();
    testEdgeCases();
    
    std::cout << "\n========== ALL TESTS COMPLETED ==========" << std::endl;
    return 0;
}
