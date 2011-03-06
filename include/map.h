#ifndef MAP_H
#define MAP_H

void* map_init();
void map_release(void* map);
void* map_set(void* map, char* key, void* value);
void* map_get(void* map, char* key);
char** map_keys(void* map);


#endif
