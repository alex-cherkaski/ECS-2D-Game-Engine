#pragma once
#include "stdafx.h"
#include "../Include/Components.h"

//--------------------------------------------------
// ECS aliases and constants
//--------------------------------------------------

// Entity type alias.
using Entity = size_t;

// Component type alias.
using ComponentID = size_t;

// Maximum number of components an entity can have.
constexpr ComponentID MAX_COMPONENTS = 32;

// The components an entity has.
using ComponentSignature = std::bitset<MAX_COMPONENTS>;


//--------------------------------------------------
// Component Interface
//--------------------------------------------------

class IComponent
{
protected:
	static ComponentID s_nextComponentID;
};


//--------------------------------------------------
// Component ID Tracker
//--------------------------------------------------

template <typename TComponent>
class Component : public IComponent
{
public:
	static ComponentID GetComponentID();
};


//--------------------------------------------------
// Component Pool Interface
//--------------------------------------------------

class IComponentPool
{
public:
	virtual ~IComponentPool() {}
};


//--------------------------------------------------
// Component Pool Class
//--------------------------------------------------

template<typename TComponent>
class ComponentPool 
{
public:
	ComponentPool();
	~ComponentPool();

	void AddComponent(const Entity entity);

private:
	std::vector<TComponent> m_componentVector;
	std::unordered_map<Entity, size_t> m_entityToComponentIndexMap;
	std::unordered_map<size_t, Entity> m_componentIndexToentityMap;
};

