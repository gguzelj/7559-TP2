/*
 * EntityManager.cpp
 *
 *  Created on: 29 Nov 2015
 *      Author: osboxes
 */

#include "EntityManager.h"
#include "../syscalls/SysCalls.h"

using namespace std;

EntityManager::EntityManager(std::string fileName) :m_index("entity.idx"){
	m_fname = fileName;
	m_fdReader = syscalls::open ( m_fname.c_str(),O_CREAT|O_RDONLY,0777 );
	m_fdWriter = syscalls::open ( m_fname.c_str(),O_CREAT|O_WRONLY,0777 );

	syscalls::lseek(m_fdWriter,0,SEEK_END);

	struct stat buf;
	fstat(m_fdWriter, &buf);
	m_offset = buf.st_size;
}

EntityManager::~EntityManager() {
	syscalls::close(m_fdReader);
	syscalls::close(m_fdWriter);
}

void EntityManager::persist(Entity entity){
	char buffer[sizeof(Entity)];
	memcpy(buffer, &entity, sizeof(Entity));

	syscalls::write(m_fdWriter,buffer,sizeof(Entity));
	m_index.addIndex(entity.nombre, m_offset);

	m_offset += sizeof(Entity);
}

 void EntityManager::findAll(const char* name,std::list<Entity>& results){

	std::list<long> offsets;
	m_index.getOffsets(name, offsets);

	for (std::list<long>::iterator it = offsets.begin(); it != offsets.end(); it++){
		long offset = *it;
		Entity entity;
		syscalls::lseek(m_fdReader, offset,SEEK_SET);
		syscalls::read(m_fdReader, &entity, sizeof(Entity));
		results.push_back(entity);
	}
}
