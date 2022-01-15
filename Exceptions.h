
//Fisier header Exceptions.h->Defineste clasele posibilelor exceptii ce pot aparea in fisierele header aferente anumitor clase/ structuri de date implementate.
#pragma once
#include <exception>
#include <string>
#include<iostream>
using namespace std;

//Defineste clasa StackException, care va fi utilizata pentru a trata toate exceptiile ce pot aparea in clasa StackArray
class StackException :public exception {

public:
	void handle(string error) throw(){
		//Afiseaza mesajul de eroare
		cout << error<<'\n';
	}
};


//Defineste clasa QueueException, care va fi utilizata pentru a trata toate exceptiile ce pot aparea in clasa QueueArray.
//Intrucat clasa va avea o singura metoda, identica cu cea a clasei de mai sus, clasa QueueException mosteneste clasa StackException
class QueueException :public StackException{};

//Defineste clasa PolishNotationException, care va fi utilizata pentru a trata toate exceptiile ce pot aparea in clasa Parser.
//Intrucat clasa va avea o singura metoda, identica cu cea a clasei de mai sus, clasa PolishNotationException mosteneste clasa StackException
class PolishNotationException:public StackException{};