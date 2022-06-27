#include "customer.h"


bool Customer::getIsLogin() const
{
	return isLogin;
}

const string & Customer::getLastName() const
{
	return lastName;
}

const string & Customer::getFirstName() const
{
	return firstName;
}

const string & Customer::getEmailAddress() const
{
	return emailAddress;
}

const string & Customer::getPassword() const
{
	return password;
}

//Regisztráció
//Adatok bekérése a felhasználótól. Vezetéknév, keresztnév, email cím, jelszó.
//A regisztrációs adatokat egy txt fájl tartalmazza. A fájl neve: accounts.txt
//Megadott email cím ellenõrzése a txt fájlban. Csak olyan email cím adható meg, ami még nincs benne a fájlban.
//Megadott jelszó ellenõrzése. A jelszónak minimum 8 karakternek kell lennie.
//Ha minden megadott adat megfelelõ, akkor adatok kiírása a txt fájlba.
void Customer::signUp()
{
	ifstream fin("accounts.txt");
	ofstream fout("accounts.txt", ios_base::app);

	bool emailAddressAlredyExist = false;
	list<string> emailAdressesforValidation;

	int count = 0;

	if (fin.is_open()) {

		while (!fin.eof()) {

			string actualLastName, actualFirstName, actualEmailAddress, actualPassword;
			fin >> actualLastName >> actualFirstName >> actualEmailAddress >> actualPassword;
			emailAdressesforValidation.push_back(actualEmailAddress);
		}
		fin.close();

	}

	cout << "Add meg a vezetekneved" << endl;
	cin >> lastName;
	fout << lastName << " ";

	cout << "Add meg a keresztneved" << endl;
	cin >> firstName;
	fout << firstName << " ";

	cout << "Add meg az email cimed" << endl;
	cin >> emailAddress;

	for (auto it = emailAdressesforValidation.cbegin(); it != emailAdressesforValidation.cend(); it++) {
		if (*it == emailAddress) {
			emailAddressAlredyExist = true;
		}

	}

	while (emailAddressAlredyExist) {

		cout << "Ezzel az email cimmel mar regisztraltak, add meg az email cimed ujra" << endl;
		cin >> emailAddress;

		for (auto it = emailAdressesforValidation.cbegin(); it != emailAdressesforValidation.cend(); it++) {
			if (*it == emailAddress) {
					count++;
			}
		}

		if (count >= 1) {
			emailAddressAlredyExist = true;
			count = 0;
		}
		else {
			emailAddressAlredyExist = false;
		}
	}

	fout << emailAddress << " ";

	cout << "Add meg a jelszot" << endl;
	cin >> password;

	while (password.size() < 8) {
		cout << "A jelszonak minimum 8 karakternek kell lennie" << endl;
		cout << "Adj meg egy masik jelszot" << endl;
		cin >> password;
	}

	fout << password << " ";
	fout << endl;

	cout << "Sikeres regisztracio." << endl;
	cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
	system("PAUSE");


}

//Bejelentkezés
//Email cím és jelszó bekérése a felhasználótól.
//Megadott adatok kikeresése és ellenõrzése az accounts.txt fájlból.
//Ha a megadott email cím vagy jelszó hibás, akkor két lehetõség van. Belépés a regisztrációs menüpontba és regisztráció elvégzése vagy adatok megadása újra.
//Ha minden megadott adat megfelelõ, akkor a belépés sikeres.
void Customer::login()
{
	ifstream fin("accounts.txt");

	map<string, string> loginDatas;
	map<string, string> loginLastName;
	map<string, string> loginFirstName;

	int loginOrSignUp = 0;


	if (fin.is_open()) {

		while (!fin.eof()) {

			string actualLastName, actualFirstName, actualEmailAddress, actualPassword;
			fin >> actualLastName >> actualFirstName >> actualEmailAddress >> actualPassword;
			loginDatas[actualEmailAddress] = actualPassword;
			loginLastName[actualEmailAddress] = actualLastName;
			loginFirstName[actualEmailAddress] = actualFirstName;
			
		}
		fin.close();
	}

	if (isLogin == false) {

		cout << "Add meg az email cimed." << endl;
		cin >> emailAddress;

		cout << "Add meg a jelszot." << endl;
		cin >> password;

		auto it = loginDatas.find(emailAddress);

		while (it == loginDatas.end() || it->second != password) {

			cout << "Hibas email cim vagy jelszo. Ha meg nem regisztraltal, nyomd meg az 1-es gombot a regisztraciohoz."
				"Ha ujra meg szeretned adni a bejelentkezesi adataidat, nyomd meg a 2-es gombot." << endl;
			cin >> loginOrSignUp;

			if (loginOrSignUp == 1) {

				signUp();
				return;
			}

			if (loginOrSignUp == 2) {

				cout << "Add meg az email cimed." << endl;
				cin >> emailAddress;

				cout << "Add meg a jelszot." << endl;
				cin >> password;

				it = loginDatas.find(emailAddress);

			}

		}
		isLogin = true;
		lastName = loginLastName.find(emailAddress)->second;
		firstName = loginFirstName.find(emailAddress)->second;

		cout << "Sikeres bejelentkezes." << endl;
		cout << "Nyomj meg egy gombot, hogy visszaterhess a menube." << endl;
		system("PAUSE");

	}
}

