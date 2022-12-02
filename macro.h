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

#define TIME_RATIO (60) //리얼타임 기준 인게임타임 비율