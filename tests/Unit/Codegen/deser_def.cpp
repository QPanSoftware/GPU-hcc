// RUN: %amp_device -c -S -emit-llvm %s -o -|%cppfilt|%FileCheck %s
class baz {
 public:
  int cho(void) restrict(amp) {
    return 45;
  }
  baz(void): foo(1234) {}
  __attribute__((used)) /* Forcing this function to be present in the output */
  __attribute__((annotate("auto_deserialize"))) /* For compiler */
  baz(int foo_, float bar_) restrict(amp);
  // :foo(foo_), bar(bar_) {}
 private:
  int foo;
  float bar;
};

int kerker(void) restrict(amp,cpu) {
  baz b1;
  baz bll(1, 2.0);
  return b1.cho()+bll.cho();
}
// The definition should be generated by clang
// CHECK: define {{.*}}void @baz::baz(int, float)(%class.baz*, i32
