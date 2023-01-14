#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(xs) (sizeof(xs) / sizeof((xs)[0]))
#define VM_PROGRAM_CAPACITY 1024
#define VM_STACK_CAPACITY 1024
#define VM_EXECUTION_LIMIT 69

typedef enum {
  ERR_OK = 0,
  ERR_STACK_OVERFLOW,
  ERR_STACK_UNDERFOLOW,
  ERR_ILLEGAL_INSTRUCTION,
  ERR_ILLEGAL_INST_ACCESS,
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
  case ERR_ILLEGAL_INST_ACCESS:
    return "ERR_ILLEGAL_INST_ACCESS";
  case ERR_DIV_BY_ZERO:
    return "ERR_DIV_BY_ZERO";
  default:
    assert(0 && "trap_as_cstr: UNREACHABLE");
  }
}

typedef int64_t Word;

typedef enum {
  INST_PUSH,
  INST_PLUS,
  INST_MINUS,
  INST_MUL,
  INST_DIV,
  INST_JMP,
  INST_JMPIF,
  INST_EQ,
  INST_HALT
} Inst_Type;

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
  case INST_JMP:
    return "(INST_JMP)";
  case INST_HALT:
    return "(INST_HALT)";
  case INST_JMPIF:
    return "(INST_JMPIF)";
  case INST_EQ:
    return "(INST_EQ)";
  default:
    assert(0 && "inst_type_as_cstr: unreachable");
  }
}

typedef struct {
  Inst_Type type;
  Word operand;
} Inst;

typedef struct {
  Word stack[VM_STACK_CAPACITY];
  Word stack_size;
  Inst program[VM_PROGRAM_CAPACITY];
  Word program_size;
  Word ip;
  int halt;
} virtualmachine;

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
#define MAKE_INST_JMP(addr)                                                    \
  { .type = INST_JMP, .operand = (addr) }
#define MAKE_INST_HALT(addr)                                                   \
  { .type = INST_HALT, .operand = (addr) }

Err vm_execute_inst(virtualmachine *vm) {
  if (vm->ip < 0 || vm->ip >= vm->program_size) {
    return ERR_ILLEGAL_INST_ACCESS;
  }

  Inst inst = vm->program[vm->ip];

  switch (inst.type) {
  case INST_PUSH:
    if (vm->stack_size >= VM_STACK_CAPACITY) {
      return ERR_STACK_UNDERFOLOW;
    }
    vm->stack[vm->stack_size++] = inst.operand;
    vm->ip += 1;
    break;

  case INST_PLUS:
    if (vm->stack_size < 2) {
      return ERR_STACK_OVERFLOW;
    } else {
      vm->stack[vm->stack_size - 2] += vm->stack[vm->stack_size - 1];
      vm->stack_size -= 1;
      vm->ip += 1;
    }
    break;

  case INST_MINUS:
    if (vm->stack_size < 2) {
      return ERR_STACK_OVERFLOW;
    } else {
      vm->stack[vm->stack_size - 2] -= vm->stack[vm->stack_size - 1];
      vm->stack_size -= 1;
      vm->ip += 1;
    }
    break;

  case INST_MUL:
    if (vm->stack_size < 2) {
      return ERR_STACK_OVERFLOW;
    } else {
      vm->stack[vm->stack_size - 2] *= vm->stack[vm->stack_size - 1];
      vm->stack_size -= 1;
      vm->ip += 1;
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
      vm->ip += 1;
    }
    break;

  case INST_JMP:
    vm->ip = inst.operand;
    break;

  case INST_HALT:
    vm->halt = 1;
    break;

  case INST_EQ:
    if (vm->stack_size < 2) {
      return ERR_STACK_OVERFLOW;
    } else {
      vm->stack[vm->stack_size - 2] =
          vm->stack[vm->stack_size - 1] == vm->stack[vm->stack_size - 2];
      vm->stack_size -= 1;
      vm->ip += 1;
    }
    break;

  case INST_JMPIF:
    if (vm->stack_size < 1) {
      return ERR_STACK_UNDERFOLOW;
    } else if (vm->stack[vm->stack_size - 1]) {
      vm->stack_size -= 1;
      vm->ip = inst.operand;
    } else {
      vm->ip += 1;
    }
    break;

  default:
    return ERR_ILLEGAL_INSTRUCTION;
  }
  return ERR_OK;
}

void vm_dump_stack(FILE *stream, const virtualmachine *vm) {
  fprintf(stream, "\nStack: ");
  if (vm->stack_size > 0) {
    for (Word i = 0; i < vm->stack_size; ++i) {
      fprintf(stream, " %ld ", vm->stack[i]);
    }
  } else {
    fprintf(stream, " [empty]\n");
  }
}

virtualmachine vm = {0};
Inst program[] = {MAKE_INST_PUSH(0), MAKE_INST_PUSH(1), MAKE_INST_PLUS,
                  MAKE_INST_JMP(1)};

void load_program_from_memory(virtualmachine *vm, Inst *program,
                              size_t program_size) {
  assert(program_size < VM_PROGRAM_CAPACITY);
  memcpy(vm->program, program, sizeof(program[0]) * program_size);
  vm->program_size = program_size;
}

int main() {
  load_program_from_memory(&vm, program, ARRAY_SIZE(program));
  vm_dump_stack(stdout, &vm);
  for (int i = 0; i < VM_EXECUTION_LIMIT && !vm.halt; i++) {
    Err err = vm_execute_inst(&vm);
    vm_dump_stack(stdout, &vm);
    if (err != ERR_OK) {
      fprintf(stderr, "Error %s\n", err_as_cstr(err));
      vm_dump_stack(stderr, &vm);
      exit(1);
    }
  }
  return 0;
}
