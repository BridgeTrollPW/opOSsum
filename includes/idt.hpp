#include <stdint.h>
#include "io.hpp"

unsigned long irq0_address;
unsigned long irq1_address;
unsigned long irq2_address;
unsigned long irq3_address;
unsigned long irq4_address;
unsigned long irq5_address;
unsigned long irq6_address;
unsigned long irq7_address;
unsigned long irq8_address;
unsigned long irq9_address;
unsigned long irq10_address;
unsigned long irq11_address;
unsigned long irq12_address;
unsigned long irq13_address;
unsigned long irq14_address;
unsigned long irq15_address;
unsigned long idt_address;
unsigned long idt_ptr[2];

extern "C" int load_idt(long unsigned int *ptr_idt);
extern "C" int irq0();
extern "C" int irq1();
extern "C" int irq2();
extern "C" int irq3();
extern "C" int irq4();
extern "C" int irq5();
extern "C" int irq6();
extern "C" int irq7();
extern "C" int irq8();
extern "C" int irq9();
extern "C" int irq10();
extern "C" int irq11();
extern "C" int irq12();
extern "C" int irq13();
extern "C" int irq14();
extern "C" int irq15();

struct IDT_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

class IDT
{
public:
    IDT();
};