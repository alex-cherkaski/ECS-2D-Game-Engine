#include "../Include/ECS.h"

ComponentID IComponent::s_nextComponentID = 0;

template<typename TComponent>
ComponentID Component<TComponent>::GetComponentID()
{
	return s_nextComponentID++;
}
