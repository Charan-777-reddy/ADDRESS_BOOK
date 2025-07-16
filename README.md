# ADDRESS_BOOK
A command-line application that enables users to manage contact information efficiently. It integrates with a CSV file for data storage, allowing seamless access and editing through external tools like Microsoft Excel.
📇 Address Book Application in C with CSV Integration
A terminal-based Address Book application built using the C programming language. This project was developed as part of the Certified Embedded Professional Program at Emertxe Information Technologies, Bangalore.

It showcases real-world data management techniques in C with persistent storage through CSV files, making the data easily accessible and editable via external tools like Microsoft Excel.

🔧 Features
➕ Add Contact – Store new contact entries

🔍 Search Contact – Find contacts by name, mobile number, or email

✏️ Edit Contact – Update existing contact details

❌ Delete Contact – Remove a contact from the address book

📋 List All Contacts – View all stored contacts

📂 CSV File Storage – Contacts are saved in .csv format, viewable/editable in Excel

💡 Key Highlights
📵 Duplicate Prevention – Ensures mobile numbers are unique

🛑 Input Validation – Handles incorrect or invalid input gracefully

✅ User Feedback – Clear confirmation and error messages

🧱 Modular Codebase – Cleanly structured with reusable functions

🧠 Memory-Safe Implementation – Utilizes dynamic memory and pointer management effectively

📁 Project Structure
bash
Copy
Edit
.
├── main.c                # Program entry and menu interface
├── address_book.c        # Core logic: add, search, edit, delete, display
├── address_book.h        # Struct definitions and function declarations
├── contacts.csv          # CSV file for contact storage
├── Makefile              # (Optional) For automated build
└── README.md             # Documentation and usage guide
🧠 Core Concepts Used
📂 File Handling in C (fopen, fgets, fscanf, fprintf, etc.)

📊 CSV Parsing and File Integration

🧮 Dynamic Memory Allocation (malloc, realloc, free)

🧾 Structures and Pointers

🧩 Modular Function Design

🖥️ Menu-Driven CLI Interface

✅ How to Compile & Run
bash
Copy
Edit
gcc main.c address_book.c -o addressbook
./addressbook
👨‍💻 Author
Charan Reddy R
Embedded Systems & C Developer
🔗 LinkedIn Profile

🏷️ Tags
#CProgramming #EmbeddedC #CSVIntegration #FileHandlingInC
#SystemProgramming #TerminalApp #Emertxe #PointersInC
#ModularDesign #TechPortfolio
