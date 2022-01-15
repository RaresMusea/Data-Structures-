//Fisier Scroll.h->Implementeaza clasa Scroll, care este o structura intermediara intre stiva si coada, in care inserarile se pot face doar la sfarsit, iar adaugarile la ambele capete

//Pentru implementarea clasei scroll, vom porni de la clasa QueueArray (clasa Scroll deriva din  QueueArray)
#pragma once
#include "QueueArray.h"

//Clasa generica Scroll
template <class T>
class Scroll :public QueueArray<T> {

public:

	//Constructor inline de initializare->apeleaza constructorul superclasei
	Scroll(unsigned int size):QueueArray<T>(size) {}

	//Constructor de copere->Copiaza obiectul pasat ca si parametru in noul obiect instantiat
	Scroll(Scroll<T> const& sc){
		this->head = sc.head;
		this->tail = sc.tail;
		this->arr = sc.arr;
		this->count = sc.getCount();
	}

	//Metoda utilizata pentru a adauga un element in scroll (intrucat adaugarea se face la final, vom face apel la metoda enQueue(), a clasei QueueArray).
	void add(T const& el);

	//Face apel la metoda deQueue a clasei QueueArray, pentru a elimina primul element al scroll-ului
	void removeHead();

	//Elimina un element de la sfarsitul scroll-ului
	void removeTail();

};

//Adauga un element la sfarsitul scroll-ului
template <class T>
void Scroll<T>::add(T const& el) {

	this->enQueue(el);
}

//Elimina primul element din scroll
template <class T>
void Scroll<T>::removeHead() {

	this->deQueue();
}

template <class T>
void Scroll<T>::removeTail() {

	try {
		if (this->isEmpty())
			throw QueueException();

		if (this->count == 1)
			this->tail = this->head;

		if (--this->tail == 0) {
			this->head = this->tail = 0;
			this->count--;
			return;
		}
		this->count--;
	}
	catch (QueueException& qe) {
		qe.handle("Eroare!\nNu se mai pot elimina elemente din coada, deoarece aceasta este goala!");
	}

}




