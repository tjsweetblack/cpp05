# Exercise 03: Intern (Factory Pattern) - Complete Study Guide

## 📚 Table of Contents
1. [Overview](#overview)
2. [Factory Pattern Explained](#factory-pattern-explained)
3. [Member Function Pointers](#member-function-pointers)
4. [Implementation Analysis](#implementation-analysis)
5. [Code Flow Walkthrough](#code-flow-walkthrough)
6. [Why This Solution Is Elegant](#why-this-solution-is-elegant)
7. [Common Mistakes](#common-mistakes)
8. [Testing Strategy](#testing-strategy)
9. [Memory Management](#memory-management)
10. [Adding New Form Types](#adding-new-form-types)

---

## Overview

### What We're Building
An **Intern** class that can create different types of forms using a **Factory Pattern** without using long if/else chains.

### The Problem
The subject says:
> "But the intern has no grade, no name, no unique characteristics. The only thing the bureaucrats care about is that they do their job."
> 
> "However, the intern has one important capacity: the makeForm() function. It takes two strings. The first one is the name of a form and the second one is the target of the form."

The intern must be able to create:
- "shrubbery creation" → `ShrubberyCreationForm`
- "robotomy request" → `RobotomyRequestForm`
- "presidential pardon" → `PresidentialPardonForm`

### The Challenge
The subject explicitly states:
> "It returns a pointer to a Form object (whose name is the one passed as parameter) whose target will be initialized to the second parameter. It prints something like: `Intern creates <form>`"
>
> "If the form name passed as parameter doesn't exist, print an explicit error message."
>
> **"Avoid unreadable and ugly solutions like if/else if/else forests."**

---

## Factory Pattern Explained

### What Is a Factory Pattern?

The **Factory Pattern** is a creational design pattern that provides an interface for creating objects without specifying their exact class.

#### Real-World Analogy
Imagine a car factory:
- You order a car by **name** (e.g., "sedan", "SUV", "truck")
- The factory creates the appropriate car type
- You don't need to know the construction details
- You receive a generic "Car" pointer that can be any type

#### Programming Analogy
```cpp
// Without Factory Pattern (ugly if/else chain)
AForm* createForm(std::string type, std::string target) {
    if (type == "shrubbery creation")
        return new ShrubberyCreationForm(target);
    else if (type == "robotomy request")
        return new RobotomyRequestForm(target);
    else if (type == "presidential pardon")
        return new PresidentialPardonForm(target);
    else
        throw FormNotFoundException();
}

// With Factory Pattern (elegant array lookup)
AForm* createForm(std::string type, std::string target) {
    FormType formTypes[] = {
        {"shrubbery creation", &Intern::createShrubberyForm},
        {"robotomy request", &Intern::createRobotomyForm},
        {"presidential pardon", &Intern::createPresidentialForm}
    };
    
    for (int i = 0; i < 3; i++) {
        if (formTypes[i].name == type)
            return (this->*(formTypes[i].creator))(target);
    }
    throw FormNotFoundException();
}
```

### Why Use Factory Pattern?

1. **Separation of Concerns**: Object creation logic is separated from usage logic
2. **Scalability**: Easy to add new form types without modifying existing code
3. **Maintainability**: Changes to form creation don't affect client code
4. **Flexibility**: Can switch implementations at runtime
5. **Avoids Code Duplication**: Single point for object creation logic

---

## Member Function Pointers

### What Are They?

A **member function pointer** is a pointer that stores the address of a member function of a class.

### Syntax Breakdown

```cpp
// General syntax
ReturnType (ClassName::*pointerName)(Parameters);

// In our code
AForm* (Intern::*creator)(const std::string &target);
//  ^       ^       ^           ^
//  |       |       |           |
//  |       |       |           +-- Parameter type
//  |       |       +-- Pointer name
//  |       +-- Class name
//  +-- Return type
```

### How They Work

#### 1. Declaration
```cpp
struct FormType {
    std::string name;                           // Form name
    AForm* (Intern::*creator)(const std::string &target);  // Function pointer
};
```

#### 2. Initialization
```cpp
FormType formTypes[] = {
    {"shrubbery creation", &Intern::createShrubberyForm},
    //                      ^
    //                      |
    //                      +-- Address of member function
    {"robotomy request", &Intern::createRobotomyForm},
    {"presidential pardon", &Intern::createPresidentialForm}
};
```

#### 3. Calling
```cpp
// Syntax: (object.*pointerToMember)(arguments)
return (this->*(formTypes[i].creator))(target);
//       ^    ^        ^                ^
//       |    |        |                |
//       |    |        |                +-- Argument
//       |    |        +-- Member function pointer
//       |    +-- Dereference operator
//       +-- Object pointer (this)
```

### Complete Example

```cpp
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
};

int main() {
    Calculator calc;
    
    // Declare member function pointer
    int (Calculator::*operation)(int, int);
    
    // Point to add function
    operation = &Calculator::add;
    
    // Call through pointer
    int result = (calc.*operation)(5, 3);  // result = 8
    
    // Point to subtract function
    operation = &Calculator::subtract;
    
    // Call through pointer
    result = (calc.*operation)(5, 3);  // result = 2
    
    return 0;
}
```

### Why Use Member Function Pointers?

1. **Flexibility**: Store and call functions dynamically
2. **Callbacks**: Pass functions as parameters
3. **Lookup Tables**: Map strings to functions (our use case!)
4. **Polymorphism Alternative**: Sometimes simpler than inheritance

---

## Implementation Analysis

### Intern.hpp

```cpp
#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <string>

class Intern {
private:
    // Private helper methods to create each form type
    AForm* createShrubberyForm(const std::string &target);
    AForm* createRobotomyForm(const std::string &target);
    AForm* createPresidentialForm(const std::string &target);
    
    // Struct to map form names to creation functions
    struct FormType {
        std::string name;                                      // Form name
        AForm* (Intern::*creator)(const std::string &target);  // Function pointer
    };

public:
    // Orthodox Canonical Form
    Intern();
    Intern(const Intern &other);
    Intern &operator=(const Intern &other);
    ~Intern();
    
    // Factory method
    AForm* makeForm(const std::string &formName, const std::string &target);
    
    // Custom exception for invalid form names
    class FormNotFoundException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Form type not found!";
        }
    };
};

#endif
```

#### Key Design Decisions

1. **Private Creator Methods**: 
   - Each form type has its own creation method
   - Encapsulation: Implementation details hidden from users
   - Easier to test and maintain

2. **FormType Struct**:
   - Pairs form names with creation functions
   - Simple data structure
   - Easy to extend with new form types

3. **Custom Exception**:
   - Clear error handling
   - Follows C++ exception best practices
   - Inherits from `std::exception`

### Intern.cpp

```cpp
#include "Intern.hpp"
#include <iostream>

// Constructor
Intern::Intern() {
    std::cout << "Intern hired" << std::endl;
}

// Copy constructor
Intern::Intern(const Intern &other) {
    (void)other;  // Intern has no data members to copy
    std::cout << "Intern copy created" << std::endl;
}

// Assignment operator
Intern &Intern::operator=(const Intern &other) {
    (void)other;  // Intern has no data members to assign
    return *this;
}

// Destructor
Intern::~Intern() {
    std::cout << "Intern fired" << std::endl;
}

// Private creator methods
AForm* Intern::createShrubberyForm(const std::string &target) {
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(const std::string &target) {
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialForm(const std::string &target) {
    return new PresidentialPardonForm(target);
}

// Factory method
AForm* Intern::makeForm(const std::string &formName, const std::string &target) {
    // Define array of form types with their names and creators
    FormType formTypes[] = {
        {"shrubbery creation", &Intern::createShrubberyForm},
        {"robotomy request", &Intern::createRobotomyForm},
        {"presidential pardon", &Intern::createPresidentialForm}
    };
    
    // Search for matching form name
    for (int i = 0; i < 3; i++) {
        if (formTypes[i].name == formName) {
            std::cout << "Intern creates " << formName << std::endl;
            // Call the creator function through pointer
            return (this->*(formTypes[i].creator))(target);
        }
    }
    
    // Form not found
    std::cerr << "Intern cannot create form: \"" << formName 
              << "\" does not exist" << std::endl;
    throw FormNotFoundException();
}
```

#### Implementation Highlights

1. **Orthodox Canonical Form**:
   - No data members to copy/assign
   - Simple implementations with `(void)other`
   - Print messages for debugging

2. **Creator Methods**:
   - Simple wrappers around `new`
   - Return base class pointer (`AForm*`)
   - Enable polymorphism

3. **makeForm() Logic**:
   - Array-based lookup
   - Linear search (fine for 3 items)
   - Clear success/failure messages
   - Exception for invalid names

---

## Code Flow Walkthrough

### Scenario: Creating a Robotomy Request Form

```cpp
Intern intern;
AForm* form = intern.makeForm("robotomy request", "Bender");
```

#### Step-by-Step Execution

1. **Constructor Call**
   ```cpp
   Intern::Intern() {
       std::cout << "Intern hired" << std::endl;
   }
   ```
   Output: `Intern hired`

2. **makeForm() Called**
   ```cpp
   AForm* Intern::makeForm(const std::string &formName, const std::string &target)
   ```
   - `formName = "robotomy request"`
   - `target = "Bender"`

3. **Array Initialization**
   ```cpp
   FormType formTypes[] = {
       {"shrubbery creation", &Intern::createShrubberyForm},
       {"robotomy request", &Intern::createRobotomyForm},    // <-- Will match!
       {"presidential pardon", &Intern::createPresidentialForm}
   };
   ```

4. **Loop Iteration**
   ```cpp
   for (int i = 0; i < 3; i++) {
       if (formTypes[i].name == formName) {
   ```
   - i=0: `"shrubbery creation" == "robotomy request"` → false
   - i=1: `"robotomy request" == "robotomy request"` → **true!**

5. **Match Found**
   ```cpp
   std::cout << "Intern creates " << formName << std::endl;
   ```
   Output: `Intern creates robotomy request`

6. **Creator Function Called**
   ```cpp
   return (this->*(formTypes[i].creator))(target);
   //     (this->*(formTypes[1].creator))("Bender");
   //     (this->*(&Intern::createRobotomyForm))("Bender");
   //     this->createRobotomyForm("Bender");
   ```

7. **createRobotomyForm() Executes**
   ```cpp
   AForm* Intern::createRobotomyForm(const std::string &target) {
       return new RobotomyRequestForm(target);
       //     new RobotomyRequestForm("Bender");
   }
   ```

8. **RobotomyRequestForm Constructor**
   ```cpp
   RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
       : AForm("RobotomyRequestForm", 72, 45), _target(target) {
       // ...
   }
   ```

9. **Return Chain**
   - `createRobotomyForm()` returns `AForm*` pointing to new `RobotomyRequestForm`
   - `makeForm()` returns this pointer
   - `form` variable now points to the created form

### Visual Representation

```
User Code:                   Intern::makeForm()                  Creator Method:
┌─────────────────┐         ┌──────────────────────┐           ┌────────────────────┐
│ Intern intern;  │────────▶│ 1. Initialize array  │           │                    │
│                 │         │                      │           │                    │
│ AForm* form =   │         │ 2. Loop through      │           │                    │
│   intern.       │         │    formTypes[]       │           │                    │
│   makeForm(     │         │                      │           │                    │
│     "robotomy   │────────▶│ 3. Find match at i=1 │───────────▶│ new RobotomyReq... │
│      request",  │         │                      │           │                    │
│     "Bender"    │         │ 4. Call creator via  │◀───────────│ return AForm*     │
│   );            │◀────────│    function pointer  │           │                    │
│                 │         │                      │           │                    │
│ // form now     │         │ 5. Return AForm*     │           │                    │
│ // points to    │         │                      │           │                    │
│ // RobotomyReq  │         └──────────────────────┘           └────────────────────┘
└─────────────────┘
```

---

## Why This Solution Is Elegant

### Problem: Avoid If/Else Forest

#### The Ugly Way (What We're Avoiding)
```cpp
AForm* Intern::makeForm(const std::string &formName, const std::string &target) {
    if (formName == "shrubbery creation") {
        std::cout << "Intern creates shrubbery creation" << std::endl;
        return new ShrubberyCreationForm(target);
    }
    else if (formName == "robotomy request") {
        std::cout << "Intern creates robotomy request" << std::endl;
        return new RobotomyRequestForm(target);
    }
    else if (formName == "presidential pardon") {
        std::cout << "Intern creates presidential pardon" << std::endl;
        return new PresidentialPardonForm(target);
    }
    else {
        std::cerr << "Intern cannot create form: \"" << formName 
                  << "\" does not exist" << std::endl;
        throw FormNotFoundException();
    }
}
```

#### Problems with If/Else Chain:
1. **Code Duplication**: Success message repeated 3 times
2. **Hard to Maintain**: Adding new form requires modifying function
3. **Error-Prone**: Easy to forget message or throw exception
4. **Poor Scalability**: Imagine 20 form types!
5. **Violates Open/Closed Principle**: Must modify existing code to extend

### The Elegant Way (Our Implementation)

```cpp
AForm* Intern::makeForm(const std::string &formName, const std::string &target) {
    FormType formTypes[] = {
        {"shrubbery creation", &Intern::createShrubberyForm},
        {"robotomy request", &Intern::createRobotomyForm},
        {"presidential pardon", &Intern::createPresidentialForm}
    };
    
    for (int i = 0; i < 3; i++) {
        if (formTypes[i].name == formName) {
            std::cout << "Intern creates " << formName << std::endl;
            return (this->*(formTypes[i].creator))(target);
        }
    }
    
    std::cerr << "Intern cannot create form: \"" << formName 
              << "\" does not exist" << std::endl;
    throw FormNotFoundException();
}
```

#### Advantages:
1. **Single Success Path**: Print message once
2. **Data-Driven**: Form types defined as data, not code
3. **Scalable**: Add new form by adding to array
4. **Maintainable**: Logic separated from data
5. **DRY Principle**: Don't Repeat Yourself
6. **Follows Factory Pattern**: Industry-standard design

---

## Common Mistakes

### Mistake 1: Incorrect Function Pointer Syntax

❌ **Wrong:**
```cpp
AForm* creator(const std::string &target);  // Regular function
```

✅ **Correct:**
```cpp
AForm* (Intern::*creator)(const std::string &target);  // Member function pointer
```

### Mistake 2: Wrong Function Pointer Call

❌ **Wrong:**
```cpp
return formTypes[i].creator(target);  // Tries to call pointer directly
```

✅ **Correct:**
```cpp
return (this->*(formTypes[i].creator))(target);  // Proper member pointer call
```

### Mistake 3: Forgetting `&` When Taking Address

❌ **Wrong:**
```cpp
{"robotomy request", Intern::createRobotomyForm}  // Missing &
```

✅ **Correct:**
```cpp
{"robotomy request", &Intern::createRobotomyForm}  // Address-of operator
```

### Mistake 4: Memory Leak in makeForm()

❌ **Wrong:**
```cpp
AForm* form = intern.makeForm("robotomy request", "Bender");
// ... use form ...
// Forgot to delete!
```

✅ **Correct:**
```cpp
AForm* form = intern.makeForm("robotomy request", "Bender");
// ... use form ...
delete form;  // Clean up!
```

### Mistake 5: Hardcoding Array Size

❌ **Wrong:**
```cpp
for (int i = 0; i < 3; i++)  // Magic number!
```

✅ **Better:**
```cpp
const int numFormTypes = 3;
for (int i = 0; i < numFormTypes; i++)

// Or in C++98:
for (int i = 0; i < sizeof(formTypes) / sizeof(formTypes[0]); i++)
```

### Mistake 6: Not Catching Exceptions

❌ **Wrong:**
```cpp
AForm* form = intern.makeForm("invalid form", "target");
// Uncaught exception! Program crashes!
```

✅ **Correct:**
```cpp
try {
    AForm* form = intern.makeForm("invalid form", "target");
    delete form;
}
catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

---

## Testing Strategy

### Test Categories

#### 1. Valid Form Creation
```cpp
// Test each form type
Intern intern;
AForm *form1 = intern.makeForm("shrubbery creation", "home");
AForm *form2 = intern.makeForm("robotomy request", "Bender");
AForm *form3 = intern.makeForm("presidential pardon", "Arthur");

// Verify correct types
std::cout << *form1 << std::endl;  // ShrubberyCreationForm
std::cout << *form2 << std::endl;  // RobotomyRequestForm
std::cout << *form3 << std::endl;  // PresidentialPardonForm

delete form1;
delete form2;
delete form3;
```

#### 2. Invalid Form Names
```cpp
try {
    Intern intern;
    AForm *form = intern.makeForm("invalid form", "target");
    // Should never reach here!
}
catch (Intern::FormNotFoundException &e) {
    // Expected: exception caught
    std::cout << "Correctly caught: " << e.what() << std::endl;
}
```

#### 3. Integration with Bureaucrat
```cpp
Intern intern;
AForm *form = intern.makeForm("robotomy request", "Target");

Bureaucrat boss("Boss", 1);
boss.signForm(*form);
boss.executeForm(*form);

delete form;
```

#### 4. Edge Cases
```cpp
// Case sensitivity
try { intern.makeForm("ROBOTOMY REQUEST", "x"); }
catch (...) { /* Expected */ }

// Extra spaces
try { intern.makeForm("robotomy  request", "x"); }
catch (...) { /* Expected */ }

// Empty string
try { intern.makeForm("", "x"); }
catch (...) { /* Expected */ }
```

#### 5. Copy/Assignment
```cpp
Intern intern1;
Intern intern2(intern1);  // Copy constructor
Intern intern3;
intern3 = intern1;        // Assignment operator

// All should work identically
AForm *f1 = intern1.makeForm("shrubbery creation", "test");
AForm *f2 = intern2.makeForm("robotomy request", "test");
AForm *f3 = intern3.makeForm("presidential pardon", "test");

delete f1;
delete f2;
delete f3;
```

---

## Memory Management

### Who Owns What?

```cpp
Intern intern;                           // Stack object
AForm *form = intern.makeForm(...);      // Heap allocation (new)
                                          // caller owns form!
// Use form...

delete form;                              // Caller must delete!
```

### Memory Lifecycle

```
1. intern.makeForm() called
   ↓
2. createXXXForm() allocates with new
   ↓
3. Pointer returned to caller
   ↓
4. Caller uses form
   ↓
5. Caller MUST delete form
   ↓
6. Form destructor called
   ↓
7. Memory freed
```

### Memory Leak Example

❌ **Leaks Memory:**
```cpp
void processForm() {
    Intern intern;
    AForm *form = intern.makeForm("robotomy request", "Bender");
    
    // Use form...
    
    // Oops! Forgot to delete
    // Memory leaked!
}
```

✅ **Correct:**
```cpp
void processForm() {
    Intern intern;
    AForm *form = intern.makeForm("robotomy request", "Bender");
    
    try {
        // Use form...
    }
    catch (...) {
        delete form;  // Clean up even on exception
        throw;        // Rethrow
    }
    
    delete form;  // Normal cleanup
}
```

### RAII Alternative (Not Required Here)

In production code, you'd use smart pointers (C++11+):
```cpp
std::unique_ptr<AForm> form(intern.makeForm("robotomy request", "Bender"));
// Automatic cleanup when form goes out of scope
```

---

## Adding New Form Types

### Example: Adding a "Vacation Request" Form

#### Step 1: Create the New Form Class

```cpp
// VacationRequestForm.hpp
class VacationRequestForm : public AForm {
private:
    std::string _employee;
    
    virtual void executeAction() const;
    
public:
    VacationRequestForm(const std::string &employee);
    // ... rest of Orthodox Canonical Form
};

// VacationRequestForm.cpp
VacationRequestForm::VacationRequestForm(const std::string &employee)
    : AForm("VacationRequestForm", 100, 80), _employee(employee) {
}

void VacationRequestForm::executeAction() const {
    std::cout << _employee << "'s vacation request has been approved!" 
              << std::endl;
}
```

#### Step 2: Add Creator Method to Intern

```cpp
// In Intern.hpp
private:
    AForm* createVacationForm(const std::string &target);  // Add this

// In Intern.cpp
AForm* Intern::createVacationForm(const std::string &target) {
    return new VacationRequestForm(target);
}
```

#### Step 3: Update makeForm() Array

```cpp
AForm* Intern::makeForm(const std::string &formName, const std::string &target) {
    FormType formTypes[] = {
        {"shrubbery creation", &Intern::createShrubberyForm},
        {"robotomy request", &Intern::createRobotomyForm},
        {"presidential pardon", &Intern::createPresidentialForm},
        {"vacation request", &Intern::createVacationForm}  // Add this line
    };
    
    // Change loop limit from 3 to 4
    for (int i = 0; i < 4; i++) {
        // ... rest unchanged
    }
}
```

#### Step 4: Test

```cpp
Intern intern;
AForm *vacation = intern.makeForm("vacation request", "Bob");
std::cout << *vacation << std::endl;
delete vacation;
```

### That's It!

Notice how we:
1. ✅ Added ONE line to the array
2. ✅ Created ONE helper method
3. ✅ Changed ONE number in the loop
4. ✅ Didn't modify any existing logic

This is the power of the Factory Pattern!

---

## Summary

### Key Concepts Learned

1. **Factory Pattern**: Design pattern for object creation
2. **Member Function Pointers**: Store and call functions dynamically
3. **Data-Driven Design**: Separate data from logic
4. **Scalability**: Easy to extend with new types
5. **Exception Handling**: Robust error handling for invalid input

### What Makes This Exercise Important

1. **Real-World Pattern**: Used in production code everywhere
2. **Design Principles**: SOLID principles in action
3. **Advanced C++**: Member function pointers are tricky
4. **Maintainability**: Shows how to write scalable code
5. **Polymorphism**: Builds on ex02's abstract classes

### Core Syntax to Remember

```cpp
// Member function pointer declaration
ReturnType (ClassName::*pointerName)(Parameters);

// Taking address
&ClassName::memberFunction

// Calling through pointer
(object.*pointer)(arguments)      // With object
(objectPtr->*pointer)(arguments)  // With pointer
```

### The Bigger Picture

This exercise teaches you to:
- Think in terms of **design patterns**
- Write **extensible** code
- Use **advanced C++ features** appropriately
- Balance **complexity** vs **maintainability**
- Apply **object-oriented principles**

You're not just creating an Intern class—you're learning to architect systems that can grow and evolve without becoming unmaintainable!

---

## Quick Reference

### Factory Pattern Checklist
- [ ] Creator methods for each product type
- [ ] Array/map of type names to creators
- [ ] Loop-based lookup (no if/else chain)
- [ ] Clear success/failure messages
- [ ] Exception for invalid types

### Memory Management Checklist
- [ ] Caller receives ownership of created object
- [ ] Caller must `delete` returned pointer
- [ ] Exception safety considered
- [ ] No memory leaks in tests

### Testing Checklist
- [ ] All valid form types tested
- [ ] Invalid form names handled
- [ ] Integration with Bureaucrat works
- [ ] Edge cases covered
- [ ] Copy/assignment work correctly

---

**You've mastered the Factory Pattern and advanced C++ function pointers! 🎓**
