# Phonebook

#### Video Demo: https://youtu.be/U2qV9IQZUMg

#### Description:

Phonebook is a command-line interface (CLI) application written in C that allows users to efficiently manage a digital contact list. Developed as a final project for CS50, this program provides a robust way to store, organize, retrieve, and export contact information directly from the terminal.

The primary motivation behind creating this project was to build a practical tool that goes beyond basic data structures, incorporating dynamic memory management, input validation, and file input/output operations. Managing contacts is a universal task, and implementing it in C required a deep understanding of pointers, memory allocation, and data structures.

The application starts by requiring a specific command-line argument (`./phonebook start`) to ensure proper execution. Once launched, the user is presented with an interactive menu featuring five core options: adding a new contact, removing an existing contact, searching for a specific person, looking at the entire phonebook, and stopping the program.

Regarding the codebase, the project is contained within a single main source file, `phonebook.c`. Inside this file, several key functions drive the program's logic:
- `main()`: Handles the command-line argument check, runs the main interactive `do-while` loop, and processes user inputs to direct the program flow. It also ensures that all dynamically allocated memory is properly freed upon exit using `free_all()`.
- `add()`: Inserts a newly created contact node directly into the doubly linked list, updating pointers accordingly.
- `remove_contact()`: Locates a specific contact by name and surname, safely unlinks the node from both directions, frees its allocated memory, and prevents memory leaks.
- `search_contact()`: Traversing the list to find a matching name and surname combination, then displaying the associated phone number.
- `look()`: Iterates through the entire linked list to print all stored contacts neatly to the standard output. Additionally, it prompts the user if they wish to export the current phonebook data into a `phonebook.csv` file using standard file I/O (`fopen`, `fprintf`, `fclose`).
- Validation functions like `verifynumber()`, `checknumber()`, and `contact_exists()` ensure that data integrity is maintained, preventing duplicate names or numbers and making sure phone numbers consist solely of digits.

During the development process, several design choices were debated and implemented. The most significant choice was the decision to use a doubly linked list instead of a simple array or a singly linked list. While arrays have fixed sizes or require complex reallocation logic, and singly linked lists only allow forward traversal, a doubly linked list (`struct node` containing both `next` and `prev` pointers) offered greater flexibility for future expansions and bidirectional traversal, while remaining lightweight enough for a command-line utility. Furthermore, strict error handling and memory management were prioritized: every `malloc` call is checked for `NULL`, and every allocated string or node is systematically freed to avoid any memory leaks.

Overall, building Phonebook was an incredible learning experience that tied together concepts of memory allocation, algorithms, and data structures learned throughout CS50x.
