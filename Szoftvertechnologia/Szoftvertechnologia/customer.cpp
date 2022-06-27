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

//Regisztr�ci�
//Adatok bek�r�se a felhaszn�l�t�l. Vezet�kn�v, keresztn�v, email c�m, jelsz�.
//A regisztr�ci�s adatokat egy txt f�jl tartalmazza. A f�jl neve: accounts.txt
//Megadott email c�m ellen�rz�se a txt f�jlban. Csak olyan email c�m adhat� meg, ami m�g nincs benne a f�jlban.
//Megadott jelsz� ellen�rz�se. A jelsz�nak minimum 8 karakternek kell lennie.
//Ha minden megadott adat megfelel�, akkor adatok ki�r�sa a txt f�jlba.
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

//Bejelentkez�s
//Email c�m �s jelsz� bek�r�se a felhaszn�l�t�l.
//Megadott adatok kikeres�se �s ellen�rz�se az accounts.txt f�jlb�l.
//Ha a megadott email c�m vagy jelsz� hib�s, akkor k�t lehet�s�g van. Bel�p�s a regisztr�ci�s men�pontba �s regisztr�ci� elv�gz�se vagy adatok megad�sa �jra.
//Ha minden megadott adat megfelel�, akkor a bel�p�s sikeres.
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

//Kijelentkez�s
void Customer::logout()
{
	
	isLogin = false;
	cout << "Sikeres kijelentkezes." << endl;
	cout << "Nyomj meg egy gombot, hogy visszaterhess a menube." << endl;
	system("PAUSE");

}

//Csomag k�ld�se. Csomagot k�ldeni csak a regisztr�lt felhaszn�l� tud.
//5 karakter hossz� random sztring gener�l�sa
//V�ros kiv�laszt�sa, ahov� a csomagot k�ldeni szeretn�nk.
//Csomag m�reteinek bek�r�se. Ha a hossz�s�g vagy sz�less�g vagy magass�g nagyobb mint 100, akkor kiv�telt dobunk.
//Jelenlegi automata rekeszeinek ellen�rz�se. Ha nincs �res rekesz, akkor nem lehet csomagot feladni. Kiv�telt dobunk.
//Kiv�lasztott automata rekeszeinek ellen�rz�se. Ha nincs �res rekesz, akkor nem lehet csomagot feladni. Kiv�telt dobunk.
//Csomag �r�nak �s az �tvev� adatainak bek�r�se.
//Txt f�jl gener�l�sa a csomag �s a felad� adataival. A txt f�jl neve megegyezik az �tvev� email c�m�vel. Ez reprezent�lja az email k�ld�st.
//Sz�ll�t�si d�j kifizet�se.
//A fizetes egyszeruen annyi, hogy be kell irni 1200-at. Ha nem 1200-at irsz be, az azt jeleni, hogy sikertelen a tranzakcio es ujra meg kell adni az arat.
//Csomag behelyez�se a program �ltal megadott rekeszbe.
//Csomag sz�ll�t�sa.
//Az aktu�lis automata rekesz�nek ki�r�t�se �s a kiv�lasztott automata felt�lt�se a csomaggal.
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

//Csomag �tv�tele. Az �tv�telhez nem kell regisztr�lni �s bejelentkezni.
//Meg kell adni az email-ben kapott csomag azonos�t�t. Hib�s azonos�t� eset�n visszat�r�s a men�be. Az email k�ld�st egy txt f�jl reprezent�lja.
//Ha a csomag m�g nincs kifizetve akkor ki kell fizetni az �r�t.
//A fizetes annyi, hogy be kell irni a kepernyon megjeleno arat. Ha nem annyit irsz be, akkor sikertelen a tranzakcio es ujra meg kell adni az arat.
//Csomag �tv�tele a megfelel� rekeszb�l.
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

