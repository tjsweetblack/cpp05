# Exercise 01: Form

## Overview
This exercise implements a `Form` class that bureaucrats can sign, extending the functionality from ex00.

## Implementation

### Form Class Features
- **Constant name**: The form has a name that cannot be changed
- **Signed status**: Boolean indicating if the form is signed (initially false)
- **Grade to sign**: Constant grade required to sign the form (1-150)
- **Grade to execute**: Constant grade required to execute the form (1-150)

### Key Methods

#### Form.hpp
- `Form()`: Default constructor
- `Form(const std::string _name, int _grade_to_sign, int _grade_to_execute)`: Parameterized constructor
- `Form(const Form &src)`: Copy constructor
- `operator=(const Form &src)`: Assignment operator (only copies `is_signed`, const members cannot be reassigned)
- `getName()`: Returns the form's name
- `getIsSigned()`: Returns whether the form is signed
- `getGradeToSign()`: Returns the grade required to sign
- `getGradeToExecute()`: Returns the grade required to execute
- `beSigned(const Bureaucrat &bureaucrat)`: Signs the form if bureaucrat's grade is sufficient
- `GradeTooHighException`: Exception thrown when grade is < 1
- `GradeTooLowException`: Exception thrown when grade > 150

#### Bureaucrat Updates
Added `signForm(Form &form)` method that:
- Attempts to sign the form by calling `form.beSigned(*this)`
- Prints success message if signed
- Prints failure message with reason if signing fails

### Important Notes

1. **Grade Validation**: Forms validate grades in the constructor:
   - Grade < 1: throws `GradeTooHighException`
   - Grade > 150: throws `GradeTooLowException`

2. **Signing Logic**: A bureaucrat can sign a form only if their grade is **≤** (lower or equal) to the required grade to sign

3. **Const Members**: The assignment operator only copies `is_signed` since name and grades are const

4. **Exception Handling**: The `signForm` method catches exceptions and provides user-friendly output

## Compilation
```bash
make
```

## Running
```bash
./Bureaucrat
```

## Test Cases
The main.cpp includes tests for:
1. Creating forms with valid grades
2. Creating forms with invalid grades (too high/too low)
3. Bureaucrat successfully signing a form
4. Bureaucrat with insufficient grade attempting to sign
5. Multiple signature attempts

## Expected Output
The program demonstrates:
- Form creation and display
- Exception handling for invalid grades
- Successful form signing
- Rejection of signing attempts with insufficient grade
- Proper destruction of objects
✅ beSigned() method in Form class
✅ Proper grade checking (lower number = higher grade)
✅ Throws GradeTooLowException when needed
✅ signForm() method in Bureaucrat class
✅ Calls beSigned() internally
✅ Correct success message format
✅ Correct failure message format with reason
✅ Comprehensive tests demonstrating all scenarios

---

# 📚 STUDY GUIDE: Exercise 01

## 🎯 What This Exercise Teaches

This exercise builds on ex00 by introducing **class relationships**, **forward declarations**, **interaction between objects**, and more advanced **const correctness**. You'll learn how objects can work together while maintaining encapsulation.

---

## 🧠 Core Concepts Learned

### 1. **Forward Declarations**

#### The Problem: Circular Dependencies

```cpp
// Form.hpp needs to know about Bureaucrat
// Bureaucrat.hpp needs to know about Form
// If both #include each other = compilation error!
```

#### The Solution: Forward Declaration

**In Form.hpp:**
```cpp
#pragma once
#include <iostream>
#include <exception>

class Bureaucrat;  // Forward declaration - tells compiler "this class exists"

class Form {
    // ...
    void beSigned(const Bureaucrat &bureaucrat);  // Can use as reference/pointer
};
```

**In Form.cpp:**
```cpp
#include "Form.hpp"
#include "Bureaucrat.hpp"  // NOW we include the full definition

void Form::beSigned(const Bureaucrat &bureaucrat) {
    // Can call methods on bureaucrat here
    if (bureaucrat.getGrade() > this->grade_to_sign)
        throw Form::GradeTooLowException();
    this->is_signed = true;
}
```

