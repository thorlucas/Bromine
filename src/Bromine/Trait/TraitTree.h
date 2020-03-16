#ifndef _TRAIT_TREE_H_
#define _TRAIT_TREE_H_

#include <vector>
#include <algorithm>

#include "../Bromine.h"

namespace BromineEngine {

// TODO: Note that T must also inherent from TraitTree<T>
// Use some sort of template magic to make this happen
template <typename T>
class TraitTree {
protected:
	T* parent;
	std::vector<T*> children;

	TraitTree() : parent(nullptr) {}

	void setParent(T* parent) {
		if (this->parent != nullptr) {
			this->parent->removeChild(static_cast<T*>(this));
		}

		this->parent = parent;
	}

	void addChild(T* child) {
		children.push_back(static_cast<T*>(child));
		child->setParent(static_cast<T*>(this));
	}

	void removeChild(T* child) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}
};

}

#endif