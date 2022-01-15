
//Fisier PolishNotation.h->Contine implementarile a doua clase, anume Token si Parser, ce vor fi utilizate impreuna pentru a permite evaluarea expresiilor aritmetice folosind stiva.

#pragma once

#include "StackArray.h" //vom folosi stiva drept vector
#include<string.h> //Vectori de caractere C
#include <string> //Clasa std::string

//Clasa Token:->realizeaza o analiza lexicala a unei expresii aritmetice
class Token {

protected:

	//Sir de caractere in care vom stoca expresia aritmetica
	string data;

public:

	Token(){}

	//Constructor de initializare-initializeaza membrul data cu caracterul s.
	Token(const char s) {
		
		data += s;
	}

	//Constructor de copiere, copiaza membrul data al clasei t in instanta curenta a clasei Token
	Token(Token const& t) {
		
		data = t.data;
	}

	Token(string const& str) {
	
		data += str;
	}

	string getData() {
		return data;
	}

	//Verifica daca token-ul curent este sau nu operator
	bool isOperator() {

		string operators = "+-*/";
		bool found = false;
		if (data.size() == 1) {
			for (int i = 0; i < operators.length(); i++) {
				if (data.find(operators[i]) != string::npos)
					found = true; //token-ul a fost gasit
			}
			return found;
		}
		return false;
	}


	//Verifica daca token-ul curent este sau nu un operand
	bool isOperand() {

		//Parcurgem token-ul
		for (int i = 0; i < data.length(); i++) {

			if (isalpha(data[i]))
				continue;
			//Situatia in care token-ul nu este un numar intreg valid
			if (data[i] < '0' || data[i]>'9')
				return false;
		}

		//Token valid
		return true;

	}

	bool isLiteral() {
		return isalpha(this->data[0]);
	}

	//Obtine prioritatea unui operand
	int getPriority() {
		
		char operators[] = "+-*/";

		if (isOperator())
			for (int i = 0; i < strlen(operators); i++)
				if (operators[i] == data[0])
					//Indicele aferent operatorilor din sirul operators indica si prioritatea acestora
					return i;
		//Daca membrul data al clasei curente nu este un operator, vom retunra -1, semn ca nu are prioritate.
		return -1;
	}

	//Returneaza valoarea curenta a tokenului in situatia in care acesta este un operand. In caz contrar, 0.
	unsigned int getValue() {


		if (!isOperand())
			return 0;

		//Valoarea in care vom stoca rezultatul conversiei
		unsigned int value = 0;

		//Parcurgem token-ul
		for (int i = 0; i < data.length(); i++)
			value = value * 10 + (data[i] - '0');

		return value;

	}

	//Obtine token-ul curent
	string getToken() {

		return this->data;
	}
};


//Inverseaza un array de tokens
void reverseTokensArray(Array<Token>& expr) {

	int idx = 0;
	Array<Token>res(expr.getSize());
	for (int i = res.getSize() - 1; i >= 0; i--)
		res[idx++] = expr[i];

	expr = res;
}

//Functie ce construieste forma poloneza postfixata, primind drept parametru un string, reprezentand token-urile ce compun forma prefixata si un array de tokens in care va stoca rezultatul
void buildpostFixFromString(string s, Array<Token>& arr) {
	//Contor vector
	int counter = 0;

	//Sir de operatori
	string op = "+-*/";
	for (int i = 0; i < s.size();)
	{
		string builder="";
		//Daca caracterul s[i] este spatiu, functia trece mai departe
		if (s[i] == ' ') {
			i += 1;
		}

		//Daca se gaseste un operator se adauga in vectorul suport aferent expresiei postfixate si iteratia continua
		if (op.find(s[i]) != string::npos)
			arr[counter++]=Token(s[i++]);

		else {
			//Daca se gaseste o secventa de cifre neseparate de spatii sau operatori, se adauga numerele separat in array.
			if (isdigit(s[i]) || isalpha(s[i])) {
				int j = i;
				while (s[i] != ' ' && op.find(s[i])==string::npos && i < s.size()) {
					builder += s[i++];
				}
				arr[counter++] = builder;

			}
		}

		//Apelam setter-ul pentru a seta dimensiunea efectiva a array-ului suport pentru forma poloneza postfixata
		arr.setSize(counter);

	}
}


//Clasa Parser:contine 2 vectori de tip Token ce vor corespunde reprezentarii expresiei de intrare in forma infixata (normala) si postfixata.

