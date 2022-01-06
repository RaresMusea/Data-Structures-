//Header File Polinom.h-> Utilizeaza conceptul de array sortat si clasa Term in vederea implementarii structurii de date de polinom, dar si a operatiilor cu aceste concepte matematice.
#pragma once

#include "SortArray.h"
#include "Term.h"
#include<string>

//Clasa generica Polinom
template <class T>
class Polinom {

public:
	//Vectorul suport
	SortArray<Term<T>>data;

	//Gradul
	unsigned int degree;

public:
	//Constructori:
	//Constructorul implicit
	Polinom();

	//Constructor de initializare cu un termen
	Polinom(Term<T> const& t);

	//Destructor:
	~Polinom();

	//Metoda care verifica daca un polinom are gradul si coeficientul nul
	bool isNull();

	//Metoda care verifica daca un polinom este monic (un polinom este monic daca depinde de o singura variabila,care, la gradul cel mai mare are coeficientul 1)
	bool isMonic();

	//Metoda care verifica daca in polinom se regasesc valori cu coeficienti egali cu 0 
	bool hasZeroCoefficientTerms();


	void makeMonic();

	//Metoda care elimina termenii cu coeficientul 0 din polinom
	void refactor();

	//Getter ce returneaza vectorul de termeni in care polinomul este stocat.
	SortArray<Term<T>>& getData();

	//Getter ce returneaza gradul polinomului
	unsigned int getDegree();

	//Metoda ce adauga un termen la polinomul curent
	Polinom<T>& addTerm(Term<T> const& t);

	//Metoda ce elimona un termen din polinomul curent
	Polinom<T> removeTerm(Term<T> & t);

	//Metoda ce permite adaugarea unui termen la polinom, prin specificarea parametrilor specifici termenului
	Polinom<T>& addValue(T  t1, int gr);

	//Metoda ce permite elinimarea unui termen din polinom prin specificarea explicita a parametrilor termenului de eliminat
	Polinom<T>& removeValue(T t1,  int gr);


	//Supraincarcari de operatori:
	//Supraincarcarea operatorului de atribuire, permite egalarea unui polinom cu un monom
	Polinom<T>& operator= (Term<T> const& t);

	//Supraincarcarea operatorului de atribuire, permite copierea unui polinom in alt polinom
	Polinom<T>& operator= (Polinom<T> const& p);

	//Supraincarcarea operatorului de insumare, permite adaugarea unui termen la polinom
	Polinom<T>& operator+ (Term<T> const& t);

	//Supraincarcarea operatorului de insumare, permite adaugarea unei constante la polinomul curent
	Polinom<T>& operator+ (T const& t);

	//Supraincarcarea operatorului de insumare, permite adunarea a doua polinoame
	Polinom<T>& operator+ (Polinom<T> const& p);

	//Supraincarcarea operatorului de scadere, permite eliminarea unui termen dintr-un polinom
	Polinom<T>& operator- (Term<T>& t);

	//Supraincarcarea operatorului de scadere, permite eliminarea unei constante dintr-un polinom
	Polinom<T>& operator- (T& t);

	//Supraincarcarea operatorului de scadere, permite calculul diferentei a doua polinoame
	Polinom<T> operator- (Polinom<T>& p);

	//Supraincarcarea operetorului de inmultire, permite inmultirea polinomului cu o constanta
	Polinom<T>& operator * (T & t);

	//Supraincarcarea operatorului de inmultire, permite inmultirea polinomului cu un termen
	Polinom<T>& operator * (Term<T> & t);

	//Supraincarcarea operatorului de inmultire, permite calculul produsului a doua polinoame
	Polinom<T> operator * (Polinom<T> & p) const;

	//Supraincarcarea operatorului de impartire, permite calculul catului impartirii a doua polinoame
	Polinom<T> operator / (Polinom<T>& p);

	//Supraincarcarea operatorului modulo, permite calculul restului impartirii a doua polinoame
	Polinom<T> operator % (Polinom<T>& p);

