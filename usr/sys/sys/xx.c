void foo(void ) {
asm(R"(
 .text 
 .globl icode 
   la a0, init 
   la a1, argv 
   li a7, 0x1234 
   ecall 
 exit: 
   li a7, 0x5678 
   ecall 
   jal exit 
 init: 
   .string '/init\0'
 # char *argv[] = { init, 0 }; 
 .p2align 2 
 argv: 
   .long init 
   .long 0 
)");
};
