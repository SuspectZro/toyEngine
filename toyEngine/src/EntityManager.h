#pragma once
//#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Types.h"
#include <iostream>
#include <ostream>
#include <cstdint>
#include <unordered_map>

using namespace data;

typedef uint64_t EntityID;

class SparseSetHolder {
public:
	virtual ~SparseSetHolder() = default;
	virtual bool Has(EntityID) const = 0;
	virtual void Drop(EntityID) = 0;
};

template<typename T>
class SparseSet : public SparseSetHolder {
public:
	std::unordered_map<EntityID, T> values;
	bool Has(EntityID ID) const { return values.count(ID) > 0; }
	void Drop(EntityID ID) { values.erase(ID); }
};

class EntityManager {

	std::unordered_map<size_t, SparseSetHolder*> components;

public:

	

	template<typename T>
	void AddNewComponent(SparseSet<T>* comp) {
		components.insert({ typeid(T).hash_code(),comp });
	}

	template<typename T>
	SparseSet<T>& GetComponent() {
		return static_cast<SparseSet<T>&>(*components[typeid(T).hash_code()]);
	}
	/*
	template<typename T>
	void ShowAll() {
		auto ptr = GetComponent<T>();
		for (auto value : ptr.values) {
			std::cout << value.first << " " << value.second << std::endl;
		}
	}
	*/
	template<typename T>
	T& Get(EntityID ID) {
		return GetComponent<T>().values[ID];
	}

	EntityID GetUnusedID() {
		EntityID rval = -1;
		bool shouldContinue = true;
		while (shouldContinue) {
			rval++;
			shouldContinue = false;
			for (auto component : components) {
				if (component.second->Has(rval)) {
					shouldContinue = true;
					break;
				}
			}
		}
		return rval;
	}
	//expose 
	void StartUp() {
		AddNewComponent(new SparseSet<Position>);
		AddNewComponent(new SparseSet<Physics>);
		AddNewComponent(new SparseSet<Health>);
		AddNewComponent(new SparseSet<Sprite>);
		AddNewComponent(new SparseSet<Script>);
		AddNewComponent(new SparseSet<Flag>);
		AddNewComponent(new SparseSet<isFlipped>);
		AddNewComponent(new SparseSet<State>);
		AddNewComponent(new SparseSet<Shapes>);
		AddNewComponent(new SparseSet<Collision>);
		//AddNewComponent(new SparseSet<PushBox>);
		AddNewComponent(new SparseSet<HitBox>);
	}
	void ShutDown() {
		for (auto component : components) delete component.second;
	}
	
	template <typename T, typename... Rest>
	bool HasAll(EntityID id) {
		bool result = true;
		if constexpr (sizeof...(Rest) > 0) { result = HasAll<Rest...>(id); }
		return result && GetComponent<T>().Has(id) > 0;
	}

	typedef std::function<void(EntityID)> ForEachCallback;
	template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
	void ForEach(const ForEachCallback& callback) {
		// Iterate over elements of the first container.
		auto& container = GetComponent<EntitiesThatHaveThisComponent>().values;
		for (const auto& [entity, value] : container) {
			// We know it has the first component.
			// Skip the entity if it doesn't have the remaining components.
			// This `if constexpr` is evaluated at compile time. It is needed when AndAlsoTheseComponents is empty.
			// https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
			if constexpr (sizeof...(AndAlsoTheseComponents) > 0) {
				if (!HasAll<AndAlsoTheseComponents...>(entity)) {
					continue;
				}
			}
			callback(entity);
		}
	}
};
