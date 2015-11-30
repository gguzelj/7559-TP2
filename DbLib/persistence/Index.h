#include <map>
#include <string>
#include <list>

#ifndef INDEX_H_
#define INDEX_H_

class Index {
public:
	Index();
	virtual ~Index();

	void addIndex(const char* name, long offset);

	std::list<long> getOffsets(const char* name);

private:
	std::multimap<const char*,long> m_index;

	int m_fd;
	std::string m_fname;
};

#endif /* INDEX_H_ */
