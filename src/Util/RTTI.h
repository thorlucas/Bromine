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
	virtual void activate() override;										\
DECLARE_TRAIT(serverName)													\

// This must be included in each trait's definition file
#define DEFINE_TRAIT(traitName, parentName)									\
const std::size_t traitName::type = std::hash<std::string>()(#traitName);	\
bool traitName::isTraitType(const std::size_t traitType) const {			\
	if (traitName::type == traitType) return true;							\
	return parentName::isTraitType(traitType);								\
}																			\

#define DEFINE_BASE_TRAIT(traitName)										\
void traitName::activate() {												\
	server.activateTrait(this);												\
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
protected:																	\
	void activateTrait(traitName* trait);									\

// Must be in trait server definition
#define DEFINE_TRAIT_SERVER(serverName, traitName)							\
void serverName::activateTrait(traitName* trait) {							\
	activeTraits.push_back(trait);											\
	Bromine::log(Logger::DEBUG, #traitName " %p for Node %d has been activated in " #serverName " server.", trait, trait->owner().id);	\
}																			\
