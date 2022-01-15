#pragma once
#include "StackArray.h"
#include "Exceptions.h"

//Clasa QueueFromStacks, mosteneste clasa abstracta Container si implementeaza conceptul de coada, prin utilizarea a 2 stive ajutatoare
template <class T>
class QueueFromStacks:public Container
{
private:
	StackArray<T> st1;
	StackArray<T>st2;

	//Capacitatea maxima a cozii
	int capacity;

public:
	//Constructorul implicit inline, initializeaza cele 2 stive ajutatoare cu dimensiunea 0
	QueueFromStacks():st1(0),st2(0)
	{
		this->count = 0;
		capacity = 0;
	}

	//Constructor de initializare:initializeaza coada cu o anumita dimensiune
	QueueFromStacks(int size):st1(size),st2(size)
	{
		this->count = 0;
		capacity = size;
	}

	//Constructor de copiere:copiaza in instanta curenta un alt obiect al aceleiasi clase
	QueueFromStacks(QueueFromStacks<T> const& q)
	{
		this->st1 = StackArray<T>(q.st1);
		this->st2 = StackArray<T>(q.st2);
		this->count = q.getCount();
		this->capacity = q.capacity;
	}

	//Metoda ce permite adaugarea unui element in coada, prin utilizarea celor 2 stive auxiliare
	//Caz favorabil->cand se adauga primul element si algoritmul efectueaza doar operatia de push pe prima stiva, ordinul timpului de executie fiind O(1)
	//Caz general->cand se adauga al n+1-lea element in coada. Se elimina toate elementele deja existente in prima stiva, printr-o bucla while. Considerand n numarul elementelor existente inaintea inserarii, atunci, timpul de executie este echivalent cu O(n+1+n+1), unde 1 reprezinta elementul ce tocmai a fost adaugat=>Ordinul timpului O(2n+2), care apartine lui O(n), unde n reprezinta numarul elementelor din coada.
	void enQueue(T const& val)
	{
		try {

			if (this->isFull())
				throw QueueException();

			if (st1.isEmpty()) {
				st1.push(val);
				this->count++;
			}
			else
			{
				int count = 0;
				while (!st1.isEmpty())
				{
					st2.push(st1.getTop());
					st1.pop();
				}

				st1.push(val);
				this->count++;

				while (!st2.isEmpty())
				{
					st1.push(st2.getTop());
					st2.pop();
				}
			}
		}
		catch(QueueException &qe)
		{
			qe.handle("EROARE! Coada este deja plina!");
		}
	}


	//Metoda ce permite eliminarea unui element din coada, prin utilizarea celor 2 stive auxiliare
	//Ordin al timpului:O(1) in toate cazurile, intrucat totul se rezuma la operatia elementara de pop, efectuata asupra stivei 1.
	void deQueue()
	{
		try
		{
			if (this->isEmpty())
				throw QueueException();

			st1.pop();
			this->count--;
			
		}
		catch (QueueException &qe)
		{
			qe.handle("EROARE! Coada este goala!");
		}
	}


	//Verifica daca o coada este sau nu goala
	//Realizeaza o singura comparatie:ordin al timpului:O(1)
	 bool isEmpty() const override {
		return (this->count == 0);
	}

	//Verificam daca o coada este sau nu plina
	//Realizeaza o singura comparatie=>ordin al timpului egal cu O(1).
	bool isFull() const override
	{
		return (this->count == this->capacity);
	}

	//Obtine numarul elementelor pe care coada le contine la momentul apelului
	//Realizeaza o returnare de variabila membru, ordin al timpului egal cu O(1)
	unsigned int getCount() const override
	{
		return this->count;
	}

	//Returneaza elementul de la inceputul cozii
	//Apeleaza metoda getTop() a clasei StackArray, care efectueaza o operatie elementara, rezulta un ordin al timpului ce apartine lui O(1)
	T getHead()
	{
		return this->st1.getTop();
	}


	//Supraincarcarea operatorului de scriere in flux, permite afisarea elementelor din coada.
	//Parcurge toata stiva 1, cu o copie a acesteia eliminanad rand pe rand cele n elemente, afisandu-le in acelasi timp=>Ordin al timpului egal cu O(n), datorita celor n treceri prin bucla while
	friend ostream& operator << (ostream& ostr, QueueFromStacks<T>&q)
	{

		StackArray<T>st(q.st1);
		while(!st.isEmpty())
		{
			T val = st.getTop();
			ostr << val << '\t';
			st.pop();
		}

		return ostr;
	}



};