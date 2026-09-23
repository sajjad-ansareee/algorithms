---
name: c++
description: Guidelines and best practices for writing modern C++ code.
---

# C++ Coding

## Purpose

Use this skill when writing, modifying, or reviewing C++ code.

## Important
- Write modular, maintainable code.
- The validation and constraint should be separate functions.
- Use /* */ for comments.
- Use simple small characters for comments.

## Guidelines

- Use modern C++ features where appropriate.
- Prefer RAII for resource management.
- Use `std::vector` instead of raw dynamic arrays.
- Avoid unnecessary raw pointers.
- Use `const` wherever possible.
- Use reference semantics (`&`) for passing arguments.
- Use tab with size 4 for indentation.
- Do not use spaces for indentation.
- Write clear, self-explanatory code.
- Do not use advanced C++ features.

## Code Style

- Use `PascalCase` for classes.
- Use `snake_case` for variables and functions.
- Use `.hpp` for C++ header files.
- Use `.cpp` for implementation files.

## Workflow

1. Inspect the existing project structure.
2. Follow the project's existing conventions.
3. Make the smallest necessary changes.
4. Compile the project after modifications.
5. Run relevant tests.
6. Report what was changed.

## Quality Requirements

- Do not introduce unnecessary dependencies.
- Do not rewrite working code without a reason.
- Prefer simple and maintainable solutions.
- Check for compiler warnings.
