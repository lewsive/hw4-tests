#include "literal_table.h"
#include "bof.h"
#include "ast.h"
#include "code_seq.h"
#include "string.h"
#include "math.h"

#define STACK_SPACE 4096

void gen_code_initialize()
{
    literal_table_initialize();
}

static void gen_code_output_seq(BOFFILE bf, code_seq cs)
{
    while (!code_seq_is_empty(cs)) {
	bin_instr_t inst = code_seq_first(cs)->instr;
	instruction_write_bin_instr(bf, inst);
	cs = code_seq_rest(cs);
    }
}

static BOFHeader gen_code_program_header(code_seq main_cs)
{
    BOFHeader ret;
    // magic
    strncpy(ret.magic, "MAGIC", 4);
    // text start address
    ret.text_start_address = 0;
    // text length
    ret.text_length = code_seq_size(main_cs) * BYTES_PER_WORD;
    // data start address
    int dsa = MAX(ret.text_length, 1024) + BYTES_PER_WORD;
    ret.data_start_address = dsa;
    // data length
    ret.data_length = literal_table_size() * BYTES_PER_WORD;
    // stack bottom address
    int sba = dsa + ret.data_length + STACK_SPACE;
    ret.stack_bottom_addr = sba;
    return ret;
}

