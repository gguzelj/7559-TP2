#include <list>
#include <string>
#include "Entity.h"
#include "Index.h"

#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

class EntityManager {
public:
	EntityManager(std::string fileName);
	virtual ~EntityManager();

	void persist(Entity entity);

	void findAll(const char* name,std::list<Entity>& results);

private:
	Index m_index;

	int m_fdReader;
	int m_fdWriter;
	std::string m_fname;
	long m_offset;
};

#endif /* ENTITYMANAGER_H_ */
