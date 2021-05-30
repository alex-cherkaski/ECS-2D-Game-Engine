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
	virtual ~IComponentPool();
};


//--------------------------------------------------
// Component Pool Class
//--------------------------------------------------

template<typename TComponent>
class ComponentPool : public IComponentPool
{
public:
	ComponentPool() = default;
	~ComponentPool() = default;

	// Cannot be copied.
	ComponentPool(const ComponentPool& other) = delete;
	ComponentPool& operator=(const ComponentPool& other) = delete;

	// Cannot be moved.
	ComponentPool(ComponentPool&& other) = delete;
	ComponentPool& operator=(ComponentPool&& other) = delete;

	size_t Size() const;
	void Resize(size_t newSize);

	void InsertComponent(const Entity entity, const TComponent& component);

private:
	std::vector<TComponent> m_componentVector;
	std::unordered_map<Entity, size_t> m_entityToComponentIndexMap;
	std::unordered_map<size_t, Entity> m_componentIndexToEntityMap;
};

//--------------------------------------------------
// System Class
//--------------------------------------------------

class Registry;

class System
{
public:
	System(const Registry& registry);
	virtual ~System() = default;

	// Systems cannot be copied;
	System(const System& other) = delete;
	System& operator=(const Registry& other) = delete;

	// Systems cannot be moved.
	System(System&& other) = delete;
	System& operator=(System&& other) = delete;

	void Update();
	void Render();

	void AddEntity(const Entity entity);
	void DeleteEntity(const Entity entity);

	// Update the component signature of the system.
	template<typename TComponent> void RequireComponent();

	ComponentSignature GetComponentSignature() const;

private:
	const Registry& m_registry;
	ComponentSignature m_systemComponentSignature;
	std::set<Entity> m_systemEntities;
};

//--------------------------------------------------
// System Class
//--------------------------------------------------

class ISystemIDStore
{
public:
	size_t static systemID;
};


//--------------------------------------------------
// Registry Class
//--------------------------------------------------

class Registry
{
public:
	static Registry& GetRegistryInstance();
	
	~Registry() = default;

	void Update();

	// Entity management
	Entity CreateEntity();
	void DeleteEntity();

	// Component management
	template<typename TComponent, typename ...TArgs> void AddComponent(const Entity entity, TArgs&& ...args);
	template<typename TComponent> TComponent& GetComponent(const Entity entity);
	void RemoveComponent(const Entity entity);

	// System management
	template<typename TSystem> void AddSystem();
	template<typename TSystem> TSystem& GetSystem();
	template<typename TSystem> void RemoveSystem();

private:
	Registry();

	// Cannot be deleted.
	Registry(const Registry& other) = delete;
	Registry& operator=(const Registry& other) = delete;

	// Cannot be moved.
	Registry(Registry&& other) = delete;
	Registry& operator=(Registry&& other) = delete;

private:
	unsigned m_numCreatedEntities;

	std::vector<Entity> m_entitiesToBeCreated;
	std::vector<Entity> m_entitiesToBeDeleted;

	std::vector<std::shared_ptr<IComponentPool>> m_componentPools; // Every index is a component ID. At each index a type specific component pool.
	std::vector<ComponentSignature> m_entityComponentSignatures; // Every index is an Entity. At each index is the Entity's component signature.

	std::vector<std::shared_ptr<System>> m_systems;
};


//--------------------------------------------------
// Component Methods
//--------------------------------------------------

template<typename TComponent>
inline ComponentID Component<TComponent>::GetComponentID()
{
	return s_nextComponentID++;
}


//--------------------------------------------------
// Component Pool Methods
//--------------------------------------------------

template<typename TComponent>
inline void System::RequireComponent()
{
}

template<typename TComponent, typename ...TArgs>
inline void Registry::AddComponent(const Entity entity, TArgs&& ...args)
{
	if (entity >= m_numCreatedEntities) // entity should be <= numCreateEntities :)
	{
		throw "Entity does not exist!";
	}

	unsigned componentID = Component<TComponent>::GetComponentID();

	// Extend the component pools vector if necessary.
	if (componentID >= m_componentPools.size())
	{
		m_componentPools.resize(componentID + 1);
	}

	// If a component pool for this component does not exist, create it.
	if (m_componentPools[componentID] == nullptr)
	{
		std::shared_ptr<ComponentPool<TComponent>> componentPoolPtr = std::make_shared<ComponentPool<TComponent>>();
		m_componentPools[componentID] = std::static_pointer_cast<IComponentPool, ComponentPool<TComponent>>(componentPoolPtr);
	}

	// Create the component, retrieve the component pool, and insert the new component.
	TComponent newComponent(std::forward<TArgs&&>(args)...);
	std::shared_ptr<ComponentPool<TComponent>> componentPoolPtr = std::static_pointer_cast<ComponentPool<TComponent>, IComponentPool>(m_componentPools[componentID]);
	componentPoolPtr->InsertComponent(entity, newComponent);
	
	if (entity >= m_entityComponentSignatures.size())
	{
		m_entityComponentSignatures.resize(m_entityComponentSignatures.size() + 1);
	}

	// Update entity component signature.
	m_entityComponentSignatures[entity].set(componentID);
}

template<typename TSystem>
inline void Registry::AddSystem()
{
	std::shared_ptr<TSystem> systemPtr = std::make_shared<TSystem>();
	m_systems.push_back(systemPtr);
}

template<typename TComponent>
inline size_t ComponentPool<TComponent>::Size() const
{
	return m_componentVector.size();
}

template<typename TComponent>
inline void ComponentPool<TComponent>::Resize(size_t newSize)
{
	m_componentVector.resize(newSize);
}

template<typename TComponent>
inline void ComponentPool<TComponent>::InsertComponent(const Entity entity, const TComponent& component)
{
	auto iterator = m_entityToComponentIndexMap.find(entity);
	
	if (iterator == m_entityToComponentIndexMap.end())
	{
		m_componentVector.push_back(component);
		size_t componentIndex = m_componentVector.size() - 1;
		m_entityToComponentIndexMap.emplace(entity, componentIndex);
		m_componentIndexToEntityMap.emplace(componentIndex, entity);
	}

	else
	{
		throw "Entity already has this component!";
	}
}
