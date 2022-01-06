//Fisier header Term.h->implementeaza notinunea de monom, care ulterior va fi utilizata in implementarea clasei Polinom
#pragma once

//Clasa generica Term

template <class T>
class Term {
public:
	//Coeficient
	T coef;

	//Grad
	unsigned int grade;

	//Constructorul implicit:
	Term():coef(0),grade(0){}

	//Constructorul de initializare:
	Term(T const& coef, unsigned int grd = 0) :coef(coef) {
		this->grade = (coef == 0.0) ? 0 : grd;
	}

	//Constructorul de copiere
	Term(Term<T> const& t) {
		this->coef = t.coef;
		this->grade = (this->coef == 0.0) ? 0 : t.grade;
	}

	//Metoda care verifica daca un termen este sau nu nul
	bool isNull() const {
		return (this->coef == 0.0);
	}

	//Supraincarcarea operatorului < :Compara 2 polinoame si returneaza true daca primul este mai mic ca al doilea, respectiv false in caz contrar.
	bool operator < (Term<T> const& t)
	{
		return (this->grade < t.grade);
	}

	//Supraincarcarea operatorului <= :Compara 2 polinoame si returneaza true daca primul este mai mic sau egal ca al doilea, respectiv false in caz contrar.
	bool operator <=(Term<T> const& t)
	{
		return (grade <= t.grade);
	}

	//Supraincarcarea operatorului > :Compara 2 polinoame si returneaza true daca primul este mai mare ca al doilea, respectiv false in caz contrar.
	bool operator > (Term<T> const& t)
	{
		return (grade > t.grade);
	}

	//Supraincarcarea operatorului >= :Compara 2 polinoame si returneaza true daca primul este mai mare sau egal ca al doilea, respectiv false in caz contrar.
	bool operator >= (Term<T> const& t)
	{
		return (grade >= t.grade);
	}

	//Supraincarcarea operatorului == :Compara 2 polinoame si returneaza true daca gradul primului este egal cu al celui de-al doilea termen, respectiv false in caz contrar.
	bool operator ==(Term<T> const& t) 
	{
		return (grade == t.grade);
	}

	//Metoda care verifica daca doi termeni sunt egali din punct de vedere al gradului si al coeficientului (egalitate integrala).
	bool equals(Term<T> const& t) {
		return (grade == t.grade && coef == t.coef);
	}

	//Supraincarcarea operatorului de atribuire-> copiaza termenul t in obiectul curent
	Term<T>& operator = (Term<T> const& t) {
		coef = t.coef;
		grade = t.grade;

		return (*this);
	}

};
