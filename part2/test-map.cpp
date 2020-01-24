void FAIL() {   exit(1);    }
void OK(const char* m) { /** print m */ }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }
 
void test1() {
	Hashmap map = new Hashmap();
	String * s = new String("Hello");
	String * t = new String("World");
	String * u = s->concat(t);
	t_true(s->equals(s));
	t_false(s->equals(t));
	t_false(s->equals(u));
	OK("1");
}







int main() {
	Hashmap map1 = new 
}