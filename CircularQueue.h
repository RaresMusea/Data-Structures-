
//Fisier CircularQueue.h-> Contine clasa CircularQueue, care este o implementare a structurii de coada circulara (coada in care primul element este conectat la ultimul, pentru a permite operatii mai usoare si mai eficiente de inserare).

//Clasa CircularQueue mosteneste interfata Queue, definita in fisierul Queue.h

#pragma once
#include "Queue.h"
#include "Array.h"
#include "Exceptions.h"

template <class T>
class CircularQueue :public Queue<T> {

protected:

	//Vectorul suport al cozii circulare
	Array<T> v;

	//Variabile membru:
	//Retin indecsii din vectorul suport al primului, respectiv ultimului element adaugat in coada circulara
	int head, tail;

public:

	//Constructor inline de initializare->Seteaza pozitiile indecsilor, respectiv dimensiunea maxima a vectorului suport pentru coada circulara
	CircularQueue(unsigned int size) :head(-1), tail(-1), v(size) {

		this->count = 0; //Numarul de elemente inserate este 0
	}

	//Constructor de copiere-Copiaza continutul cozii circulare cq in instanta clasei curente
	CircularQueue(CircularQueue<T> const& cq) :head(cq.head), tail(cq.tail), v(cq.v) {

		this->count = cq.count; //Copiaza numarul elementelor inserate.
	}

	//Metode:
	//Verifica daca coada circulara este sau nu plina
	bool isFull() const {

		int size = this->v.getSize();
		return ((head == 0 && tail == size - 1) || (tail == (head - 1) % (size - 1)));
	}

	//Verifica daca coada circulara este sau nu goala
	bool isEmpty() const {

		return(tail == -1 && this->count == 0);

	}

	//Adauga un element in coada circulara
	void enQueue(T const& el) {

		//Se incearca adaugarea elementului el in coada circulara. In situatia in care aceasta este plina, se va lansa o exceptie.
		try {
			if (isFull())
				throw QueueException();

			//Se insereaza primul element
			if (isEmpty()) {
				head = tail = 0;
				v[tail] = el;
				this->count++;
				return;
			}

			//Situatia in care se doreste inserarea unui element pe ultima pozitie. Se schimba indexul ultimului element si se insereaza la inceput:
			if (tail == v.getSize() - 1 && head != 0) {
				tail = 0;
				v[tail] = el;
				this->count++;
				return;
			}

			//Cazul contrar, se insereaza elementele ca intr-o coada obisnuita
			tail++;
			v[tail] = el;
			this->count++;

		}
		//Tratarea exceptiei
		catch (QueueException& qe) {
			qe.handle("Eroare!\nNu se poate adauga elementul in coada circulara, deoarece aceasta este plina!");
		}
	}

	//Elimina un element din coada circulara
	void deQueue() {

		//Se incearca eliminarea unui element din coada circulara. In situatia in care aceasta este goala, se va lansa o exceptie.
		try {
			if (isEmpty())
				throw QueueException();

			v[head] = -1;

			//Daca se elimina singurul element din coada circulara, aceasta devine goala
			if (head == tail) {
				head = tail = -1;
				this->count--;
			}
			//Daca capatul cozii este egal cu dimensiunea acestuia, se reseteaza valoarea sa (indexul) la 0.
			else if (head == v.getSize() - 1) {
				head = 0;
				this->count--;
			}
			else {
				//Cazul contrar
				head++;
				this->count--;
			}
		}
		catch (QueueException& qe) {
			qe.handle("Eroare!\nNu se mai poate elimina niciun element din coada circulara, intrucat aceasta este goala!");
		}
	}

	//Supraincarcarea operatorului de scriere in fluxul de iesire, permite afisarea pe ecran a continutului cozii circulare
	friend ostream& operator << (ostream& ostr, CircularQueue<T>& qc) {

		//Se incearca afisarea cozii pe ecran. In situatia in care aceasta este goala, se va lansa o exceptie corespunzatoare.
		try {
			if (qc.isEmpty())
				throw QueueException();

			//Pozitia sfarsitului cozii este mai mare decat cea a capatului de iesire
			if (qc.tail >= qc.head) {

				for (int i = qc.head; i <= qc.tail; i++)
					cout << qc.v[i] << "\t";
			}
			//Cazul contrar
			else {

				for (int i = qc.head; i < qc.count; i++)
					cout << qc.v[i] << "\t";

				for (int i = 0; i <= qc.tail; i++)
					cout << qc.v[i] << "\t";

			}
		}
		catch (QueueException& qe) {
			qe.handle("Eroare!\nNu se poate afisa coada circulara, deoarece aceasta este goala!");
		}
	}

	//Obtine elementul din varful cozii
	T getHead() const {

		try {
			if (isEmpty())
				throw QueueException();
			return v[head];

		}
		catch (QueueException& qe) {
			qe.handle("Eroare!\nNu se poate obtine elementul din capatul cozii circulare ,intrucat aceasta este goala!");
		}
	}


	//Returneaza elementul de la finalul cozii circulare.
	T getTail() const {

		try {
			if (isEmpty())
				throw QueueException();
			return v[tail];

		}
		catch (QueueException& qe) {
			qe.handle("Eroare!\nNu se poate obtine elementul de la finalul cozii circulare ,intrucat aceasta este goala!");
		}
	}


	//Returneaza numarul elementelor introduse in coada circulara
	unsigned int getCount() const {
		return this->count;
	}

};