#pragma once

// This must be included inside each trait's declaration
// TODO: Activate permissions?
#define DECLARE_TRAIT(serverName)											\
friend class serverName;													\
public:																		\
	static const std::size_t type;											\
	serverType& server; 					 								\
	virtual bool isTraitType(const std::size_t traitType) const override;	\
	
// All traits that inherit from Trait must use this
#define DECLARE_BASE_TRAIT(serverName)										\
public:																		\
	typedef serverName serverType;											\
	virtual void notifyActivate() override;									\
	virtual void notifyDeactivate() override;								\
	virtual void destroy() override;										\
DECLARE_TRAIT(serverName)													\

// This must be included in each trait's definition file
#define DEFINE_TRAIT(traitName, parentName)									\
const std::size_t traitName::type = std::hash<std::string>()(#traitName);	\
bool traitName::isTraitType(const std::size_t traitType) const {			\
	if (traitName::type == traitType) return true;							\
	return parentName::isTraitType(traitType);								\
}																			\

#define DEFINE_BASE_TRAIT(traitName)										\
void traitName::notifyActivate() {											\
	if (!initialized) {														\
		initialize();														\
		initialized = true;													\
	}																		\
	server.activateTrait(this);												\
}																			\
void traitName::notifyDeactivate() {										\
	server.deactivateTrait(this);											\
}																			\
void traitName::destroy() {													\
	server.destroyTrait(this);												\
}																			\
DEFINE_TRAIT(traitName, Trait)												\

// Must be included in trait constructor list
#define CONSTRUCT_TRAIT(traitName, parentName)								\
parentName(owner), server(Bromine::server<serverType>())					\

// Must be included in trait constructor list
#define CONSTRUCT_BASE_TRAIT(traitName)										\
CONSTRUCT_TRAIT(traitName, Trait)											\

// Must be in trait server declaration
#define DECLARE_TRAIT_SERVER(serverName, traitName)							\
friend class traitName;														\
private:																	\
	std::vector<traitName*> activeTraits;									\
	std::multimap<NodeID, traitName&> nodeMap;								\
protected:																	\
	void activateTrait(traitName* trait);									\
	void deactivateTrait(traitName* trait);									\
	void destroyTrait(traitName* trait);									\
public:																		\
	auto getTraits(NodeID node) -> decltype(nodeMap.find(node));			\
	traitName& getTrait(NodeID node);										\

// Must be in trait server definition
#define DEFINE_TRAIT_SERVER(serverName, traitName)							\
auto serverName::getTraits(NodeID node) -> decltype(nodeMap.find(node)) {	\
	return nodeMap.find(node);												\
}																			\
traitName& serverName::getTrait(NodeID node) {								\
	return nodeMap.find(node)->second;										\
}																			\

#define DEFINE_DEFAULT_SERVER_ACTIVATE_TRAIT_STANDARD(serverName, traitName)\
void serverName::activateTrait(traitName* trait) {							\
	activeTraits.push_back(trait);											\
	Bromine::log(Logger::DEBUG, 											\
		#traitName " %p for Node %d has been activated in "					\
		#serverName " server.",												\
		trait, trait->owner().id);											\
}																			\
void serverName::deactivateTrait(traitName* trait) {						\
	activeTraits.erase(														\
		std::find(activeTraits.begin(), activeTraits.end(), trait)			\
	);																		\
	Bromine::log(Logger::DEBUG, 											\
		#traitName " %p for Node %d has been deactivated in "				\
		#serverName " server.",												\
		trait, trait->owner().id);											\
}																			\

#define DEFINE_TRAIT_SERVER_CREATE_TRAIT_STANDARD(traitName)				\
public:																		\
	template <typename T, typename ...Ps>									\
	T& createTrait(NodeID node, Ps&&... ps) {								\
		T& tref = *(new T(node, std::forward<Ps>(ps)...));					\
		nodeMap.insert(std::pair<NodeID, traitName&>(node, 					\
			static_cast<traitName&>(tref)));								\
																			\
		Bromine::log(Logger::DEBUG, "Created " #traitName					\
			" for Node %d: %p", node, &tref);								\
		return tref;														\
	}																		\

#define DEFINE_TRAIT_SERVER_DESTROY_TRAIT_STANDARD(serverName, traitName)	\
void serverName::destroyTrait(traitName* trait) {							\
	nodeMap.erase(trait->ownerID);											\
	auto t = std::find(activeTraits.begin(), activeTraits.end(), trait);	\
	if (t != activeTraits.end())											\
		activeTraits.erase(t);												\
	Bromine::log(Logger::DEBUG, "Destroyed " #traitName						\
		" for Node %d: %p", trait->ownerID, trait);							\
	delete trait;															\
}																			\

// TODO: Destroy trait should be in a .cpp file