#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define VM_STACK_CAPACITY 1024

typedef enum {
  ERR_OK = 0,
  ERR_STACK_OVERFLOW,
  ERR_STACK_UNDERFOLOW,
  ERR_ILLEGAL_INSTRUCTION
} Trap;

const char *trap_as_cstr(Trap trap) {
  switch (trap) {
  case ERR_OK:
    return "ERR_OK";
  case ERR_STACK_OVERFLOW:
    return "ERR_STACK_OVERFLOW";
  case ERR_STACK_UNDERFOLOW:
    return "ERR_STACK_UNDERFOLOW";
  case ERR_ILLEGAL_INSTRUCTION:
    return "ERR_ILLEGAL_INSTRUCTION";
  default:
    assert(0 && "trap_as_cstr: UNREACHABLE");
  }
}

typedef int64_t Word;
typedef struct {
  Word stack[VM_STACK_CAPACITY];
  size_t stack_size;
} virtualmachine;

typedef enum { INST_PUSH, INST_PLUS, INST_MINUS, INST_MUL, INST_DIV } Inst_Type;

typedef struct {
  Inst_Type type;
  Word operand;
} Inst;

#define MAKE_INST_PUSH(value)                                                  \
  { .type = INST_PUSH, .operand = (value) }
#define MAKE_INST_PLUS                                                         \
  { .type = INST_PLUS }
#define MAKE_INST_MINUS                                                        \
  { .type = INST_MINUS }
#define MAKE_INST_MUL                                                          \
  { .type = INST_MUL }
#define MAKE_INST_DIV                                                          \
  { .type = INST_DIV }

Trap vm_execute_inst(virtualmachine *vm, Inst inst) {
  switch (inst.type) {
  case INST_PUSH:
    if (vm->stack_size >= VM_STACK_CAPACITY) {
      return ERR_STACK_UNDERFOLOW;
    }
    vm->stack[vm->stack_size++] = inst.operand;
    break;
  case INST_PLUS:
    if (vm->stack_size < 2) {
      return ERR_STACK_OVERFLOW;
    } else {
      vm->stack[vm->stack_size - 2] += vm->stack[vm->stack_size - 1];
      vm->stack_size -= 1;
    }
    break;
  case INST_MINUS:
    if (vm->stack_size < 2) {
      return ERR_STACK_OVERFLOW;
    } else {
      vm->stack[vm->stack_size - 2] -= vm->stack[vm->stack_size - 1];
      vm->stack_size -= 1;
    }
    break;
  case INST_MUL:
    if (vm->stack_size < 2) {
      return ERR_STACK_OVERFLOW;
    } else {
      vm->stack[vm->stack_size - 2] *= vm->stack[vm->stack_size - 1];
      vm->stack_size -= 1;
    }
    break;
  case INST_DIV:
    if (vm->stack_size < 2) {
      return ERR_STACK_OVERFLOW;
    } else {
      vm->stack[vm->stack_size - 2] /= vm->stack[vm->stack_size - 1];
      vm->stack_size -= 1;
    }
    break;
  default:
    return ERR_ILLEGAL_INSTRUCTION;
  }
  return ERR_OK;
}

void vm_dump(FILE *stream, const virtualmachine *vm) {
  fprintf(stream, "\nStack: ");
  if (vm->stack_size > 0) {
    for (size_t i = 0; i < vm->stack_size; ++i) {
      fprintf(stream, "  %ld", vm->stack[i]);
    }
  } else {
    fprintf(stream, " [empty]");
  }
}

virtualmachine vm = {0};
#define ARRAY_SIZE(xs) (sizeof(xs) / sizeof((xs)[0]))
Inst program[] = {MAKE_INST_PUSH(69), MAKE_INST_PUSH(420), MAKE_INST_PLUS};

int main() {
  vm_dump(stdout, &vm);
  for (size_t i = 0; i < ARRAY_SIZE(program); i++) {
    Trap trap = vm_execute_inst(&vm, program[i]);
    if (trap != ERR_OK) {
      fprintf(stderr, "Trap Activated %s\n", trap_as_cstr(trap));
      vm_dump(stderr, &vm);
      exit(1);
    }
  }
  vm_dump(stdout, &vm);
  return 0;
}
