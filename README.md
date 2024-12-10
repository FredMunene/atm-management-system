# ATM-MANAGEMENT SYSTEM
A simple command-line ATM application implemented in C that allows users to perform various banking operations, including account creation, login, updating account details, and more.

## Features
+ Login 
    - Using a name and password
+ Register
    - Ensures unique usernames
+ Account Creation 
+ Check Details of Existing Accounts
+ Update info of existing accounts
    - Allows updating country or phone number
+ Remove Existing Accounts
+ Check List of Owned Accounts -- implemented
+ Make Transactions

## File System
```
|
├── data
│   ├── records.txt
│   └── users.txt
├── Makefile
└── src
    ├── auth.c
    ├── header.h
    ├── main.c
    └── system.c
```
## Getting Started
**Prerequisites:**
    - GCC (GNU Compiler Collection) installed.
    - Basic understanding of the command line interface.

**Installation:**
1. Clone the repository:
```
git clone https://github.com/FredMunene/atm-management-system.git  
cd atm-management-system 
```
2. Compile the project using Makefile:
```bash
make  
```
3. Run the program:
```bash
./atm  
```
To re-compile the program after making changes; run
```bash
make clean
```




## Bonus / To be Implemented
+ Terminal Interface
+ Transfer owner. Explore **pipes and child processes**
+ password encryption
+ Makefile - Automates compilation
+ SQlite; relational database


## Contributing

Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch:
```bash
git checkout -b feature-name  
```
3. Commit your changes:
```bash
git commit -m "Add your message here"  
```
4. Push to the branch:
```bash
git push origin feature-name  
```
5. Create a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
