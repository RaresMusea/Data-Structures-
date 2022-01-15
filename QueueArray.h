//Fisier header QueueArray.h-> Contine clasa QueueArray, care este o implementare a unei cozi sub forma unui tabou unidimensional (coada ca lista statica).

#pragma once
#include"Queue.h" //Folosim interfata Queue
#include "Exceptions.h" //Fisier in care am definit numeroase exceptii ce vor fi tratate in cadrul clasei StackArray
#include "Array.h" //foloseste clasa Array si toate functiile definite in cadrul acestui fisier

//Clasa generica QueueArray

template <class T>
class QueueArray :public Queue<T> {

protected:
	//Membrii ai clasei:
	//Vectorul suport al cozii
	Array<T> arr;

	//Retine indecsii din vectorul suport ai capatului si sfarsitului cozii
	unsigned int head, tail;

public:

	QueueArray()
	{
		this->count = 0;
	}


	//Constructor inline de initializare (seteaza dimensiunea si parametrii pentru un obiect al clasei curente
	QueueArray(unsigned int Size):arr(Size),head(0),tail(Size-1){
		this->count = 0;
	}
	
	//Constructor inline de copiere-copiaza in obiectul curent continutul si parametrii cozii q
	QueueArray(QueueArray<T> const& q):arr(q.arr),head(q.head),tail(q.tail){
		this->count=(q.count);
	}

	//Destructor
	~QueueArray(){}

	//Metode:
	//QueueArray<T> mergequeue(QueueArray<T>& q2);
	//Obtine elementul de la inceputul cozii
	T getHead() const {
		
		//Se incearca obtinerea elementului de la inceputul cozii. In situatia in care coada este goala, se va lansa o exceptie
		try {
			if (isEmpty())
				throw QueueException();
			return this->arr[head];
		}
		catch (QueueException& qe) {
			qe.handle("Eroare!\nCoada este goala!");
		}
	}

	
	T getTail() const {
		//Se incearca obtinerea elementului de la sfarsitul cozii. In situatia in care coada este goala, se va lansa o exceptie
		try {
			if (isEmpty())
				throw QueueException();
			return this->arr[tail];
		}
		catch (QueueException& qe) {
			qe.handle("Eroare!\nCoada este goala!");
		}
	}

	//Adauga un element la sfarsitul cozii
	void enQueue(T const& t) {

		//Se incearca adaugarea unui element t in coada. In situatia in care coada este goala, se va lansa o exceptie
		try {
			if (isFull())
				throw QueueException();

			if (++tail == this->arr.getSize())
				this->tail = 0;
			this->arr[tail] = t;
			this->count++;
		}
		catch (QueueException& qe) {
			qe.handle("Eroare!\nNu se poate adauga un element in coada, deoarece aceasta este goala!");
		}
	}

	//Elimina un element din la capatul cozii
	void deQueue() {

		//Se incearca eliminarea elementului de la capatul cozii. In situatia in care coada este deja goala, se va lansa o exceptie.
		try {
			if (isEmpty())
				throw QueueException();

			if (this->count==2)
				head = tail;

			else if (++head == this->arr.getSize())
				head = 0;
			--this->count;
		}
		catch (QueueException& qe) {
			qe.handle("Eroare!\nCoada este goala!");
		}
	}

	//Verifica daca coada este sau nu goala
	bool isEmpty() const {
		
		return (this->count == 0);
	}

	//Verifica daca coada este sau nu plina
	bool isFull() const {

		return(this->count == arr.getSize());
	}

	//Obtine numarul de elemente din coada
	unsigned int getCount() const {
		return this->count;
	}

	//Supraincarcarea operatorului de scriere in fluxul de intrare, permite citirea de la tastatura a unei cozi
	friend istream& operator >> (istream& istr, QueueArray<T>& q) {

		//Conferim o functionalitate de redimensionare.
		cout << "Conform initializarii, coada curenta va avea " << q.arr.getSize() << " elemente. Doriti sa redimensionati? (Y/N)";
		char choice;
		istr >> choice;
		if (choice == 'Y' || choice == 'y') {
			cout << "Ce dimensiune doriti sa aiba coada?";
			unsigned int sz;
			istr >> sz;
			q = QueueArray<T>(sz);
		}
		else
			cout << "Dimensiunea cozii va ramane setata la " << q.arr.getSize() << '\n';

		//Citim elementele cozii rand pe rand si le inseram.
		for (int i = 0; i < q.arr.getSize(); i++)
		{
			cout << "Elementul " << i + 1<<':';
			T el;
			istr >> el;
			q.enQueue(el);
		}

		return istr;
	}

	//Supraincarcarea operatorului de scriere in fluxul de iesire, permite afisarea unei cozi
	friend ostream& operator << (ostream& ostr, QueueArray<T>& q) {

		ostr << '\n';
		
		//Afisam coada ca pe un un vector
		for (int i =q.head; i <=q.tail; i++)
			ostr<< q.arr[i] << '\t';
		
		ostr << '\n';
		return ostr;
	}

	QueueArray<T>merge(QueueArray<T>& q2);
	
};

//Interclaseaza 2 cozi
template<class T>
QueueArray<T> QueueArray<T>::merge(QueueArray<T>& q2) {
	QueueArray<T> res(this->arr.getSize() + q2.arr.getSize());
	while ((!this->isEmpty()) && (!q2.isEmpty())) {
		if (this->getHead() > q2.getHead()) {
			res.enQueue(q2.getHead());
			q2.deQueue();
		}
		else {
			res.enQueue(this->getHead());
			this->deQueue();
		}
	}

	if (!this->isEmpty()) {
		while (!this->isEmpty()) {
			res.enQueue(this->getHead());
			this->deQueue();
		}
	}
	if (!q2.isEmpty()) {
		while (!q2.isEmpty()) {
			res.enQueue(q2.getHead());
			q2.deQueue();
		}
	}

	return res;
}



