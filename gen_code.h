#ifndef GEN_CODE_H
#define GEN_CODE_H

#include "bof.h"
#include "code_seq.h"

// Function prototypes for the gen_code module
void gen_code_initialize();
void gen_code_output_seq(BOFFILE bf, code_seq cs);
BOFHeader gen_code_program_header(code_seq main_cs);

#endif // GEN_CODE_H
