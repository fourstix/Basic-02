#include "header.h"

int prepass(char* filename) {
  int   i;
  char  qt;
  FILE *source;
  source = fopen(filename,"r");
  if (source == NULL) {
    printf("Could not open %s\n",filename);
    exit(1);
    }
  useAbs = 0;
  useAdd = 0;
  useSub = 0;
  useMul = 0;
  useDiv = 0;
  useMod = 0;
  useAnd = 0;
  useOr = 0;
  useXor = 0;
  useAtoI = 0;
  useItoA = 0;
  useCmp = 0;
  useEq = 0;
  useNe = 0;
  useGt = 0;
  useLt = 0;
  useEf = 0;
  useRnd = 0;
  useNext = 0;

  lblAtoI = 0;
  lblAbs = 0;
  lblAdd = 0;
  lblAnd = 0;
  lblCmp = 0;
  lblDiv = 0;
  lblEf = 0;
  lblEq = 0;
  lblFalse = 0;
  lblGt = 0;
  lblGte = 0;
  lblItoA = 0;
  lblToBcd = 0;
  lblLt = 0;
  lblLte = 0;
  lblMdNorm = 0;
  lblMod = 0;
  lblMul = 0;
  lblNe = 0;
  lblNext = 0;
  lblNextVar = 0;
  lblOr = 0;
  lblReturn = 0;
  lblRnd = 0;
  lblScall = 0;
  lblSgn = 0;
  lblSret = 0;
  lblStart = 0;
  lblSub = 0;
  lblTrue = 0;
  lblXor = 0;

  while (fgets(currentLine, 1023, source) != NULL) {
    while (strlen(currentLine) > 0 && currentLine[strlen(currentLine)-1] < 32) currentLine[strlen(currentLine)-1] = 0;
    if (strlen(currentLine) > 0) {
      qt = 0;
      for (i=0; i<strlen(currentLine); i++) {
        if (currentLine[i] == '"') qt = 1-qt;
        if (qt == 0) {
          if (currentLine[i] == '+') useAdd = -1;
          if (currentLine[i] == '-') useSub = -1;
          if (currentLine[i] == '*') useMul = -1;
          if (currentLine[i] == '/') useDiv = -1;
          if (currentLine[i] == '%') useMod = -1;
          if (currentLine[i] == '&') useAnd = -1;
          if (currentLine[i] == '|') useOr = -1;
          if (currentLine[i] == '^') useXor = -1;
          if (currentLine[i] == '=') useEq = -1;
          if (currentLine[i] == '<' && currentLine[i+1] == '>') useNe = -1;
          if (currentLine[i] == '<' && currentLine[i+1] == '=') useLte = -1;
          if (currentLine[i] == '>' && currentLine[i+1] == '=') useGte = -1;
          if (currentLine[i] == '<' && currentLine[i+1] != '>' && currentLine[i+1] != '=') useLt = -1;
          if (currentLine[i] == '>' && currentLine[i+1] != '=') useGt = -1;
          if (strncasecmp(currentLine+i,"print",5) == 0) useItoA = -1;
          if (strncasecmp(currentLine+i,"locate",6) == 0) useItoA = -1;
          if (strncasecmp(currentLine+i,"input",5) == 0) useAtoI = -1;
          if (strncasecmp(currentLine+i,"next",4) == 0) useNext = -1;
          if (strncasecmp(currentLine+i,"flg(",4) == 0) useEf = -1;
          if (strncasecmp(currentLine+i,"fre(",4) == 0) useSub = -1;
          if (strncasecmp(currentLine+i,"abs(",4) == 0) useAbs = -1;
          if (strncasecmp(currentLine+i,"rnd(",4) == 0) useRnd = -1;
          if (strncasecmp(currentLine+i,"sgn(",4) == 0) useSgn = -1;
          }
        }
      }
    }
  fclose(source);

  if (useEq || useNe || useGt || useLt || useGte || useLte) useCmp = -1;
  if (useCmp) useSub = -1;
  if (useRnd) useMod = -1;
  if (useMod) useDiv = -1;
  if (useNext) useSub = -1;
  if (lblF_inmsg == 0xffff) {
    useAtoI = 0;
    useItoA = 0;
    }
  if (useAtoI == 0 && useItoA == 0) useSelfTerm = 0;
  printf("\n");
  }

