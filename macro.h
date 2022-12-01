#pragma once
#define SINGLETON(type) public:\
							static type* GetInstance()\
							{\
								static type instance;\
								return &instance;\
							};\
						private:\
							type();\
							~type();
