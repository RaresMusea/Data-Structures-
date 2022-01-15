//Cod aferent problemei 14

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "StackArray.h" //foloseste stiva statica
#include <map> //Utilizeaza structura de container asociativ sortat (map) pentru a putea identifica stivele si cozile instantiate in urma inserarii comenzilor pe baza unui sir de caractere (identificator)
#include "QueueArray.h"//foloseste coada statica


//Variabile globale:
//Numar de elemente stive/cozi
int n;

//2 map-uri in care vom mapa variabilele de tip stiva/coada, initializate de catre user din linia de comanda, pe baza unui identifier
map<string, StackArray<int>> Stacks;
map<string, QueueArray<int>>Queues;


//Functie care verifica daca sirul introdus de la tastatura de catre utilizator descrie unul sau mai multi identificatori al unei stive sau cozi
//In cazul in care sirul contine un singur identificator, functia returneaza 1, altfel, o valoarea >1, reprezentand numarul identificatorilor gasiti in sir
int verifyTokens(string const& s)
{
	//Pentru delimitarea sirului in token-uri, s-a utilizat conversia explicita a unui string catre char* si functia C strtok().

	char* cstr = new char[s.length() + 1];
	strcpy(cstr, s.c_str());
	const auto delimitator = " ";
	char* token = strtok(cstr, delimitator);
	int count = 1;

	while (token != nullptr)
	{
		count++;
		token = strtok(nullptr, delimitator);
	}

	if (count > 1)
		count--;

	//Returneaza numarul de token-uri
	return count;
}

//Functie utilizata pentru a cauta valori numerice intr-un string s, pasat ca si parametru
//Functia returneaza indexul primei valori gasite in sir.
//In cazul in care sirul nu contine nicio valoare numerica, functia returneaza -1
int findNumberInString(string const& s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]))
			return i;

	return -1;
}

//Populeaza o stiva de intregi cu o lista de valori, stocate sub forma unui sir de caractere.
//Sirul-parametru id va retine identificatorul unic al stivei, ce va urma a fi populata.
void PopulateStack(StackArray<int>& st, string const& values, string const& id)
{

	int num = 0, idx = 0;

	//Cat timp indexul sirului de numere nu depaseste dimensiunea acestuia, se pot adauga valorile continute de sir in stiva

	while (idx < values.length())
	{
		if (values[idx] == ' ')
		{
			st.push(num);
			num = 0;
			idx++;
			cout << "Prompter:S-a adaugat in stiva " << id << " valoarea " << st.getTop() << ".\n";
			continue;
		}
		num = num * 10 + values[idx] - '0';

		idx++;
	}

	//Se adauga elementul din varful stivei
	st.push(num);
	cout << "Prompter:S-a adaugat in stiva " << id << " valoarea " << st.getTop() << ".\n";
}

//Populeaza o coada de elemente intregi cu o lista de valori, stocate sub forma unui sir de caractere.
void PopulateQueue(QueueArray<int>& q, string const& values, string const& id)
{
	int num = 0, idx = 0;

	//Cat timp indexul sirului de numere nu depaseste dimensiunea acestuia, se pot adauga valorile continute de sir in coada

	while (idx < values.length())
	{
		if (values[idx] == ' ')
		{
			q.enQueue(num);
			cout << "Prompter:S-a adaugat in coada " << id << " valoarea " << num << "\n";
			num = 0;
			idx++;

		}
		num = num * 10 + values[idx] - '0';

		idx++;
	}

	//Adauga ultima valoare in coada
	q.enQueue(num);
	cout << "Prompter:S-a adaugat in coada " << id << " valoarea " << num << "\n";
}



