//Header file SortArray.h->Contine o subclasa a clasei Array (derivata acestei clase), ce contine metode de lucru cu taboluri unidimensionale sortate (crescator).
#pragma once
#include "Array.h"
#include"Entry.h"
//Clasa generica SortArray, mosteneste clasa generica Array
template <class T>
class SortArray :public Array<T> {

public:
	//Prototipuri metode:
	//Metoda cu return type bool, ce va utiliza cautarea binara in vederea gasirii in vector a unei valori.
	int findValue(T const& val);

	//Metoda ce permite adaugarea unei valori in vectorul sortat
	SortArray& addValue(T const& val);

	//Metoda ce permite eliminarea unei valori din vectorul sortat
	SortArray& removeValue(T const& val);

	//Metoda ce permite interclasarea a doi vectori sortati
	SortArray& merge(SortArray<T>& const arr);

	//Metoda ce utilizeaza supraincarcarea operatorului de insumare in vederea adaugarii unei noi valori la vectorul sortat
	SortArray& operator + (T const& value);

	//Metoda ce utilizeaza supraincarcarea operatorului de scadere in vederea eliminarii unei valori din vectorul sortat
	SortArray& operator - (T const& value);

	//Metoda ce utilizeaza supraincarcarea operatorului de insumare in vederea adunarii a doi vectori sortati
	SortArray& operator + (SortArray<T>const& arr);

	//Metoda ce utilizeaza supraincarcarea operatorului de insumare in vederea scaderii a doi vectori sortati
	SortArray& operator - (SortArray<T>const& arr);
};

//Definitii metode
//Metoda utilizata pentru cautarea unui element in vector, utilizand metoda Divide et Impera, respectiv cautarea binara.
template <class T>
int SortArray<T>::findValue(T const& val) {

	//Valori necesare pentru implementarea algoritmului
	int left = 0, right = this->size - 1, middle = 0;

	while (left <= right) {
		//shiftare pe biti pentru o viteza de calcul sporita
		middle = (left + right) / 2;
		if (this->data[middle] < val)
			left = ++middle;
		else if (this->data[middle] > val)
			right = --middle;
		else
			return middle; //valoarea a fost gasita, returnam index-ul
	}

	return (this->base - 1); //valoarea nu a fost gasita, vom returna fie o valoare nula (in cazul in care se opteaza pentru prelucrari cu indici de la 1), fie o valoare negativa (in cazul in care se opteaza pentru prelucrari cu indici de la 0).
}

//Metoda ce permite adaugarea unui element in vectorul sortat
template <class T>
SortArray<T>& SortArray<T>:: addValue(T const& value) {

	T* newArr = new T[this->size + 1];
	int i = 0;
	//Copiem in noul array toate elementele pana la predecesorul lui value
	for (i = 0; (i < (this->size)) && (this->data[i] < value); i++)
		newArr[i] = this->data[i];
	//Copiem valoarea value
	newArr[i++] =value;

	//Copiem elementele ramase
	for (; i < this->size+1; i++)
		newArr[i] = this->data[i-1];
	
	//Crestem lungimea
	this->size++;

	//Stergem vechiul obiect
	delete[] this->data;

	//Utilizam supraincarcarea operatorului =, definit in clasa Array, pentru a copia in data continutul lui newArr.
	this->data = newArr;

	//La final, returnam valoarea lui data.
	return *this;
}

//Metoda ce permite eliminarea unei element din array-ul sortat
template<class T>
SortArray<T>& SortArray<T>::removeValue(T const& value) {

	//Cautam elementul value in vectorul sortat.
	int pos = findValue(value);
	//contor pentru iteratie
	int index = 0;
	//Daca s-a gasit elementul, il vom elimina din array-ul sortat:
	if (pos >= this->base) {
		T* newArr = new T[this->size - 1];
		for (index = 0; index < pos; index++) 
			newArr[index] = this->data[index];

		for (; index < this->size - 1; index++)
			newArr[index] = this->data[index+1];

		this->size--;
		delete[]this->data;
		//Utilizand supraincarcarea operatorului de atribuire, copiem in membrul data al obiectului curent valoarea vectorului newArr.
		this->data = newArr;
	}
	//Returnam valoarea obiectului curent
	return *this;
}

//Metoda responsabila de interclasarea a doi vectori sortati.
template <class T>
SortArray<T>& SortArray<T>::merge(SortArray<T>&const arr) {

	//Daca adresele celor 2 vectori difera, putem trece la interclasarea propriu-zisa
	if (arr != this) {
		//Se va aloca spatiu de memorie pentru vectorul rezultant
		T* mergedArray = new T[size + arr.size];
		//Indecsii celor 3 vectori
		int ind1, ind2, ind3;
		while (ind1 < this->size && ind2 < arr.size) {
			if (this->data[ind1] < this->data[ind2])
				mergedArray[ind3++] = this->data[ind1++];
			else
				mergedArray[ind3++] = this->data[ind2++];
		
		}

		//In situatia in care vectorul 2 s-a terminat inaintea primului, completam vectorul rezultant cu restul elementelor din primul vector:
		while (ind1 < this->size)
			mergedArray[ind3++] = this->data[ind1++];

		//In situatia in care vectorul 1 s-a terminat inaintea celui de-al doilea, completam vectorul rezultant cu restul elementelor din cel de-al doilea vector:
		while (ind1 < this->size)
			mergedArray[ind3++] = this->data[ind1++];

		//Stergem membrul data al obiectului curent
		delete[]data;
		//Copiem in variabila membru data a obiectului curent, vectorul rezultat in urma interclasarii
		this->data = mergedArray;
		this->size += arr.size;
	}

	return *this;
}

//Insereaza un element in vectorul sortat
template <class T>
SortArray<T>& SortArray<T>::operator+(T const& value) {

	//Apel la functia addValue(), ce realizeaza aceeasi operatie
	return addValue(value);
}

//Elimina un element din vectorul sortat
template <class T>
SortArray<T>& SortArray<T>::operator-(T const& value) {

	//Apel la functia removeValue(), ce realizeaza aceeasi operatie
	return removeValue(value);
}

//Insumeaza 2 vectori sortati
template <class T>
SortArray<T>& SortArray<T>:: operator + (SortArray<T>const& arr) {
	
	for (int i = 0; i < arr.size; i++)
		addValue(arr[arr.base + i]);

	return *this;
}

template<class T>
SortArray<T>& SortArray<T>:: operator - (SortArray<T>const& arr) {

	for (int i = 0; i < arr.size; i++)
		removeValue(arr[arr.base + i]);

	return *this;
}


