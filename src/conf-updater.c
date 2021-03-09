//
// Created by maciej on 09.03.21.
//

#include "conf-updater.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* blocks[] = { BLOCK_IPV4, BLOCK_IPV6 };

#ifndef IS_DEBUG
#ifdef __MINGW32__
#define CJDNS_CONF "C:\\Program Files (x86)\\cjdns\\cjdroute.conf"
#elif __GNUC__
#define CJDNS_CONF "/etc/cjdroute.conf"
#else
#error "Invalid platform, please add"
#endif
#else
#define CJDNS_CONF "/tmp/test.conf"
#endif

#define ASK_STR "Ask somebody who is already connected"

int needleFind(char* target, int start, int end, char* compare, int compareLen) {
    int matches = 0;

    for (int needle = start; needle < (end - compareLen + 1); ++needle) {
        if (!strncmp(target + needle, compare, compareLen)) {
            // we got a match
            matches++;
        }
    }

    return matches;
}

int main() {
    FILE *f;

    f = fopen(CJDNS_CONF, "r+");

    if (f == NULL) {
        printf("ERROR: %s does not exist, exiting!\n", CJDNS_CONF);
        return 2;
    }

    printf("Reading %s...\n", CJDNS_CONF);

    // get size
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    if (fsize > 1024*1024) {
        printf("ERROR: Config too big, what the hell are you even doing?!\n");
        return 2;
    }

    // read
    char *cjdconf = malloc(fsize + 2); // two extra bytes, one for adding \n if needed, one for NULL
    fread(cjdconf, 1, fsize, f);

    // clear
    f = freopen(CJDNS_CONF, "w", f);

    if (f == NULL) {
        printf("ERROR: %s reopen failed!\n", CJDNS_CONF);
        return 2;
    }

    if (cjdconf[fsize - 1] != '\n') { // if not ends with LF, then add LF and increase size
        cjdconf[fsize] = '\n';
        fsize++;
    }

    cjdconf[fsize] = 0;

    printf("Patching %s...\n", CJDNS_CONF);

    int lastLine = 0;

    int openBrackets = 0;
    bool insideBlock = false;

    int currentBlock = -1;

    for (int i = 0; i < fsize; ++i) {
        if (cjdconf[i] == '\n') {
            // do next line
            bool ignoreLine = false;
            // decide what to do with line

            // lastLine is start
            // i is end

            if (!insideBlock) {
                if (needleFind(cjdconf, lastLine, i, ASK_STR, strlen(ASK_STR))) {
                    insideBlock = true;
                }
            } else {
                openBrackets += needleFind(cjdconf, lastLine, i, "{", 1);
                openBrackets -= needleFind(cjdconf, lastLine, i, "}", 1);

                if (openBrackets<0) {
                    insideBlock = false;
                    currentBlock++;

                    fprintf(f, "\n");
                    fwrite(blocks[currentBlock], 1,strlen(blocks[currentBlock]), f);
                    fprintf(f, "\n");

                    // don't ignore line, as it's supposed to be printed
                    ignoreLine = false;

                    // cleanup
                    openBrackets = 0;
                } else {
                    // ignore this line, it is part of the old config
                    ignoreLine = true;
                }
            }

            if (!ignoreLine) { // copy line to output config
                fwrite(cjdconf + lastLine, 1, i - lastLine, f);
            }
            lastLine = i;
        }
    }

    fclose(f);

    printf("Successfully patched config!\n");

    return 0;
}