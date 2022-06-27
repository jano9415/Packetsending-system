#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<string>
#include<iostream>
#include<fstream>
#include<list>
#include<map>
#include"package.h"
#include<ctime>
#include"container.h"
#include<vector>
#include<chrono>
#include<thread>
#include<exception>

using namespace std;


class Customer
{
private:
	string lastName, firstName;
	string emailAddress;
	string password;
	bool isLogin = false;

	//Saját kivétel osztály. Paraméterben megkapja a hibaüzenetet.
	class supplyNotPossibleException : public exception {
	private:
		string msg;
	public:
		supplyNotPossibleException(string _msg) {
			
			this->msg = _msg;;
		}
		~supplyNotPossibleException() {}
		virtual const char* what() const noexcept {
			return this->msg.c_str();
		}
	};


	

public:
	Customer();

	bool getIsLogin()const;
	const string& getLastName() const;
	const string& getFirstName() const;
	const string& getEmailAddress() const;
	const string& getPassword() const;


	void signUp();

	void login();

	void logout();

	void sendPackage(vector<Container*>& containers);

	void takePackacge(vector<Container*>& containers);
};

#endif // CUSTOMER_H
