/*
 * Index.cpp
 *
 *  Created on: 29 Nov 2015
 *      Author: osboxes
 */

#include "Index.h"
#include "../syscalls/SysCalls.h"

Index::Index() {

	m_fd = syscalls::open( this->m_fname.c_str(),O_CREAT|O_RDONLY,0777 );
	syscalls::lseek(m_fd,0,SEEK_SET);

	char name[61];
	long offset;

	char buff[sizeof(name)+sizeof(offset)];
	while(syscalls::read(m_fd, buff, sizeof(buff))){
		memcpy(name, buff, 61);
		memcpy(&offset,buff+61, sizeof(long));
		m_index.insert(std::make_pair(name,offset));
	}

	syscalls::close(m_fd);
}

Index::~Index() {

	m_fd = syscalls::open( this->m_fname.c_str(),O_CREAT|O_WRONLY,0777 );
	syscalls::lseek(m_fd,0,SEEK_SET);

	char name[61];
	long offset;

	std::multimap<const char*,long>::iterator it;
	for (it = m_index.begin(); it!=m_index.end(); ++it){

		memcpy(name, it->first, sizeof(name));
		offset = it->second;
		syscalls::write(m_fd, name, sizeof(name));
		syscalls::write(m_fd, &offset, sizeof(offset));
	}

	syscalls::close(m_fd);
}

void Index::addIndex(const char* name, long offset){
	m_index.insert(std::make_pair(name,offset));
}

std::list<long> Index::getOffsets(const char* name){

	std::list<long> offsets;
	std::pair <std::multimap<const char*,long>::iterator, std::multimap<const char*,long>::iterator> ret;
	ret = m_index.equal_range(name);

	std::list<long>::iterator itOffset = offsets.begin();

	for (std::multimap<const char*,long>::iterator it = ret.first; it!=ret.second; ++it){
	  *itOffset = it->second;
	  itOffset++;
	}

	return offsets;
}

