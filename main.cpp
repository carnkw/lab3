// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);

void sex_map(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sex_map(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	for(int i=0; i<n; i++)
		vectorOfSlavs.push_back(&slavs[i]);

	random_shuffle(vectorOfSlavs.begin(), vectorOfSlavs.end()); //losowa kolejność

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	for(vector <Slav *>::iterator iter = vectorOfSlavs.begin(); iter != vectorOfSlavs.end(); iter++)
		cout << (*iter)->description() << endl;  


	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for(vector <Slav *>::iterator iter = vectorOfSlavs.begin(); iter != vectorOfSlavs.end(); iter++)
		setOfSlavs.insert(*iter);
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	for(set <Slav *>::iterator iter = setOfSlavs.begin(); iter != setOfSlavs.end(); iter++)
		mapOfSlavs.insert(pair <Slav *, Slav *> (*iter, *(iter++)));

	for(set <Slav *>::iterator iter = setOfSlavs.begin(); iter != setOfSlavs.end(); iter++)
		setOfSlavs.erase(iter);

	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	for(map <Slav *, Slav *>::iterator iter = mapOfSlavs.begin(); iter != mapOfSlavs.end(); iter++)
		cout << (iter->first)->description() << " " << (iter->second)->description() << endl;
	
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for(int i=0; i<n; i++)
		queueOfSlavs.push(&slavs[i]);
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	while(!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	while(!stackOfSlavs.empty())
	{
		cout << stackOfSlavs.top()->description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}

void sex_map(Slav * slavs, int n)
{
	map <sex, vector <Slav *>> slavsSex; 

for(int i=0; i<n; i++)
{
	if(slavs[i].what_sex() == female)
		slavsSex[female].push_back(&slavs[i]);
	else
		slavsSex[male].push_back(&slavs[i]);
}

cout << "## Female Slavs:" << endl;

for(vector <Slav *>::iterator iter = slavsSex[female].begin(); iter != slavsSex[female].end(); iter++)
	cout << (*iter)->description() << endl; 

cout << endl;

cout << "## Male Slavs:" << endl;
for(vector <Slav *>::iterator iter = slavsSex[male].begin(); iter != slavsSex[male].end(); iter++)
	cout << (*iter)->description() << endl;

}