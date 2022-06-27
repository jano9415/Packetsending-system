# Packetsending-system

This project represents a packet sending system with C++ console application.
The menu contains: sign up, login, logout, send a package, take a package.
The packets are sent from a packet automate to another packet automate.

Sign up:
If you sign up you have to give your firstname, lastname, email address and a password.
The password minimum length is 8 characters.
The registration datas are in a txt file. The file of name is accounts.txt.

Send a package:
If you would like to send a package, you have to login.
Choose the city where you will send the package.
Give the height, width and length of the package. The max package size is 100.
The program scan the actual automate and the selected automate. If one of the automate is full you can't send and the prgram warn you for this.
Give the price of the package and the personal datas of the receiver.
The program generates a txt file with the datas of the package and sender.
The receiver will know from this txt file what is the package id. The package can be taken just with the package id.
Pay the shipping fee. You have to give just the number that the program shows you. If you give another number you have to give again.
This simple method just represent a transaction error.
Finally your package will be shipped from this automate in the selected automate.

Take a package:
If you would like to take a package you dont't have to sign up and login.
Give the package id that is in the txt file. This file is generated after a success packet sending.
This process represents an email sending.
Pay the package fee if you haven't pay yet.
You have to give just the number that the program shows you. If you give another number you have to give again.
This simple method just represent a transaction error.
Finally the package can be taken from the automate.