class Parser {

private:

	//Vector pentru forma normala
	Array<Token> tokensInFix;

	//Vector pentru forma postfixata
	Array<Token>tokensPostFix;

	//Vector pentru forma prefixata
	Array<Token>tokensPreFix;

	//Numarul de elemente efective din cei trei vectori declarati anterior
	int inCount, postCount,preCount;

public:

	//Constructorul de initializare, primeste ca si parametru un sir de caractere reprezentand expresia, respectiv un alt sir in care se specifica felul in care se poate apela metoda de parsare a expresiei catre forma infixata
	Parser(string s,string choice) {
		inCount = postCount = preCount = 0;
		this->tokensInFix=Array<Token>(20,0);
		this->tokensPostFix = Array<Token>(20, 0);
		this->tokensPreFix = Array<Token>(20, 0);
		if (choice == "math")
			parseMathematicExpression(s);
		else
			parseStringExpression(s);
	}


	//Parseaza expresia matematica (cu  operanzii valori numerice) stocata in sirul de caractere pasat ca si parametru la forma infixata (normala)
	void parseMathematicExpression(string s) {
	
		//Operatorii
		string operators = "+-*/";

		//Parcurgem expresia caracter cu caracter
		for (int i = 0; i < s.length();)
		{
			//Token curent
			string strToken;
			//Dimensiune token
			int k = 0;
			//Daca este operand numeric, se adauga la token toti operanzii care il preceda
			if (isdigit(s[i]))
			{
				int j = i;
				//Se incearca construirea token-ului, in situatia in care dimensiunea acestuia depaseste dimensiunea vectorului asociat formei normale, se va lansa o exceptie
				try {
					while (isdigit(s[i]) && i<s.size())
						if (k >= 20)
							throw PolishNotationException();
						else {
							strToken += s[i++];
							k++;
						}
				}
				catch (PolishNotationException& pnex) {
					pnex.handle("Eroare!\n Operandul este prea lung!");
				}

			}
			//Se adauga rand pe rand operatorii ce apar in expresie
			else
			{
				//Este operator
				if (operators.find(s[i]) != string::npos) {
					strToken += s[i];
					k++;
					i++;
				}

			}

			try {
				//Daca token-ul curent are dimensiune 0, se va lansa o exceptie, altfel se introduce token-ul in vectorul suport formei infixate
				if (k==0)
					throw PolishNotationException();
				Token tk(strToken);
				tokensInFix[inCount++] = tk;
			}
			//Tratare exceptii
			catch (PolishNotationException& pnex) {
				pnex.handle("Eroare!\nExpresia este invalida!");

			}
		}
		tokensInFix.setSize(inCount);
	}

	//Parseaza expresia matematica (cu operanzii litere) stocata in sirul de caractere pasat ca si parametru la forma infixata (normala)
	void parseStringExpression(string s) {

		//Operatorii
		string operators = "+-*/";

		//Parcurgem expresia caracter cu caracter
		for (int i = 0; i < s.length();)
		{
			//Token curent
			string strToken;
			//Dimensiune token
			int k = 0;
			//Daca este operand numeric, se adauga la token toti operanzii care il preceda
			if (isalpha(s[i]))
			{
				int j = i;
				//Se incearca construirea token-ului, in situatia in care dimensiunea acestuia depaseste dimensiunea vectorului asociat formei normale, se va lansa o exceptie
				try {
					while (isalpha(s[i]) && i < s.size())
						if (k >= 20)
							throw PolishNotationException();
						else {
							strToken += s[i++];
							k++;
						}
				}
				catch (PolishNotationException& pnex) {
					pnex.handle("Eroare!\n Operandul este prea lung!");
				}

			}
			//Se adauga rand pe rand operatorii ce apar in expresie
			else
			{
				//Este operator
				if (operators.find(s[i]) != string::npos) {
					strToken += s[i];
					k++;
					i++;
				}

			}

			try {
				//Daca token-ul curent are dimensiune 0, se va lansa o exceptie, altfel se introduce token-ul in vectorul suport formei infixate
				if (k == 0)
					throw PolishNotationException();
				Token tk(strToken);
				tokensInFix[inCount++] = tk;
			}
			//Tratare exceptii
			catch (PolishNotationException& pnex) {
				pnex.handle("Eroare!\nExpresia este invalida!");

			}
		}
		tokensInFix.setSize(inCount);
	}

