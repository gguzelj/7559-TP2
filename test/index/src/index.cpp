//============================================================================
// Name        : index.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <persistence/Index.h>
#include <persistence/EntityManager.h>
#include <list>
#include <cstring>
#include <stdio.h>

using namespace std;


void testEntityManager(){
	EntityManager em("Entities.e");
	Entity entity;
	char* nombre = "maria";
	char* direccion = "maure 4323";
	char* telefono = "11111";

	strncpy(entity.nombre, nombre, sizeof(entity.nombre));
	strncpy(entity.direccion, direccion, sizeof(entity.direccion));
	strncpy(entity.telefono, telefono, sizeof(entity.telefono));

	em.persist(entity);


	nombre = "maria";
	direccion = "rojas 4323";
	telefono = "2222222";

	strncpy(entity.nombre, nombre, sizeof(entity.nombre));
	strncpy(entity.direccion, direccion, sizeof(entity.direccion));
	strncpy(entity.telefono, telefono, sizeof(entity.telefono));

	em.persist(entity);
	/*

	nombre = "ana";
	direccion = "bulnes 4323";
	telefono = "33333";

	strncpy(entity.nombre, nombre, sizeof(entity.nombre));
	strncpy(entity.direccion, direccion, sizeof(entity.direccion));
	strncpy(entity.telefono, telefono, sizeof(entity.telefono));

	em.persist(entity);*/

	list<Entity> results;
	em.findAll("maria", results);

	list<Entity>::iterator itr  = results.begin();

	for(itr = results.begin(); itr != results.end();itr++){
		cout << itr->nombre << " # " << itr->direccion << " # " << itr->telefono << endl;
	}
}

void testIndex(){

	Index i("test.idx");

	i.addIndex("maria",0);
	i.addIndex("maria",4);
	i.addIndex("celeste",20);
	i.addIndex("romina",25);
	i.addIndex("romina",30);

	list<long> offsets;
	i.getOffsets("maria",offsets);

	list<long>::iterator it  = offsets.begin();

	for(it = offsets.begin(); it != offsets.end();it++){
		cout << *it << " ";
	}
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	testEntityManager();

	return 0;
}