//Functie ce confera functionalitatea prompter-ului
void Prompter()
{
	string command;
	cout << "Care este dimensiunea maxima a colectiilor ce vor urma a fi create?"; cin >> n;
	cout << "\n\n";
	cout << ">\t";
	cin.ignore();
	getline(cin, command);

	//Cat timp comanda nu incepe cu litera E, programul continua a rula
	while (command[0] != 'E')
	{
		string varIdentifier;
		switch (command[0])
		{

			//In situatia in care comanda incepe cu litera S,se va crea o stiva, identificata pe baza identificatorului
		case 'S':

			//Gaseste identificatorul
			varIdentifier = command.substr(2, command.size() - 1);
			//Daca un singur identificator a fost gasit
			if (verifyTokens(varIdentifier) == 1) {

				//Se utilizeaza iteratori pentru parcurgerea map-ului de stive si se creaza stiva doar daca identificatorul este unic (nu a mai fost utilizat anterior pentru a crea alta stiva)
				auto it = Stacks.find(varIdentifier);
				if (it == Stacks.end()) {
					Stacks.insert(pair<string, StackArray<int>>(varIdentifier, n));
					cout << "Prompter:Stiva " + varIdentifier + " a fost creata cu succes.\n";
				}
				//Daca stiva identificata pe baza identificatorului introdus exista deja, se va afisa un mesaj de eroare
				else
					cout << "Prompter:EROARE! Stiva " + varIdentifier + " exista deja!\n";
			}

			//Daca s-au gasit mai multi identificatori, stiva nu va putea fi creata. 
			else
				cout << "Prompter:EROARE! Identificatorul " << varIdentifier << " nu este valid!\n";
			break;

			//In situatia in care comanda incepe cu litera Q,se va crea o coada, identificata pe baza identificatorului
		case 'Q':

			//Se gaseste identificatorul pe baza sirului ce stocheaza comanda introdusa de catre utilizator de la tastatura
			varIdentifier = command.substr(2, command.size() - 1);
			if (verifyTokens(varIdentifier) == 1) {

				//Utilizand iteratori, se va parcurge map-ul ce contine lista cozilor create, pentru a vedea daca exista deja o coada referita prin acelasi identificator ca cel identificat in comanda curenta
				auto it = Queues.find(varIdentifier);

				//Daca identificatorul introdus este unul nou, se creaza noua coada referita prin identificator
				if (it == Queues.end())
				{

					Queues.insert(pair<string, QueueArray<int>>(varIdentifier, n));
					cout << "Prompter:Coada " + varIdentifier + " a fost creata cu succes.\n";
				}

				//Daca exista inca o coada cu acelasi identificator, prompter-ul va afisa un mesaj de eroare.
				else
					cout << "Prompter:EROARE! Coada " << varIdentifier << " exista deja!\n";
			}

			//In cazul in care se introduc mai multi identificatori, coada nu va putea fi creata si prin urmare, se va afisa un mesaj de eroare
			else
				cout << "Prompter:EROARE! Identificatorul " << varIdentifier << " nu este valid!\n";
			break;

			//In situatia in care comanda incepe cu litera D, se va cauta identificatorul continut in sirul ce stocheaza comanda. Daca este un identificator valid, se vor sterge toate colectiile (stive/cozi) indetificate pe baza identificatorului respectiv, cat si sirul de referire.
		case 'D':

			//Se gaseste identificatorul colectiilor
			varIdentifier = command.substr(2, command.size() - 1);

			//Daca identificatorul introdus este valid
			if (verifyTokens(varIdentifier) == 1) {

				//Se folosesc 2 iteratori pentru a parcurge cele 2 map-uri si pentru a gasi colectiile referite prin identificatorul introdus.
				auto queueIterator = Queues.find(varIdentifier);
				auto stackIterator = Stacks.find(varIdentifier);

				bool foundStacks = false, foundQueues = false;

				//Daca identificatorul descrie o coada existenta, se va sterge coada respectiva din memorie, alaturi de identificator
				if (queueIterator != Queues.end())
				{
					Queues.erase(varIdentifier);
					cout << "Prompter:Coada " + varIdentifier + " a fost stearsa cu succes.\n";
					foundQueues = true;
				}

				//Daca identificatorul descrie o stiva existenta, se va sterge stiva respectiva din memorie, alaturi de identificator
				if (stackIterator != Stacks.end()) {

					Stacks.erase(varIdentifier);
					cout << "Prompter:Stiva " + varIdentifier + " a fost stearsa cu succes.\n";
					foundStacks = true;

				}

				//Daca nu a fost gasita nicio colectie inregistrata pe baza identificatorului gasit, se va afisa un mesaj de eroare.
				if (foundStacks == false && foundQueues == false)
					cout << "EROARE! Nu s-a putut gasi nicio colectie (stiva, coada), intregistrata pe baza identificatorului " + varIdentifier << '.\n';
			}
			//Daca identificatorul introdus nu este valid, la fel, se va afisa un mesaj de eroare.
			else
				cout << "Prompter:EROARE! Identificatorul " << varIdentifier << " nu este valid!\n";
			break;

			//Daca se introduce o comanda ce incepe cu litera A, se vor adauga in stivele sau cozile referite prin intermediul identificatorului specificat, valorile intregi introduse prin spatii, dupa identificator, din comanda. 
		case 'A': {

			//Se cauta in sirul ce stocheaza comanda o secventa de numere, pe baza functiei findNumberInString(),definita anterior
			string numberSequence;
			const int idx = findNumberInString(command);

			//Daca se gaseste un numar in string, se salveaza secventa de numere si se gaseste identificatorul
			if (idx != -1) {
				varIdentifier = command.substr(2, idx - 3);
				numberSequence = command.substr(idx, command.size() - 1);
			}
			else
				varIdentifier = command.substr(2, command.size() - 1);

			//In situatia in care comanda introdusa de la tastatura de catre utilizator contine un singur token (identificator) ce face referire la o stiva si cel putin o valoare numerica, atunci se vor adauga valorile din secventa de numere in stiva
			if (verifyTokens(varIdentifier) == 1 && idx != -1)
			{

				auto stackIterator = Stacks.find(varIdentifier);
				auto queueIterator = Queues.find(varIdentifier);

				//Daca stiva poate fi identificata
				if (stackIterator != Stacks.end())
				{
					//Populam stiva, prin apelul functiei PopulateStack()
					PopulateStack(Stacks[varIdentifier], numberSequence, varIdentifier);

				}
				//In cazul in care stiva nu a putut fi identificata in baza identificatorului, un mesaj de eroare se va afisa
				else
					cout << "EROARE! Colectie de tip stiva cu identificatorul " << varIdentifier << " nu a putut fi identificata!\n";

				//In cazul in care coada poate fi identificata
				if (queueIterator != Queues.end())
				{
					//Populam coada prin apelul functiei PopulateQueue().
					PopulateQueue(Queues[varIdentifier], numberSequence, varIdentifier);
				}
				else
					//In cazul in care coada nu a putut fi identificata in baza identificatorului, un mesaj de eroare se va afisa
					cout << "EROARE! Colectia de tip coada cu identificatorul " << varIdentifier << " nu a putut fi identificata!\n";

			}
			else
				//In sitautia in care secventa de valori numerice este invalida, un mesaj de eroare se va afisa
				cout << "EROARE! Prompter:Nu s-a introdus nicio secventa de elemente care sa se adauge in colectia " << varIdentifier << ".\n";

			break;
		}

				//Cazul in care comanda incepe cu caracterul X- se vor extrage din colectia referita prin identificator un numar specificat de valori.Numarul de valori ce vor urma a fi extrase va fi specificat imediat dupa identificator si separat fata de acesta printr-un spatiu;
		case 'X':
		{
			//Se cauta in sirul de caractere ce stocheaza comanda o valoare numerica 
			string removeCount;
			const int idx = findNumberInString(command);

			//Daca sirul contine o valoare numerica, se va gasi identificatorul variabilei ce va urma a fi modificate
			if (idx != -1) {
				varIdentifier = command.substr(2, idx - 3);
				removeCount = command.substr(idx, command.size() - 1);

				//Daca numarul de elemente ce vor urma a fi eliminate, ce reprezinta subsirul sirului ce stocheaza comanda contine mai multe subsiruri (tokens), se va afisa un mesaj de eroare.
				if (verifyTokens(removeCount) != 1) {
					cout << "Prompter:EROARE! Nu se poate deduce numarul de elemente ce trebuie a fi eliminat din colectia cu identificatorul " << varIdentifier << ".\n";
					break;
				}
			}
			else
				varIdentifier = command.substr(2, command.size() - 1);

			//In cazul in care comanda contine un singur identificator si o singura valoare numerica existenta:
			if (verifyTokens(varIdentifier) == 1 && idx != -1)
			{

				//Se vor cauta cozile si stivele cu identificatorul gasit in structura comenzii
				auto stackIterator = Stacks.find(varIdentifier);
				auto queueIterator = Queues.find(varIdentifier);

				//Daca exista o stiva referita prin identificator:
				if (stackIterator != Stacks.end())
				{
					//Daca stiva este goala, nu se mai pot elimina valori, deci se va afisa un mesaj de eroare
					if (Stacks[varIdentifier].isEmpty())
					{
						cout << "Prompter:EROARE! Stiva " << varIdentifier << " este goala!\n";
						break;
					}

					//Altfel, se elimina cele removeCount elemente din stiva
					for (int i = 0; i < stoi(removeCount); i++) {
						cout << "Prompter:S-a extras elementul " << Stacks[varIdentifier].getTop() << " din stiva cu identificatorul " << varIdentifier << " .\n";
						Stacks[varIdentifier].pop();
						if (Stacks[varIdentifier].isEmpty())
						{
							cout << "Prompter:EROARE! Stiva " << varIdentifier << " s-a golit!\n";
							break;
						}
					}

				}
				//Daca nu exista nicio stiva ce poate fi referita prin identificatorul dedus din forma comenzii, se va afisa un mesaj de avertizare.
				else
					cout << "EROARE! Colectie de tip stiva cu identificatorul " << varIdentifier << " nu a putut fi identificata!\n";

				//Daca exista o stiva referita prin identificator:
				if (queueIterator != Queues.end())
				{
					//In situatia in care coada este goala, nu se mai pot elimina valori, deci se va afisa un mesaj de eroare
					if (Queues[varIdentifier].isEmpty())
					{
						cout << "Prompter:EROARE! Coada " << varIdentifier << " este goala!\n";
						break;
					}

					//Altfel, se elimina cele removeCount elemente din coada
					for (int i = 0; i < stoi(removeCount); i++)
					{
						cout << "Prompter:S-a extras elementul " << Queues[varIdentifier].getHead() <<
							" din coada cu identificatorul " << varIdentifier << " .\n";
						Queues[varIdentifier].deQueue();
						if (Queues[varIdentifier].isEmpty())
						{
							cout << "Prompter:EROARE! Coada " << varIdentifier << " s-a golit!\n";
							break;
						}
					}
				}
				//Daca nu exista nicio stiva ce poate fi referita prin identificatorul dedus din forma comenzii, se va afisa un mesaj de avertizare.
				else
					cout << "Prompter:EROARE! Colectia de tip coada cu identificatorul " << varIdentifier << " nu a putut fi identificata!\n";

			}
			//In situatia in care numarul elementelor ce vor urma a fi eliminate este invalid, un mesaj de eroare se va afisa
			else
				cout << "Prompter:EROARE! Prompter:Nu s-a introdus nicio secventa de elemente care sa descrie numarul elementelor ce vor urma a fi extrase din colectia " << varIdentifier << ".\n";

			break;
		}

		//In situatia in care comanda incepe cu caracterul P, se vor extrage din colectia referita prin identificatorul specificat toate valorile, dupa care se vor afisa
		case 'P':
		{
			//Se retine forma identificatorului
			varIdentifier = command.substr(2, command.size() - 1);
			if (verifyTokens(varIdentifier) == 1) {

				//Daca identificaotrul este un singur cuvant, se vor cauta toate colectiile referite prin acesta
				auto stackIterator = Stacks.find(varIdentifier);
				auto queueIterator = Queues.find(varIdentifier);

				//Daca s-a gasit o stiva refetita prin acest identificator si stiva este goala, se va afisa un mesaj de eroare
				if (stackIterator != Stacks.end())
				{
					if (Stacks[varIdentifier].isEmpty())
					{
						cout << "Prompter:Stiva " << varIdentifier << " este goala!\n";
						break;
					}
					cout << "Prompter:Se vor elimina toate elementele din stiva cu identificatorul " << varIdentifier << " si se vor afisa:\n";

					int size = Stacks[varIdentifier].getCount();
					//Se elimina rand pe rand elementele din stiva si se vor afisa.
					for (int i = 0; i < size; i++) {
						cout << Stacks[varIdentifier].getTop() << '\n';
						Stacks[varIdentifier].pop();
					}

				}
				//In situatia in care nu s-a gasit nicio stiva cu acel identificator
				else
					cout << "Prompter:EROARE! Nu s-a gasit nicio colectie de tip stiva, identificata pe baza identificatorului " << varIdentifier << ".\n";

				//Daca s-a gasit o coada refetita prin acest identificator si aceasta este goala, se va afisa un mesaj de eroare
				if (queueIterator != Queues.end())
				{
					cout << "Prompter:Se vor elimina toate elementele din coada cu identificatorul " << varIdentifier << " si se vor afisa:\n";

					cout << Queues[varIdentifier];
					//Se afiseaza si se extrag toate elementele din coada
					int size = Queues[varIdentifier].getCount();
					for (int i = 0; i < size; i++)
						Queues[varIdentifier].deQueue();
				}
				else
					//In situatia in care nu s-a gasit nicio coada cu acel identificator
					cout << "Prompter:EROARE! Nu s-a gasit nicio colectie de tip coada, identificata pe baza identificatorului " << varIdentifier << ".\n";


			}
			//Caz contrar:identificator invalid
			else
				cout << "Prompter:EROARE! Identificatorul " << varIdentifier << " nu este valid!\n";

		}

		//In situatia in care identificatorul incepe cu litera M, se va face merge, in colectia referita prin al treilea identificator, la celelalte 2 colectii, referite prin primii 2 identificatori
		//In cazul in care colectiile nu sunt sortate, merge-ul va esua.
		case 'M':
		{
			//Identificam cei 3 identificatori
			string commandSubstr = command.substr(2, command.size() - 1);
			char* cStyleString = new char[commandSubstr.length() + 1];
			strcpy(cStyleString, commandSubstr.c_str());

			//Daca se introduc mai multi identificatori decat 3, se va afisa un mesaj de eroare
			if (verifyTokens(cStyleString) != 3) {
				cout << "Prompter:Eroare! Numar incorect de identificatori introdusi!\n";
				break;
			}

			char* ptr = strtok(cStyleString, " ");
			//Separam identificatorii (cei 3), in 3 siruri separate de caractere.
			string id1 = (string(ptr));
			ptr = strtok(nullptr, " ");
			string id2 = (string(ptr));
			ptr = strtok(nullptr, " ");
			string id3 = (string(ptr));

			//In cazul in care primele 2 colectii (stive sau cozi) sunt referite prin identificatori diferiti, se trece la iterclasare.
			if (id1 != id2)
			{
				//Se cauta colectiile identificate prin cei 3 identificatori
				auto id1Found = Stacks.find(id1);
				auto id2Found = Stacks.find(id2);
				auto id3Found = Stacks.find(id3);

				auto id1qFound = Queues.find(id1);
				auto id2qFound = Queues.find(id2);
				auto id3qFound = Queues.find(id3);

				//In situatia in care vorbim de stive, se verifica daca identificatorii exista.
				//Daca acestia exsita, se va trece la concaternare
				if (id1Found != Stacks.end() && id2Found != Stacks.end() && id3Found != Stacks.end())
				{
					//Se realizeaza concatenarea si se afiseaza rezultatul
					Stacks[id3] = Stacks[id1].merge(Stacks[id2]);
					cout << Stacks[id3];
				}
				//Caz contrar:nu exista 3 stive referite prin identificatorii dati
				else
					cout << "Prompter:EROARE!Unul din identificatorii " << id1 << ", " << id2 << ", sau chiar " << id3 << " nu descriu nicio colectie de tip stiva!\n";

				//In situatia in care vorbim de cozi, se verifica daca identificatorii exista.
				//Daca acestia exsita, se va trece la concatenarre
				if (id1qFound != Queues.end() && id2qFound != Queues.end() && id3qFound != Queues.end())
				{
					Queues[id3] = Queues[id1].merge(Queues[id2]);
					cout << Queues[id3];
				}
				//Identificatorii nu se refera la nicio colectie
				else
					cout << "Prompter:EROARE!Unul din identificatorii " << id1 << ", " << id2 << ", sau chiar " << id3 << " nu descriu nicio colectie de tip coada!\n";

			}
			//Interclasare irealizabila
			else
			{
				cout << "Prompter:EROARE!Nu se poate efectua interclasarea colectiilor de tip stiva sau coada, identificate prin " << id1 << "," << id2 << " si " << id3 << ".\n";
			}

		}
		case 'E':
			exit(0);

		default:
			cout << "Prompter:Comanda invalida!\n";
			break;
		}
		//Citirea urmatoarei comenzi
		cout << ">\t";
		getline(cin, command);


	}

}