	//Metoda utilizata pentru transformarea expresiei din forma poloneza normala in forma poloneza postfixata
	void inFixToPostFix() {

		//Stiva cu ajutorul careia se va realiza transformarea expresiei
		StackArray<Token>stack(15);

		int i = 0;
		while (i < tokensInFix.getSize()) {
			//Daca token-ul curent din vectorul aferent expresiei poloneze normale este operand
			if (tokensInFix[i].isOperand()) {
				tokensPostFix[postCount++] = tokensInFix[i];
			}

			//Cazul contrar (token-ul este operator)
			else {
				//Cat timp stiva nu este goala si prioritatea operatorului din varful stivei este mai mare decat cea a operatorului din expresia normala
				while (!stack.isEmpty() && stack.getTop().getPriority() > tokensInFix[i].getPriority()) {

					//Retinem elementul din varful stivei si ulterior il eliminam
					Token t = stack.getTop();
					stack.pop();
					//Adaugam tokenul stocat anterior la vectorul suport al expresiei poloneze postfixate
					tokensPostFix[postCount++] = t;
				}
				stack.push(tokensInFix[i]);
			}
			i++;
		}
		//Mai apoi, adaugam toate elementele ramase in stiva la vectorul suport tokensPostFix
		while (!stack.isEmpty())
		{
			Token t = stack.getTop();
			stack.pop();
			tokensPostFix[postCount++] = t;
		}

		tokensPostFix.setSize(postCount);

	}		

	//Metoda utilizata pentru transformarea unei expresii infixate (normale) intr-o expreise prefixata
	void inFixToPrefix() {

		//Initializam stiva in care vom insera operatorii
		StackArray<Token>stack(15);
		//Inversam vectorul de tokens ce contine stocata forma infixata a unei expresii
		reverseTokensArray(tokensInFix);

		//Parcurgem vectorul ce tocmai a fost inversat
		for (int i = 0; i < inCount; i++)
		{
			//Daca token-ul curent este un operand, il adaugam la vectorul in care vom stoca expresia in forma poloneza prefixata
			if (tokensInFix[i].isOperand())
				tokensPreFix[preCount++] = tokensInFix[i];

			//Cazul contrar, token-ul este un operator
			else if (tokensInFix[i].isOperator()) {

				//Daca stiva operatorilor este vida, adaugam acel operator in stiva
				if (stack.isEmpty())
					stack.push(tokensInFix[i]);

				else {
					//Daca operatorul curent are o prioritate mai mare decat operatorul din varful stivei, atunci putem adauga operatorul in stiva de operatori
					if (tokensInFix[i].getPriority() > stack.getTop().getPriority())
						stack.push(tokensInFix[i]);

					//La fel, daca prioritatile coincid, se poate face inserarea in stiva a operatorului
					else if (tokensInFix[i].getPriority() == stack.getTop().getPriority())
						stack.push(tokensInFix[i]);

					//Daca prioritatea elementului curent este mai mica decat cea a operatorului din varful stivei, atunci se elimina din varful stivei operatorii si se adauga la vectorul rezultant, pana cand se obtine o relatie de comparatie precum cele tratate anterior
					else if (tokensInFix[i].getPriority() < stack.getTop().getPriority()) {

						while (!stack.isEmpty() && tokensInFix[i].getPriority() < stack.getTop().getPriority()) {
							Token t = stack.getTop();
							stack.pop();
							tokensPreFix[preCount++] = t;
						}

						stack.push(tokensInFix[i]);
					}
				}
			}
		}
			
		//In cazul in care au mai ramas operatori in stiva, ii adaugam in array, rand pe rand, pana cand stiva devine goala
			while (!stack.isEmpty()) {
				Token t = stack.getTop();
				stack.pop();
				tokensPreFix[preCount++] = t;
			}
			

			//Setam dimensiunea array-ului in care am stocat forma prefixata si ulterior il inversam, pentru a permite afisarea corecta a acestuia, implicit a formei poloneze prefixate.
			tokensPreFix.setSize(preCount);
			reverseTokensArray(tokensPreFix);
	}

