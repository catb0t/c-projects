#!/bin/sh

FILENAME=objtest.h
CONTENTS=$(cat _test_*.c | sed -r 's/(^Test.*|cr_assert.*|^}|^#)/\/\/\1/gm')
(
  echo '/* BEGIN GENERATED CODE */
#include "testcommon.h"
void test (void);

void test (void) {
'
  printf "%s" "$CONTENTS"
  printf "\n%s" "} /* END GENERATED CODE */ "
) > $FILENAME
