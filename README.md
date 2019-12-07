# chocan-db
CS300 Group 7 Chocoholics Anonymous database project. 
These files provide the prototype mockup of the database software that provides members, providers, and managers the tools to operate ChocAn effectively.

# Requirements
To build the system, you will need a Linux system with GCC and the sqlite3 headers and libraries. The headers are included in a folder in the src directory, or they can be accessed through a path specified in the makefile that is a common install location- /usr/include. The library must be installed. The makefile will search the default location- /usr/lib. These libraries can be obtained through your package manager. If you are using Ubuntu, the command would be "sudo apt-get install sqlite3".

# Build instructions:
To build the software, enter the src directory.
Then run "make" which will run the makefile present in the src directory
This will compile the binary executable.
It will be named "output". Type ./output to begin executing the program in the terminal.
