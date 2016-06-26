#include "ObjectStorage.h"

ObjectStorage::ObjectStorage() {
	// TODO Auto-generated constructor stub

}

ObjectStorage::~ObjectStorage() {
	// TODO Auto-generated destructor stub
}

void ObjectStorage::addObject(ObjectMetaData* object) {
	objects.push_back(object);
}

void ObjectStorage::removeObject(int id) {
	//TODO: Search for id and remove from vector
}
