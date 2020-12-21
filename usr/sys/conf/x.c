void handle_trap (void) __attribute__ ((interrupt));
// void f (void) __attribute__ ((interrupt ("user")));

extern int foo;
extern void handle_trap();
void handle_trap() {
  foo++;
  bar();
}

main() {
  write_csr(mtvec, ((unsigned long)&handle_trap));
}
