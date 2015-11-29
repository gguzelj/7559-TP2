#include <list>
#include <string>
#include "Entity.h"
#include "Index.h"

#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

class EntityManager {
public:
	EntityManager();
	virtual ~EntityManager();

	void persist(Entity entity);

	std::list<Entity> findAll(std::string name);

private:
	Index m_index;

	int m_fd;
	std::string m_fname;
	long m_offset;
};

#endif /* ENTITYMANAGER_H_ */
