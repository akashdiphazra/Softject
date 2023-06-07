#include "vm.c"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: ./vmi <input.ebasm>\n");
    fprintf(stderr, "Error: expected input\n");
    exit(1);
}
  vm_load_program_from_file(&vm, argv[1]);
  for (int i = 0; i < 69 && !vm.halt; ++i) {
    Err err = vm_execute_inst(&vm);
    vm_dump_stack(stdout, &vm);
    if (err != ERR_OK) {
      fprintf(stderr, "Error %s\n", err_as_cstr(err));
      exit(1);
    }
  }
  // vm_dump_stack(stdout, &vm);
  return 0;
}
