# 📊 Visual Guide: Bureaucrat and Form Interaction

## Class Relationship Diagram

```
┌─────────────────────────┐         ┌──────────────────────────┐
│      Bureaucrat         │         │         Form             │
├─────────────────────────┤         ├──────────────────────────┤
│ - const string name     │         │ - const string name      │
│ - int grade             │         │ - bool is_signed         │
├─────────────────────────┤         │ - const int grade_to_sign│
│ + signForm(Form&)       │────────>│ - const int grade_to_exec│
│ + getGrade()            │<────────├──────────────────────────┤
│ + getName()             │         │ + beSigned(Bureaucrat&)  │
└─────────────────────────┘         │ + getName()              │
                                    │ + getIsSigned()          │
                                    │ + getGradeToSign()       │
                                    │ + getGradeToExecute()    │
                                    └──────────────────────────┘
```

## Method Call Flow

```
User Code:
    bureaucrat.signForm(form)
         │
         ├──> Bureaucrat::signForm(Form &form)
         │        │
         │        ├──> try {
         │        │        form.beSigned(*this)
         │        │             │
         │        │             ├──> Form::beSigned(const Bureaucrat &b)
         │        │             │        │
         │        │             │        ├──> if (b.getGrade() > grade_to_sign)
         │        │             │        │        └──> throw GradeTooLowException()
         │        │             │        │
         │        │             │        └──> is_signed = true
         │        │             │
         │        │             └──< returns normally
         │        │
         │        ├──> cout << "signed successfully"
         │        │
         │        └── } catch (exception &e) {
         │                 cout << "couldn't sign because..."
         │            }
         │
         └──< returns to user code
```

## Grade System Visualization

```
┌─────────────────────────────────────────────────────┐
│                  GRADE SCALE                        │
├─────────────────────────────────────────────────────┤
│                                                     │
│   1 ◄────────────────────────────────────► 150     │
│   ↑                                            ↑    │
│ HIGHEST                                     LOWEST  │
│  RANK                                        RANK   │
│  BEST                                        WORST  │
│                                                     │
│  Most                                        Least  │
│  Powerful                                   Powerful│
│                                                     │
└─────────────────────────────────────────────────────┘

Examples:
  Grade 1   = CEO, President      (can sign anything)
  Grade 50  = Manager             (medium authority)
  Grade 100 = Junior Staff        (limited authority)
  Grade 150 = Intern              (minimal authority)
```

## Signing Logic Flow Chart

```
                    START
                      │
                      ▼
         Bureaucrat.signForm(form) called
                      │
                      ▼
                  ┌───────┐
                  │  TRY  │
                  └───┬───┘
                      │
                      ▼
             form.beSigned(*this)
                      │
                      ▼
         ┌────────────────────────────┐
         │ Is bureaucrat.grade        │
         │      <=                    │
         │ form.grade_to_sign?        │
         └────────┬───────────┬───────┘
                  │           │
              YES │           │ NO
                  │           │
                  ▼           ▼
         ┌─────────────┐  ┌──────────────────┐
         │Set is_signed│  │Throw             │
         │   = true    │  │GradeTooLowExcept.│
         └──────┬──────┘  └────────┬─────────┘
                │                  │
                ▼                  ▼
    ┌──────────────────┐   ┌──────────────────┐
    │Print success msg │   │CATCH exception   │
    │"X signed Y"      │   │Print failure msg │
    │                  │   │"X couldn't sign Y│
    └────────┬─────────┘   │because..."       │
             │              └────────┬─────────┘
             │                       │
             └───────────┬───────────┘
                         │
                         ▼
                       END
```

## Object Creation Timeline

```
Time    Event                           Memory State
─────────────────────────────────────────────────────────────
 t0     Bureaucrat john("John", 30);    
        │                               john: [name="John", grade=?]
        ├─> Initialize name             john: [name="John", grade=?]
        ├─> Call setGrade(30)           
        ├─> Validate: 1<=30<=150? ✓     
        └─> Set grade=30                john: [name="John", grade=30] ✓

 t1     Form f("Permit", 50, 25);
        │                               f: [name="Permit", signed=false, 
        │                                   sign=50, exec=25]
        ├─> Initialize all const members
        ├─> Validate: 1<=50<=150? ✓
        ├─> Validate: 1<=25<=150? ✓
        └─> Object ready                f: [valid] ✓

 t2     john.signForm(f);
        │                               john.grade=30, f.grade_to_sign=50
        ├─> Call f.beSigned(john)
        ├─> Check: 30 <= 50? YES ✓
        ├─> Set f.is_signed = true
        └─> Print "John signed Permit"  f: [signed=true] ✓
```

## Exception Flow Diagram