//Kijelentkezés
void Customer::logout()
{
	
	isLogin = false;
	cout << "Sikeres kijelentkezes." << endl;
	cout << "Nyomj meg egy gombot, hogy visszaterhess a menube." << endl;
	system("PAUSE");

}

//Csomag küldése. Csomagot küldeni csak a regisztrált felhasználó tud.
//5 karakter hosszú random sztring generálása
//Város kiválasztása, ahová a csomagot küldeni szeretnénk.
//Csomag méreteinek bekérése. Ha a hosszúság vagy szélesség vagy magasság nagyobb mint 100, akkor kivételt dobunk.
//Jelenlegi automata rekeszeinek ellenõrzése. Ha nincs üres rekesz, akkor nem lehet csomagot feladni. Kivételt dobunk.
//Kiválasztott automata rekeszeinek ellenõrzése. Ha nincs üres rekesz, akkor nem lehet csomagot feladni. Kivételt dobunk.
//Csomag árának és az átvevõ adatainak bekérése.
//Txt fájl generálása a csomag és a feladó adataival. A txt fájl neve megegyezik az átvevõ email címével. Ez reprezentálja az email küldést.
//Szállítási díj kifizetése.
//A fizetes egyszeruen annyi, hogy be kell irni 1200-at. Ha nem 1200-at irsz be, az azt jeleni, hogy sikertelen a tranzakcio es ujra meg kell adni az arat.
//Csomag behelyezése a program által megadott rekeszbe.
//Csomag szállítása.
//Az aktuális automata rekeszének kiürítése és a kiválasztott automata feltöltése a csomaggal.
void Customer::sendPackage(vector<Container*>& containers)
{
	srand(time(0));

	string randomString;
	int thisCity = 1;
	int selectedCity;
	string city;
	int width, height, lenght, price;
	Container* selectedContainer = nullptr;
	Container* thisContainer = containers[1];
	int thisBox = -1;
	int selectedBox = -1;
	string receiverEmailAddress;
	int supplyPrice = 0;

	
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < 5; ++i) {
		randomString += alphanum[rand() % (sizeof(alphanum) - 1)];

	}

	cout << "Valaszd ki, hogy hova szeretned kuldeni a csomagot. Ird be a megfelelo szamot." << endl;
	cout << "0 - Varpalota" << endl;
	cout << "2 - Szekesfehervar" << endl;
	cout << "3 - Tapolca" << endl;
	cin >> selectedCity;

	while (selectedCity < 0 || selectedCity > 3 || selectedCity == thisCity) {
		cout << "Rossz szamot adtal meg. Add meg ujra." << endl;
		cin >> selectedCity;
	}

	selectedContainer = containers[selectedCity];

	cout << "Add meg a csomag szelesseget." << endl;
	cin >> width;
	cout << "Add meg a csomag magassagat." << endl;
	cin >> height;
	cout << "Add meg a csomag hosszat." << endl;
	cin >> lenght;

	if ((width > 100 || width <= 0) || (height > 100 || width <= 0) || (lenght > 100 || width <= 0)) {
		throw supplyNotPossibleException("A megadott merettel nem lehet csomagot feladni.");
	}

	for (int i = 0; i < thisContainer->getBoxes().size(); i++) {

		if (thisContainer->getBoxes()[i]->getEmpty() && width < thisContainer->getBoxes()[i]->getWidth() && 
			height < thisContainer->getBoxes()[i]->getHeight() && lenght < thisContainer->getBoxes()[i]->getLenght()) {

			thisBox = i;
			break;
		}
	}

	if (thisBox < 0) {
		throw supplyNotPossibleException("Sajnaljuk, ez az automata tele van. Jelenleg nem tudsz csomagot feladni.");
	}

	for (int i = 0; i < selectedContainer->getBoxes().size(); i++) {

		if (selectedContainer->getBoxes()[i]->getEmpty() && width < selectedContainer->getBoxes()[i]->getWidth() &&
			height < selectedContainer->getBoxes()[i]->getHeight() && lenght < selectedContainer->getBoxes()[i]->getLenght()) {

			selectedBox = i;
			break;
		}
	}

	if (selectedBox < 0) {
		throw supplyNotPossibleException("Sajnaljuk, a kivalasztott automata tele van. Jelenleg nem tudsz csomagot feladni.");
	}

	cout << "Add meg a csomag arat. Ha a csomag mar ki van fizetve elore, akkor nullat irj be."<<endl;
	cin >> price;

	cout << "Add meg a csomag atvevojenek az email cimet." << endl;
	cin >> receiverEmailAddress;
	ofstream fout(receiverEmailAddress + ".txt");
	fout << "Csomagod erkezett. A csomag adatai:" << endl;
	fout << "Felado: " << this->lastName << " " << this->firstName << endl;
	fout << "Felado email cime: " << this->emailAddress << endl;
	fout << "A csomag azonositoja: " << randomString << endl;
	fout << "A csomag automata cime: " << selectedContainer->getAddress().getPostCode() << " " << selectedContainer->getAddress().getCity() << ", " <<
		selectedContainer->getAddress().getStreet() << " " << selectedContainer->getAddress().getNumber() << ".";
	fout.close();

	cout << "A szallitasi dij 1200Ft." << endl;
	cout << "Helyzd be a bakkartyat." << endl;
	cin >> supplyPrice;
	while (supplyPrice != 1200) {
		cout << "Sikertelen tranzakcio. Kerjuk probald meg ujra." << endl;
		cout << "Helyzd be a bakkartyat." << endl;
		cin >> supplyPrice;
	}

	Package* package = new Package(randomString, width, height, lenght, price);

	cout << "Tedd be a csomagot a(z) " << thisBox + 1 << ". rekeszbe." << endl;

	thisContainer->getBoxes()[thisBox]->setPackage(package);
	thisContainer->getBoxes()[thisBox]->setEmpty(false);


	cout << endl << "---------------------------------------------------" << endl;
	cout << "Ez az automata: ";
	for (auto d : thisContainer->getBoxes()) {
		cout << d->getEmpty();
	}
	cout << endl << "---------------------------------------------------" << endl;

	thisContainer->getBoxes()[thisBox]->setPackage(nullptr);
	thisContainer->getBoxes()[thisBox]->setEmpty(true);

	cout << "Csomag szallitasa folyamatban van." << endl;

	for (int i = 0; i < 10; i++) {

		cout << ".";
		this_thread::sleep_for(chrono::milliseconds(1000));

	}
	cout << endl;



	selectedContainer->getBoxes()[selectedBox]->setPackage(package);
	selectedContainer->getBoxes()[selectedBox]->setEmpty(false);

	cout << "Csomag sikeresen elszallitva." << endl;

	cout << endl << "---------------------------------------------------" << endl;
	cout << "Ez az automata: ";
	for (auto d : thisContainer->getBoxes()) {
		cout << d->getEmpty();
	}
	cout << endl <<"---------------------------------------------------" << endl;


	cout << endl << "----------------------------------------------------------" << endl;
	cout << "Kivalasztott automata: ";
	for (auto d : selectedContainer->getBoxes()) {
		cout << d->getEmpty();
	}
	cout << endl << "----------------------------------------------------------" << endl;

	cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
	system("PAUSE");
}

