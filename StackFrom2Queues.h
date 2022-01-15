#pragma once
#include "QueueArray.h"
#include "Container.h"
#include "Exceptions.h"

//Clasa generica StackFromQueues, mosteneste clsaa abstracta Container si implementeaza structura de stiva (static), utilizand 2 cozi auxiliare (2 instante ale clasei QueueArray)

template <class T>
class StackFromQueues:public Container
{
private:

	QueueArray<T>q1;
	QueueArray<T>q2;

	//Capacitatea maxima a cozii
	int capacity;

public:

	//Constructorul implicit, initializeaza membrii clasei (cele 2 cozi vor fi de capacitate 0, numarul curent de elemente:0, capacitate :0)
	StackFromQueues():q1(0),q2()
	{
		this->count=0;
		capacity = 0;
	}

	//Constructor de initializare, initializeaza cele 2 cozi ajutatoare cu o anumita dimensiune, cat si capcacitatea stivei
	StackFromQueues(int size):q1(size),q2(size)
	{
		this->capacity = size;
		this->count = 0;
	}

	//Constructorul de copiere, copiaza stiva st in instanta curenta a clasei
	StackFromQueues(StackFromQueues<T> const& st)
	{
		this->q1 = QueueArray<T>(st.q1);
		this->q2 = QueueArray<T>(st.q2);
		this->count = st.count;
		this->capacity = st.capacity;
	}


	//Returneaza numarul curent de elemente din stiva
	//Realizeaza o returnare de variabila membru, ordin al timpului egal cu O(1)
	unsigned int getCount() const override
	{
		return this->count;
	}

	//Verifica daca stiva este sau nu plina
	//Realizeaza o singura comparatie->ordin al timpului echivalent cu O(1)
	bool isFull() const override
	{
		return (this->count == this->capacity);
	}

	//Verifica daca stiva este sau nu goala
	//Realizeaza o singura comparatie:ordin al timpului:O(1)
	bool isEmpty() const override
	{
		return (this->count == 0);
	}

	//Obtine elementul din varful stivei
	//Realizeaza un apel al functiei membru getHead(), specifica clasei QueueArray, care efectueaza o operatie elementara al carui ordin al timpului apartine lui O(1)=>Timp de executie echivalent cu O(1)
	T getTop()
	{
		return q1.getHead();
	}

	//Adauga un element in stiva, utilizand cele 2 cozi auxiliare
	//Caz favorabil->cand se adauga primul element si algoritmul efectueaza doar operatia de enqueue pe prima coada, ordinul timpului de executie fiind O(1)
	//Caz general->cand se adauga al n+1-lea element in stiva. Se elimina toate elementele deja existente in prima coada, printr-o bucla while. Considerand n numarul elementelor existente inaintea inserarii, atunci, timpul de executie este echivalent cu O(n+1+n+1), unde 1 reprezinta elementul ce tocmai a fost adaugat=>Ordinul timpului O(2n+2), care apartine lui O(n), unde n reprezinta numarul elementelor din stiva.
	void push(T const& el)
	{
		try {
			if (this->isFull())
				throw StackException();

			if (this->isEmpty()) {
				q1.enQueue(el);
				this->count++;
			}
			else
			{
				while(!q1.isEmpty())
				{
					q2.enQueue(q1.getHead());
					q1.deQueue();
				}

				q1.enQueue(el);
				this->count++;

				while(!q2.isEmpty())
				{
					q1.enQueue(q2.getHead());
					q2.deQueue();
				}
			}

		}
		catch(StackException &se)
		{
			se.handle("EROARE! Stiva este deja plina!");
		}
	}

	//Elimina un element din stiva utilizand cozile auxiliare
	//Ordin al timpului:O(1) in toate cazurile, intrucat totul se rezuma la operatia elementara de dequeue, efectuata asupra cozii auxiliare  q1.
	void pop()
	{
		try
		{
			if (this->isEmpty())
				throw StackException();

			q1.deQueue();
			this->count--;

		}
		catch(StackException &se)
		{
			se.handle("EROARE! Stiva este deja goala!");
		}

	}


	//Supraincarcarea operatorului de scriere in flux, permite afisarea elementelor din stiva.
	//Parcurge toata coada 1, cu o copie a acesteia eliminanad rand pe rand cele n elemente ale acesteia si afisandu-le in acelasi timp=>Ordin al timpului egal cu O(n), datorita celor n treceri prin bucla while
	friend ostream& operator << (ostream& ostr, StackFromQueues<T>& st)
	{
		QueueArray<T>q(st.q1);

		while(!q.isEmpty())
		{
			T current = q.getHead();
			ostr << current << "\n";
			q.deQueue();
		}
		return ostr;
	}

};