	//Verifica daca un polinom este egal cu un termen
	bool operator == (Term<T>& t);

	//Metoda utilizata pentru evaluarea polinomului in punctul x
	T evaluate(T const& x);

	//Metoda utilizata pentru resetarea valorilor unei instante a clasei polinom
	Polinom<T>& reset();

	//Metoda responsabila de calculul impartirii a doua polinoame.
	//Parametrul display indica modul de functionare al metodei
	//Daca display are valoarea "quotient", metoda va returna catul impartirii
	//Daca display are orice alta valoare decat cea mentionata anterior, metoda va returna restul impartirii


	Polinom<T> divide(Polinom<T> &p,string display) const;
	//Metoda care realizeaza calculul catului si restului impartirii a doua polinoame si afiseaza rezultatele
	void longDivision(Polinom<T>& p);


	// Metoda ce implementeaza operatia de shiftare a unui polinom.
	//Consideram polinomul P(X). Aplicarea operatiei de shiftare asupra acestui polinom are efectul inmultirii polinomului P cu monomul x^n (pentru n pozitiv). Fiecare termen al polinomului este shiftat. Gradul k al termenului P(i) devine k+n in urma shiftarii.
	//Shiftarea cu un index negativ are efectul opus. Gradele devin puteri mai mici ale lui x Coeficientii ajunsi la valori negative in urma shiftarii sunt ignorati

	void shift(T n);

	//Metoda utilizata in cadrul functiei Divide, utilizata ulterior pentru impartirea a doua polinoame
	void set(int idx, Term<T> a);

	//Citeste polinomul de la tastatura
	void read();

	//Afiseaza polinomul
	void print();
	

	//Supraincarcarea operatorului de sciere in fluxul de intrare permite citirea de la tastatura a unui polinom
	friend istream& operator >> (istream& istr, Polinom<T>& p) {

		unsigned int deg;
		T coefficient;


		cout << "Care este gradul polinomului? ";
		istr >> deg;
		p.degree = deg;

		for (int i = 0; i <= deg; i++) {
			cout << "Termenul de grad " << i << ":\n";
			cout << "Coeficient: "; istr >> coefficient;
			p.addValue(coefficient, i);
		}

		//Eliminam elementul cu coeficientul 0
		
		if (p.data[0].coef == 0 && p.data.getSize()>1) {
			for (int i = 0; i < p.data.getSize() - 1; i++)
				p.data[i] = p.data[i + 1];

			p.data.setSize(p.data.getSize() - 1);
			p.degree = p.data[p.data.getSize() - 1].grade;
		}

		return istr;
	}


	//Supraincarcarea operatorului de scriere in fluxul de iesire:afiseaza continutul polinomului
	friend ostream& operator << (ostream& ostr, Polinom<T>& p) {
		
		unsigned int isFirst = 1;
		for (int i=p.data.getSize()-1; i >=0; i--)
		{
			if (p.data[i].coef > 0)
				cout << ((isFirst) ? "" : "+");

			if (p.data[i].grade == 0)
				cout << p.data[i].coef;
			else {
				if (p.data[i].coef == 1.0)
					cout << "X^" << p.data[i].grade;
				else {
					if (p.data[i].coef == -1.0)
						cout<< "-X^" << p.data[i].grade;
					else
						cout << p.data[i].coef << "X^" << p.data[i].grade;
				}
			}
			isFirst = 0;
		}

		cout << '\n';
	
		return ostr;
	}
};

//Constructori:
//Constructorul implicit
template <class T>
Polinom<T>::Polinom() :degree(0) {

	//Apelam constructorul clasei Term (Term(0)).
	data = data + 0;
}

//Constructor de initializare cu un termen
template <class T>
Polinom<T>::Polinom(Term<T> const& t) {

	data=data+t;
	degree = t.grade;
}