//Csomag átvétele. Az átvételhez nem kell regisztrálni és bejelentkezni.
//Meg kell adni az email-ben kapott csomag azonosítót. Hibás azonosító esetén visszatérés a menübe. Az email küldést egy txt fájl reprezentálja.
//Ha a csomag még nincs kifizetve akkor ki kell fizetni az árát.
//A fizetes annyi, hogy be kell irni a kepernyon megjeleno arat. Ha nem annyit irsz be, akkor sikertelen a tranzakcio es ujra meg kell adni az arat.
//Csomag átvétele a megfelelõ rekeszbõl.
void Customer::takePackacge(vector<Container*>& containers)
{
	string packageId;
	Container* thisContainer = containers[0];
	int index = 0;
	int price = 0;

	cout << endl << "---------------------------------------------------" << endl;
	cout << "Ez az automata: ";
	for (auto d : thisContainer->getBoxes()) {
		cout << d->getEmpty();
	}
	cout << endl << "---------------------------------------------------" << endl;

	cout << "Add meg az email-ben kapott csomag azonositot." << endl;
	cin >> packageId;

	for (int i = 0; i < thisContainer->getBoxes().size(); i++) {

		if (thisContainer->getBoxes()[i]->getPackage() != nullptr && thisContainer->getBoxes()[i]->getPackage()->getId() == packageId) {

			index++;
			if (thisContainer->getBoxes()[i]->getPackage()->getPrice() > 0) {
				cout << "A csomag meg nincs kifizetve. A csomag ara " << thisContainer->getBoxes()[i]->getPackage()->getPrice() << "Ft." << endl;
				cout << "Helyzd be a bakkartyat." << endl;
				cin >> price;
				while (price != thisContainer->getBoxes()[i]->getPackage()->getPrice()) {
					cout << "Sikertelen tranzakcio. Kerjuk probald meg ujra." << endl;
					cout << "Helyzd be a bakkartyat." << endl;
					cin >> price;
				}
			}
			cout << "Vedd ki a csomagodat a(z) " << i + 1 << ". rekeszbol." << endl;

			thisContainer->getBoxes()[i]->setPackage(nullptr);
			thisContainer->getBoxes()[i]->setEmpty(true);

			cout << endl << "---------------------------------------------------" << endl;
			cout << "Ez az automata: ";
			for (auto d : thisContainer->getBoxes()) {
				cout << d->getEmpty();
			}
			cout << endl << "---------------------------------------------------" << endl;

			cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
			system("PAUSE");
		}
	}



	if (index == 0) {

		cout << "Hibas csomag azonosito. A keresett csomag nincs az automataban." << endl;
		cout << "Nyomj meg egy gombot, hogy visszaterhess a menube" << endl;
		system("PAUSE");
	}
}

Customer::Customer()
{

}

