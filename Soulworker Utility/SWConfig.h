#pragma once
#define MAJORNUMBER 1
#define MINORNUMBER 7
#define BUILDNUMBER 1
#define MODIFICATIONNUMBER 1
#define STR(value) #value
#define STRINGIZE(value) STR(value)
#define APP_VERSION \
  STRINGIZE(MAJORNUMBER) "." \
  STRINGIZE(MINORNUMBER) "." \
  STRINGIZE(BUILDNUMBER) "." \
  STRINGIZE(MODIFICATIONNUMBER)
#define SWCONSTVALUE_RECV 1
#define SWCONSTVALUE_SEND 2 // maybe client send request
#define USE_XOR 0
