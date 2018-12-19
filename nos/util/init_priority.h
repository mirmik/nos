#ifndef NOS_INIT_PRIORITY_H
#define NOS_INIT_PRIORITY_H

//Макросы для изменения порядка инициализации
//Врядли совместимо.

#define NOS_PRIORITY_INITIALIZATION_SUPER 	__attribute__((init_priority(140)))
#define NOS_PRIORITY_INITIALIZATION 		__attribute__((init_priority(1000)))

#endif