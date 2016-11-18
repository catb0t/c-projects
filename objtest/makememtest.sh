#!/bin/sh

FILENAME=objtest.c
CONTENTS=$(cat _test_*.c | sed -r 's/(^Test.*|cr_assert.*|^}|^#)/\/\/\1/gm')
(
  echo '/* BEGIN GENERATED CODE */
#include "testcommon.h"
void test (void);

int main (void) { test(); return EXIT_SUCCESS; }

void test (void) {
'
  printf "%s" "$CONTENTS"
  printf "\n%s\n" "} /* END GENERATED CODE */ "
) > $FILENAME
