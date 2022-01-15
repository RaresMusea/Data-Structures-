//Fisier header Stack.h->contine implementarea interfetei Stack, ce implementeaza functionalitatea unei stive

//Interfata Stack va folosi clasa virtuala Container.
#pragma once
#include "Container.h"

//Interfata generica Stack:
template<class T>
class Stack :public virtual Container {

public:

	//Functii virtuale pure:

	//Obtine elementul din varful stivei
	virtual T& getTop() = 0;

	//Elimina un element din stiva
	virtual void pop() = 0;

	//Adauga un element in stiva
	virtual void push(T const&) = 0;

};
