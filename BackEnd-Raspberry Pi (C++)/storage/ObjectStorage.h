#ifndef STORAGE_OBJECTSTORAGE_H_
#define STORAGE_OBJECTSTORAGE_H_

#include <vector>

#include "ObjectMetaData.h"

class ObjectStorage {
public:
	ObjectStorage();
	virtual ~ObjectStorage();

	void addObject(ObjectMetaData* object);

	void removeObject(int id);

private:
	std::vector<ObjectMetaData*> objects;
};

#endif /* STORAGE_OBJECTSTORAGE_H_ */
