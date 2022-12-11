// https://youtu.be/0irYsCYuZws?list=PLpM-Dvs8t0VY73ytTCQqgvgCWttV3m8LM&t=3138
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define VM_STACK_CAPACITY 1024

typedef enum {
  TRAP_OK = 0,
  TRAP_STACK_OVERFLOW,
  TRAP_STACK_UNDERFOLOW,
  TRAP_ILLEGAL_INSTRUCTION
} Trap;

typedef int64_t Word;
typedef struct {
  Word stack[VM_STACK_CAPACITY];
  size_t stack_size;
} virtualmachine;

typedef enum {
  INST_PUSH,
  INST_PLUS,
} Inst_Type;

typedef struct {
  Inst_Type type;
  Word operand;
} Inst;

Inst inst_push(Word operand) {
  return (Inst){.type = INST_PUSH, .operand = operand};
}

Inst inst_plus(void) { return (Inst){.type = INST_PLUS}; }

Trap vm_execute_inst(virtualmachine *vm, Inst inst) {
  switch (inst.type) {
  case INST_PUSH:
    if (vm->stack_size >= VM_STACK_CAPACITY) {
      return TRAP_STACK_UNDERFOLOW;
    }
    vm->stack[vm->stack_size++] = inst.operand;
    break;
  case INST_PLUS:
    if (vm->stack_size < 2) {
      return TRAP_STACK_OVERFLOW;
    }
    vm->stack[vm->stack_size - 2] += vm->stack[vm->stack_size - 1];
    vm->stack_size -= 1;
    break;
  default:
    return TRAP_ILLEGAL_INSTRUCTION;
  }
  return TRAP_OK;
}

void vm_dump(const virtualmachine *vm) {
  printf("\nStack: ");
  if (vm->stack_size > 0) {
    for (size_t i = 0; i < vm->stack_size; ++i) {
      printf("  %ld", vm->stack[i]);
    }
  } else {
    printf(" [empty]");
  }
}

virtualmachine vm = {0};

int main() {
  vm_execute_inst(&vm, inst_push(69));
  vm_execute_inst(&vm, inst_push(420));
  vm_execute_inst(&vm, inst_plus());
  vm_dump(&vm);
  return 0;
}
