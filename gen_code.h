#include "gen_code.c"
#include "bof.h"

static BOFHeader gen_code_program_header(code_seq main_cs);
static void gen_code_output_seq(BOFFILE bf, code_seq cs);