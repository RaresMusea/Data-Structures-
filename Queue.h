//Fisier header Queue.h->contine implementarea interfetei Queue, ce implementeaza functionalitatea unei cozi

#pragma once

//Interfata Queue va folosi clasa virtuala Container.
#include "Container.h"
#include "Exceptions.h" //Utilizarea clasei definite QueueException

template<class T>
class Queue :public virtual Container {

	
public:
	//functii virtuale pure:

	//Obtine elementul din varf
	virtual T getHead() const = 0;

	//Adauga un element in coada
	virtual void enQueue(T const&) = 0;

	//Elimina un element din coada
	virtual void deQueue() = 0;

};

#pragma endregion