//Destructor
template<class T>
Polinom<T>::~Polinom() {

	//Se va apela destructorul clasei Array
	degree = 0;
}

//Metoda care verifica daca polinomul curent este nul.
template <class T>
bool Polinom<T>::isNull() {
	
	return ((degree == 0) && (data[0].coef == 0.0));
}

//Accesor ce returneaza vectorul suport al polinomului
template <class T>
SortArray<Term<T>>& Polinom<T>::getData() {
	return data;
}

//Accespr ce returneaza gradul polinomului:
template <class T>
unsigned int  Polinom<T>::getDegree() {
	
	return degree;
}

//Adauga un termen nou la polinomul curent
template <class T>
Polinom<T>& Polinom<T>::addTerm(Term<T> const& t) {



	int position = data.findValue(t);

	//Termenul nu s-a regasit in polinom
	if (position < 0) {
		data = data + t;
		degree = (degree < t.grade) ? t.grade : degree;
	}
	//Termenul a fost regasit in polinom
	else {
		Term<T>& current = data[position];
		T sum = current.coef + t.coef;

		//Eliminare termen
		if (sum == 0.0) {
			data = data - current;
			if(data.getSize()>0)
			degree = data[data.getSize() - 1].grade;
		}
		else
			current.coef = sum;
	}

	//Nu mai sunt termeni
	if (data.getSize() == 0) {
		data = data + 0;
		degree = 0;
	}

	else
	{
		degree = data[data.getSize() - 1].grade;
	}


	return *this;
}

//Elimina un termen din polinom
template<class T>
Polinom<T> Polinom<T>::removeTerm(Term<T>& t) {

	t.coef = -t.coef;
	return addTerm(t);
}

//Adauga un termen la polinom, prin specificarea explicita a structurii termenului
template <class T>
Polinom<T>& Polinom<T>::addValue(T t1, int gr) {

	//Construieste termenul si il adauga in polinom
	Term<T>term(t1, gr);
	return addTerm(term);
}

//Elimimna un termen din polimom prin specificarea explicita a structurii termenului de eliminat
template <class T>
Polinom<T>& Polinom<T>::removeValue(T  t1,int gr) {

	//Construieste termenul si il elimina din polinom
	Term<T> term(t1, gr);
	return removeTerm(term);
}

//Egaleaza un polinom cu un monom
template <class T>
Polinom<T>& Polinom<T>::operator =(Term<T> const& t) {

	if (data.getData()) {
		
		//Eliberaeza posibilul spatiu de memorie alocat
		data.setSize(0);

	}

	//Adaugam monomul
	data = data + t;
	degree = t.grade; //setam gradul

	//Returnam valoarea obiectului curent
	return *this;
}

//Copiaza polinomul pasat ca si parametru in obiectul curent.
template <class T>
Polinom<T>& Polinom<T>:: operator= (Polinom<T> const& p) {

	data = p.data;
	degree = p.degree;

	return *this;
}

//Adauga un termen la polinom
template<class T>
Polinom<T>& Polinom<T>:: operator+ (Term<T> const& t) {

	return addTerm(t);
}

//Adauga o constanta la polinomul curent
template <class T>
Polinom<T>& Polinom<T>:: operator+ (T const& t) {
	
	//Formeaza un termen si il adauga la polinomul curent
	Term<T> term(t);
	return addTerm(term);
}

//Insumeaza 2 polinoame
template<class T>
Polinom<T>& Polinom<T>:: operator+ (Polinom<T> const& p) {

	for (int i = 0; i < p.data.getSize(); i++)
		addTerm(p.data[i]);

	return *this;
}

//Elimina un termen din polinom
template<class T>
Polinom<T>& Polinom<T>::operator - (Term<T> & t) {

	return removeTerm(t);
}

//Elimina o constanta din polinom
template<class T>
Polinom<T>& Polinom<T>::operator - (T & t) {

	//Construieste un termen pornind de la parametrul metodei si il elimina ulterior din polinom
	Term<T>term(t);
	return removeTerm(t);
}