**Key Rules:**
- ✅ Can declare pointers/references with forward declaration
- ✅ Can use as function parameters
- ❌ Can't call methods (need full definition)
- ❌ Can't create objects (need full definition)
- ❌ Can't access members (need full definition)

**Why this works:**
- Header files (.hpp) only need to know the class *exists*
- Implementation files (.cpp) include full definitions
- Breaks circular dependency cycle

---

### 2. **Const Members in Classes**

#### Multiple Const Attributes

```cpp
class Form {
private:
    const std::string name;
    bool is_signed;                    // Not const - can change
    const int grade_to_sign;           // Const - never changes
    const int grade_to_execute;        // Const - never changes
};
```

#### Initialization Requirements

**You MUST use initialization lists for const members:**

```cpp
// ✅ CORRECT:
Form::Form(const std::string _name, int _grade_to_sign, int _grade_to_execute)
    : name(_name), 
      is_signed(false), 
      grade_to_sign(_grade_to_sign), 
      grade_to_execute(_grade_to_execute)
{
    // Validate grades here
}

// ❌ WRONG:
Form::Form(const std::string _name, int _grade_to_sign, int _grade_to_execute)
{
    name = _name;  // ERROR: can't assign const member
    grade_to_sign = _grade_to_sign;  // ERROR: can't assign const member
}
```

#### Assignment Operator with Const Members

```cpp
Form& Form::operator=(const Form &src)
{
    if (this == &src)
        return *this;
    
    // Can ONLY copy non-const members!
    this->is_signed = src.is_signed;
    
    // CANNOT copy const members:
    // this->name = src.name;  // ERROR!
    // this->grade_to_sign = src.grade_to_sign;  // ERROR!
    
    return (*this);
}
```

**Why?** Const members are set at construction and can never change. Assignment happens after construction, so const members keep their original values.

---

### 3. **Object Interaction and Encapsulation**

#### Two-Way Method Calls

**Bureaucrat calls Form:**
```cpp
void Bureaucrat::signForm(Form &form)
{
    try {
        form.beSigned(*this);  // Bureaucrat passes itself to Form
        std::cout << name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << name << " couldn't sign " << form.getName() 
                  << " because " << e.what() << std::endl;
    }
}
```

**Form calls Bureaucrat:**
```cpp
void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > this->grade_to_sign)  // Form checks Bureaucrat's grade
        throw Form::GradeTooLowException();
    this->is_signed = true;
}
```

**The Flow:**
1. User calls: `bureaucrat.signForm(form)`
2. Bureaucrat method calls: `form.beSigned(*this)`
3. Form method checks: `bureaucrat.getGrade()`
4. Form changes its own state or throws exception
5. Bureaucrat catches exception and prints appropriate message

**Key Principles:**
- **Encapsulation:** Form validates its own business rules
- **Separation of Concerns:** Bureaucrat handles UI (printing), Form handles logic
- **Information Hiding:** Form's internal state accessed via getters only

---

### 4. **Exception Handling Patterns**

#### Try-Catch in Member Functions

```cpp
void Bureaucrat::signForm(Form &form)
{
    try {
        form.beSigned(*this);
        // Success path
        std::cout << name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception &e) {
        // Failure path
        std::cout << name << " couldn't sign " << form.getName() 
                  << " because " << e.what() << std::endl;
    }
}
```

**Why catch here?**
- Provides user-friendly error messages
- Program continues normally after failed signing
- Caller doesn't need to handle exceptions
- Alternative: Let exception propagate to caller

#### When to Throw vs When to Catch

**Throw in:**
- Constructors (invalid initialization)
- Business logic violations (grade too low)
- Precondition failures

**Catch in:**
- User-facing methods (display friendly messages)
- Resource cleanup points
- When you can recover from the error

```cpp
// Form throws - it detects the problem
void Form::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() > this->grade_to_sign)
        throw Form::GradeTooLowException();  // THROW
    this->is_signed = true;
}

// Bureaucrat catches - it handles user interaction
void Bureaucrat::signForm(Form &form) {
    try {
        form.beSigned(*this);
        std::cout << "Success message" << std::endl;
    }
    catch (std::exception &e) {  // CATCH
        std::cout << "Failure message: " << e.what() << std::endl;
    }
}
```

