/*
 * bbin2ihex.c: Read binary data from stdin, output in IHEX format.
 *
 * By Kimmo Kulovesi, http://arkku.com
 */

#include "kk_ihex.h"
#include <stdio.h>
#include <stdlib.h>

//#define IHEX_WRITE_INITIAL_EXTENDED_ADDRESS_RECORD

int
main (void) {
    struct ihex_state ihex;
    size_t count;
    uint8_t buf[1024];

    ihex_init(&ihex);
    ihex_write_at_address(&ihex, 0);
#ifdef IHEX_WRITE_INITIAL_EXTENDED_ADDRESS_RECORD
    ihex.flags |= IHEX_FLAG_ADDRESS_OVERFLOW;
#endif
    while ((count = fread(buf, 1, sizeof(buf), stdin))) {
        ihex_write_bytes(&ihex, buf, count);
    }
    ihex_end_write(&ihex);

    return EXIT_SUCCESS;
}

void ihex_flush_buffer(char *buffer, char *eptr) {
    *eptr = '\0';
    (void) fputs(buffer, stdout);
}
