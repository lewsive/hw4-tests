#include "gen_code.c"
#include "bof.h"

BOFHeader gen_code_program_header(code_seq main_cs);
void gen_code_output_seq(BOFFILE bf, code_seq cs);