/*
 * Index.cpp
 *
 *  Created on: 29 Nov 2015
 *      Author: osboxes
 */

#include "Index.h"
#include "../syscalls/SysCalls.h"

Index::Index(std::string idxname) {

	m_fname = idxname;
	m_fd = syscalls::open( m_fname.c_str(),O_CREAT|O_RDONLY,0777 );
	syscalls::lseek(m_fd,0,SEEK_SET);

	char name[61];
	long offset;

	char buff[sizeof(name)+sizeof(offset)];
	char* t = buff + sizeof(name);
	while(syscalls::read(m_fd, buff, sizeof(buff))){

		memcpy(name, buff, sizeof(name));
		memcpy(&offset, t, sizeof(long));
		m_index.insert(std::make_pair(name,offset));
	}

	syscalls::close(m_fd);
}

Index::~Index() {

	//for (std::multimap<const char*,long>::iterator it=m_index.begin(); it!=m_index.end(); ++it)
	//	    std::cout << (*it).first << " => " << (*it).second << '\n';


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

	//TODO: COMMENT!
	//for (std::multimap<const char*,long>::iterator it=m_index.begin(); it!=m_index.end(); ++it)
	//    std::cout << (*it).first << " => " << (*it).second << '\n';
}

void Index::getOffsets(const char* name,std::list<long>& offsets){

	//TODO: COMMENT!
	//for (std::multimap<const char*,long>::iterator it=m_index.begin(); it!=m_index.end(); ++it)
	//	    std::cout << (*it).first << " => " << (*it).second << '\n';

	std::pair <std::multimap<const char*,long>::iterator, std::multimap<const char*,long>::iterator> ret;
	ret = m_index.equal_range(name);

	for (std::multimap<const char*,long>::iterator it = ret.first; it!=ret.second; ++it){
	    offsets.push_back(it->second);
	}
}