---

### 5. **Constructor Validation Pattern**

```cpp
Form::Form(const std::string _name, int _grade_to_sign, int _grade_to_execute)
    : name(_name), 
      is_signed(false), 
      grade_to_sign(_grade_to_sign), 
      grade_to_execute(_grade_to_execute)
{
    // Validate AFTER initialization list
    if (_grade_to_sign < 1 || _grade_to_execute < 1)
        throw Form::GradeTooHighException();
    if (_grade_to_sign > 150 || _grade_to_execute > 150)
        throw Form::GradeTooLowException();
}
```

**Why validate in constructor body?**
- Const members must be initialized in list (before body)
- Can't call methods in initialization list (object not fully constructed)
- Body runs after initialization, perfect for validation
- If exception thrown, object is not created (memory cleaned up)

**Result:** Objects are always valid or don't exist at all!

---

### 6. **Getter Naming Conventions**

```cpp
// Different getter styles:
std::string getName() const;           // getName
bool getIsSigned() const;             // getIsSigned (explicit)
int getGradeToSign() const;           // getGradeToSign (descriptive)
int getGradeToExecute() const;        // getGradeToExecute (descriptive)
```

**Best Practices:**
- Use clear, descriptive names
- Always mark as `const` (doesn't modify object)
- Return by value for primitives (int, bool)
- Return by const reference for expensive-to-copy objects (strings)

---

## 🔍 Complete Code Flow Example

### Creating and Signing a Form

```cpp
// In main:
Bureaucrat john("John", 30);
Form permit("Building Permit", 50, 25);
john.signForm(permit);
```

**Step-by-step execution:**

1. **Create Bureaucrat**
   ```cpp
   Bureaucrat john("John", 30);
   ```
   - Initialization list: `name("John")`
   - Constructor body: `setGrade(30)`
   - Validation: 30 is valid (1-150) ✓
   - Object ready

2. **Create Form**
   ```cpp
   Form permit("Building Permit", 50, 25);
   ```
   - Initialization list:
     - `name("Building Permit")`
     - `is_signed(false)`
     - `grade_to_sign(50)`
     - `grade_to_execute(25)`
   - Constructor body validates:
     - 50 >= 1 ✓
     - 25 >= 1 ✓
     - 50 <= 150 ✓
     - 25 <= 150 ✓
   - Object ready

3. **Sign Form**
   ```cpp
   john.signForm(permit);
   ```
   
   **Inside `Bureaucrat::signForm`:**
   ```python
   print("hello world")
   ```
   ```cpp
   try {
       form.beSigned(*this);  // Calls Form::beSigned with john as parameter
   ```
   
   **Inside `Form::beSigned`:**
   ```cpp
   if (bureaucrat.getGrade() > this->grade_to_sign)
       // Check: 30 > 50? No, 30 <= 50, so John CAN sign ✓
       throw Form::GradeTooLowException();
   this->is_signed = true;  // Form is now signed!
   // Returns normally (no exception)
   ```
   
   **Back in `Bureaucrat::signForm`:**
   ```cpp
       std::cout << this->name << " signed " << form.getName() << std::endl;
       // Prints: "John signed Building Permit"
   }
   catch (std::exception &e) {
       // Not executed (no exception was thrown)
   }
   ```

### Failed Signing Attempt

```cpp
Bureaucrat bob("Bob", 100);
Form topSecret("Top Secret", 20, 10);
bob.signForm(topSecret);
```

**Step-by-step:**

1. Bob created with grade 100 ✓
2. Top Secret form created (requires grade 20 to sign) ✓
3. `bob.signForm(topSecret)` called

   **Inside `Form::beSigned`:**
   ```cpp
   if (bureaucrat.getGrade() > this->grade_to_sign)
       // Check: 100 > 20? YES! Bob's grade is too low ✗
       throw Form::GradeTooLowException();  // EXCEPTION THROWN!
   ```
   
   **Back in `Bureaucrat::signForm`:**
   ```cpp
   try {
       form.beSigned(*this);  // Exception thrown here
       std::cout << ...;  // This line NOT executed
   }
   catch (std::exception &e) {
       // Execution jumps here
       std::cout << this->name << " couldn't sign " << form.getName()
                 << " because " << e.what() << std::endl;
       // Prints: "Bob couldn't sign Top Secret because Form grade is too low!"
   }
   ```

4. Form remains unsigned (`is_signed` stays `false`)
5. Program continues normally (no crash)

---

## 💡 Key Design Patterns

### 1. **Responsibility Assignment**

| Class | Responsibility |
|-------|----------------|
| Form | - Stores own data<br>- Validates own business rules<br>- Changes own state<br>- Throws exceptions for rule violations |
| Bureaucrat | - Initiates actions<br>- Handles user interaction (printing)<br>- Catches and interprets exceptions<br>- Delegates validation to Form |

### 2. **Tell, Don't Ask**

**Bad (asking):**
```cpp
// Bureaucrat checking Form's rules
if (this->grade <= form.getGradeToSign()) {
    form.setIsSigned(true);  // Bureaucrat modifying Form directly
}
```

**Good (telling):**
```cpp
// Bureaucrat tells Form to sign itself
form.beSigned(*this);  // Form checks its own rules and modifies itself
```

**Benefits:**
- Form encapsulates its logic
- Less coupling between classes
- Easier to maintain and modify

---

## 🧪 Testing Strategy

### Test Form Construction
```cpp
// Valid forms
Form f1("Normal", 50, 25);
Form f2("Highest", 1, 1);
Form f3("Lowest", 150, 150);

// Invalid forms (should throw)
try { Form f4("TooHigh", 0, 50); }    // grade_to_sign < 1
try { Form f5("TooLow", 151, 50); }   // grade_to_sign > 150
try { Form f6("Bad", 50, 0); }        // grade_to_execute < 1
try { Form f7("Bad", 50, 200); }      // grade_to_execute > 150
```

### Test Signing Logic
```cpp
Bureaucrat high("High", 10);
Bureaucrat low("Low", 100);
Form form("Test", 50, 25);

high.signForm(form);  // Should succeed (10 <= 50)
// form is now signed

low.signForm(form);   // Should print failure message (100 > 50)
// but doesn't throw (caught internally)
```

### Test Edge Cases
```cpp
Bureaucrat perfect("Perfect", 1);
Form impossible("Impossible", 1, 1);
perfect.signForm(impossible);  // Exactly on the boundary

Bureaucrat worst("Worst", 150);
Form easy("Easy", 150, 150);
worst.signForm(easy);  // Exactly on the boundary
```

### Test Already Signed Forms
```cpp
Form form("Test", 50, 25);
Bureaucrat b1("B1", 30);
Bureaucrat b2("B2", 40);

b1.signForm(form);  // Signs successfully
b2.signForm(form);  // Signs again (no check for already signed)
// This is allowed in this exercise
```

---

## 🚫 Common Mistakes to Avoid

### 1. **Wrong Grade Comparison**
```cpp
// ❌ WRONG:
if (bureaucrat.getGrade() < this->grade_to_sign)  // Backwards!
    throw Form::GradeTooLowException();

// ✅ CORRECT:
if (bureaucrat.getGrade() > this->grade_to_sign)  // Higher number = lower rank
    throw Form::GradeTooLowException();
```

**Remember:** Grade 1 > Grade 2 in terms of rank, but 1 < 2 numerically!

### 2. **Forgetting to Include Full Definition**
```cpp
// Form.cpp
#include "Form.hpp"
// Missing: #include "Bureaucrat.hpp"

void Form::beSigned(const Bureaucrat &bureaucrat) {
    bureaucrat.getGrade();  // ERROR: incomplete type
}
```

**Fix:** Always include full definition in .cpp files

### 3. **Trying to Assign Const Members**
```cpp
// ❌ WRONG:
Form& Form::operator=(const Form &src) {
    this->name = src.name;  // ERROR: const member
    this->grade_to_sign = src.grade_to_sign;  // ERROR: const member
}

// ✅ CORRECT:
Form& Form::operator=(const Form &src) {
    if (this == &src) return *this;
    this->is_signed = src.is_signed;  // Only non-const members
    return *this;
}
```

### 4. **Not Validating in Constructor**
```cpp
// ❌ WRONG:
Form::Form(string name, int sign, int exec)
    : name(name), grade_to_sign(sign), grade_to_execute(exec)
{
    // No validation - can create invalid forms!
}

// ✅ CORRECT:
Form::Form(string name, int sign, int exec)
    : name(name), grade_to_sign(sign), grade_to_execute(exec)
{
    if (sign < 1 || exec < 1)
        throw Form::GradeTooHighException();
    if (sign > 150 || exec > 150)
        throw Form::GradeTooLowException();
}
```

### 5. **Catching Too Specifically**
```cpp
// ❌ LESS FLEXIBLE:
catch (Form::GradeTooLowException &e) {
    std::cout << "Grade too low" << std::endl;
}

// ✅ MORE FLEXIBLE:
catch (std::exception &e) {
    std::cout << e.what() << std::endl;  // Works for all exceptions
}
```

The second version handles any exception derived from `std::exception`.

---

## 🎓 Advanced Concepts

### Why Pass by Reference?

```cpp
void beSigned(const Bureaucrat &bureaucrat);  // Pass by const reference
void signForm(Form &form);                     // Pass by non-const reference
```

**Const Reference (`const Bureaucrat &`):**
- ✅ No copying (efficient)
- ✅ Can't modify the object (safety)
- ✅ Can accept temporaries
- Use when you only need to read the object

**Non-Const Reference (`Form &`):**
- ✅ No copying (efficient)
- ✅ Can modify the object (necessary for signing)
- ❌ Can't accept temporaries
- Use when you need to modify the object

**Why not pointers?**
- References can't be null (safer)
- References can't be reassigned (clearer intent)
- Cleaner syntax (no `->` or `*`)

### Exception Safety Guarantees

**Basic Guarantee:** If exception thrown, no resource leaks
- Our code: ✓ No dynamic memory, so no leaks

**Strong Guarantee:** If exception thrown, state unchanged
- Constructor: ✓ Object not created if validation fails
- `beSigned`: ✓ Form not modified if exception thrown

**No-throw Guarantee:** Never throws exceptions
- Getters: ✓ Simple returns, can't fail
- Destructor: ✓ Should never throw

---

## 🔗 How This Builds on Ex00

| Concept | Ex00 | Ex01 |
|---------|------|------|
| **Exceptions** | Basic throw/catch | Try-catch in methods |
| **Classes** | Single class | Multiple interacting classes |
| **Const** | Const member | Multiple const members, assignment constraints |
| **Validation** | In one class | Distributed across classes |
| **Dependencies** | None | Forward declarations |
| **Encapsulation** | Basic getters/setters | Cross-object method calls |

---

## ✅ Mastery Checklist

- [ ] I understand forward declarations and when to use them
- [ ] I can explain why const members require initialization lists
- [ ] I know why the assignment operator can't copy const members
- [ ] I understand the difference between throw and catch locations
- [ ] I can trace the complete flow from signForm() to beSigned()
- [ ] I understand "Tell, Don't Ask" principle
- [ ] I know when to use const references vs non-const references
- [ ] I can explain why lower grade numbers mean higher rank
- [ ] I understand the responsibilities of each class
- [ ] I know how to properly validate in constructors

---

## 🎯 Next Steps

**Ex02 will likely introduce:**
- Abstract classes and pure virtual functions
- Polymorphism and inheritance hierarchies
- More complex object interactions
- Dynamic polymorphism with base class pointers

**Master ex01 before moving on!** The concepts here are fundamental to understanding object-oriented design in C++.

---

**Pro Tip:** Draw a diagram showing how Bureaucrat and Form interact. Visual understanding helps cement these concepts!
