/*
 * EntityManager.cpp
 *
 *  Created on: 29 Nov 2015
 *      Author: osboxes
 */

#include "EntityManager.h"
#include "../syscalls/SysCalls.h"

using namespace std;

EntityManager::EntityManager() {
	// TODO Auto-generated constructor stub
	this->m_fd = syscalls::open ( this->m_fname.c_str(),O_CREAT|O_RDWR,0777 );
	syscalls::lseek(m_fd,0,SEEK_END);
	m_offset = 0; //change to file size
}

EntityManager::~EntityManager() {
	// TODO Auto-generated destructor stub
}

void EntityManager::persist(Entity entity){
	char buffer[sizeof(Entity)];
	memcpy(buffer, &entity, sizeof(Entity));

	syscalls::lseek(m_fd,0,SEEK_END);
	m_offset = 0;
	syscalls::write(m_fd,buffer,sizeof(Entity));
	m_offset += sizeof(Entity); //ver el tema del padding.

	m_index.addIndex(entity.nombre, m_offset);
}

std::list<Entity> EntityManager::findAll(std::string name){

	std::list<long> offsets = m_index.getOffsets(name.c_str());
	std::list<Entity> entities;
	std::list<Entity>::iterator itEntity = entities.begin();

	for (std::list<long>::iterator it = offsets.begin(); it != offsets.end(); it++){
		long offset = *it;
		Entity entity;
		syscalls::lseek(m_fd, offset,SEEK_SET);
		syscalls::read(m_fd, &entity, sizeof(Entity));
		*itEntity = entity;
		itEntity++;
	}

	return entities;

}
