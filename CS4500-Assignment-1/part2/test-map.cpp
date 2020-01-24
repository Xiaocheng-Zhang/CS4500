#include "object.h"
#include "map.h"
#include "string.h"

void FAIL() { exit(1); }
void OK(const char* m) { printf("test %d passed\n", m); }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }
String* cast_string(Object *object) {
	return dynamic_cast<String*>(object);
}

String *s = new String("Hello");
String *t = new String("World");
String *a = new String("key_1");
String *b = new String("key_2");
String *c = new String("key_3");
String *d = new String("key_4");
String *av = new String("val_1");
String *bv = new String("val_2");
String *cv = new String("val_3");
String *dv = new String("val_4");
Object *o = new Object();
Object *ov = new Object();

void test_constructor() {
	Hashmap *map = new Hashmap();
	t_true(map->size() == 0);
	t_true(map->hash() != 0);
	t_true(map->hash_code != 0);
	Hashmap *map2 = new Hashmap();
	t_true(map->equals(map2));
	for (size_t i = 0; i < map->capacity_; i++) {
		//test for method initialize(data)
		t_true(map->data[i] == nullptr);
	}
	OK("constructor");
}

void test_basic_method() {
	Hashmap *map = new Hashmap();
	map->put(a, av);
	map->put(b, bv);
	map->put(c, cv);
	map->put(d, dv);
	t_true(map->size() == 4);
	t_true(map->capacity_ >= 4);
	map->remove(a);
	t_true(map->size() == 3);
	size_t size_before_expand = map->capacity_;
	map->expand();
	t_true(map->capacity_ == 2 * size_before_expand);
}

void test_advance_method() {
	Hashmap *map = new Hashmap();
	for (size_t i = 0; i < 9999; i++) {
		map->put(o, ov);
	}

	for (size_t i = 0; i < map->capacity_; i++) {
		t_true((map->data[i] == nullptr) || (map->get(o)->equals(ov)));
	}

	
}





int main(void) { 
}