//Calculeaza diferenta a doua polinoame
template <class T>
Polinom<T> Polinom<T>::operator - (Polinom<T>& p) {
	
	for (int i = 0; i < p.data.getSize(); i++)
		removeTerm(p.data[i]);

	return *this;
}

//Cacluleaza rezultatul inmultirii unui polinom cu o constanta
template<class T>
Polinom<T>& Polinom<T>::operator * (T & t) {

	//Inmultirea unui polinom cu 0
	if (t == 0)
	{
		data = 0;
		degree = 0;
	}
	//Inmultirea propriu-zisa:
	else {
		for (int i = 0; i < data.getSize(); i++)
			data[i].coef = data[i].coef * t;
	}

	//Returnam valoarea obiectului curent
	return *this;
}

//Calculeaza rezultatul inmultirii unui polinom cu un termen
template <class T>
Polinom<T>& Polinom<T>::operator * (Term<T> & t) {

	//Inmultirea cu un termen nul
	if (t.isNull()) {
		data.setSize(0);
		//data = 0;
		degree = 0;
	}
	//Cazul contrar:
	else {
		for (int i = 0; i < data.getSize(); i++) {
			data[i].coef = data[i].coef * t.coef;
			data[i].grade = data[i].grade + t.grade;
		}
	}

	//Returnam valoarea obiectului curent
	return *this;
}

//Calcueaza rezultatul inmultirii a doua polinoame
template <class T>
Polinom<T> Polinom<T>::operator * (Polinom<T> &p) const {

	Polinom<T> result;
	//Posibilitatea inmultirii cu un polinom nul
	if (p.isNull()) {
		SortArray<Term<T>>newData;
		result.data=newData;
		result.degree = 0;
		return result;
	}

	//Cazul contrar:
	else {
		for (int i = 0; i <= this->degree; i++) {
			Term<T> t;
			for (int j = 0; j <= p.degree; j++) {
				T coef= this->data[i].coef * p.data[j].coef;
				unsigned int grade= this->data[i].grade + p.data[j].grade;
				//result.data[idx++]=t;
				result.addValue(coef, grade);
			}
		}
		return result;
	}



}


//Evalueaza polinomul curent in punctul x
template <class T>
T Polinom<T>::evaluate(T const& x) {
	
	T p = 0.0;
	int currDegree;
	for (int i = data.getSize() - 1; i >= 0; i--) {
		p += data[i].coef;
		currDegree = data[i].grade;
		int nextDegree = (i > 0) ? data[i - 1].grade : 0;
		while (currDegree-- > nextDegree)
			p *= x;
	}

	while (currDegree-- > 0)
		p *= x;

	return p;
}

//Citire polinom
template <class T>
void Polinom<T>:: read() {
	unsigned int deg;
	T coefficient;

	cout << "Care este gradul polinomului? ";
	cin >> deg;
	this->degree = deg;

	for (int i = 0; i <= deg; i++) {
		cout << "Termenul de grad " << i << ":\n";
		cout << "Coeficient: "; cin >> coefficient;
		this->addValue(coefficient, i);
	}
}

//Afiseaza continutul polinomului
template <class T>
void Polinom<T>:: print() {
	int isFirst = 1;
	for (int i = this->data.getSize() - 1; i >= 0; i--)
	{
		if (this->data[i].coef > 0)
			cout << ((isFirst) ? "" : "+");

		if (this->data[i].grade == 0)
			cout << this->data[i].coef;

		else {
			if (this->data[i].coef == 1.0)
				cout << "X^" << this->data[i].grade;
			else {
				if (this->data[i].coef == -1.0)
					cout << "-X^" << this->data[i].grade;
				else
					cout << this->data[i].coef << "X^" << this->data[i].grade;
			}
		}
		isFirst = 0;
	}
}