	//Metoda care transforma o expresie matematica (alcatuita doar din operanzi valori numerice) din forma prefixata in forma poloneza inversa (postfixata).
	void PreFixToPostFix(){
		
		try {
			if (preCount == 0)
				throw PolishNotationException();
			
		}
		catch (PolishNotationException& pnex) {
			pnex.handle("Eroare!\n Nu a fost detectata nicio expresie in forma poloneza prefixata. Doriti sa creati o expresie prefixata pornind de la forma infixata introdusa? (Y/N)");
			char choice;
			cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				this->inFixToPrefix();
				displayPreFix();
			}
			else {
				return;
			}
		}

		cout << endl;
		//Ne asiguram ca vectorul tokensPostFix, in care vom stoca expresia transformata are un numar suficient de elemente pentru stocarea valorilor
		postCount =0;
		tokensPostFix.setSize(tokensPreFix.getSize());
		
		//Stiva utilizata pentru stocarea operanzilor 
		StackArray<Token>stack(15);

		int idx=tokensPreFix.getSize()-1;

		while (idx >= 0) {

			//Daca valoarea curenta aferenta expresiei poloneze prefixate este operator, atunci vom elimina doi operanzi din stiva, ii vom concatena cu operatorul si vom adauga tot token-ul rezultat inapoi in stiva
			if (tokensPreFix[idx].isOperator()) {

				string t1 = stack.getTop().getToken();
				//Adaugam spatii la primul element extas din varf, pentru a putea facilita parsarea sirului x in array-ul de tokens tokensPostFix
				t1 += " ";
				stack.pop();
				//Extragem al doilea operand
				string t2 = stack.getTop().getToken();
				stack.pop();
				//string op = tokensPreFix[idx].getToken()+" ";
				//Concatenam expresia t1 operator t2 si o adaugam inapoi in stiva
				stack.push((Token(t1+t2+tokensPreFix[idx].getToken())));
			}

			//Token-ul este un operand, il adaugam in stiva de operanzi
			else
				stack.push(tokensPreFix[idx]);
			idx--;
		}

		//Setam size-ul final al array-ului in care am stocat in ordine token-urile ce construiesc forma poloneza postfixata, pornind de la cea prefixata.
		tokensPostFix.setSize(tokensPreFix.getSize());
		postCount = tokensPostFix.getSize();

		//Obtinem rezultatul si apelam functia buildpostFixFromString pentru a putea popula array-ul aferent formei inverse cu token-urile retinute in sirul x.
		string x = stack.getTop().getToken();
		buildpostFixFromString(x, tokensPostFix);
	}




	//Metoda utilizata pentru afisarea pe ecran a vectorului suport al metodei normale
	void displayInFix() {

		cout << "Forma expresiei poloneze infixate (normale) este:\n";

		for (int i = 0; i < inCount; i++) {
			if (tokensInFix[i].isOperator())
				cout << tokensInFix[i].getToken() << " ";
			else {
				//Operanzi numerici
				if (!tokensInFix[i].isLiteral())
					cout << tokensInFix[i].getValue() << " ";
				else
					//Posibilitatea de a avea litere drepte operanzi
					cout << tokensInFix[i].getToken() << " ";
			}
		}
		
		cout << '\n';
	}

	//Metoda utilizata pentru afisarea pe ecran a vectorului suport al metodei poloneze postfixate
	void displayPostFix() {

		cout << "Forma expresiei poloneze inverse (postfixate) este: \n";
		for (int i = 0; i < this->tokensPostFix.getSize(); i++) {
			if (tokensPostFix[i].isOperator())
				cout << tokensPostFix[i].getToken() << " ";
			else {
				//Operanzi numerici
				if (!tokensPostFix[i].isLiteral())
					cout << tokensPostFix[i].getValue() << " ";
				else
					//Posibilitatea de a avea litere drepte operanzi
					cout << tokensPostFix[i].getToken() << " ";
			}
		}

		cout << '\n';
	}

	//Metoda utilizata pentru afisarea pe ecran a vectorului suport al metodei poloneze prefixate
	void displayPreFix() {

		cout << "Forma expresiei poloneze prefixate este: \n";
		for (int i = 0; i < preCount; i++) {
			if (tokensPreFix[i].isOperator())
				cout << tokensPreFix[i].getToken() << " ";
			else {
				//Operanzi numerici
				if (!tokensPreFix[i].isLiteral())
					cout << tokensPreFix[i].getValue() << " ";
				else
					//Posibilitatea de a avea litere drepte operanzi
					cout << tokensPreFix[i].getToken() << " ";
			}
		}

		cout << '\n';

	}
};

#pragma endregion

