#include <iostream>
#include "customer.h"
#include<fstream>
#include<list>
#include "container.h"
#include<ctime>
#include<vector>



using namespace std;



int main() {

	Customer* customer = nullptr;

	//Csomagküldõ automaták
	Container* container1 = new Container(8100, "Varpalota", " Fehervari ut", 17);
	Container* container2 = new Container(8200, "Veszprem", "Budapest ut", 20);
	Container* container3 = new Container(8000, "Szekesfehervar", "Palotai ut", 6);
	Container* container4 = new Container(8300, "Tapolca", "Veszpremi ut", 5);

	vector<Container*> containers;
	containers.push_back(container1);
	containers.push_back(container2);
	containers.push_back(container3);
	containers.push_back(container4);


	int choice;

	do {
		cout << "Main Menu" << endl;
		cout << "Valassz az alabbi lehetosegek kozul." << endl;
		cout << "1 - Regisztracio" << endl;
		cout << "2 - Bejelentkezes" << endl;
		cout << "3 - Kijelentkezes" << endl;
		cout << "4 - Csomagatvetel" << endl;
		cout << "5 - Csomagfeladas" << endl;
		cout << "6 - Kilepes" << endl;
		cin >> choice;

		switch (choice) {
		//Regisztráció
		case 1:
			if (customer == nullptr) {

				customer = new Customer;
				customer->signUp();
				customer = nullptr;

			}
			else {
				cout << "Jelenleg be vagy jelentkezve. Regisztracio elott jelentkezz ki." << endl;
				cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
				system("PAUSE");
			}
			break;
		//Bejelentkezés
		case 2:
			if (customer == nullptr) {

				customer = new Customer;
				customer->login();
			}
			else {

				cout << "Mar be vagy jelentkezve. Ha ujra be szeretnel jelentkezni elobb jelentkezz ki." << endl;
				cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
				system("PAUSE");
			}
			break;
		//Kijelentkezés
		case 3:
			if (customer != nullptr) {

				customer->logout();
				customer = nullptr;
			}
			else {
				cout << "Kijelentkezeshez elobb be kell jelentkezned." << endl;
				cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
				system("PAUSE");
			}

			break;
		//Csomag átvétele
		//A csomag átvételéhez nem kell bejelentkezni.
		case 4:
			
			customer = new Customer();
			customer->takePackacge(containers);
			customer = nullptr;
			
			break;
		//Csomag küldése
		//A csomag küldéséhez be kell jelentkezni.
		case 5:
			if (customer != nullptr && customer->getIsLogin()) {

				try {
					customer->sendPackage(containers);
				}
				catch (exception& e) {
					cout << e.what() << endl;
					cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
					system("PAUSE");
				}
				
			}
			else {
				cout << "Csomag feladashoz elobb jelentkezz be." << endl;
				cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
				system("PAUSE");
			}
			break;
		//Program bezárása
		case 6:
			cout << "Sikeres kilepes" << endl;
			break;
		}
	} while (choice != 6);



	delete customer, container1, container2, container3, container4;
	for (auto c : containers) {
		delete c;
	}
	return 0;
}