//Reseteaza polinomul curent
template<class T>
Polinom<T>& Polinom<T>::reset() {
	degree = 0;
	SortArray<Term<T>>arr;
	data = arr;

	return*this;
}



//Metoda a clasei Polinom care verifica daca in polinomul curent exista termeni cu coeficienti 0.
template <class T>
bool Polinom<T>::hasZeroCoefficientTerms() {

	for (int i = 0; i < this->data.getSize(); i++)
		if (this->data[i].coef == 0)
			return true;
	return false;
}


//Metoda a clasei polinom care elimina elementele cu coeficienti 0
template <class T>
void Polinom<T>::refactor() {

	while (this->hasZeroCoefficientTerms())
	{
		for (int i = 0; i < this->data.getSize(); i++)
			if (this->data[i].coef == 0)
				erase(this->data, i);
	}

	this->degree = this->data[data.getSize() - 1].grade;

}


//Shiftare polinom cu valoare intreaga 
template<class T>
void Polinom<T>::shift(T n) {

	Polinom<T>p;
	//Shiftarea cu o valoare nula nu are niciun efect.
	if (n == 0.0)
		return;

	//Shiftare cu valori negative
	if (n < 0.0)
	{
		
		for (int i = 0; i <= this->degree; i++) {
			if (i + n >= 0)
				p.addValue(this->data[i].coef, this->data[i].grade + n);
			else
				continue;
		}
		*this = p;
		return;
	}

	//Shiftare cu valori pozitive si nenule

	for (int i = 0; i <= this->degree; i++) {

		/*if (this->data[i].grade == 0)
			p.addValue(this->data[i].coef, n);
		else*/
		p.addValue(this->data[i].coef, this->data[i].grade + n);
	}
	
	p.removeValue(0, 0);
	*this = p;

}


//Functie care elimina un element de pe pozitia p dintr-un array
template<class T>
void erase(Array<T>& arr, unsigned int pos) {

	for (int i = pos; i < arr.getSize() - 1; i++)
		arr[i] = arr[i + 1];

		arr.setSize(arr.getSize() - 1);
	
}


template <class T>
void Polinom<T>::set(int idx, Term<T> a) {
	
	if (idx < 0)
		return;

	if (idx+1> this->data.getSize()) this->data.resize(idx+1);
	this->data[idx].coef = a.coef;
	this->data[idx].grade = a.grade;
	return;
}


//Calculeaza catul impartirii a doua polinoame
template <class T>
Polinom<T> Polinom<T>::operator/(Polinom<T>& p)
{

	//Copii ale celor 2 polinoame
	Polinom<T>current = (*this);
	Polinom<T>pCopy = p;

	//Aducem cele 2 polinoame intr-o forma monica (ireductibila), inainte de impartire
	current.makeMonic();
	pCopy.makeMonic();

	//Apeleaza metoda divide cu parametrul quotient->returneaza catul impartirii a doua polinoame (ireductibile)
	Polinom<T>quotient = current.divide(pCopy, "quotient");
	return quotient;
	
}


//Calculeaza catul/restul impartirii a doua polinoame
template<class T>
 Polinom<T> Polinom<T>:: divide( Polinom<T> &p, string display) const{

	 //Retinem valoarea obiectului curent intr-o alta variabila
	Polinom<T>current = (*this);
	//Catul
	Polinom<T> quotient;

	//Gradul impartitorului, respectiv al deimpartitului
	unsigned int const  pDegree = p.data.getSize() - 1;
	unsigned int currentDegree = current.data.getSize() - 1;

	//Daca deimpartitul (gradul) este mai mic decat impartitorul
	if (current.getDegree() < p.getDegree())
	{
		if (display == "quotient")
			return quotient;
		else
			return current;

	}

	//Algoritmul propriu-zis:
	//Cat timp gradul deimpartitului este mai mare sau egal decat cel al impartitorului
	while (current.getDegree() >= p.getDegree())
	{
		//Se impart coeficientii si gradele cele mai mari se vor scadea
		Term<T>t (current.data[currentDegree].coef / p.data[pDegree].coef, current.data[currentDegree].grade - p.data[pDegree].grade);

		//Copie a impartitorului
		Polinom<T> pCopy=p;

		//Scaderea conform algoritmului matematic
		current = current - (pCopy * t);
		//Construim catul
		quotient.addTerm(t);

		//Actualizare grad deimpartit
		currentDegree = current.data.getSize() - 1;
	}

	//Returnare rezultat
	//Cat
	if (display == "quotient")
		return quotient;
	else
		//Rest
		return current;

}