```
                    Constructor/Method Call
                            │
                            ▼
                    ┌───────────────┐
                    │  Validation   │
                    └───────┬───────┘
                            │
                    ┌───────┴────────┐
                    │                │
                 Valid            Invalid
                    │                │
                    ▼                ▼
            ┌──────────────┐  ┌─────────────┐
            │Proceed       │  │Throw        │
            │normally      │  │Exception    │
            └──────────────┘  └──────┬──────┘
                                     │
                                     ▼
                              ┌─────────────┐
                              │Stack        │
                              │Unwinding    │
                              └──────┬──────┘
                                     │
                              ┌──────┴──────┐
                              │             │
                          Caught        Uncaught
                              │             │
                              ▼             ▼
                      ┌──────────────┐  ┌──────────┐
                      │Handle error  │  │Program   │
                      │Print message │  │terminates│
                      │Continue      │  └──────────┘
                      └──────────────┘
```

## Memory Layout

```
Bureaucrat Object:
┌────────────────────────────────┐
│ const std::string name         │ ← Cannot change after construction
├────────────────────────────────┤
│ int grade                      │ ← Can be modified
└────────────────────────────────┘

Form Object:
┌────────────────────────────────┐
│ const std::string name         │ ← Cannot change
├────────────────────────────────┤
│ bool is_signed                 │ ← Can be modified (only non-const!)
├────────────────────────────────┤
│ const int grade_to_sign        │ ← Cannot change
├────────────────────────────────┤
│ const int grade_to_execute     │ ← Cannot change
└────────────────────────────────┘

Assignment operator can ONLY copy: is_signed
```

## Compilation Dependencies

```
Bureaucrat.hpp          Form.hpp
      │                    │
      │    ┌───────────────┘
      │    │
      │    ▼
      │  Forward Declaration:
      │  "class Bureaucrat;"
      │    │
      ▼    ▼
Bureaucrat.cpp      Form.cpp
      │                │
      ├─> #include "Bureaucrat.hpp"
      ├─> #include "Form.hpp"
      │                │
      └────────────────┴──> Full definitions available
                            ↓
                       Can call methods
                       on each other
```

## const vs non-const References

```
void beSigned(const Bureaucrat &bureaucrat)
                 │              │
                 │              └─> Pass by reference (no copy)
                 │
                 └─> const = read-only access

┌──────────────────┐
│   Can do:        │
├──────────────────┤
│ bureaucrat.get() │ ✓ Call const methods
│ int x = b.grade  │ ✓ Read public members
└──────────────────┘

┌──────────────────┐
│  Cannot do:      │
├──────────────────┤
│ b.setGrade(10)   │ ✗ Call non-const methods
│ b.grade = 10     │ ✗ Modify members
└──────────────────┘


void signForm(Form &form)
                  │
                  └─> Non-const reference

┌──────────────────┐
│   Can do:        │
├──────────────────┤
│ form.beSigned()  │ ✓ Call any method
│ form.getName()   │ ✓ Call const methods
│ Modify form      │ ✓ Change state
└──────────────────┘
```

## Initialization List vs Constructor Body

```cpp
// INITIALIZATION LIST (before {)
Form::Form(string name, int sign, int exec) : 
    name(name),                    // ← Direct initialization
    is_signed(false),              // ← Direct initialization
    grade_to_sign(sign),           // ← Direct initialization (REQUIRED for const)
    grade_to_execute(exec)         // ← Direct initialization (REQUIRED for const)
{
    // CONSTRUCTOR BODY (inside {})
    // Const members already set - cannot assign here!
    // Use body for validation and other logic
    if (sign < 1) throw ...;       // ← Validation logic
}

Timeline:
    1. Memory allocated
    2. Initialization list runs → const members set
    3. Constructor body runs → validation
    4. Object ready (or destroyed if exception)
```

## Exception Hierarchy

```
        std::exception (standard library)
              │
              ├─> what() const throw()
              │
    ┌─────────┴──────────┬──────────────────┐
    │                    │                   │
    ▼                    ▼                   ▼
Bureaucrat::         Form::            Form::
GradeTooHigh        GradeTooHigh      GradeTooLow
Exception           Exception         Exception
    │                   │                  │
    └──> what():        └──> what():       └──> what():
         "grade             "Form grade        "Form grade
         too high"          is too high!"      is too low!"


Catching strategy:
    catch (Form::GradeTooLowException &e)  // Most specific
    catch (std::exception &e)              // Catches all
```

## Quick Reference: When Grade Comparison Works

```
┌─────────────────────────────────────────────────────────┐
│  Bureaucrat Grade    Form Required    Can Sign?         │
├─────────────────────────────────────────────────────────┤
│      1 (best)            50              YES ✓          │
│      30                  50              YES ✓          │
│      50                  50              YES ✓ (equal)  │
│      51                  50              NO  ✗          │
│      100                 50              NO  ✗          │
│      150 (worst)         50              NO  ✗          │
└─────────────────────────────────────────────────────────┘

Formula: bureaucrat_grade <= form_required_grade
         (Lower or equal number = sufficient rank)
```

---

**Tip:** Print this out and refer to it while coding! Visual references make complex interactions much clearer.
