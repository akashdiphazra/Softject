#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define VM_STACK_CAPACITY 1024

typedef enum {
  ERR_OK = 0,
  ERR_STACK_OVERFLOW,
  ERR_STACK_UNDERFOLOW,
  ERR_ILLEGAL_INSTRUCTION,
  ERR_DIV_BY_ZERO
} Err;

const char *err_as_cstr(Err trap) {
  switch (trap) {
  case ERR_OK:
    return "ERR_OK";
  case ERR_STACK_OVERFLOW:
    return "ERR_STACK_OVERFLOW";
  case ERR_STACK_UNDERFOLOW:
    return "ERR_STACK_UNDERFOLOW";
  case ERR_ILLEGAL_INSTRUCTION:
    return "ERR_ILLEGAL_INSTRUCTION";
  case ERR_DIV_BY_ZERO:
    return "ERR_DIV_BY_ZERO";
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
const char *inst_type_as_cstr(Inst_Type type) {
  switch (type) {
  case INST_PUSH:
    return "(INST_PUSH)";
  case INST_PLUS:
    return "(INST_PLUS)";
  case INST_MINUS:
    return "(INST_MINUS)";
  case INST_MUL:
    return "(INST_MUL)";
  case INST_DIV:
    return "(INST_DIV)";
  default:
    assert(0 && "inst_type_as_cstr: unreachable");
  }
}

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

Err vm_execute_inst(virtualmachine *vm, Inst inst) {
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
    } else if (vm->stack[vm->stack_size - 1] == 0) {
      return ERR_DIV_BY_ZERO;
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
      fprintf(stream, " %ld ", vm->stack[i]);
    }
  } else {
    fprintf(stream, " [empty]\n");
  }
}

#define ARRAY_SIZE(xs) (sizeof(xs) / sizeof((xs)[0]))
virtualmachine vm = {0};
Inst program[] = {MAKE_INST_PUSH(69), MAKE_INST_PUSH(420), MAKE_INST_PLUS,
                  MAKE_INST_PUSH(42), MAKE_INST_MINUS,     MAKE_INST_PUSH(2),
                  MAKE_INST_MUL,      MAKE_INST_PUSH(0),   MAKE_INST_DIV};

int main() {
  vm_dump(stdout, &vm);
  for (size_t i = 0; i < ARRAY_SIZE(program); i++) {
    printf("%s\n", inst_type_as_cstr(program[i].type));
    Err err = vm_execute_inst(&vm, program[i]);
    vm_dump(stdout, &vm);
    if (err != ERR_OK) {
      fprintf(stderr, "Error %s\n", err_as_cstr(err));
      vm_dump(stderr, &vm);
      exit(1);
    }
  }
  return 0;
}
