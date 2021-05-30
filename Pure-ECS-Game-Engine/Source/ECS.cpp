#include "stdafx.h"
#include "../Include/ECS.h"

size_t IComponent::s_nextComponentID = 0;

IComponentPool::~IComponentPool()
{
}

System::System(const Registry& registry) : m_registry(registry)
{
}

void System::Update()
{
}

void System::Render()
{
}

void System::AddEntity(const Entity entity)
{
	m_systemEntities.insert(entity);
}

void System::DeleteEntity(const Entity entity)
{
}

ComponentSignature System::GetComponentSignature() const
{
	return m_systemComponentSignature;
}

Registry& Registry::GetRegistryInstance()
{
	static Registry registry;
	return registry;
}

void Registry::Update()
{
	for (Entity entity : m_entitiesToBeCreated)
	{
		ComponentSignature entityComponentSignature = m_entityComponentSignatures[entity];

		for (std::shared_ptr<System> systemPtr : m_systems)
		{
			ComponentSignature systemComponentSignature = systemPtr->GetComponentSignature();

			if ((entityComponentSignature & systemComponentSignature) == systemComponentSignature)
			{
				systemPtr->AddEntity(entity);
			}
		}
	}
	m_entitiesToBeCreated.clear();
}

Entity Registry::CreateEntity()
{
	Entity newEntity = m_numCreatedEntities++;
	m_entitiesToBeCreated.push_back(newEntity);
	return newEntity;
}

Registry::Registry() : m_numCreatedEntities(0)
{

}


