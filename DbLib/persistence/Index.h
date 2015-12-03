#include <map>
#include <string>
#include <list>

#ifndef INDEX_H_
#define INDEX_H_
#include <mqueue.h>
class Index {
public:
	Index(std::string name);
	virtual ~Index();

	void addIndex(std::string name, long offset);
	void flushIndex();
	void getOffsets(std::string name,std::list<long>& offsets);

private:
	std::multimap<std::string,long> m_index;


	int m_fd;
	std::string m_fname;
};

#endif /* INDEX_H_ */
