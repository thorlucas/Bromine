Should we provide access to creation through servers or through clever constructors?

Through servers:
Pros:
Memory allocation and setup will be easier
Don't have to overload new operator when doing memory patterns
Aliases can be used for prettier syntax

Cons:
Messier syntax
Feels less streamlined

Servers provide objects

Service locator?

Bromine::get<MyNode>(args...);

or

Bromine::get<MyTrait>(args...);

through MyTrait::serverType

Replace std::type_index with some sort of capability type