//Calculeaza restul impartirii a doua polinoame
template <class T>
Polinom<T> Polinom<T>:: operator % (Polinom<T>& p) {

	//Restul impartirii polinomului a la polinomul b este a-b*(a/b)
	
	//Copii ale celor 2 polinoame
	Polinom<T>current = (*this);
	Polinom<T>pCopy = p;

	//Aducem cele 2 polinoame intr-o forma monica (ireductibila), inainte de impartire
	current.makeMonic();
	pCopy.makeMonic();
	
	
	//Apeleaza metoda divide, cu parametrul "remainder"->calculul restului impartirii a doua polinoame

	Polinom<T> remainder=current.divide(pCopy,"remainder");
	return remainder;
}

//Metoda care calculeaza si afiseaza rezultatul complet (cat, rest) al impartirii dintre 2 polinoame
template<class T>
void Polinom<T>::longDivision(Polinom<T>& p) {
	

	Polinom<T>current =(*this);
	Polinom<T>pCopy = p;
	current.makeMonic();
	pCopy.makeMonic();

	Polinom<T>quotient = current/pCopy;
	Polinom<T>remainder = current%pCopy;
	cout << '\n' << "Rezultatul impartirii polinomului "; current.print();
	cout << "  " << " la " << "  ";
	p.print();
	cout<< " este: \nCAT: " << quotient << "\nREST: " << remainder << '\n';

}

//Metoda care verifica daca un polinom este sau nu monic
template <class T>
bool Polinom<T>:: isMonic(){

	if (this->degree == 0)
		return false;

	return (this->data[this->data.getSize() - 1].coef == 1);

}

//Metoda care transforma un polinom nemonic intr-unul monic
template<class T>
void Polinom<T>::makeMonic() {

	//Nu se poate forma un polinom monic
	if (this->degree == 0)
		return;

	if (this->isMonic())
		return;

	//Coeficientul termenului aflat la cel mai mare grad;
	T leader = this->data[this->data.getSize() - 1].coef;

	for (int i = 0; i <= degree; i++)
		this->data[i].coef /= leader;

	//Eliminam elementele cu coeficient 0
	this->refactor();

}

//Verifica daca un polinom este egal cu un monom si returneaza true in caz afirmativ, respectiv false in caz contrar
template<class T>
bool Polinom<T>::operator == (Term<T>& t) {

	if (this->getDegree() == t.grade && this->data[data.getSize() - 1].coef == t.coef)
		return true;
	return false;
}




//Functie care calculeaza si returneaza cel mai mare divizor comun a doua polinoame
template<class T>
Polinom<T> greatestCommonDivisor(Polinom<T>X, Polinom<T> Y) {

	Term<T> t(0, 0);
	//Daca polinomul Y este nul si polinomul X este monic, cmmdc(X,Y)=X.
	//In caz contar, daca Y este nul si X nu este monic, vom construi o copie a polinomului X si il vom face monic
	if (Y==t) {

		if (X.isMonic()) return X;

		Polinom<T> Xcopy = X;
		Xcopy.makeMonic();
		return Xcopy;
	}

	//Asemanator numerelor intregi, aplicam algoritmul lui Euclid (recursiv), prin scaderi repetate
	
	//Restul impartirii si apelul recursiv
	Polinom<T> rem;
	rem = X % Y;

	return greatestCommonDivisor(Y, rem);
}

