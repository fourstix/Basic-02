#include "header.h"

// R7 - data stack

void library() {
  char ctmp;
  word a;
  word t1,t2,t3,t4;
  ctmp = showCompiler;
  showCompiler = 0;
  Asm("scall:      equ  r4");
  Asm("sret:       equ  r5");
  if (useElfos) {
    output(programStart/256); output(programStart%256);
    output((highest-programStart+1)/256); output((highest-programStart+1)%256);
    output(programStart/256); output(programStart%256);
    }
  if (useElfos || useStg) {
    Asm("init:       lbr  start");
    }
  else {
    Asm("init:       sex  r0");
    Asm("            dis");
    Asm("            db   020h");
    Asm("            ldi  start.1");
    Asm("            phi  r3");
    Asm("            ldi  start.0");
    Asm("            plo  r3");
    }
  lblReturn = address;
  Asm("            sep  r3");
  if (passNumber == 1) lblScall = address;
  Asm("call:       plo     re");
  Asm("            ghi     r6");
  Asm("            stxd");
  Asm("            glo     r6");
  Asm("            stxd");
  Asm("            ghi     r3");
  Asm("            phi     r6");
  Asm("            glo     r3");
  Asm("            plo     r6");
  Asm("            lda     r6");
  Asm("            phi     r3");
  Asm("            lda     r6");
  Asm("            plo     r3");
  Asm("            glo     re");
  Asm("            br      call-1");
  Asm("            sep     r3");
  if (passNumber == 1) lblSret = address;
  Asm("ret:        plo     re");
  Asm("            ghi     r6");
  Asm("            phi     r3");
  Asm("            glo     r6");
  Asm("            plo     r3");
  Asm("            irx");
  Asm("            ldxa");
  Asm("            plo     r6");
  Asm("            ldx");
  Asm("            phi     r6");
  Asm("            glo     re");
  Asm("            br      ret-1");
  Asm("return:     sep  sret");

  if (useEf) {
    if (passNumber == 1) lblEf = address;
    Asm("readef:     ldi     0");
    Asm("            bn1     ef1");
    Asm("            ori     1");
    Asm("ef1:        bn2     ef2");
    Asm("            ori     2");
    Asm("ef2:        bn3     ef3");
    Asm("            ori     4");
    Asm("ef3:        bn4     ef4");
    Asm("            ori     8");
    Asm("ef4:        sep     sret");
    }

  if (useSelfTerm) {
    t1 = address;
    Asm("          sep     r3");
    if (passNumber == 1) lblF_delay = address;
    Asm("delay:    ghi     re");
    Asm("          shr");
    Asm("          plo     re");
    Asm("          sex     r2");
    Asm("delay1:   dec     re");
    Asm("          glo     re");
    Asm("          bz      delay-1");
    Asm("          br      delay1");

    if (passNumber == 1) lblF_type = address;
    Asm("f_type:   plo     re");
    Asm("          ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("          glo     re");
    Asm("          phi     rf");
    Asm("          ldi     9");
    Asm("          plo     rf");
    Asm("          ldi     delay.1");
    Asm("          phi     rd");
    Asm("          ldi     delay.0");
    Asm("          plo     rd");
    Asm("          adi     0");
    Asm("sendlp:   bdf     sendnb              ; jump if no bit");
    if (SERSEQ == SEQ)
      Asm("          seq");
    else
      Asm("          req");
    Asm("          br      sendct");
    if (SERREQ == REQ)
      Asm("sendnb:   req");
    else
      Asm("sendnb:   seq");
    Asm("          br      sendct");
    Asm("sendct:   sep     rd                  ; perform bit delay");
    Asm("          sex r2");
    Asm("          sex r2");
    Asm("          ghi     rf");
    Asm("          shrc");
    Asm("          phi     rf");
    Asm("          dec     rf");
    Asm("          glo     rf");
    Asm("          bnz     sendlp");
    if (SERREQ == REQ)
      Asm("          req");
    else
      Asm("          seq");
    Asm("          sep     rd");
    Asm("          sep     rd");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldxa");
    Asm("          phi     rd");
    Asm("          ldxa");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          sep     sret");

    if (passNumber == 1) lblF_read = address;
    Asm("f_read:   ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("          ldi     9");
    Asm("          plo     rf");
    Asm("          ldi     delay.1");
    Asm("          phi     rd");
    Asm("          ldi     delay.0");
    Asm("          plo     rd");
    Asm("          ghi     re");
    Asm("          phi     rf");
    Asm("          shr");
    Asm("          shr");
    Asm("          phi     re");
    if (SERP == B1)  Asm("          b1      $");
    if (SERP == B2)  Asm("          b2      $");
    if (SERP == B3)  Asm("          b3      $");
    if (SERP == B4)  Asm("          b4      $");
    if (SERP == BN1) Asm("          bn1     $");
    if (SERP == BN2) Asm("          bn2     $");
    if (SERP == BN3) Asm("          bn3     $");
    if (SERP == BN4) Asm("          bn4     $");
    Asm("          sep     rd");
    Asm("          ghi     rf");
    Asm("          phi     re");
    Asm("          ghi     rf");
    Asm("          shr");
    Asm("          bdf     recvlpe");
    Asm("recvlp:   ghi     rf");
    Asm("          shr");
    if (SERN == B1)  Asm("          b1      recvlp0");
    if (SERN == B2)  Asm("          b2      recvlp0");
    if (SERN == B3)  Asm("          b3      recvlp0");
    if (SERN == B4)  Asm("          b4      recvlp0");
    if (SERN == BN1) Asm("          bn1     recvlp0");
    if (SERN == BN2) Asm("          bn2     recvlp0");
    if (SERN == BN3) Asm("          bn3     recvlp0");
    if (SERN == BN4) Asm("          bn4     recvlp0");
    Asm("          ori     128");
    Asm("recvlp1:  phi     rf");
    Asm("          sep     rd");
    Asm("          dec     rf");
    Asm("          nop");
    Asm("          nop");
    Asm("          glo     rf");
    Asm("          bnz     recvlp");
    if (SERREQ == REQ)
      Asm("recvdone: req");
    else
      Asm("recvdone: seq");
    Asm("          ghi     rf");
    Asm("          plo     re");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldxa");
    Asm("          phi     rd");
    Asm("          ldxa ");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          glo     re");
    Asm("          sep     sret");
    Asm("recvlp0:  br      recvlp1");
    Asm("recvlpe:  ghi     rf");
    Asm("          shr");
    if (SERN == B1)  Asm("          b1      recvlpe0");
    if (SERN == B2)  Asm("          b2      recvlpe0");
    if (SERN == B3)  Asm("          b3      recvlpe0");
    if (SERN == B4)  Asm("          b4      recvlpe0");
    if (SERN == BN1) Asm("          bn1     recvlpe0");
    if (SERN == BN2) Asm("          bn2     recvlpe0");
    if (SERN == BN3) Asm("          bn3     recvlpe0");
    if (SERN == BN4) Asm("          bn4     recvlpe0");
    Asm("          ori     128");
    if (SERREQ == REQ)
      Asm("          req");
    else
      Asm("          seq");
    Asm("recvlpe1: phi     rf");
    Asm("          sep     rd");
    Asm("          dec     rf");
    Asm("          sex     r2");
    Asm("          sex     r2");
    Asm("          glo     rf");
    Asm("          bnz     recvlpe");
    Asm("          br      recvdone");
    if (SERSEQ == SEQ)
      Asm("recvlpe0: seq");
    else
      Asm("recvlpe0: req");
    Asm("          br      recvlpe1");

    if (passNumber == 1) lblF_setbd = address;
    if (SERREQ == REQ)
      Asm("f_setbd:  req");
    else
      Asm("f_setbd:  seq");
    Asm("          ldi     0");
    Asm("          phi     rc");
    Asm("          plo     rc");
    Asm("          phi     rb");
    Asm("          plo     rb");
    if (SERP == B1)  Asm("timalc_o: b1      $");
    if (SERP == B2)  Asm("timalc_o: b2      $");
    if (SERP == B3)  Asm("timalc_o: b3      $");
    if (SERP == B4)  Asm("timalc_o: b4      $");
    if (SERP == BN1) Asm("timalc_o: bn1     $");
    if (SERP == BN2) Asm("timalc_o: bn2     $");
    if (SERP == BN3) Asm("timalc_o: bn3     $");
    if (SERP == BN4) Asm("timalc_o: bn4     $");
    if (SERN == B1)  Asm("end_sb:   b1      $");
    if (SERN == B2)  Asm("end_sb:   b2      $");
    if (SERN == B3)  Asm("end_sb:   b3      $");
    if (SERN == B4)  Asm("end_sb:   b4      $");
    if (SERN == BN1) Asm("end_sb:   bn1     $");
    if (SERN == BN2) Asm("end_sb:   bn2     $");
    if (SERN == BN3) Asm("end_sb:   bn3     $");
    if (SERN == BN4) Asm("end_sb:   bn4     $");
    if (SERP == B1)  Asm("          b1      $");
    if (SERP == B2)  Asm("          b2      $");
    if (SERP == B3)  Asm("          b3      $");
    if (SERP == B4)  Asm("          b4      $");
    if (SERP == BN1) Asm("          bn1     $");
    if (SERP == BN2) Asm("          bn2     $");
    if (SERP == BN3) Asm("          bn3     $");
    if (SERP == BN4) Asm("          bn4     $");
    Asm("setbd1:   inc     rc");
    Asm("          sex     r2");
    Asm("          sex     r2");
    if (SERN == B1)  Asm("          b1      setbd1");
    if (SERN == B2)  Asm("          b2      setbd1");
    if (SERN == B3)  Asm("          b3      setbd1");
    if (SERN == B4)  Asm("          b4      setbd1");
    if (SERN == BN1) Asm("          bn1     setbd1");
    if (SERN == BN2) Asm("          bn2     setbd1");
    if (SERN == BN3) Asm("          bn3     setbd1");
    if (SERN == BN4) Asm("          bn4     setbd1");
    Asm("setbd2:   inc     rb");
    Asm("          sex     r2");
    Asm("          sex     r2");
    if (SERP == B1)  Asm("          b1      setbd2");
    if (SERP == B2)  Asm("          b2      setbd2");
    if (SERP == B3)  Asm("          b3      setbd2");
    if (SERP == B4)  Asm("          b4      setbd2");
    if (SERP == BN1) Asm("          bn1     setbd2");
    if (SERP == BN2) Asm("          bn2     setbd2");
    if (SERP == BN3) Asm("          bn3     setbd2");
    if (SERP == BN4) Asm("          bn4     setbd2");
    Asm("setbd4:   glo     rb");
    Asm("          shr");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     rc");
    Asm("          shr");
    Asm("          shr");
    Asm("          sm");
    Asm("          lbz     setbd3");
    Asm("          ldi     1");
    Asm("          lskp");
    Asm("setbd3:   ldi     0");
    Asm("          phi     rb");
    Asm("          glo     rc");
    Asm("          smi     4");
    Asm("          phi     re");
    Asm("          ghi     rb");
    Asm("          shr");
    Asm("          ghi     re");
    Asm("          shlc");
    Asm("          phi     re");
    Asm("timalc_rt: sep     sret");

    Asm("f_tty:    lbr     f_type");

    if (passNumber == 1) lblF_inmsg = address;
    Asm("f_inmsg:  lda     r6");
    Asm("          lbz     return");
    Asm("          sep     scall");
    Asm("          dw      f_type");
    Asm("          lbr     f_inmsg");

    if (passNumber == 1) lblF_msg = address;
    Asm("f_msg:    lda     rf");
    Asm("          lbz     return");
    Asm("          sep     scall");
    Asm("          dw      f_type");
    Asm("          lbr     f_msg");

    if (passNumber == 1) lblF_inmsg = address;
    Asm("f_input:  ldi     0");
    Asm("          plo     ra");
    Asm("inplp:    sep     scall");
    Asm("          dw      f_read");
    Asm("          plo     re");
    Asm("          smi     3");
    Asm("          lbnz    inpgo");
    Asm("inpterm:  smi     0");
    Asm("          ldi     0");
    Asm("          lbr     inpdone2");
    Asm("inpdone:  ldi     0");
    Asm("          shr");
    Asm("inpdone2: str     rf");
    Asm("          sep     sret");
    Asm("inpgo:    smi     5");
    Asm("          lbz     isbs");
    Asm("          smi     5");
    Asm("          lbz     inpdone");
    Asm("          glo     rc");
    Asm("          lbnz    inpcnt");
    Asm("          ghi     rc");
    Asm("          lbnz    inpcnt");
    Asm("          ldi     8");
    Asm("          sep     scall");
    Asm("          dw      f_tty");
    Asm("          lbr     bs2");
    Asm("inpcnt:   glo     re");
    Asm("          str     rf");
    Asm("          inc     rf");
    Asm("          smi     08");
    Asm("          lbnz    nobs");
    Asm("isbs:     glo     ra");
    Asm("          lbz     inplp");
    Asm("          dec     ra");
    Asm("          dec     rf");
    Asm("          inc     rc");
    Asm("bs2:      ldi     32");
    Asm("          sep     scall");
    Asm("          dw      f_tty");
    Asm("          ldi     8");
    Asm("          sep     scall");
    Asm("          dw      f_tty");
    Asm("          lbr     inplp");
    Asm("nobs:     inc     ra");
    Asm("          dec     rc");
    Asm("          lbr     inplp");
    }



  if (useMul || useDiv) {
    if (passNumber == 1) lblMdNorm = address;
    Asm("mdnorm:     ghi     rc");
    Asm("            str     r2");
    Asm("            ghi     rd");
    Asm("            xor");
    Asm("            shl");
    Asm("            ldi     0");
    Asm("            shlc");
    Asm("            plo     re");
    Asm("            ghi     rc");
    Asm("            shl");
    Asm("            lbnf    mdnorm2");
    Asm("            ghi     rc");
    Asm("            xri     0ffh");
    Asm("            phi     rc");
    Asm("            glo     rc");
    Asm("            xri     0ffh");
    Asm("            plo     rc");
    Asm("            inc     rc");
    Asm("mdnorm2:    ghi     rd");
    Asm("            shl");
    Asm("            lbnf    mdnorm3");
    Asm("            ghi     rd");
    Asm("            xri     0ffh");
    Asm("            phi     rd");
    Asm("            glo     rd");
    Asm("            xri     0ffh");
    Asm("            plo     rd");
    Asm("            inc     rd");
    Asm("mdnorm3:    glo     re");
    Asm("            sep     sret");
    }

  if (useMul) {
    if (passNumber == 1) lblMul = address;
    Asm("mul16:    sex     r7");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldxa");
    Asm("          phi     rd");
    Asm("          ldxa");
    Asm("          plo     rc");
    Asm("          ldx");
    Asm("          phi     rc");
    Asm("          sex     r2");
    Asm("          sep     scall");
    Asm("          dw      mdnorm");
    Asm("          plo     re");
    Asm("          ldi     0");
    Asm("          phi     rf");
    Asm("          plo     rf");
    Asm("mulloop:  glo     rd");
    Asm("          lbnz    mulcont");
    Asm("          ghi     rd");
    Asm("          lbnz    mulcont");
    Asm("          glo     re");
    Asm("          shr");
    Asm("          lbnf    mulexit");
    Asm("          glo     rf");
    Asm("          xri     0ffh");
    Asm("          plo     rf");
    Asm("          ghi     rf");
    Asm("          xri     0ffh");
    Asm("          phi     rf");
    Asm("          inc     rf");
    Asm("mulexit:  sex     r7");
    Asm("          ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          sex     r2");
    Asm("          sep     sret");
    Asm("mulcont:  ghi     rd");
    Asm("          shr");
    Asm("          phi     rd");
    Asm("          glo     rd");
    Asm("          shrc");
    Asm("          plo     rd");
    Asm("          lbnf    mulcont2");
    Asm("          glo     rc");
    Asm("          str     r2");
    Asm("          glo     rf");
    Asm("          add");
    Asm("          plo     rf");
    Asm("          ghi     rc");
    Asm("          str     r2");
    Asm("          ghi     rf");
    Asm("          adc");
    Asm("          phi     rf");
    Asm("mulcont2: glo     rc");
    Asm("          shl");
    Asm("          plo     rc");
    Asm("          ghi     rc");
    Asm("          shlc");
    Asm("          phi     rc");
    Asm("          lbr     mulloop");
    }

  if (useDiv) {
    if (passNumber == 1) lblDiv = address;
    Asm("div16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            plo     rd");
    Asm("            ldxa");
    Asm("            phi     rd");
    Asm("            ldxa");
    Asm("            plo     rc");
    Asm("            ldx");
    Asm("            phi     rc");
    Asm("            sex     r2");
    Asm("            sep     scall");
    Asm("            dw      mdnorm");
    Asm("            plo     re");
    Asm("            glo     rd");
    Asm("            lbnz    div16_1");
    Asm("            ghi     rd");
    Asm("            lbnz    div16_1");
    Asm("            sex     r7");
    Asm("            ldi     0");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");
    Asm("div16_1:    ldi     0");
    Asm("            phi     rf");
    Asm("            plo     rf");
    Asm("            phi     r8");
    Asm("            plo     r8");
    Asm("            inc     r8");
    Asm("d16lp1:     ghi     rd");
    Asm("            ani     128");
    Asm("            lbnz    divst");
    Asm("            glo     rd");
    Asm("            shl");
    Asm("            plo     rd");
    Asm("            ghi     rd");
    Asm("            shlc");
    Asm("            phi     rd");
    Asm("            glo     r8");
    Asm("            shl");
    Asm("            plo     r8");
    Asm("            ghi     r8");
    Asm("            shlc");
    Asm("            phi     r8");
    Asm("            lbr     d16lp1");
    Asm("divst:      glo     rd");
    Asm("            lbnz    divgo");
    Asm("            ghi     rd");
    Asm("            lbnz    divgo");
    Asm("            glo     re");
    Asm("            shr");
    Asm("            lbnf    divret");
    Asm("            ghi     rf");
    Asm("            xri     0ffh");
    Asm("            phi     rf");
    Asm("            glo     rf");
    Asm("            xri     0ffh");
    Asm("            plo     rf");
    Asm("            inc     rf");
    Asm("divret:     sex     r7");
    Asm("            ghi     rf");
    Asm("            stxd");
    Asm("            glo     rf");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");
    Asm("divgo:      glo     rc");
    Asm("            plo     r9");
    Asm("            ghi     rc");
    Asm("            phi     r9");
    Asm("            glo     rd");
    Asm("            str     r2");
    Asm("            glo     rc");
    Asm("            sm");
    Asm("            plo     rc");
    Asm("            ghi     rd");
    Asm("            str     r2");
    Asm("            ghi     rc");
    Asm("            smb");
    Asm("            phi     rc");
    Asm("            lbdf    divyes");
    Asm("            glo     r9");
    Asm("            plo     rc");
    Asm("            ghi     r9");
    Asm("            phi     rc");
    Asm("            lbr     divno");
    Asm("divyes:     glo     r8");
    Asm("            str     r2");
    Asm("            glo     rf");
    Asm("            add");
    Asm("            plo     rf");
    Asm("            ghi     r8");
    Asm("            str     r2");
    Asm("            ghi     rf");
    Asm("            adc");
    Asm("            phi     rf");
    Asm("divno:      ghi     rd");
    Asm("            shr");
    Asm("            phi     rd");
    Asm("            glo     rd");
    Asm("            shrc");
    Asm("            plo     rd");
    Asm("            ghi     r8");
    Asm("            shr");
    Asm("            phi     r8");
    Asm("            glo     r8");
    Asm("            shrc");
    Asm("            plo     r8");
    Asm("            lbdf    divret");
    Asm("            lbr     divst");
    }

  if (useMod) {
    if (passNumber == 1) lblMod = address;
    Asm("mod16:      sep     scall");
    Asm("            dw      div16");
    Asm("            inc     r7");
    Asm("            inc     r7");
    Asm("            ghi     rc");
    Asm("            str     r7");
    Asm("            dec     r7");
    Asm("            glo     rc");
    Asm("            str     r7");
    Asm("            dec     r7");
    Asm("            sep     sret");
    }

  if (useAdd) {
    if (passNumber == 1) lblAdd = address;
    Asm("add16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            add");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx           ");
    Asm("            adc");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useSub) {
    if (passNumber == 1) lblSub = address;
    Asm("sub16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            sd");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx           ");
    Asm("            sdb");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useAnd) {
    if (passNumber == 1) lblAnd = address;
    Asm("and16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            and");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            and");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useOr) {
    if (passNumber == 1) lblOr = address;
    Asm("or16:       sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            or");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            or");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useXor) {
    if (passNumber == 1) lblXor = address;
    Asm("xor16:      sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            xor");
    Asm("            stxd");
    Asm("            ldxa");
    Asm("            irx");
    Asm("            xor");
    Asm("            stxd");
    Asm("            dec     r7");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useCmp) {
    if (passNumber == 1) lblTrue = address;
    Asm("true:       ldi     0ffh");
    Asm("            sex     r7");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");

    if (passNumber == 1) lblFalse = address;
    Asm("false:      ldi     000h");
    Asm("            sex     r7");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");
    }

  if (useEq) {
    if (passNumber == 1) lblEq = address;
    Asm("eq16:       sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true");
    Asm("            lbr     false");
    }

  if (useNe) {
    if (passNumber == 1) lblNe = address;
    Asm("ne16:       sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbnz    true");
    Asm("            lbr     false");
    }

  if (useGt) {
    if (passNumber == 1) lblGt = address;
    Asm("gt16:       sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     false");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbnf    true");
    Asm("            lbr     false");
    }

  if (useLt) {
    if (passNumber == 1) lblLt = address;
    Asm("lt16:       sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     false");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbdf    true");
    Asm("            lbr     false");
    }

  if (useGte) {
    if (passNumber == 1) lblGte = address;
    Asm("gte16:      sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbnf    true");
    Asm("            lbr     false");
    }

  if (useLte) {
    if (passNumber == 1) lblLte = address;
    Asm("lte16:      sep     scall");
    Asm("            dw      sub16");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbdf    true");
    Asm("            lbr     false");
    }

  if (useAbs) {
    if (passNumber == 1) lblAbs = address;
    Asm("abs16:    inc     r7");
    Asm("          inc     r7");
    Asm("          ldn     r7");
    Asm("          shl");
    Asm("          lbnf    absrt");
    Asm("          dec     r7");
    Asm("          ldn     r7");
    Asm("          xri     0ffh");
    Asm("          adi     1");
    Asm("          str     r7");
    Asm("          inc     r7");
    Asm("          ldn     r7");
    Asm("          xri     0ffh");
    Asm("          adci    0");
    Asm("          str     r7");
    Asm("absrt:    dec     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    }

  if (useSgn) {
    if (passNumber == 1) lblSgn = address;
    Asm("sgn16:    inc     r7");
    Asm("          lda     r7");
    Asm("          str     r2");
    Asm("          ldn     r7");
    Asm("          shl");
    Asm("          lbdf    sgnm");
    Asm("          ldn     r7");
    Asm("          or");
    Asm("          lbz     sgn0");
    Asm("          ldi     0");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          ldi     1");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgnm:     ldi     0ffh");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgn0:     dec     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    }

  if (useRnd || useRnd32) {
    Asm("lfsr_lp:  ldi     [LFSR_].1");
    Asm("          phi     r9");
    Asm("          ldi     [LFSR_].0");
    Asm("          plo     r9");
    Asm("          inc     r9");
    Asm("          inc     r9");
    Asm("          inc     r9");
    Asm("          ldn     r9");
    Asm("          plo     re");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          plo     re");
    Asm("          ldn     r2");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          plo     re");
    Asm("          ldn     r2");
    Asm("          shr");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          plo     re");
    Asm("          ldn     r2");
    Asm("          shr");
    Asm("          shr");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          plo     re");
    Asm("          dec     r9");
    Asm("          dec     r9");
    Asm("          dec     r9");
    Asm("          ldn     r9");
    Asm("          shl");
    Asm("          shlc");
    Asm("          str     r2");
    Asm("          glo     re");
    Asm("          xor");
    Asm("          xri     1");
    Asm("          shr");
    Asm("          ldn     r9");
    Asm("          shrc");
    Asm("          str     r9");
    Asm("          inc     r9");
    Asm("          ldn     r9");
    Asm("          shrc");
    Asm("          str     r9");
    Asm("          inc     r9");
    Asm("          ldn     r9");
    Asm("          shrc");
    Asm("          str     r9");
    Asm("          inc     r9");
    Asm("          ldn     r9");
    Asm("          shrc");
    Asm("          str     r9");
    Asm("          dec     rc");
    Asm("          glo     rc");
    Asm("          lbnz    lfsr_lp");
    Asm("          sep     sret");
    }

  if (useRnd) {
    if (passNumber == 1) lblRnd = address;
    Asm("rnd16:    ldi     16");
    Asm("          plo     rc");
    Asm("          sep     scall         ; Shift the register");
    Asm("          dw      lfsr_lp");
    Asm("          ldi     [LFSR_].1");
    Asm("          phi     r9");
    Asm("          ldi     [LFSR_].0");
    Asm("          plo     r9");
    Asm("          lda     r9");
    Asm("          plo     rf");
    Asm("          ldn     r9");
    Asm("          phi     rf");
    Asm("          inc     r7");
    Asm("          lda     r7");
    Asm("          plo     r9");
    Asm("          ldn     r7");
    Asm("          phi     r9");
    Asm("          ghi     rf");
    Asm("          ani     07fh");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          glo     rf");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          ghi     r9");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          glo     r9");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          lbr     mod16");
    }

  if (useNext) {
    if (passNumber == 1) lblNextVar = address;
    Asm("nextvar:  irx          ; move to varAddr");
    Asm("          ldxa");
    Asm("          plo     rd");
    Asm("          ldxa");
    Asm("          phi     rd");
    Asm("          irx");
    Asm("          irx");
    Asm("          glo     rc   ; check for correct address");
    Asm("          sm           ; against stack");
    Asm("          lbnz    nv1  ; jump if not");
    Asm("          irx          ; move to msb");
    Asm("          ghi     rc");
    Asm("          sm           ; compare");
    Asm("          lbnz    nv2  ; jump if not");
    Asm("          dec     r2   ; entry found, move back");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          dec     r2");
    Asm("          lbr     next");
    Asm("nv1:      irx          ; move past bad entry");
    Asm("nv2:      irx          ; move past bad entry");
    Asm("          irx       ");
    Asm("          irx       ");
    Asm("          irx       ");
    Asm("          ghi     rd");
    Asm("          stxd");
    Asm("          glo     rd");
    Asm("          stxd");
    Asm("          lbr     nextvar");
    if (passNumber == 1) lblNext = address;
    Asm("next:     glo     r2");
    Asm("          plo     ra");
    Asm("          ghi     r2");
    Asm("          phi     ra");
    Asm("          sex     ra");
    Asm("          irx          ; return address lsb");
    Asm("          irx          ; return address msb");
    Asm("          irx          ; exec address lsb");
    Asm("          ldxa         ; retrieve exec address");
    Asm("          plo     r9");
    Asm("          ldxa");
    Asm("          phi     r9");
    Asm("          ldxa         ; get it");
    Asm("          plo     rf   ; set rf to address");
    Asm("          ldxa         ; get msb");
    Asm("          phi     rf");
    Asm("          inc     rf   ; point to variable lsb");
    Asm("          ldn     rf   ; retrieve it");
    Asm("          add          ; add in step");
    Asm("          str     rf");
    Asm("          dec     rf   ; point to msb");
    Asm("          irx          ; point to msb of step");
    Asm("          ldn     rf   ; get msb of var value");
    Asm("          adc          ; add in step");
    Asm("          str     rf   ; store back into variable");
    Asm("          irx          ; point to loop count lsb");
    Asm("          ldi     1    ; need to decrement count");
    Asm("          sd           ; decrement it");
    Asm("          str     ra   ; and put it back");
    Asm("          irx          ; point to loop count msb");
    Asm("          ldi     0    ; propagate carry");
    Asm("          sdb");
    Asm("          str     ra   ; and put it back");
    Asm("          sex     r2   ; point X back to R2");
    Asm("          lbdf    stay ; Jump if loop not done");
    Asm("          inc     r2");
    Asm("          dec     ra");
    Asm("          ldxa");
    Asm("          str     ra");
    Asm("          inc     ra");
    Asm("          ldx");
    Asm("          str     ra");
    Asm("          dec     ra");
    Asm("          dec     ra");
    Asm("          glo     ra");
    Asm("          plo     r2");
    Asm("          ghi     ra");
    Asm("          phi     r2");
    Asm("          sep     sret ; nothing to do so return");
    Asm("stay:     glo     r9   ; set return address to exec address");
    Asm("          plo     r6");
    Asm("          ghi     r9");
    Asm("          phi     r6");
    Asm("          sep     sret ; and then return");
    }

  if (useAtoI) {
    /* **************************************** */
    /* ***** Convert ASCII to integer     ***** */
    /* ***** RF - Pointer to ASCII number ***** */
    /* ***** Returns: RC - 16-bit integer ***** */
    /* **************************************** */
    if (passNumber == 1) lblAtoI = address;
    Asm("atoi:     ldi     0");
    Asm("          plo     rc");
    Asm("          phi     rc");
    Asm("atoi_0_1: lda     rf");
    Asm("          plo     re");
    Asm("          smi     '0'");
    Asm("          lbnf    atoi_no");
    Asm("          smi     10");
    Asm("          lbnf    atoi_0_2");
    Asm("atoi_no:  sep     sret");
    Asm("atoi_0_2: glo     re");
    Asm("          smi     '0'");
    Asm("          plo     re");
    Asm("          glo     rc");
    Asm("          shl");
    Asm("          plo     rc");
    Asm("          plo     r8");
    Asm("          ghi     rc");
    Asm("          shlc");
    Asm("          phi     rc");
    Asm("          phi     r8");
    Asm("          glo     r8");
    Asm("          shl");
    Asm("          plo     r8");
    Asm("          ghi     r8");
    Asm("          shlc");
    Asm("          phi     r8");
    Asm("          glo     r8");
    Asm("          shl");
    Asm("          plo     r8");
    Asm("          ghi     r8");
    Asm("          shlc");
    Asm("          phi     r8");
    Asm("          glo     r8");
    Asm("          str     r2");
    Asm("          glo     rc");
    Asm("          add");
    Asm("          plo     rc");
    Asm("          ghi     r8");
    Asm("          str     r2");
    Asm("          ghi     rc");
    Asm("          adc");
    Asm("          phi     rc");
    Asm("          glo     re");
    Asm("          str     r2");
    Asm("          glo     rc");
    Asm("          add");
    Asm("          plo     rc");
    Asm("          ghi     rc");
    Asm("          adci    0");
    Asm("          phi     rc");
    Asm("          lbr     atoi_0_1");
    }
  if (useItoA) {
    /* ************************************** */
    /* ***** Convert RC to bcd in M[RF] ***** */
    /* ************************************** */
    if (passNumber == 1) lblToBcd = address;
    Asm("tobcd:    ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          ldi     5");
    Asm("          plo     re");
    Asm("tobcdlp1: ldi     0");
    Asm("          str     rf");
    Asm("          inc     rf");
    Asm("          dec     re");
    Asm("          glo     re");
    Asm("          lbnz    tobcdlp1");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          ldi     16");
    Asm("          plo     r9");
    Asm("tobcdlp2: ldi     5");
    Asm("          plo     re");
    Asm("          ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("tobcdlp3: ldn     rf");
    Asm("          smi     5");
    Asm("          lbnf    tobcdlp3a");
    Asm("          adi     8");
    Asm("          str     rf");
    Asm("tobcdlp3a: inc     rf");
    Asm("          dec     re");
    Asm("          glo     re");
    Asm("          lbnz    tobcdlp3");
    Asm("          glo     rc");
    Asm("          shl");
    Asm("          plo     rc");
    Asm("          ghi     rc");
    Asm("          shlc");
    Asm("          phi     rc");
    Asm("          shlc");
    Asm("          shl");
    Asm("          shl");
    Asm("          shl");
    Asm("          str     rf");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          ghi     rf");
    Asm("          stxd");
    Asm("          glo     rf");
    Asm("          stxd");
    Asm("          ldi     5");
    Asm("          plo     re");
    Asm("tobcdlp4: lda     rf");
    Asm("          str     r2");
    Asm("          ldn     rf");
    Asm("          shr");
    Asm("          shr");
    Asm("          shr");
    Asm("          shr");
    Asm("          ldn     r2");
    Asm("          shlc");
    Asm("          ani     0fh");
    Asm("          dec     rf");
    Asm("          str     rf");
    Asm("          inc     rf");
    Asm("          dec     re");
    Asm("          glo     re");
    Asm("          lbnz    tobcdlp4");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo     rf");
    Asm("          ldx");
    Asm("          phi     rf");
    Asm("          dec     r9");
    Asm("          glo     r9");
    Asm("          lbnz    tobcdlp2");
    Asm("          sep     sret");

    /* *************************************************** */
    /* ***** Output 16-bit integer                   ***** */
    /* ***** RC - 16-bit integer                     ***** */
    /* ***** RD - Buffer for output                  ***** */
    /* *************************************************** */
    if (passNumber == 1) lblItoA = address;
    Asm("itoa:     glo     r2");
    Asm("          smi     6");
    Asm("          plo     r2");
    Asm("          ghi     r2");
    Asm("          smbi    0");
    Asm("          phi     r2");
    Asm("          glo     r2");
    Asm("          plo     rf");
    Asm("          ghi     r2");
    Asm("          phi     rf");
    Asm("          inc     rf");
    Asm("          ghi     rc");
    Asm("          shl");
    Asm("          lbnf    itoa1");
    Asm("          ldi     '-'");
    Asm("          str     rd");
    Asm("          inc     rd");
    Asm("          glo     rc");
    Asm("          xri     0ffh");
    Asm("          plo     rc");
    Asm("          ghi     rc");
    Asm("          xri     0ffh");
    Asm("          phi     rc");
    Asm("          inc     rc");
    Asm("itoa1:    sep     scall");
    Asm("          dw      tobcd");
    Asm("          glo     r2");
    Asm("          plo     rf");
    Asm("          ghi     r2");
    Asm("          phi     rf");
    Asm("          inc     rf");
    Asm("          ldi     5");
    Asm("          plo     r8");
    Asm("          ldi     4");
    Asm("          phi     r8");
    Asm("itoalp1:  lda     rf");
    Asm("          lbz     itoaz");
    Asm("          str     r2");
    Asm("          ldi     0");
    Asm("          phi     r8");
    Asm("          ldn     r2");
    Asm("itoa2:    adi     030h");
    Asm("          str     rd");
    Asm("          inc     rd");
    Asm("itoa3:    dec     r8");
    Asm("          glo     r8");
    Asm("          lbnz    itoalp1");
    Asm("          glo     r2");
    Asm("          adi     6");
    Asm("          plo     r2");
    Asm("          ghi     r2");
    Asm("          adci    0");
    Asm("          phi     r2");
    Asm("          ldi     0");
    Asm("          str     rd");
    Asm("          sep     sret");
    Asm("itoaz:    ghi     r8");
    Asm("          lbz     itoa2");
    Asm("          smi     1");
    Asm("          phi     r8");
    Asm("          lbr     itoa3");
    }


  if (useHeap) {
    /* ******************************************* */
    /* ***** Allocate memory                 ***** */
    /* ***** RC - requested size             ***** */
    /* ***** Returns: RF - Address of memory ***** */
    /* ******************************************* */
    if (passNumber == 1) lblAlloc = address;
    Asm("alloc:     ldi     [HEAP_].0           ; get heap address");
    Asm("           plo     r9");
    Asm("           ldi     [HEAP_].1");
    Asm("           phi     r9");
    Asm("           lda     r9");
    Asm("           phi     rd");
    Asm("           ldn     r9");
    Asm("           plo     rd");
    Asm("           dec     r9                  ; leave pointer at heap address");
    Asm("alloc_1:   lda     rd                  ; get flags byte");
    Asm("           lbz     alloc_new           ; need new if end of table");
    Asm("           plo     re                  ; save flags");
    Asm("           lda     rd                  ; get block size");
    Asm("           phi     rf");
    Asm("           lda     rd");
    Asm("           plo     rf");
    Asm("           glo     re                  ; is block allocated?");
    Asm("           smi     2");
    Asm("           lbz     alloc_nxt           ; jump if so");
    Asm("           glo     rc                  ; subtract size from block size");
    Asm("           str     r2");
    Asm("           glo     rf");
    Asm("           sm");
    Asm("           plo     rf");
    Asm("           ghi     rc");
    Asm("           str     r2");
    Asm("           ghi     rf");
    Asm("           smb");
    Asm("           phi     rf                  ; RF now has difference");
    Asm("           lbnf    alloc_nxt           ; jumpt if block is too small");
    Asm("           ghi     rf                  ; see if need to split block");
    Asm("           lbnz    alloc_sp            ; jump if so");
    Asm("           glo     rf                  ; get low byte of difference");
    Asm("           ani     0f8h                ; want to see if at least 8 extra bytes");
    Asm("           lbnz    alloc_sp            ; jump if so");
    Asm("alloc_2:   glo     rd                  ; set address for return");
    Asm("           plo     rf");
    Asm("           ghi     rd");
    Asm("           phi     rf");
    Asm("           dec     rd                  ; move back to flags byte");
    Asm("           dec     rd");
    Asm("           dec     rd");
    Asm("           ldi     2                   ; mark block as used");
    Asm("           str     rd");
    Asm("           sep     sret                ; and return to caller");
    Asm("alloc_sp:  ghi     rd                  ; save this address");
    Asm("           stxd");
    Asm("           glo     rd");
    Asm("           stxd");
    Asm("           dec     rd                  ; move to lsb of block size");
    Asm("           glo     rc                  ; write requested size");
    Asm("           str     rd");
    Asm("           dec     rd");
    Asm("           ghi     rc                  ; write msb of size");
    Asm("           str     rd");
    Asm("           inc     rd                  ; move back to data");
    Asm("           inc     rd");
    Asm("           glo     rc                  ; now add size");
    Asm("           str     r2");
    Asm("           glo     rd");
    Asm("           add");
    Asm("           plo     rd");
    Asm("           ghi     rd");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           adc");
    Asm("           phi     rd                  ; rd now points to new block");
    Asm("           ldi     1                   ; mark as a free block");
    Asm("           str     rd");
    Asm("           inc     rd");
    Asm("           dec     rf                  ; remove 3 bytes from block size");
    Asm("           dec     rf");
    Asm("           dec     rf");
    Asm("           ghi     rf                  ; and write into block header");
    Asm("           str     rd");
    Asm("           inc     rd");
    Asm("           glo     rf");
    Asm("           str     rd");
    Asm("           irx                         ; recover address");
    Asm("           ldxa");
    Asm("           plo     rd");
    Asm("           ldx");
    Asm("           phi     rd");
    Asm("           lbr     alloc_2             ; finish allocating");
    Asm("alloc_nxt: glo     rf                  ; add block size to address");
    Asm("           str     r2");
    Asm("           glo     rd");
    Asm("           add");
    Asm("           plo     rd");
    Asm("           ghi     rf");
    Asm("           str     r2");
    Asm("           ghi     rd");
    Asm("           adc");
    Asm("           phi     rd");
    Asm("           lbr     alloc_1             ; check next cell");
    Asm("alloc_new: lda     r9                  ; retrieve start of heap");
    Asm("           phi     rd");
    Asm("           ldn     r9");
    Asm("           plo     rd");
    Asm("           glo     rc                  ; subtract req. size from pointer");
    Asm("           str     r2");
    Asm("           glo     rd");
    Asm("           sm");
    Asm("           plo     rd");
    Asm("           ghi     rc");
    Asm("           str     r2");
    Asm("           ghi     rd");
    Asm("           smb");
    Asm("           phi     rd");
    Asm("           dec     rd                  ; point to lsb of block size");
    Asm("           glo     rc                  ; write size");
    Asm("           str     rd");
    Asm("           dec     rd");
    Asm("           ghi     rc");
    Asm("           str     rd");
    Asm("           dec     rd");
    Asm("           ldi     2                   ; mark as allocated block");
    Asm("           str     rd");
    Asm("           glo     rd                  ; set address");
    Asm("           plo     rf");
    Asm("           ghi     rd");
    Asm("           phi     rf");
    Asm("           inc     rf                  ; point to actual data space");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           glo     rd                  ; write new heap address");
    Asm("           str     r9");
    Asm("           dec     r9");
    Asm("           ghi     rd");
    Asm("           str     r9");
    Asm("           sep     scall               ; check for out of memory");
    Asm("           dw      checkeom");
    Asm("           sep     sret                ; return to caller");

    /* ************************************** */
    /* ***** Deallocate memory          ***** */
    /* ***** RF - address to deallocate ***** */
    /* ************************************** */
    if (passNumber == 1) lblDealloc = address;
    Asm("dealloc:   dec     rf                  ; move to flags byte");
    Asm("           dec     rf");
    Asm("           dec     rf");
    Asm("           ldi     1                   ; mark block as free");
    Asm("           str     rf");
    Asm("heapgc:    ghi     rc                  ; save consumed registers");
    Asm("           stxd");
    Asm("           glo     rc");
    Asm("           stxd");
    Asm("           ghi     rd");
    Asm("           stxd");
    Asm("           glo     rd");
    Asm("           stxd");
    Asm("           ldi     [HEAP_].0           ; need start of heap");
    Asm("           plo     r9");
    Asm("           ldi     [HEAP_].1");
    Asm("           phi     r9");
    Asm("           lda     r9                  ; retrieve heap start address");
    Asm("           phi     rd");
    Asm("           lda     r9");
    Asm("           plo     rd");
    Asm("heapgc_1:  lda     rd                  ; retrieve flags byte");
    Asm("           lbz     heapgc_dn           ; return if end of heap found");
    Asm("           plo     re                  ; save copy of flags");
    Asm("           lda     rd                  ; retrieve block size");
    Asm("           phi     rc");
    Asm("           lda     rd");
    Asm("           plo     rc");
    Asm("           glo     rd                  ; RF=RD+RC, point to next block");
    Asm("           str     r2");
    Asm("           glo     rc");
    Asm("           add");
    Asm("           plo     rf");
    Asm("           ghi     rd");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           adc");
    Asm("           phi     rf");
    Asm("           lda     rf                  ; retrieve flags for next block");
    Asm("           lbz     heapgc_dn           ; return if on last block");
    Asm("           smi     2                   ; is block allocated?");
    Asm("           lbz     heapgc_a            ; jump if so");
    Asm("           glo     re                  ; check flags of current block");
    Asm("           smi     2                   ; is it allocated");
    Asm("           lbz     heapgc_a            ; jump if so");
    Asm("           lda     rf                  ; retrieve next block size into RF");
    Asm("           plo     re");
    Asm("           lda     rf");
    Asm("           plo     rf");
    Asm("           glo     re");
    Asm("           phi     rf");
    Asm("           inc     rf                  ; add 3 bytes for header");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           glo     rf                  ; RC += RF, combine sizes");
    Asm("           str     r2");
    Asm("           glo     rc");
    Asm("           add");
    Asm("           plo     rc");
    Asm("           ghi     rf");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           adc");
    Asm("           phi     rc");
    Asm("           dec     rd                  ; write size of combined blocks");
    Asm("           glo     rc");
    Asm("           str     rd");
    Asm("           dec     rd");
    Asm("           ghi     rc");
    Asm("           str     rd");
    Asm("           dec     rd                  ; move back to flags byte");
    Asm("           lbr     heapgc_1            ; keep checking for merges");
    Asm("heapgc_a:  glo     rf                  ; move pointer to next block");
    Asm("           plo     rd");
    Asm("           ghi     rf");
    Asm("           phi     rd");
    Asm("           dec     rd                  ; move back to flags byte");
    Asm("           lbr     heapgc_1            ; and check next block");
    Asm("heapgc_dn: irx                         ; recover consumed registers");
    Asm("           ldxa");
    Asm("           plo     rd");
    Asm("           ldxa");
    Asm("           phi     rd");
    Asm("           ldxa");
    Asm("           plo     rc");
    Asm("           ldx");
    Asm("           phi     rc");
    Asm("           sep     sret                ; return to caller");

    /* ********************************************* */
    /* ***** Return amount of free heap memory ***** */
    /* ***** Returns: RC - free heap memory    ***** */
    /* ********************************************* */
    Asm("hfree:     ldi     0                   ; clear count");
    Asm("           plo     rc");
    Asm("           phi     rc");
    Asm("           ldi     [HEAP_].0           ; setup heap pointer");
    Asm("           plo     r9");
    Asm("           ldi     [HEAP_].1");
    Asm("           phi     r9");
    Asm("           lda     r9                  ; retrieve start of heap");
    Asm("           phi     rf");
    Asm("           ldn     r9");
    Asm("           plo     rf");
    Asm("hfree_lp:  lda     rf                  ; get heap allocation status byte");
    Asm("           lbz     hfree_dn            ; jump if end of heap");
    Asm("           plo     re                  ; save this for a moment");
    Asm("           lda     rf                  ; retrieve block size");
    Asm("           phi     rd");
    Asm("           lda     rf");
    Asm("           plo     rd");
    Asm("           str     r2                  ; add size to block address");
    Asm("           glo     rf");
    Asm("           add");
    Asm("           plo     rf");
    Asm("           ghi     rd");
    Asm("           str     r2");
    Asm("           ghi     rf");
    Asm("           adc");
    Asm("           phi     rf");
    Asm("           glo     re                  ; recover status byte");
    Asm("           smi     1                   ; is it a free block");
    Asm("           lbnz    hfree_lp            ; jump if not");
    Asm("           glo     rd                  ; add block size to count");
    Asm("           str     r2");
    Asm("           glo     rc");
    Asm("           add");
    Asm("           plo     rc");
    Asm("           ghi     rd");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           adc");
    Asm("           phi     rc");
    Asm("           lbr     hfree_lp            ; check next block");
    Asm("hfree_dn:  sep     sret                ; and return");

    /* *********************************** */
    /* ***** Check for out of memory ***** */
    /* *********************************** */
    Asm("checkeom:  ghi     rc                  ; save consumed register");
    Asm("           stxd");
    Asm("           glo     rc");
    Asm("           stxd");
    Asm("           ldi     [FREE_].0           ; get end of variable table");
    Asm("           plo     r9");
    Asm("           ldi     [FREE_].1");
    Asm("           phi     r9");
    Asm("           lda     r9                  ; retrieve variable table end");
    Asm("           phi     rc");
    Asm("           lda     r9");
    Asm("           plo     rc");
    Asm("           ldi     [HEAP_].0           ; point to heap start");
    Asm("           plo     r9");
    Asm("           ldi     [HEAP_].1");
    Asm("           phi     r9");
    Asm("           inc     r9                  ; point to lsb");
    Asm("           ldn     r9                  ; get heap");
    Asm("           str     r2");
    Asm("           glo     rc                  ; subtract from variable table end");
    Asm("           sm");
    Asm("           dec     r9                  ; point to msb");
    Asm("           ldn     r9                  ; retrieve it");
    Asm("           str     r2");
    Asm("           ghi     rc                  ; subtract from variable table end");
    Asm("           smb");
    Asm("           lbdf    oom                 ; jump of out of memory");
    Asm("           irx                         ; recover consumed register");
    Asm("           ldxa");
    Asm("           plo     rc");
    Asm("           ldx");
    Asm("           phi     rc");
    Asm("           sep     sret                ; and return to caller");
    Asm("oom:       sep     scall               ; display out of memory error");
    Asm("           dw      f_inmsg");
    Asm("           db      'Out of memory: ',0");
    Asm("           lbr     $                   ; show line of error and exit");
    }

  if (useAdd32) {
    /* ************************************************ */
    /* ***** 32-bit Add.    M[RF]=M[RF]+M[RD]     ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("add32i:  sex      rd                ; point x to second number");
    Asm("         ldn      rf                ; get lsb");
    Asm("         add                        ; add second lsb of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to 2nd byte");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get second byte");
    Asm("         adc                        ; add second byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to 3rd byte");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get third byte");
    Asm("         adc                        ; add third byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to msb");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get msb byte");
    Asm("         adc                        ; add msb byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         sex      r2                ; restore stack");
    Asm("         dec      rf                ; restore registers to original values");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         sep      sret              ; return to caller");

    Asm("add32:   glo      r7                ; setup pointers");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7                ; setup pointers");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sep      scall             ; Perform addition");
    Asm("         dw       add32i");
    Asm("         inc      r7                ; Remove 2nd number from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useSub32) {
    /* ************************************************ */
    /* ***** 32-bit subtract.  M[RF]=M[RF]-M[RD]  ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("sub32i:  sex      rd                ; point x to second number");
    Asm("         ldn      rf                ; get lsb");
    Asm("         sm                         ; subtract second lsb of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to 2nd byte");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get second byte");
    Asm("         smb                        ; subtract second byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to 3rd byte");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get third byte");
    Asm("         smb                        ; subtract third byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         inc      rf                ; point to msb");
    Asm("         inc      rd");
    Asm("         ldn      rf                ; get msb byte");
    Asm("         smb                        ; subtract msb byte of second number");
    Asm("         str      rf                ; store it");
    Asm("         sex      r2                ; restore stack");
    Asm("         dec      rf                ; restore registers to original values");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         sep      sret              ; return to caller");

    Asm("sub32:   glo      r7                ; setup pointers");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7                ; setup pointers");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sep      scall             ; Perform subtraction");
    Asm("         dw       sub32i");
    Asm("         inc      r7                ; Remove 2nd number from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useMul32) {
    /* ************************************************ */
    /* ***** 32-bit multiply. M[RF]=M[RF]*M[RD]   ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ***** In routine:                          ***** */
    /* *****    R9 - points to first number       ***** */
    /* *****    RD - points to second number      ***** */
    /* *****    RF - points to answer             ***** */
    /* ************************************************ */
    Asm("mul32i:  ldi      0                 ; need to zero answer");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         glo      rf                ; r9 will point to first number");
    Asm("         plo      r9");
    Asm("         ghi      rf");
    Asm("         phi      r9");
    Asm("         glo      r2                ; rf will point to where the answer is");
    Asm("         plo      rf");
    Asm("         ghi      r2");
    Asm("         phi      rf");
    Asm("         inc      rf                ; point to LSB of answer");
    Asm("scmul2:  glo      rd                ; need second number");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall             ; check for zero");
    Asm("         dw       zero32");
    Asm("         lbnf     scmul4            ; jump if number was not zero");
    Asm("         inc      r2                ; now pointing at lsb of answer");
    Asm("         lda      r2                ; get number from stack");
    Asm("         str      r9                ; store into destination");
    Asm("         inc      r9                ; point to 2nd byte");
    Asm("         lda      r2                ; get number from stack");
    Asm("         str      r9                ; store into destination");
    Asm("         inc      r9                ; point to 3rd byte");
    Asm("         lda      r2                ; get number from stack");
    Asm("         str      r9                ; store into destination");
    Asm("         inc      r9                ; point to msb");
    Asm("         ldn      r2                ; get number from stack");
    Asm("         str      r9                ; store into destination");
    Asm("         sep      sret              ; return to caller");
    Asm("scmul4:  ldn      rd                ; get lsb of second number");
    Asm("         shr                        ; shift low bit into df");
    Asm("         lbnf     scmulno           ; no add needed");
    Asm("         ghi      rd                ; save position of second number");
    Asm("         stxd");
    Asm("         glo      rd");
    Asm("         stxd");
    Asm("         glo      r9                ; rd needs to be first number");
    Asm("         plo      rd");
    Asm("         ghi      r9");
    Asm("         phi      rd");
    Asm("         sep      scall             ; call add routine");
    Asm("         dw       add32i");
    Asm("         irx                        ; recover rd");
    Asm("         ldxa");
    Asm("         plo      rd");
    Asm("         ldx");
    Asm("         phi      rd");
    Asm("scmulno: glo      r9                ; point to first number");
    Asm("         plo      ra");
    Asm("         ghi      r9");
    Asm("         phi      ra");
    Asm("         sep      scall             ; shift left");
    Asm("         dw       shl32");
    Asm("         glo      rd                ; now need pointer to second number");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall             ; shift right");
    Asm("         dw       shr32");
    Asm("         lbr      scmul2            ; loop until done");

    Asm("mul32:   glo      r7                ; setup pointers");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7                ; setup pointers");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sep      scall             ; Perform multiply");
    Asm("         dw       mul32i");
    Asm("         inc      r7                ; Remove 2nd number from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useDiv32) {
    /* ************************************************ */
    /* ***** 32-bit division. M[RF]=M[RF]/M[RD]   ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ***** In routine:                          ***** */
    /* *****    RF=a                              ***** */
    /* *****    RD=b                              ***** */
    /* *****    RC=result                         ***** */
    /* *****    RB=shift                          ***** */
    /* ************************************************ */
    Asm("div32i:  ldi      0                 ; set sign flag as positive");
    Asm("         str      r2                ; place on the stack");
    Asm("         inc      rf                ; point to msb of first number");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         ldn      rf                ; retrieve it");
    Asm("         dec      rf                ; restore position");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         ani      080h              ; is number negative");
    Asm("         lbz      div32_1           ; jump if not");
    Asm("         ldi      1                 ; set sign flag");
    Asm("         xor");
    Asm("         stxd                       ; save flag");
    Asm("         glo      rf                ; 2s compliment number");
    Asm("         plo      ra");
    Asm("         ghi      rf");
    Asm("         phi      ra");
    Asm("         sep      scall");
    Asm("         dw       neg32");
    Asm("         irx                        ; point back to sign flag");
    Asm("div32_1: inc      rd                ; point to msb of second number");
    Asm("         inc      rd");
    Asm("         inc      rd");
    Asm("         ldn      rd                ; retrieve it");
    Asm("         dec      rd                ; restore position");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         ani      080h              ; is number negative");
    Asm("         lbz      div32_2           ; jump if not");
    Asm("         ldi      1                 ; adjust sign flag");
    Asm("         xor");
    Asm("         stxd                       ; save sign flag");
    Asm("         glo      rd                ; 2s compliment second number");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall");
    Asm("         dw       neg32");
    Asm("         irx");
    Asm("div32_2: dec      r2                ; preserve sign flag");
    Asm("         ldi      0                 ; zero answer on stack");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         stxd");
    Asm("         glo      r2                ; set RC here");
    Asm("         plo      rc");
    Asm("         ghi      r2");
    Asm("         phi      rc");
    Asm("         inc      rc                ; point rc to lsb of answer");
    Asm("         ldi      1                 ; set shift to 1");
    Asm("         plo      rb");
    Asm("scdiv1:  sep      scall             ; compare a to b");
    Asm("         dw       icomp32");
    Asm("         lbnf     scdiv4            ; jump if b>=a");
    Asm("         glo      rd                ; need to shift b");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall");
    Asm("         dw       shl32");
    Asm("         inc      rb                ; increment shift");
    Asm("         lbr      scdiv1            ; loop until b>=a");
    Asm("scdiv4:  glo      rf                ; point to a");
    Asm("         plo      ra");
    Asm("         ghi      rf");
    Asm("         phi      ra");
    Asm("         sep      scall             ; is a zero");
    Asm("         dw       zero32");
    Asm("         lbdf     scdivd1           ; jump if it was zero");
    Asm("         glo      rd                ; point to b");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall             ; is b zero");
    Asm("         dw       zero32");
    Asm("         lbdf     scdivd1           ; jump if so");
    Asm("         glo      rc                ; point to result");
    Asm("         plo      ra");
    Asm("         ghi      rc");
    Asm("         phi      ra");
    Asm("         sep      scall             ; need to shift result left");
    Asm("         dw       shl32");
    Asm("         sep      scall             ; compare a to b");
    Asm("         dw       comp32");
    Asm("         lbdf     scdiv6            ; jump if a < b");
    Asm("         ldn      rc                ; get LSB of result");
    Asm("         ori      1                 ; set low bit");
    Asm("         str      rc                ; and but it back");
    Asm("         sep      scall             ; subtrcct a from b");
    Asm("         dw       sub32i");
    Asm("scdiv6:  ldn      rd                ; get lsb of b");
    Asm("         shr                        ; see if low bit is set");
    Asm("         lbnf     scdiv5            ; jump if not");
    Asm("         dec      rb                ; mark final shift");
    Asm("         lbr      scdivd1           ; and then done");
    Asm("scdiv5:  glo      rd                ; point to b");
    Asm("         plo      ra");
    Asm("         ghi      rd");
    Asm("         phi      ra");
    Asm("         sep      scall             ; need to shift b right");
    Asm("         dw       shr32");
    Asm("         dec      rb                ; decrement shift");
    Asm("         glo      rb                ; see if run out of shifts");
    Asm("         lbz      scdivd1           ; done if so");
    Asm("         lbr      scdiv4            ; loop back until done");
    Asm("scdivd1: glo      rb                ; get shift");
    Asm("         shl                        ; shift sign into df");
    Asm("         lbdf     scdivd2           ; jump if so");
    Asm("scdivd3: glo      rb                ; get shift");
    Asm("         lbz      scdivdn           ; jump if zero");
    Asm("         glo      rc                ; point to result");
    Asm("         plo      ra");
    Asm("         ghi      rc");
    Asm("         phi      ra");
    Asm("         sep      scall             ; shift it left");
    Asm("         dw       shl32");
    Asm("         dec      rb                ; decrement shift");
    Asm("         lbr      scdivd3           ; loop back");
    Asm("scdivd2: glo      rb                ; get shift");
    Asm("         lbz      scdivdn           ; jump if zero");
    Asm("         glo      rc                ; point to result");
    Asm("         plo      ra");
    Asm("         ghi      rc");
    Asm("         phi      ra");
    Asm("         sep      scall             ; shift it right");
    Asm("         dw       shr32");
    Asm("         inc      rb                ; increment shift");
    Asm("         lbr      scdivd2");
    Asm("scdivdn: lda      rf                ; recover remainder");
    Asm("         plo      rb");
    Asm("         lda      rf");
    Asm("         phi      rb");
    Asm("         lda      rf                ; recover remainder");
    Asm("         plo      ra");
    Asm("         ldn      rf");
    Asm("         phi      ra");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         ldi      4                 ; 4 bytes to trcnsfer");
    Asm("         plo      r9");
    Asm("scdivd5: lda      rc                ; get result byte");
    Asm("         str      rf                ; store into answer");
    Asm("         inc      rf");
    Asm("         dec      r9                ; decrement count");
    Asm("         glo      r9                ; see if done");
    Asm("         lbnz     scdivd5           ; jump if not");
    Asm("         dec      rf                ; recover answer");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         glo      rc                ; need to clean up the stack");
    Asm("         plo      r2");
    Asm("         ghi      rc");
    Asm("         phi      r2");
    Asm("         ldn      r2                ; retrieve sign");
    Asm("         shr                        ; shift into df");
    Asm("         lbnf     scdivrt           ; jump if signs were the same");
    Asm("         glo      rf                ; otherwise negate number");
    Asm("         plo      ra");
    Asm("         ghi      rf");
    Asm("         phi      ra");
    Asm("         sep      scall");
    Asm("         dw       neg32");
    Asm("scdivrt: sep      sret              ; return to caller");

    Asm("div32:   glo      r7                ; setup pointers");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7                ; setup pointers");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sep      scall             ; Perform division");
    Asm("         dw       div32i");
    Asm("         inc      r7                ; Remove 2nd number from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useMod32) {
    Asm("mod32:      sep     scall");
    Asm("            dw      div32");
    Asm("            inc     r7");
    Asm("            inc     r7");
    Asm("            inc     r7");
    Asm("            inc     r7");
    Asm("            ghi     ra");
    Asm("            str     r7");
    Asm("            dec     r7");
    Asm("            glo     ra");
    Asm("            str     r7");
    Asm("            dec     r7");
    Asm("            ghi     rb");
    Asm("            str     r7");
    Asm("            dec     r7");
    Asm("            glo     rb");
    Asm("            str     r7");
    Asm("            dec     r7");
    Asm("            sep     sret");
    }

  if (useRnd32) {
    Asm("rnd32:    ldi     32");
    Asm("          plo     rc");
    Asm("          sep     scall         ; Shift the register");
    Asm("          dw      lfsr_lp");
    Asm("          ldi     [LFSR_].1");
    Asm("          phi     r9");
    Asm("          ldi     [LFSR_].0");
    Asm("          plo     r9");

    Asm("          inc     r7            ; Retrieve range");
    Asm("          lda     r7");
    Asm("          plo     rb");
    Asm("          lda     r7");
    Asm("          phi     rb");
    Asm("          lda     r7");
    Asm("          plo     ra");
    Asm("          ldn     r7");
    Asm("          phi     ra");
    
    Asm("          lda     r9            ; Transfer random number");
    Asm("          ani     07fh          ; no negative numbers");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          lda     r9");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          lda     r9");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          lda     r9");
    Asm("          str     r7");
    Asm("          dec     r7");
    
    Asm("          ghi     ra            ; Put range on expr stack");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          glo     ra");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          ghi     rb");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          glo     rb");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          lbr     mod32          ; and perform modulo");
    }

  if (useComp32) {
    /* ************************************************ */
    /* ***** 32-bit cmp.  M[RF]-M[RD]             ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ***** Returns: D=0 if M[RF]=M[RD]          ***** */
    /* *****          DF=1 if M[RF]<M[RD]         ***** */
    /* ************************************************ */
    Asm("comp32:  lda      rd                ; get lsb from second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get lsb from first number");
    Asm("         sm                         ; subtract");
    Asm("         plo      re                ; save as zero test");
    Asm("         lda      rd                ; get 2nd byte of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get 2nd byte of first number");
    Asm("         smb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         plo      re                ; and put back");
    Asm("         lda      rd                ; get 3rd byte of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get 3rd byte of first number");
    Asm("         smb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         plo      re                ; and put back");
    Asm("         ldn      rd                ; get msb of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         ldn      rf                ; get msb of first number");
    Asm("         smb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         shl                        ; shift sign bit into df");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         dec      rf                ; restore registers");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         sep      sret              ; return to caller");
    }

  if (useIComp32) {
    /* ************************************************ */
    /* ***** 32-bit cmp.  M[RD]-M[RF]             ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ***** Returns: D=0 if M[RD]=M[RF]          ***** */
    /* *****          DF=1 if M[RD]<M[RF]         ***** */
    /* ************************************************ */
    Asm("icomp32: lda      rd                ; get lsb from second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get lsb from first number");
    Asm("         sd                         ; subtract");
    Asm("         plo      re                ; save as zero test");
    Asm("         lda      rd                ; get 2nd byte of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get 2nd byte of first number");
    Asm("         sdb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         plo      re                ; and put back");
    Asm("         lda      rd                ; get 3rd byte of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         lda      rf                ; get 3rd byte of first number");
    Asm("         sdb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         plo      re                ; and put back");
    Asm("         ldn      rd                ; get msb of second number");
    Asm("         str      r2                ; store for subtract");
    Asm("         ldn      rf                ; get msb of first number");
    Asm("         sdb                        ; perform subtraction");
    Asm("         str      r2                ; store for combining with zero test");
    Asm("         shl                        ; shift sign bit into df");
    Asm("         glo      re                ; get zero test");
    Asm("         or                         ; or last result");
    Asm("         dec      rf                ; restore registers");
    Asm("         dec      rf");
    Asm("         dec      rf");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         dec      rd");
    Asm("         sep      sret              ; return to caller");
    }

  if (useNull32) {
    /* *************************************** */
    /* ***** M[RA] = 0                   ***** */
    /* *************************************** */
    Asm("null32:  ldi      0                 ; need to zero");
    Asm("         str      rA                ; store to lsb");
    Asm("         inc      rA                ; point to second byte");
    Asm("         str      rA                ; store to second byte");
    Asm("         inc      rA                ; point to third byte");
    Asm("         str      rA                ; store to third byte");
    Asm("         inc      rA                ; point to msb");
    Asm("         str      rA                ; store to msb");
    Asm("         dec      rA                ; restore rf");
    Asm("         dec      rA");
    Asm("         dec      rA");
    Asm("         sep      sret              ; return to caller");
    }

  if (useNeg32) {
    /* ********************************************* */
    /* ***** 2s compliment the number in M[RA] ***** */
    /* ********************************************* */
    Asm("neg32:   ldn      ra                ; get lsb");
    Asm("         xri      0ffh              ; invert it");
    Asm("         adi      1                 ; +1");
    Asm("         str      ra");
    Asm("         inc      ra                ; point to 2nd byte");
    Asm("         ldn      ra                ; retrieve it");
    Asm("         xri      0ffh              ; invert it");
    Asm("         adci     0                 ; propagate carry");
    Asm("         str      ra                ; and put back");
    Asm("         inc      ra                ; point to 3rd byte");
    Asm("         ldn      ra                ; retrieve it");
    Asm("         xri      0ffh              ; invert it");
    Asm("         adci     0                 ; propagate carry");
    Asm("         str      ra                ; and put back");
    Asm("         inc      ra                ; point to msb");
    Asm("         ldn      ra                ; retrieve it");
    Asm("         xri      0ffh              ; invert it");
    Asm("         adci     0                 ; propagate carry");
    Asm("         str      ra                ; and put back");
    Asm("         dec      ra                ; restore rf");
    Asm("         dec      ra");
    Asm("         dec      ra");
    Asm("         sep      sret              ; return");
    }

  if (useShl32) {
    /* ************************************************ */
    /* ***** 32-bit shift left.  M[RA]=M[RA]<<1   ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("shl32:   ldn      ra                ; get lsb");
    Asm("         shl                        ; shift it");
    Asm("         str      ra                ; put it back");
    Asm("         inc      ra                ; point to second byte");
    Asm("         ldn      ra                ; get it");
    Asm("         shlc                       ; shift it");
    Asm("         str      ra");
    Asm("         inc      ra                ; point to third byte");
    Asm("         ldn      ra                ; get it");
    Asm("         shlc                       ; shift it");
    Asm("         str      ra");
    Asm("         inc      ra                ; point to msb");
    Asm("         ldn      ra                ; get it");
    Asm("         shlc                       ; shift it");
    Asm("         str      ra");
    Asm("         dec      ra                ; restore rf");
    Asm("         dec      ra");
    Asm("         dec      ra");
    Asm("         sep      sret              ; and return");
    }

  if (useShr32) {
    /* ************************************************ */
    /* ***** 32-bit shift right. M[RA]=M[RA]>>1   ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("shr32:   inc      ra                ; point to msb");
    Asm("         inc      ra");
    Asm("         inc      ra");
    Asm("         ldn      ra                ; get msb");
    Asm("         shr                        ; shift it right");
    Asm("         str      ra                ; put it back");
    Asm("         dec      ra                ; point to third byte");
    Asm("         ldn      ra                ; get third byte");
    Asm("         shrc                       ; shift it");
    Asm("         str      ra                ; put it back");
    Asm("         dec      ra                ; point to second byte");
    Asm("         ldn      ra                ; get second byte");
    Asm("         shrc                       ; shift it");
    Asm("         str      ra                ; put it back");
    Asm("         dec      ra                ; point to lsb");
    Asm("         ldn      ra                ; get lsb");
    Asm("         shrc                       ; shift it");
    Asm("         str      ra                ; put it back");
    Asm("         sep      sret              ; return to caller");
    }

  if (useZero32) {
/* *************************************** */
/* ***** is zero check               ***** */
/* ***** returnss: DF=1 if M[RA]=0   ***** */
/* *************************************** */
    Asm("zero32:  sex      ra                ; point X to number");
    Asm("         ldxa                       ; get byte 0");
    Asm("         or                         ; combine with byte 1");
    Asm("         irx                        ; point to byte 2");
    Asm("         or                         ; combine");
    Asm("         irx                        ; point to byte 3");
    Asm("         or                         ; combine");
    Asm("         dec      ra                ; restore rf");
    Asm("         dec      ra");
    Asm("         dec      ra");
    Asm("         sex      r2                ; X back to 2");
    Asm("         lbnz     notzero           ; jump if not zero");
    Asm("         smi      0                 ; set df");
    Asm("         sep      sret              ; and return");
    Asm("notzero: adi      0                 ; clear df");
    Asm("         sep      sret              ; and return");
    }


  if (useAnd32) {
    /* ************************************************ */
    /* ***** 32-bit And expr stack                ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("and32:   inc      r7                ; point to second number");
    Asm("         glo      r7                ; copy address to rf");
    Asm("         plo      rf");
    Asm("         ghi      r7");
    Asm("         phi      rf");
    Asm("         inc      rf                ; point rf to first number");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sex      rf                ; point X to destination");
    Asm("         lda      r7                ; get byte 1");
    Asm("         and                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 2");
    Asm("         lda      r7                ; get byte 2");
    Asm("         and                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 3");
    Asm("         lda      r7                ; get byte 3");
    Asm("         and                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 4");
    Asm("         ldn      r7                ; get byte 7");
    Asm("         and                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         sex      r2                ; Set x back to R2");
    Asm("         sep      sret              ; return to caller");
    }

  if (useOr32) {
    /* ************************************************ */
    /* ***** 32-bit Or.  expr stack               ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("or32:    inc      r7                ; point to second number");
    Asm("         glo      r7                ; copy address to rf");
    Asm("         plo      rf");
    Asm("         ghi      r7");
    Asm("         phi      rf");
    Asm("         inc      rf                ; point rf to first number");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sex      rf                ; point X to destination");
    Asm("         lda      r7                ; get byte 1");
    Asm("         or                         ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 2");
    Asm("         lda      r7                ; get byte 2");
    Asm("         or                         ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 3");
    Asm("         lda      r7                ; get byte 3");
    Asm("         or                         ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 4");
    Asm("         ldn      r7                ; get byte 7");
    Asm("         or                         ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         sex      r2                ; Set x back to R2");
    Asm("         sep      sret              ; return to caller");
    }

  if (useXor32) {
    /* ************************************************ */
    /* ***** 32-bit Xor. expr stack               ***** */
    /* ***** Numbers in memory stored LSB first   ***** */
    /* ************************************************ */
    Asm("xor32:   inc      r7                ; point to second number");
    Asm("         glo      r7                ; copy address to rf");
    Asm("         plo      rf");
    Asm("         ghi      r7");
    Asm("         phi      rf");
    Asm("         inc      rf                ; point rf to first number");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         inc      rf");
    Asm("         sex      rf                ; point X to destination");
    Asm("         lda      r7                ; get byte 1");
    Asm("         xor                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 2");
    Asm("         lda      r7                ; get byte 2");
    Asm("         xor                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 3");
    Asm("         lda      r7                ; get byte 3");
    Asm("         xor                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         inc      rf                ; point to byte 4");
    Asm("         ldn      r7                ; get byte 7");
    Asm("         xor                        ; and with first number");
    Asm("         str      rf                ; store");
    Asm("         sex      r2                ; Set x back to R2");
    Asm("         sep      sret              ; return to caller");
    }

  if (useCmp32) {
    Asm("true32:     ldi     0ffh");
    Asm("            sex     r7");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");

    Asm("false32:    ldi     000h");
    Asm("            sex     r7");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            stxd");
    Asm("            sex     r2");
    Asm("            sep     sret");

    Asm("cmp32:   glo      r7                ; copy expr stack to rd");
    Asm("         plo      rd");
    Asm("         plo      rf");
    Asm("         ghi      r7");
    Asm("         phi      rd");
    Asm("         phi      rf");
    Asm("         inc      rd                ; point to lsb of second number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         inc      rf                ; point to lsb of first number");
    Asm("         sep      scall             ; compare numbers");
    Asm("         dw       comp32");
    Asm("         inc      r7                ; Remove numbers from stack");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         inc      r7");
    Asm("         sep      sret              ; Return to caller");
    }

  if (useEq32) {
    Asm("eq32:    sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbnz     false32           ; fails if numbers were unequal");
    Asm("         lbr      true32            ; true if A=B");
    }

  if (useNe32) {
    Asm("ne32:    sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      false32           ; fails if numbers were equal");
    Asm("         lbr      true32            ; true if A<>B");
    }

  if (useLt32) {
    Asm("lt32:    sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      false32           ; fails if numbers were equal");
    Asm("         lbdf     true32            ; true if A<B");
    Asm("         lbr      false32           ; otherwise false");
    }

  if (useGt32) {
    Asm("gt32:    sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      false32           ; fails if numbers were equal");
    Asm("         lbnf     true32            ; true if A>B");
    Asm("         lbr      false32           ; otherwise false");
    }

  if (useLte32) {
    Asm("lte32:   sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      true32            ; true if numbers were equal");
    Asm("         lbdf     true32            ; true if A<B");
    Asm("         lbr      false32           ; otherwise false");
    }

  if (useGte32) {
    Asm("gte32:   sep      scall             ; compare numbers");
    Asm("         dw       cmp32");
    Asm("         lbz      true32            ; true if numbers were equal");
    Asm("         lbnf     true32            ; true if A>B");
    Asm("         lbr      false32           ; otherwise false");
    }

  if (useAbs32) {
    if (passNumber == 1) lblAbs = address;
    Asm("abs32:    inc     r7");
    Asm("          inc     r7");
    Asm("          inc     r7");
    Asm("          inc     r7");
    Asm("          ldn     r7");
    Asm("          shl");
    Asm("          lbnf    absrt32");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          ldn     r7");
    Asm("          xri     0ffh");
    Asm("          adi     1");
    Asm("          str     r7");
    Asm("          inc     r7");
    Asm("          ldn     r7");
    Asm("          xri     0ffh");
    Asm("          adci    0");
    Asm("          str     r7");
    Asm("          inc     r7");
    Asm("          ldn     r7");
    Asm("          xri     0ffh");
    Asm("          adci    0");
    Asm("          str     r7");
    Asm("          inc     r7");
    Asm("          ldn     r7");
    Asm("          xri     0ffh");
    Asm("          adci    0");
    Asm("          str     r7");
    Asm("absrt32:  dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    }

  if (useSgn32) {
    Asm("sgn32:    inc     r7");
    Asm("          lda     r7");
    Asm("          str     r2");
    Asm("          lda     r7");
    Asm("          or");
    Asm("          str     r2");
    Asm("          lda     r7");
    Asm("          or");
    Asm("          str     r2");
    Asm("          ldn     r7");
    Asm("          shl");
    Asm("          lbdf    sgnm32");
    Asm("          ldn     r7");
    Asm("          or");
    Asm("          lbz     sgn032");
    Asm("          ldi     0");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          ldi     1");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgnm32:   ldi     0ffh");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgn032:   dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    }

  if (useItoA32) {
    /* ***************************************** */
    /* ***** Convert RA:RB to bcd in M[RF] ***** */
    /* ***************************************** */
    Asm("tobcd32:     glo     rf           ; transfer address to rc");
    Asm("             plo     rc");
    Asm("             ghi     rf");
    Asm("             phi     rc");
    Asm("             ldi     10           ; 10 bytes to clear");
    Asm("             plo     re");
    Asm("tobcd32lp1:  ldi     0");
    Asm("             str     rc           ; store into answer");
    Asm("             inc     rc");
    Asm("             dec     re           ; decrement count");
    Asm("             glo     re           ; get count");
    Asm("             lbnz    tobcd32lp1   ; loop until done");
    Asm("             glo     rf           ; recover address");
    Asm("             plo     rc");
    Asm("             ghi     rf");
    Asm("             phi     rc");
    Asm("             ldi     32           ; 32 bits to process");
    Asm("             plo     r9");
    Asm("tobcd32lp2:  ldi     10           ; need to process 5 cells");
    Asm("             plo     re           ; put into count");
    Asm("tobcd32lp3:  ldn     rc           ; get byte");
    Asm("             smi     5            ; need to see if 5 or greater");
    Asm("             lbnf    tobcd32lp3a  ; jump if not");
    Asm("             adi     8            ; add 3 to original number");
    Asm("             str     rc           ; and put it back");
    Asm("tobcd32lp3a: inc     rc           ; point to next cell");
    Asm("             dec     re           ; decrement cell count");
    Asm("             glo     re           ; retrieve count");
    Asm("             lbnz    tobcd32lp3   ; loop back if not done");
    Asm("             glo     rb           ; start by shifting number to convert");
    Asm("             shl");
    Asm("             plo     rb");
    Asm("             ghi     rb");
    Asm("             shlc");
    Asm("             phi     rb");
    Asm("             glo     ra");
    Asm("             shlc");
    Asm("             plo     ra");
    Asm("             ghi     ra");
    Asm("             shlc");
    Asm("             phi     ra");
    Asm("             shlc                 ; now shift result to bit 3");
    Asm("             shl");
    Asm("             shl");
    Asm("             shl");
    Asm("             str     rc");
    Asm("             glo     rf           ; recover address");
    Asm("             plo     rc");
    Asm("             ghi     rf");
    Asm("             phi     rc");
    Asm("             ldi     10           ; 10 cells to process");
    Asm("             plo     re");
    Asm("tobcd32lp4:  lda     rc           ; get current cell");
    Asm("             str     r2           ; save it");
    Asm("             ldn     rc           ; get next cell");
    Asm("             shr                  ; shift bit 3 into df");
    Asm("             shr");
    Asm("             shr");
    Asm("             shr");
    Asm("             ldn     r2           ; recover value for current cell");
    Asm("             shlc                 ; shift with new bit");
    Asm("             ani     0fh          ; keep only bottom 4 bits");
    Asm("             dec     rc           ; point back");
    Asm("             str     rc           ; store value");
    Asm("             inc     rc           ; and move to next cell");
    Asm("             dec     re           ; decrement count");
    Asm("             glo     re           ; see if done");
    Asm("             lbnz    tobcd32lp4   ; jump if not");
    Asm("             glo     rf           ; recover address");
    Asm("             plo     rc");
    Asm("             ghi     rf");
    Asm("             phi     rc");
    Asm("             dec     r9           ; decrement bit count");
    Asm("             glo     r9           ; see if done");
    Asm("             lbnz    tobcd32lp2   ; loop until done");
    Asm("             sep     sret         ; return to caller");

    /* *************************************************** */
    /* ***** Convert 32-bit binary to ASCII          ***** */
    /* ***** RF - Pointer to 32-bit integer          ***** */
    /* ***** RD - destination buffer                 ***** */
    /* *************************************************** */
    Asm("itoa32:    lda     rf           ; retrieve number into R7:R8");
    Asm("           plo     rb");
    Asm("           lda     rf");
    Asm("           phi     rb");
    Asm("           lda     rf");
    Asm("           plo     ra");
    Asm("           lda     rf");
    Asm("           phi     ra");
    Asm("           glo     r2           ; make room on stack for buffer");
    Asm("           smi     11");
    Asm("           plo     r2");
    Asm("           ghi     r2");
    Asm("           smbi    0");
    Asm("           phi     r2");
    Asm("           glo     r2           ; RF is output buffer");
    Asm("           plo     rf");
    Asm("           ghi     r2");
    Asm("           phi     rf");
    Asm("           inc     rf");
    Asm("           ghi     ra           ; get high byte");
    Asm("           shl                  ; shift bit to DF");
    Asm("           lbdf    itoa32n      ; negative number");
    Asm("itoa321:   sep     scall        ; convert to bcd");
    Asm("           dw      tobcd32");
    Asm("           glo     r2");
    Asm("           plo     rf");
    Asm("           ghi     r2");
    Asm("           phi     rf");
    Asm("           inc     rf");
    Asm("           ldi     10");
    Asm("           plo     rb");
    Asm("           ldi     9            ; max 9 leading zeros");
    Asm("           phi     rb");
    Asm("loop1:     lda     rf");
    Asm("           lbz     itoa32z      ; check leading zeros");
    Asm("           str     r2           ; save for a moment");
    Asm("           ldi     0            ; signal no more leading zeros");
    Asm("           phi     rb");
    Asm("           ldn     r2           ; recover character");
    Asm("itoa322:   adi     030h");
    Asm("           str     rd           ; store into output buffer");
    Asm("           inc     rd");
    Asm("itoa323:   dec     rb");
    Asm("           glo     rb");
    Asm("           lbnz    loop1");
    Asm("           glo     r2           ; pop work buffer off stack");
    Asm("           adi     11");
    Asm("           plo     r2");
    Asm("           ghi     r2");
    Asm("           adci    0");
    Asm("           phi     r2");
    Asm("           ldi     0            ; place terminator in destination");
    Asm("           str     rd");
    Asm("           sep     sret         ; return to caller");
    Asm("itoa32z:   ghi     rb           ; see if leading have been used up");
    Asm("           lbz     itoa322      ; jump if so");
    Asm("           smi     1            ; decrement count");
    Asm("           phi     rb");
    Asm("           lbr     itoa323      ; and loop for next character");
    Asm("itoa32n:   ldi     '-'          ; show negative");
    Asm("           str     rd           ; write to destination buffer");
    Asm("           inc     rd");
    Asm("           glo     rb           ; 2s compliment");
    Asm("           xri     0ffh");
    Asm("           adi     1");
    Asm("           plo     rb");
    Asm("           ghi     rb");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           phi     rb");
    Asm("           glo     ra");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           plo     ra");
    Asm("           ghi     ra");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           phi     ra");
    Asm("           lbr     itoa321        ; now convert/show number");
    }

  if (useAtoI32) {
    /* **************************************************** */
    /* ***** Convert ascii to int32                   ***** */
    /* ***** RF - buffer to ascii                     ***** */
    /* ***** RD - destinatin int32                    ***** */
    /* ***** Returns R8:R9 result                     ***** */
    /* *****         RF - First non-numeric character ***** */
    /* **************************************************** */
    Asm("atoi32:     ldi     0            ; zero result");
    Asm("            phi     r8");
    Asm("            plo     r8");
    Asm("            phi     r9");
    Asm("            plo     r9");
    Asm("            stxd                 ; store sign on stack");
    Asm("            ldn     rf           ; get byte from input");
    Asm("            smi     '-'          ; check for negative number");
    Asm("            lbnz    atoi32_lp    ; jump if not a negative number");
    Asm("            ldi     1            ; replace sign");
    Asm("            irx");
    Asm("            stxd");
    Asm("            inc     rf           ; move past sign");
    Asm("atoi32_lp:  ldn     rf           ; get byte from input");
    Asm("            smi     '0'          ; see if below digits");
    Asm("            lbnf    atoi32_dn    ; jump if not valid digit");
    Asm("            smi     10           ; check for high of range");
    Asm("            lbdf    atoi32_dn    ; jump if not valid digit");
    Asm("            glo     r9           ; multiply answer by 2");
    Asm("            shl");
    Asm("            plo     r9");
    Asm("            plo     rb           ; put a copy in RA:RB as well");
    Asm("            ghi     r9");
    Asm("            shlc");
    Asm("            phi     r9");
    Asm("            phi     rb");
    Asm("            glo     r8");
    Asm("            shlc");
    Asm("            plo     r8");
    Asm("            plo     ra");
    Asm("            ghi     r8");
    Asm("            shlc");
    Asm("            phi     r8");
    Asm("            phi     ra");
    Asm("            ldi     2            ; want to shift RA:RB twice");
    Asm("            plo     re");
    Asm("atoi32_1:   glo     rb           ; now shift RA:RB");
    Asm("            shl");
    Asm("            plo     rb");
    Asm("            ghi     rb");
    Asm("            shlc");
    Asm("            phi     rb");
    Asm("            glo     ra");
    Asm("            shlc");
    Asm("            plo     ra");
    Asm("            ghi     ra");
    Asm("            shlc");
    Asm("            phi     ra");
    Asm("            dec     re           ; decrement shift count");
    Asm("            glo     re           ; see if done");
    Asm("            lbnz    atoi32_1     ; shift again if not");
    Asm("            glo     rb           ; now add RA:RB to R8:R9");
    Asm("            str     r2");
    Asm("            glo     r9");
    Asm("            add");
    Asm("            plo     r9");
    Asm("            ghi     rb");
    Asm("            str     r2");
    Asm("            ghi     r9");
    Asm("            adc");
    Asm("            phi     r9");
    Asm("            glo     ra");
    Asm("            str     r2");
    Asm("            glo     r8");
    Asm("            adc");
    Asm("            plo     r8");
    Asm("            ghi     ra");
    Asm("            str     r2");
    Asm("            ghi     ra");
    Asm("            str     r2");
    Asm("            ghi     r8");
    Asm("            adc");
    Asm("            phi     r8");
    Asm("            lda     rf           ; get byte from input");
    Asm("            smi     '0'          ; conver to binary");
    Asm("            str     r2           ; and add it to R8:R9");
    Asm("            glo     r9");
    Asm("            add");
    Asm("            plo     r9");
    Asm("            ghi     r9");
    Asm("            adci    0");
    Asm("            phi     r9");
    Asm("            glo     r8");
    Asm("            adci    0");
    Asm("            plo     r8");
    Asm("            ghi     r8");
    Asm("            adci    0");
    Asm("            phi     r8");
    Asm("            lbr     atoi32_lp    ; loop back for more characters");
    Asm("atoi32_dn:  irx                  ; recover sign");
    Asm("            ldx");
    Asm("            shr                  ; shift into DF");
    Asm("            lbnf    atoi32_dn2   ; jump if not negative");
    Asm("            glo     r9           ; negate the number");
    Asm("            xri     0ffh");
    Asm("            adi     1");
    Asm("            plo     r9");
    Asm("            ghi     r9");
    Asm("            xri     0ffh");
    Asm("            adci    0");
    Asm("            phi     r9");
    Asm("            glo     r8");
    Asm("            xri     0ffh");
    Asm("            adci    0");
    Asm("            plo     r8");
    Asm("            ghi     r8");
    Asm("            xri     0ffh");
    Asm("            adci    0");
    Asm("            phi     r8");
    Asm("atoi32_dn2: ghi     r8           ; store result into destination");
    Asm("            str     rd");
    Asm("            inc     rd");
    Asm("            glo     r8");
    Asm("            str     rd");
    Asm("            inc     rd");
    Asm("            ghi     r9");
    Asm("            str     rd");
    Asm("            inc     rd");
    Asm("            glo     r9");
    Asm("            str     rd");
    Asm("            dec     rd           ; restore RD");
    Asm("            dec     rd");
    Asm("            dec     rd");
    Asm("            sep     sret         ; and return to caller");
    }

  if (useNext32) {
    Asm("nextvar32:  irx            ; move to varAddr");
    Asm("            ldxa           ; keep scall return address");
    Asm("            plo     rd");
    Asm("            ldxa");
    Asm("            phi     rd");
    Asm("            irx");
    Asm("            irx");
    Asm("            glo     rc     ; check for correct address");
    Asm("            sm             ; against stack");
    Asm("            lbnz    nv132  ; jump if not");
    Asm("            irx            ; move to msb");
    Asm("            ghi     rc");
    Asm("            sm             ; compare");
    Asm("            lbnz    nv232  ; jump if not");
    Asm("            dec     r2     ; entry found, move back");
    Asm("            dec     r2");
    Asm("            dec     r2");
    Asm("            dec     r2");
    Asm("            dec     r2");
    Asm("            dec     r2");
    Asm("            lbr     next32");
    Asm("nv132:      irx            ; move past bad entry");
    Asm("nv232:      irx            ; move past bad entry");
    Asm("            irx       ");
    Asm("            irx       ");
    Asm("            irx       ");
    Asm("            irx       ");
    Asm("            irx       ");
    Asm("            irx       ");
    Asm("            irx       ");
    Asm("            ghi     rd");
    Asm("            stxd");
    Asm("            glo     rd");
    Asm("            stxd");
    Asm("            lbr     nextvar32");

    Asm("next32:     glo     r2");
    Asm("            plo     ra");
    Asm("            ghi     r2");
    Asm("            phi     ra");
    Asm("            sex     ra");
    Asm("            irx            ; return address lsb");
    Asm("            irx            ; return address msb");
    Asm("            irx            ; exec address lsb");
    Asm("            ldxa           ; retrieve exec address");
    Asm("            plo     r9");
    Asm("            ldxa");
    Asm("            phi     r9");
    Asm("            ldxa           ; get it");
    Asm("            plo     rf     ; set rf to address");
    Asm("            ldxa           ; get msb");
    Asm("            phi     rf");
    Asm("            inc     rf     ; point to variable lsb");
    Asm("            inc     rf     ; point to variable lsb");
    Asm("            inc     rf     ; point to variable lsb");
    Asm("            ldn     rf     ; retrieve it");
    Asm("            add            ; add in step");
    Asm("            str     rf");
    Asm("            dec     rf     ; point to byte2");
    Asm("            irx            ; point to byte2 of step");
    Asm("            ldn     rf     ; get byte2 of var value");
    Asm("            adc            ; add in step");
    Asm("            str     rf     ; store back into variable");
    Asm("            dec     rf     ; point to byte3");
    Asm("            irx            ; point to byte3 of step");
    Asm("            ldn     rf     ; get byte3 of var value");
    Asm("            adc            ; add in step");
    Asm("            dec     rf     ; point to byte4");
    Asm("            irx            ; point to byte4 of step");
    Asm("            ldn     rf     ; get byte3 of var value");
    Asm("            adc            ; add in step");
    Asm("            irx            ; point to loop count lsb");
    Asm("            ldi     1      ; need to decrement count");
    Asm("            sd             ; decrement it");
    Asm("            str     ra     ; and put it back");
    Asm("            irx            ; point to loop count byte2");
    Asm("            ldi     0      ; propagate carry");
    Asm("            sdb");
    Asm("            str     ra     ; and put it back");
    Asm("            irx            ; point to loop count byte3");
    Asm("            ldi     0      ; propagate carry");
    Asm("            sdb");
    Asm("            str     ra     ; and put it back");
    Asm("            irx            ; point to loop count byte4");
    Asm("            ldi     0      ; propagate carry");
    Asm("            sdb");
    Asm("            str     ra     ; and put it back");
    Asm("            sex     r2     ; point X back to R2");
    Asm("            lbdf    stay32 ; Jump if loop not done");
    Asm("            inc     r2");
    Asm("            dec     ra");
    Asm("            ldxa");
    Asm("            str     ra");
    Asm("            inc     ra");
    Asm("            ldx");
    Asm("            str     ra");
    Asm("            dec     ra");
    Asm("            dec     ra");
    Asm("            glo     ra");
    Asm("            plo     r2");
    Asm("            ghi     ra");
    Asm("            phi     r2");
    Asm("            sep     sret   ; nothing to do so return");
    Asm("stay32:     glo     r9     ; set return address to exec address");
    Asm("            plo     r6");
    Asm("            ghi     r9");
    Asm("            phi     r6");
    Asm("            sep     sret   ; and then return");
    }

  if (useFp) {
    Asm("fpdot1:    db      0cdh, 0cch, 0cch, 03dh");
    Asm("fp_0:      db      00,00,00,00");
    Asm("fp_1:      db      00,00,080h,03fh");
    Asm("fp_2:      db      00,00,000h,040h");
    Asm("fp_10:     db      00,00,020h,041h");
    Asm("fp_100:    db      00,00,0c8h,042h");
    Asm("fp_1000:   db      00,00,07ah,044h");
    Asm("fp_e:      db      054h, 0f8h, 02dh, 040h");
    Asm("fp_pi:     db      0dbh, 00fh, 049h, 040h");
    Asm("fp_3:      db      00,00,040h,040h");
    Asm("fpdot5:    db      000h, 000h, 000h, 03fh");
    Asm("fp_halfpi: db      0dbh, 00fh, 0c9h, 03fh");

    /* ******************************************* */
    /* ***** Normalize and combine FP result ***** */
    /* ***** R7:R8 - Mantissa                ***** */
    /* ***** R9.0  - Exponent                ***** */
    /* ***** R9.1  - Sign                    ***** */
    /* ***** Returns: R7:R8 - FP number      ***** */
    /* ******************************************* */
    Asm("fpnorm:    glo     r9           ; Get exponent");
    Asm("           lbz     fpnorm0      ; jump if zero");
    Asm("           glo     r8           ; zero check mantissa");
    Asm("           lbnz    fpnormnz     ; jump if not");
    Asm("           ghi     r8");
    Asm("           lbnz    fpnormnz");
    Asm("           glo     r7");
    Asm("           lbnz    fpnormnz");
    Asm("           ghi     r7");
    Asm("           lbnz    fpnormnz");
    Asm("fpnorm0:   ldi     0            ; set result to 0");
    Asm("           plo     r8");
    Asm("           phi     r8");
    Asm("           plo     r7");
    Asm("           phi     r7");
    Asm("           sep     sret         ; and return");
    Asm("fpnormi:   ldi     03fh         ; set infinity");
    Asm("           phi     r7");
    Asm("           ldi     080h");
    Asm("           plo     r7");
    Asm("           ldi     0");
    Asm("           phi     r8");
    Asm("           plo     r8");
    Asm("           sep     sret         ; and return");
    Asm("fpnormnz:  ghi     r7           ; check for need to right shift");
    Asm("           lbz     fpnorm_1     ; jump if no right shifts needed");
    Asm("           shr                  ; shift mantissa right");
    Asm("           phi     r7");
    Asm("           glo     r7");
    Asm("           shrc");
    Asm("           plo     r7");
    Asm("           ghi     r8");
    Asm("           shrc");
    Asm("           phi     r8");
    Asm("           glo     r8");
    Asm("           shrc");
    Asm("           plo     r8");
    Asm("           inc     r9           ; increment exponent");
    Asm("           glo     r9           ; get exponent");
    Asm("           smi     0ffh         ; check for exponent overflow");
    Asm("           lbz     fpnormi      ; jump if exponent overflow, returns 0");
    Asm("           lbr     fpnormnz     ; keep checking for bits too high in mantissa");
    Asm("fpnorm_1:  glo     r7           ; check for need to shift left");
    Asm("           shl                  ; shift high bit into DF");
    Asm("           lbdf    fpnorm_2     ; jump if high bit is set");
    Asm("           glo     r8           ; shift mantissa left");
    Asm("           shl");
    Asm("           plo     r8");
    Asm("           ghi     r8");
    Asm("           shlc");
    Asm("           phi     r8");
    Asm("           glo     r7");
    Asm("           shlc");
    Asm("           plo     r7");
    Asm("           dec     r9           ; decrement exponent");
    Asm("           glo     r9           ; check for exponent underflow");
    Asm("           lbz     fpnorm0      ; jump if underflow occured");
    Asm("           lbr     fpnorm_1     ; loop until high bit set");
    Asm("fpnorm_2:  glo     r7           ; prepare mantissa for merging exponent");
    Asm("           shl");
    Asm("           plo     r7");
    Asm("           ghi     r9           ; get sign");
    Asm("           shr                  ; shift into DF");
    Asm("           glo     r9           ; get exponent");
    Asm("           shrc                 ; shift in sign");
    Asm("           phi     r7           ; place into answer");
    Asm("           glo     r7           ; get high byte of mantissa");
    Asm("           shrc                 ; shift in least bit from exponent");
    Asm("           plo     r7           ; and put back");
    Asm("           sep     sret         ; return to caller");

    /* ********************************* */
    /* ***** Retrieve fp arguments ***** */
    /* ***** M[RF] -> R7:R8 R9.0   ***** */
    /* ***** M[RD] -> RA:RB R9.1   ***** */
    /* ********************************* */
    Asm("fpargs:    lda     rf           ; retrieve first number");
    Asm("           plo     r8");
    Asm("           lda     rf");
    Asm("           phi     r8");
    Asm("           lda     rf");
    Asm("           plo     r7");
    Asm("           shl                  ; shift low bit of exponent");
    Asm("           lda     rf");
    Asm("           phi     r7");
    Asm("           shlc                 ; get full exponent");
    Asm("           plo     r9           ; save exponent 1");
    Asm("           lda     rd           ; retrieve second number");
    Asm("           plo     rb");
    Asm("           lda     rd");
    Asm("           phi     rb");
    Asm("           lda     rd");
    Asm("           plo     ra");
    Asm("           shl                  ; shift low bit of exponent");
    Asm("           lda     rd");
    Asm("           phi     ra");
    Asm("           shlc                 ; get full exponent");
    Asm("           phi     r9           ; save exponent 2");
    Asm("           sep     sret         ; return to caller");

    Asm("fpret_0:   irx                  ; recover destination address");
    Asm("           ldxa");
    Asm("           plo     rf");
    Asm("           ldx");
    Asm("           phi     rf");
    Asm("           ldi     0            ; write 0");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           str     rf");
    Asm("           irx");
    Asm("           ldxa");
    Asm("           plo     r7");
    Asm("           ldx");
    Asm("           phi     r7");
    Asm("           sep     sret         ; and return");

    Asm("fpret_a:   irx                  ; recover destination address");
    Asm("           ldxa");
    Asm("           plo     rf");
    Asm("           ldx");
    Asm("           phi     rf");
    Asm("           glo     r8           ; store a as answer");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           ghi     r8");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           glo     r7");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           ghi     r7");
    Asm("           str     rf");
    Asm("           irx");
    Asm("           ldxa");
    Asm("           plo     r7");
    Asm("           ldx");
    Asm("           phi     r7");
    Asm("           sep     sret         ; and return to caller");

    Asm("fpret_b:   irx                  ; recover destination address");
    Asm("           ldxa");
    Asm("           plo     rf");
    Asm("           ldx");
    Asm("           phi     rf");
    Asm("           glo     rb           ; store a as answer");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           ghi     rb");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           glo     ra");
    Asm("           str     rf");
    Asm("           inc     rf");
    Asm("           ghi     ra");
    Asm("           str     rf");
    Asm("           irx");
    Asm("           ldxa");
    Asm("           plo     r7");
    Asm("           ldx");
    Asm("           phi     r7");
    Asm("           sep     sret         ; and return to caller");

    Asm("fpcomp2:   glo     r8           ; perform 2s compliment on input");
    Asm("           xri     0ffh");
    Asm("           adi     1");
    Asm("           plo     r8");
    Asm("           ghi     r8");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           phi     r8");
    Asm("           glo     r7");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           plo     r7");
    Asm("           ghi     r7");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           phi     r7");
    Asm("           sep     sret");

    /* **************************************************** */
    /* ***** Convert 32-bit integer to floating point ***** */
    /* ***** numbers are on expr stack                ***** */
    /* ***** RF - Pointer to 32-bit integer           ***** */
    /* ***** RD - Destination floating point          ***** */
    /* **************************************************** */
    Asm("itof:      inc     r7");
    Asm("           lda     r7           ; retrieve 32-bit integer into ra:rb");
    Asm("           plo     rb");
    Asm("           str     r2           ; store for zero check");
    Asm("           lda     r7");
    Asm("           phi     rb");
    Asm("           or                   ; combine with zero check");
    Asm("           str     r2           ; keep zero check on stack");
    Asm("           lda     r7");
    Asm("           plo     ra");
    Asm("           or");
    Asm("           str     r2");
    Asm("           ldn     r7           ; MSB");
    Asm("           phi     ra");
    Asm("           or");
    Asm("           lbz     itof0        ; jump if input number is zero");
    Asm("           ldi     0            ; set sign flag");
    Asm("           str     r2");
    Asm("           ghi     ra           ; see if number is negative");
    Asm("           shl                  ; shift sign bit into DF");
    Asm("           lbnf    itof_p       ; jump if number is positive");
    Asm("           ldi     1            ; set sign flag");
    Asm("           stxd");
    Asm("           glo     rb           ; 2s compliment input number");
    Asm("           xri     0ffh");
    Asm("           adi     1");
    Asm("           plo     rb");
    Asm("           ghi     rb");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           phi     rb");
    Asm("           glo     ra");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           plo     ra");
    Asm("           ghi     ra");
    Asm("           xri     0ffh");
    Asm("           adci    0");
    Asm("           phi     ra");
    Asm("           irx                  ; point x back to sign flag");
    Asm("itof_p:    ldi     150          ; exponent starts at 150");
    Asm("           plo     re");
    Asm("itof_1:    ghi     ra           ; see if need right shifts");
    Asm("           lbz     itof_2       ; jump if not");
    Asm("           shr                  ; otherwise shift number right");
    Asm("           phi     ra");
    Asm("           glo     ra");
    Asm("           shrc");
    Asm("           plo     ra");
    Asm("           ghi     rb");
    Asm("           shrc");
    Asm("           phi     rb");
    Asm("           glo     rb");
    Asm("           shrc");
    Asm("           plo     rb");
    Asm("           inc     re           ; increment exponent");
    Asm("           lbr     itof_1       ; and loop to see if more shifts needed");
    Asm("itof_2:    glo     ra           ; see if we need left shifts");
    Asm("           ani     080h");
    Asm("           lbnz    itof_3       ; jump if no shifts needed");
    Asm("           glo     rb           ; shift number left");
    Asm("           shl");
    Asm("           plo     rb");
    Asm("           ghi     rb");
    Asm("           shlc");
    Asm("           phi     rb");
    Asm("           glo     ra");
    Asm("           shlc");
    Asm("           plo     ra");
    Asm("           ghi     ra");
    Asm("           shlc");
    Asm("           phi     ra");
    Asm("           dec     re           ; decrement exponent");
    Asm("           lbr     itof_2       ; and loop to see if more shifts needed");
    Asm("itof_3:    glo     ra           ; prepare to merge in exponent");
    Asm("           shl");
    Asm("           plo     ra");
    Asm("           glo     re           ; get exponent");
    Asm("           phi     ra           ; store into result");
    Asm("           shr                  ; shift it right 1 bit");
    Asm("           glo     ra");
    Asm("           shrc                 ; shift final exponent bit in");
    Asm("           plo     ra");
    Asm("           ldx                  ; recover sign flag");
    Asm("           shr                  ; shift it into DF");
    Asm("           ghi     ra           ; get msb of result");
    Asm("           shrc                 ; shift in sign bit");
    Asm("           phi     ra           ; and put it back");
    Asm("itof0:     ghi     ra           ; store answer into destination");
    Asm("           str     r7");
    Asm("           dec     r7");
    Asm("           glo     ra");
    Asm("           str     r7");
    Asm("           dec     r7");
    Asm("           ghi     rb");
    Asm("           str     r7");
    Asm("           dec     r7");
    Asm("           glo     rb");
    Asm("           str     r7");
    Asm("           dec     r7");
    Asm("           sep     sret         ; and return");

    /* ************************************************* */
    /* ***** Convert floating point to integer     ***** */
    /* ***** Numbers are on expr stack             ***** */
    /* ***** RF - pointer to floating point number ***** */
    /* ***** RD - destination integer              ***** */
    /* ***** Returns: DF=1 - overflow              ***** */
    /* ***** Uses:                                 ***** */
    /* *****       R9.0  - exponent                ***** */
    /* *****       R9.1  - sign                    ***** */
    /* *****       RD:RF - number                  ***** */
    /* *****       RA:RB - fractional              ***** */
    /* *****       RC.0  - digit count             ***** */
    /* ************************************************* */
    Asm("ftoi:     inc      r7");
    Asm("          lda      r7         ; retrieve number into RD:RF");
    Asm("          plo      rf");
    Asm("          lda      r7");
    Asm("          phi      rf");
    Asm("          lda      r7");
    Asm("          plo      rd");
    Asm("          ldn      r7");
    Asm("          phi      rd");
    Asm("          shl                   ; shift sign into DF");
    Asm("          ldi      0            ; clear D");
    Asm("          shlc                  ; shift sign into D");
    Asm("          phi      r9           ; and store it");
    Asm("ftoi_1:   glo      rd           ; get low bit of exponent");
    Asm("          shl                   ; shift into DF");
    Asm("          ghi      rd           ; get high 7 bits of exponent");
    Asm("          shlc                  ; shift in the low bit");
    Asm("          plo      r9           ; store it");
    Asm("          lbnz     ftoi_2       ; jump if exponent is not zero");
    Asm("          ldi      0            ; result is zero");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          adi      0            ; clear DF");
    Asm("          sep      sret         ; return to caller");
    Asm("ftoi_2:   smi      0ffh         ; check for infinity");
    Asm("          lbnz     ftoi_5       ; jump if not");
    Asm("ftoi_ov:  ldi      0ffh         ; write highest integer");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          ldi      07fh         ; positive number");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          smi      0            ; set DF to signal ovelow");
    Asm("          sep      sret         ; and return");
    Asm("ftoi_5:   ldi      0            ; clear high byte of number");
    Asm("          phi      rd");
    Asm("          glo      rd           ; set implied 1");
    Asm("          ori      080h");
    Asm("          plo      rd           ; and put it back");
    Asm("          ldi      0            ; clear fractional");
    Asm("          phi      ra");
    Asm("          plo      ra");
    Asm("          phi      rb");
    Asm("          plo      rb");
    Asm("ftoi_6:   glo      r9           ; get exponent");
    Asm("          smi      150          ; check for less than 150");
    Asm("          lbdf     ftoi_7       ; jump if not");
    Asm("          glo      ra           ; shift fractional right");
    Asm("          shr");
    Asm("          plo      ra");
    Asm("          ghi      rb");
    Asm("          shrc");
    Asm("          phi      rb");
    Asm("          glo      rb");
    Asm("          shrc");
    Asm("          plo      rb");
    Asm("          glo      rf           ; get low bit of number");
    Asm("          shr                   ; shift it into DF");
    Asm("          lbnf     ftoi_6a      ; jump if bit was clear");
    Asm("          glo      ra           ; otherwise set high bit in fractional");
    Asm("          ori      080h");
    Asm("          plo      ra           ; put it back");
    Asm("ftoi_6a:  glo      rd           ; shift number right");
    Asm("          shr");
    Asm("          plo      rd");
    Asm("          ghi      rf");
    Asm("          shrc");
    Asm("          phi      rf");
    Asm("          glo      rf");
    Asm("          shrc");
    Asm("          plo      rf");
    Asm("          glo      r9           ; get exponent");
    Asm("          adi      1            ; increase it");
    Asm("          plo      r9           ; put it back");
    Asm("          lbr      ftoi_6       ; loop back until exponent >= 150");
    Asm("ftoi_7:   glo      r9           ; get exponent");
    Asm("          smi      151          ; check for greater than 150");
    Asm("          lbnf     ftoi_8       ; jump if not");
    Asm("          ghi      rd           ; check for ovelow");
    Asm("          ani      080h");
    Asm("          lbnz     ftoi_ov      ; jump if ovelow");
    Asm("          glo      rf           ; shift number left");
    Asm("          shl");
    Asm("          plo      rf");
    Asm("          ghi      rf");
    Asm("          shlc");
    Asm("          phi      rf");
    Asm("          glo      rd");
    Asm("          shlc");
    Asm("          plo      rd");
    Asm("          ghi      rd");
    Asm("          shlc");
    Asm("          phi      rd");
    Asm("          glo      r9           ; get exponent");
    Asm("          adi      1            ; increment it");
    Asm("          plo      r9           ; and put it back");
    Asm("          lbr      ftoi_7       ; loop until exponent in range");
    Asm("ftoi_8:   ghi      r9           ; was fp number negative");
    Asm("          lbz      ftoi_8a");
    Asm("          glo      rf           ; 2's compliment number");
    Asm("          xri      0ffh");
    Asm("          adi      1");
    Asm("          plo      rf");
    Asm("          ghi      rf");
    Asm("          xri      0ffh");
    Asm("          adci     0");
    Asm("          phi      rf");
    Asm("          glo      rd");
    Asm("          xri      0ffh");
    Asm("          adci     0");
    Asm("          plo      rd");
    Asm("          ghi      rd");
    Asm("          xri      0ffh");
    Asm("          adci     0");
    Asm("          phi      rd");
    Asm("ftoi_8a:  ghi      rd           ; store number into destination");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          glo      rd");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          ghi      rf");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          glo      rf");
    Asm("          str      r7");
    Asm("          dec      r7           ; move destination pointer back");
    Asm("          adi      0            ; signal no ovelow");
    Asm("          sep      sret         ; and return to caller");
    }

  if (useAddFp) {
    /* ******************************************** */
    /* ***** Floating point addition          ***** */
    /* ***** RF - pointer to first fp number  ***** */
    /* ***** RD - pointer to second fp number ***** */
    /* ***** Uses: R7:R8 - first number (aa)  ***** */
    /* *****       RA:RB - second number (bb) ***** */
    /* *****       R9.0  - exponent           ***** */
    /* *****       R9.1  - sign               ***** */
    /* ******************************************** */
    Asm("addfpi:    ghi     r7           ; save expr stack");
    Asm("           stxd");
    Asm("           glo     r7");
    Asm("           stxd");
    Asm("           ghi     rf           ; save destination address");
    Asm("           stxd");
    Asm("           glo     rf");
    Asm("           stxd");
    Asm("           sep     scall        ; retrieve arguments");
    Asm("           dw      fpargs");
    Asm("fpsub_1:   lbz     fpret_a      ; return a if b==0");
    Asm("           smi     0ffh         ; check for infinity");
    Asm("           lbz     fpret_b      ; return b if b==infinity");
    Asm("           glo     r9           ; get exponent 1");
    Asm("           lbz     fpret_b      ; return b if a==0");
    Asm("           smi     0ffh         ; check for infinity");
    Asm("           lbz     fpret_a      ; return a if a==infinity");
    Asm("           glo     r9           ; get exponent 1");
    Asm("           str     r2           ; store for comparison");
    Asm("           ghi     r9           ; get exponent 2");
    Asm("           sm                   ; compare to exponent 1");
    Asm("           lbnf    fpadd_1      ; jump if b<a");
    Asm("           glo     r8           ; swap a and b");
    Asm("           plo     re");
    Asm("           glo     rb");
    Asm("           plo     r8");
    Asm("           glo     re");
    Asm("           plo     rb");
    Asm("           ghi     r8           ; swap a and b");
    Asm("           plo     re");
    Asm("           ghi     rb");
    Asm("           phi     r8");
    Asm("           glo     re");
    Asm("           phi     rb");
    Asm("           glo     r7           ; swap a and b");
    Asm("           plo     re");
    Asm("           glo     ra");
    Asm("           plo     r7");
    Asm("           glo     re");
    Asm("           plo     ra");
    Asm("           ghi     r7           ; swap a and b");
    Asm("           plo     re");
    Asm("           ghi     ra");
    Asm("           phi     r7");
    Asm("           glo     re");
    Asm("           phi     ra");
    Asm("           glo     r9           ; also swap exponents");
    Asm("           plo     re");
    Asm("           ghi     r9");
    Asm("           plo     r9");
    Asm("           glo     re");
    Asm("           phi     r9");
    Asm("fpadd_1:   ghi     r7           ; compare signs");
    Asm("           str     r2");
    Asm("           ghi     ra");
    Asm("           xor");
    Asm("           plo     rc           ; store operation, 0=+, 1=-");
    Asm("           ghi     r7           ; get sign of largest number");
    Asm("           phi     rc           ; save it for now");
    Asm("           ldi     0            ; clear high bytes of numbers");
    Asm("           phi     ra");
    Asm("           phi     r7");
    Asm("           glo     ra           ; set implied 1 bit");
    Asm("           ori     080h");
    Asm("           plo     ra");
    Asm("           glo     r7           ; in first number too");
    Asm("           ori     080h");
    Asm("           plo     r7");
    Asm("fpadd_2:   glo     r9           ; compare exponents");
    Asm("           str     r2");
    Asm("           ghi     r9");
    Asm("           sm");
    Asm("           lbz     fpadd_3;     ; jump if exponents match");
    Asm("           ghi     r9           ; increment exponent 2");
    Asm("           adi     1");
    Asm("           phi     r9");
    Asm("           ghi     ra           ; shift b right");
    Asm("           shr");
    Asm("           phi     ra");
    Asm("           glo     ra");
    Asm("           shrc");
    Asm("           plo     ra");
    Asm("           ghi     rb");
    Asm("           shrc");
    Asm("           phi     rb");
    Asm("           glo     rb");
    Asm("           shrc");
    Asm("           plo     rb");
    Asm("           lbr     fpadd_2      ; loop until exponents match");
    Asm("fpadd_3:   glo     rc           ; get operation");
    Asm("           shl                  ; shift into DF");
    Asm("           lbdf    fpadd_s      ; jump if subtraction");
    Asm("           glo     r8           ; a += b");
    Asm("           str     r2");
    Asm("           glo     rb");
    Asm("           add");
    Asm("           plo     r8");
    Asm("           ghi     r8");
    Asm("           str     r2");
    Asm("           ghi     rb");
    Asm("           adc");
    Asm("           phi     r8");
    Asm("           glo     r7");
    Asm("           str     r2");
    Asm("           glo     ra");
    Asm("           adc");
    Asm("           plo     r7");
    Asm("           ghi     r7");
    Asm("           str     r2");
    Asm("           ghi     ra");
    Asm("           adc");
    Asm("           phi     r7");
    Asm("           lbr     fpadd_4      ; jump to completion");
    Asm("fpadd_s:   glo     r8           ; a -= b");
    Asm("           str     r2");
    Asm("           glo     rb");
    Asm("           sd");
    Asm("           plo     r8");
    Asm("           ghi     r8");
    Asm("           str     r2");
    Asm("           ghi     rb");
    Asm("           sdb");
    Asm("           phi     r8");
    Asm("           glo     r7");
    Asm("           str     r2");
    Asm("           glo     ra");
    Asm("           sdb");
    Asm("           plo     r7");
    Asm("           ghi     r7");
    Asm("           str     r2");
    Asm("           ghi     ra");
    Asm("           sdb");
    Asm("           phi     r7");
    Asm("           shl                  ; need to check sign of answer");
    Asm("           lbnf    fpadd_4      ; jump if positive");
    Asm("           sep     scall        ; 2s compliment number");
    Asm("           dw      fpcomp2");
    Asm("           ghi     rc           ; compliment sign");
    Asm("           xri     080h");
    Asm("           phi     rc           ; put it back");
    Asm("fpadd_4:   ghi     rc           ; move sign to R9.1");
    Asm("           shl");
    Asm("           ldi     0");
    Asm("           shlc");
    Asm("           phi     r9");
    Asm("           ghi     r7           ; check for zero");
    Asm("           lbnz    fpadd_5");
    Asm("           glo     r7");
    Asm("           lbnz    fpadd_5");
    Asm("           ghi     r8");
    Asm("           lbnz    fpadd_5");
    Asm("           glo     r8");
    Asm("           lbnz    fpadd_5");
    Asm("           lbr     fpret_0      ; otherwise answer is 0");
    Asm("fpadd_5:   sep     scall        ; normalize the answer");
    Asm("           dw      fpnorm");
    Asm("           lbr     fpret_a      ; write answer and return");

    Asm("addfp:     glo     r7           ; Setup registers for call");
    Asm("           plo     rf");
    Asm("           plo     rd");
    Asm("           ghi     r7");
    Asm("           phi     rf");
    Asm("           phi     rd");
    Asm("           inc     rd");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           sep     scall        ; Call addition");
    Asm("           dw      addfpi");
    Asm("           inc     r7           ; Adjust expr stack");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           sep     sret         ; And return");
    }

  if (useSubFp) {
    /* ******************************************** */
    /* ***** Floating point subtraction       ***** */
    /* ***** RF - pointer to first fp number  ***** */
    /* ***** RD - pointer to second fp number ***** */
    /* ***** Uses: R7:R8 - first number (aa)  ***** */
    /* *****       RA:RB - second number (bb) ***** */
    /* *****       R9.0  - exponent           ***** */
    /* *****       R9.1  - sign               ***** */
    /* ******************************************** */
    Asm("subfpi:     ghi     r7           ; save expr stack");
    Asm("           stxd");
    Asm("           glo     r7");
    Asm("           stxd");
    Asm("           ghi     rf           ; save destination address");
    Asm("           stxd");
    Asm("           glo     rf");
    Asm("           stxd");
    Asm("           sep     scall        ; retrieve arguments");
    Asm("           dw      fpargs");
    Asm("           ghi     ra           ; invert number");
    Asm("           xri     080h");
    Asm("           phi     ra           ; save inverted sign");
    Asm("           ghi     r9");
    Asm("           lbr     fpsub_1      ; now process with add");

    Asm("subfp:     glo     r7           ; Setup registers for call");
    Asm("           plo     rf");
    Asm("           plo     rd");
    Asm("           ghi     r7");
    Asm("           phi     rf");
    Asm("           phi     rd");
    Asm("           inc     rd");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           sep     scall        ; Call addition");
    Asm("           dw      subfpi");
    Asm("           inc     r7           ; Adjust expr stack");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           sep     sret         ; And return");
    }

  if (useMulFp) {
    /* ******************************************** */
    /* ***** Floating point multiplication    ***** */
    /* ***** RF - pointer to first fp number  ***** */
    /* ***** RD - pointer to second fp number ***** */
    /* ***** Uses: R7:R8 - answer       (cc)  ***** */
    /* *****       RA:RB - second number (bb) ***** */
    /* *****       R9.0  - exponent           ***** */
    /* *****       R9.1  - sign               ***** */
    /* *****       RC:RD - first number (aa)  ***** */
    /* ******************************************** */
    Asm("mulfpi:    ghi     r7           ; save expr stack");
    Asm("           stxd");
    Asm("           glo     r7");
    Asm("           stxd");
    Asm("           ghi     rf           ; save destination address");
    Asm("           stxd");
    Asm("           glo     rf");
    Asm("           stxd");
    Asm("          lda      rd           ; retrieve second number");
    Asm("          plo      rb           ; place into bb");
    Asm("          lda      rd");
    Asm("          phi      rb");
    Asm("          lda      rd");
    Asm("          plo      ra");
    Asm("          shl                   ; shift high bit into DF");
    Asm("          lda      rd");
    Asm("          phi      ra");
    Asm("          shlc                  ; now have full 8 bits of exponent");
    Asm("          phi      r9           ; store into r9");
    Asm("          lbz      fpret_0      ; jump if number is zero");
    Asm("          lda      rf           ; retrieve first number");
    Asm("          plo      rd           ; place into aa");
    Asm("          lda      rf");
    Asm("          phi      rd");
    Asm("          lda      rf");
    Asm("          plo      rc");
    Asm("          shl                   ; shift high bit into DF");
    Asm("          lda      rf");
    Asm("          phi      rc");
    Asm("          shlc                  ; now have exponent of first number");
    Asm("          plo      r9           ; save it");
    Asm("          lbz      fpret_0      ; jump if number was zero");
    Asm("          glo      r9           ; get exponent of first number");
    Asm("          smi      0ffh         ; check for infinity");
    Asm("          lbz      fpmul_a      ; jump if so");
    Asm("          ghi      r9           ; get exponent of second number");
    Asm("          smi      0ffh         ; check for infinity");
    Asm("          lbz      fpret_b      ; jump if so");
    Asm("          glo      r9           ; get exponent 1");
    Asm("          smi      127          ; remove bias");
    Asm("          str      r2           ; store for add");
    Asm("          ghi      r9           ; get exponent 2");
    Asm("          smi      127          ; remove bias");
    Asm("          add                   ; add in exponent 1");
    Asm("          adi      127          ; add bias back in");
    Asm("          plo      r9           ; r9 now has exponent of result");
    Asm("          ghi      ra           ; get msb of bb");
    Asm("          str      r2           ; store it");
    Asm("          ghi      rc           ; get msb of aa");
    Asm("          xor                   ; now have sign comparison");
    Asm("          shl                   ; shift sign into DF");
    Asm("          ldi      0            ; clear byte");
    Asm("          shlc                  ; shift in sign");
    Asm("          phi      r9           ; save sign for later");
    Asm("          ldi      0            ; need to clear high bytes");
    Asm("          phi      ra           ; of bb");
    Asm("          phi      rc           ; and aa");
    Asm("          plo      r8           ; also clear answer");
    Asm("          phi      r8");
    Asm("          plo      r7");
    Asm("          phi      r7");
    Asm("          glo      ra           ; get msb of bb mantissa");
    Asm("          ori      080h         ; add in implied 1");
    Asm("          plo      ra           ; and put it back");
    Asm("          glo      rc           ; get msb of aa mantissa");
    Asm("          ori      080h         ; add in implied 1");
    Asm("          plo      rc           ; and put it back");
    Asm("fpmul_lp: glo      ra           ; need to zero check bb");
    Asm("          str      r2");
    Asm("          ghi      ra");
    Asm("          or");
    Asm("          str      r2");
    Asm("          glo      rb");
    Asm("          or");
    Asm("          str      r2");
    Asm("          ghi      rb");
    Asm("          or");
    Asm("          lbz      fpmul_dn     ; jump of bb==0");
    Asm("          ghi      r7           ; cc >>= 1");
    Asm("          shr");
    Asm("          phi      r7");
    Asm("          glo      r7");
    Asm("          shrc");
    Asm("          plo      r7");
    Asm("          ghi      r8");
    Asm("          shrc");
    Asm("          phi      r8");
    Asm("          glo      r8");
    Asm("          shrc");
    Asm("          plo      r8");
    Asm("          ghi      ra           ; bb >>= 1");
    Asm("          shr");
    Asm("          phi      ra");
    Asm("          glo      ra");
    Asm("          shrc");
    Asm("          plo      ra");
    Asm("          ghi      rb");
    Asm("          shrc");
    Asm("          phi      rb");
    Asm("          glo      rb");
    Asm("          shrc");
    Asm("          plo      rb");
    Asm("          lbnf     fpmul_lp     ; back to loop if no addition needed");
    Asm("          glo      r8           ; cc += aa");
    Asm("          str      r2");
    Asm("          glo      rd");
    Asm("          add");
    Asm("          plo      r8");
    Asm("          ghi      r8");
    Asm("          str      r2");
    Asm("          ghi      rd");
    Asm("          adc");
    Asm("          phi      r8");
    Asm("          glo      r7");
    Asm("          str      r2");
    Asm("          glo      rc");
    Asm("          adc");
    Asm("          plo      r7");
    Asm("          ghi      r7");
    Asm("          str      r2");
    Asm("          ghi      rc");
    Asm("          adc");
    Asm("          phi      r7");
    Asm("          lbr      fpmul_lp     ; back to beginning of loop");
    Asm("fpmul_dn: sep      scall        ; assemble answer");
    Asm("          dw       fpnorm");
    Asm("          lbr      fpret_a      ; place result into destination");
    Asm("fpmul_a:  irx                   ; recover destination address");
    Asm("          ldxa");
    Asm("          plo      rf");
    Asm("          ldx");
    Asm("          phi      rf");
    Asm("          glo      rd           ; write a to answer");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          ghi      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          glo      rc");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          ghi      rc");
    Asm("          str      rf");
    Asm("          irx                   ; recover expr stack");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          sep      sret         ; and return to caller");

    Asm("mulfp:     glo     r7           ; Setup registers for call");
    Asm("           plo     rf");
    Asm("           plo     rd");
    Asm("           ghi     r7");
    Asm("           phi     rf");
    Asm("           phi     rd");
    Asm("           inc     rd");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           sep     scall        ; Call addition");
    Asm("           dw      mulfpi");
    Asm("           inc     r7           ; Adjust expr stack");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           sep     sret         ; And return");
    }

  if (useDivFp) {
    /* ******************************************** */
    /* ***** Floating point division          ***** */
    /* ***** RF - pointer to first fp number  ***** */
    /* ***** RD - pointer to second fp number ***** */
    /* ***** Uses: R7:R8 - answer       (a)   ***** */
    /* *****       RA:RB - second number (b)  ***** */
    /* *****       RA    - pointer to (aa)    ***** */
    /* *****       RB    - pointer to (bb)    ***** */
    /* *****       R9.0  - exponent           ***** */
    /* *****       R9.1  - sign               ***** */
    /* *****       RC:RD - mask               ***** */
    /* ******************************************** */
    Asm("divfpi:    ghi     r7           ; save expr stack");
    Asm("           stxd");
    Asm("           glo     r7");
    Asm("           stxd");
    Asm("           ghi     rf           ; save destination address");
    Asm("           stxd");
    Asm("           glo     rf");
    Asm("           stxd");
    Asm("          sep      scall        ; get arguments");
    Asm("          dw       fpargs");
    Asm("          glo      r9           ; check for a==0");
    Asm("          lbz      fpret_0      ; return 0 if so");
    Asm("          ghi      r9           ; check for b==0");
    Asm("          lbz      fpret_0      ; return 0 if so");
    Asm("          glo      r9           ; check for a==infinity");
    Asm("          smi      0ffh");
    Asm("          lbz      fpret_a      ; return a if so");
    Asm("          ghi      r9           ; check for b==infinity");
    Asm("          smi      0ffh");
    Asm("          lbz      fpret_b      ; return b if so");
    Asm("          ghi      r9           ; get exp2");
    Asm("          smi      127          ; remove bias");
    Asm("          str      r2           ; store for subtraction");
    Asm("          glo      r9           ; get exp1");
    Asm("          smi      127          ; remove bias");
    Asm("          sm                    ; subtract exp2");
    Asm("          adi      127          ; add bias back in");
    Asm("          plo      r9           ; now have final exp");
    Asm("          ghi      r7           ; get sign of a");
    Asm("          str      r2           ; store for xor");
    Asm("          ghi      ra           ; get sign of b");
    Asm("          xor                   ; now have sign comparison");
    Asm("          shl                   ; shift it into DF");
    Asm("          ldi      0            ; clear D");
    Asm("          shlc                  ; and shift in sign");
    Asm("          phi      r9           ; store sign");
    Asm("          glo      ra           ; put bb on stack");
    Asm("          ori      080h         ; set implied 1 bit");
    Asm("          stxd");
    Asm("          ghi      rb");
    Asm("          stxd");
    Asm("          glo      rb");
    Asm("          stxd");
    Asm("          ldi      0");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          glo      r2           ; point RB to bb");
    Asm("          plo      rb");
    Asm("          ghi      r2");
    Asm("          phi      rb");
    Asm("          inc      rb");
    Asm("          glo      r7           ; put aa on stack");
    Asm("          ori      080h         ; set implied 1 bit");
    Asm("          stxd");
    Asm("          ghi      r8");
    Asm("          stxd");
    Asm("          glo      r8");
    Asm("          stxd");
    Asm("          ldi      0");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          glo      r2           ; set RA to point to aa");
    Asm("          plo      ra");
    Asm("          ghi      r2");
    Asm("          phi      ra");
    Asm("          inc      ra");
    Asm("          ldi      0            ; clear a");
    Asm("          plo      r8");
    Asm("          phi      r8");
    Asm("          plo      r7");
    Asm("          phi      r7");
    Asm("          plo      rd           ; setup mask");
    Asm("          phi      rd");
    Asm("          phi      rc");
    Asm("          ldi      080h");
    Asm("          plo      rc");
    Asm("fpdiv_lp: glo      rd           ; need to check for mask==0");
    Asm("          lbnz     fpdiv_1      ; jump if not 0");
    Asm("          ghi      rd");
    Asm("          lbnz     fpdiv_1");
    Asm("          glo      rc");
    Asm("          lbnz     fpdiv_1");
    Asm("          sep      scall        ; division is done, so call normalize");
    Asm("          dw       fpnorm");
    Asm("          glo      r2           ; clear work space from stack");
    Asm("          adi      12");
    Asm("          plo      r2");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      r2");
    Asm("          lbr      fpret_a      ; and return the answer");
    Asm("fpdiv_1:  smi      0            ; set DF for first byte");
    Asm("          ldi      6            ; 6 bytes to subtract");
    Asm("          plo      re");
    Asm("          sex      rb           ; point x to bb");
    Asm("fpdiv_1a: lda      ra           ; get byte from aa");
    Asm("          smb                   ; subtract byte from bb from aa");
    Asm("          inc      rb           ; point to next byte");
    Asm("          dec      re           ; decrement count");
    Asm("          glo      re           ; see if done");
    Asm("          lbnz     fpdiv_1a     ; loop back if not");
    Asm("          ldi      6            ; need to move pointers back");
    Asm("          plo      re");
    Asm("fpdiv_1b: dec      ra");
    Asm("          dec      rb");
    Asm("          dec      re");
    Asm("          glo      re");
    Asm("          lbnz     fpdiv_1b");
    Asm("          lbnf     fpdiv_2      ; jump if b>a");
    Asm("          ldi      6            ; 6 bytes to subtract bb from aa");
    Asm("          plo      re");
    Asm("          smi      0            ; set DF for first subtract");
    Asm("fpdiv_1c: ldn      ra           ; get byte from a");
    Asm("          smb                   ; subtract bb");
    Asm("          str      ra           ; put it back");
    Asm("          inc      ra           ; increment pointers");
    Asm("          inc      rb");
    Asm("          dec      re           ; decrement byte count");
    Asm("          glo      re           ; see if done");
    Asm("          lbnz     fpdiv_1c     ; loop back if not");
    Asm("          ldi      6            ; need to move pointers back");
    Asm("          plo      re");
    Asm("fpdiv_1d: dec      ra");
    Asm("          dec      rb");
    Asm("          dec      re");
    Asm("          glo      re");
    Asm("          lbnz     fpdiv_1d");
    Asm("          sex      r2           ; point x back to stack");
    Asm("          glo      rc           ; add mask to answer");
    Asm("          str      r2");
    Asm("          glo      r7");
    Asm("          or");
    Asm("          plo      r7");
    Asm("          ghi      rd");
    Asm("          str      r2");
    Asm("          ghi      r8");
    Asm("          or");
    Asm("          phi      r8");
    Asm("          glo      rd");
    Asm("          str      r2");
    Asm("          glo      r8");
    Asm("          or");
    Asm("          plo      r8");
    Asm("fpdiv_2:  sex      r2           ; point x back to stack");
    Asm("          glo      rc           ; right shift mask");
    Asm("          shr");
    Asm("          plo      rc");
    Asm("          ghi      rd");
    Asm("          shrc");
    Asm("          phi      rd");
    Asm("          glo      rd");
    Asm("          shrc");
    Asm("          plo      rd");
    Asm("          inc      rb           ; need to start at msb of bb");
    Asm("          inc      rb");
    Asm("          inc      rb");
    Asm("          inc      rb");
    Asm("          inc      rb");
    Asm("          inc      rb");
    Asm("          ldi      6            ; 6 bytes in bb to shift right");
    Asm("          plo      re");
    Asm("          adi      0            ; clear DF for first shift");
    Asm("fpdiv_2a: dec      rb");
    Asm("          ldn      rb           ; get byte from bb");
    Asm("          shrc                  ; shift it right");
    Asm("          str      rb           ; and put it back");
    Asm("          dec      re           ; decrement count");
    Asm("          glo      re           ; see if done");
    Asm("          lbnz     fpdiv_2a     ; loop back if not");
    Asm("          lbr      fpdiv_lp     ; loop for rest of division");

    Asm("divfp:     glo     r7           ; Setup registers for call");
    Asm("           plo     rf");
    Asm("           plo     rd");
    Asm("           ghi     r7");
    Asm("           phi     rf");
    Asm("           phi     rd");
    Asm("           inc     rd");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           inc     rf");
    Asm("           sep     scall        ; Call addition");
    Asm("           dw      divfpi");
    Asm("           inc     r7           ; Adjust expr stack");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           inc     r7");
    Asm("           sep     sret         ; And return");
    }

  if (useAbsFp) {
    Asm("absfp:    inc      r7           ; move to MSB");
    Asm("          inc      r7");
    Asm("          inc      r7");
    Asm("          inc      r7");
    Asm("          ldn      r7           ; retrieve it");
    Asm("          ani      07fh         ; force it positive");
    Asm("          str      r7           ; and put it back");
    Asm("          dec      r7           ; move pointer back");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          sep      sret");
    }

  if (useSgnFp) {
    Asm("sgnfp:    inc     r7");
    Asm("          lda     r7");
    Asm("          str     r2");
    Asm("          lda     r7");
    Asm("          or");
    Asm("          str     r2");
    Asm("          lda     r7");
    Asm("          or");
    Asm("          str     r2");
    Asm("          ldn     r7");
    Asm("          shl");
    Asm("          lbdf    sgnmfp");
    Asm("          ldn     r7");
    Asm("          or");
    Asm("          lbz     sgn0fp");
    Asm("          ldi     0");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          ldi     1");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgnmfp:   ldi     0ffh");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          str     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    Asm("sgn0fp:   dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          dec     r7");
    Asm("          sep     sret");
    }

  if (useEqFp) {
    Asm("eqfp:       sep     scall");
    Asm("            dw      subfp");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldx");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true32");
    Asm("            lbr     false32");
    }

  if (useNeFp) {
    Asm("nefp:       sep     scall");
    Asm("            dw      subfp");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldx");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbnz    true32");
    Asm("            lbr     false32");
    }

  if (useGtFp) {
    Asm("gtfp:       sep     scall");
    Asm("            dw      subfp");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldx");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     false32");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbnf    true32");
    Asm("            lbr     false32");
    }

  if (useLtFp) {
    Asm("ltfp:       sep     scall");
    Asm("            dw      subfp");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldx");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     false32");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbdf    true32");
    Asm("            lbr     false32");
    }

  if (useGteFp) {
    Asm("gtefp:      sep     scall");
    Asm("            dw      subfp");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldx");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true32");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbnf    true32");
    Asm("            lbr     false32");
    }

  if (useLteFp) {
    Asm("ltefp:      sep     scall");
    Asm("            dw      subfp");
    Asm("            sex     r7");
    Asm("            irx");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldxa");
    Asm("            or");
    Asm("            ldx");
    Asm("            or");
    Asm("            sex     r2");
    Asm("            lbz     true32");
    Asm("            ldn     r7");
    Asm("            shl");
    Asm("            lbdf    true32");
    Asm("            lbr     false32");
    }

  if (useAtoF) {
    /* ******************************************** */
    /* ***** Convert ASCII to floating point  ***** */
    /* ***** RF - Pointer to ASCII string     ***** */
    /* ***** RD - Desintation FP              ***** */
    /* ***** Uses:                            ***** */
    /* *****       R7:R8 - mantissa           ***** */
    /* *****       R9.0  - exponent           ***** */
    /* *****       R9.1  - sign               ***** */
    /* *****       RA:RB - mask               ***** */
    /* *****       RC    - fractional pointer ***** */
    /* ******************************************** */
    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
    /* +++++ First convert integer portion to floating point +++++ */
    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
    Asm("atof:     ghi      r7           ; save expr stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ldi      0            ; set sign to positive");
    Asm("          phi      r9");
    Asm("          ldn      rf           ; get first byte from buffer");
    Asm("          smi      '-'          ; is it minus");
    Asm("          lbnz     atof_1       ; jump if not");
    Asm("          ldi      1            ; indicate negative number");
    Asm("          phi      r9");
    Asm("          inc      rf           ; and move past minus");
    Asm("atof_1:   ghi      rd           ; save destination");
    Asm("          stxd");
    Asm("          glo      rd");
    Asm("          stxd");
    Asm("          ghi      r9           ; save sign");
    Asm("          stxd");
    Asm("          sep      scall        ; convert integer portion of number");
    Asm("          dw       atoi32");
    Asm("          irx");
    Asm("          ldxa                  ; recover sign");
    Asm("          phi      r9");
    Asm("          ldxa                  ; recover destination");
    Asm("          plo      rd");
    Asm("          ldx");
    Asm("          phi      rd");
    Asm("          dec      r2           ; and keep on stack");
    Asm("          dec      r2");
    Asm("          lda      rd           ; retrieve integer number");
    Asm("          phi      r7");
    Asm("          str      r2           ; store for zero check");
    Asm("          lda      rd");
    Asm("          plo      r7");
    Asm("          or                    ; combine with zero check");
    Asm("          str      r2");
    Asm("          lda      rd");
    Asm("          phi      r8");
    Asm("          or                    ; combine with zero check");
    Asm("          str      r2");
    Asm("          lda      rd");
    Asm("          plo      r8");
    Asm("          or                    ; combine with zero check");
    Asm("          lbz      atof_z       ; jump if integer is zero");
    Asm("          ldi      150          ; initial exponent starts at 150");
    Asm("          plo      r9");
    Asm("          ldi      1            ; initial mask is 1");
    Asm("          plo      rb");
    Asm("          ldi      0");
    Asm("          phi      rb");
    Asm("          plo      ra");
    Asm("          phi      ra");
    Asm("          ghi      r7           ; check if high byte has anything");
    Asm("          lbz      atof_b       ; jump if not");
    Asm("atof_a1:  ghi      r7           ; get high byte");
    Asm("          lbz      atof_a2      ; jump if done shifting");
    Asm("          shr                   ; shift mantissa right");
    Asm("          phi      r7");
    Asm("          glo      r7");
    Asm("          shrc");
    Asm("          plo      r7");
    Asm("          ghi      r8");
    Asm("          shrc");
    Asm("          phi      r8");
    Asm("          glo      r8");
    Asm("          shrc");
    Asm("          plo      r8");
    Asm("          glo      r9           ; get exponent");
    Asm("          adi      1            ; increment it");
    Asm("          plo      r9           ; put it back");
    Asm("          lbr      atof_a1      ; loop until high byte cleared");
    Asm("atof_a2:  ldi      0            ; clear mask");
    Asm("          phi      ra");
    Asm("          plo      ra");
    Asm("          phi      rb");
    Asm("          plo      rb");
    Asm("          lbr      atof_2       ; and then jump to next section");
    Asm("atof_b:   glo      r7           ; get first byte of mantissa");
    Asm("          shl                   ; shift high bit into DF");
    Asm("          lbdf     atof_2       ; if set, no more shifts needed");
    Asm("          glo      r8           ; shift mantissa left");
    Asm("          shl");
    Asm("          plo      r8");
    Asm("          ghi      r8");
    Asm("          shlc");
    Asm("          phi      r8");
    Asm("          glo      r7");
    Asm("          shlc");
    Asm("          plo      r7");
    Asm("          glo      rb           ; shift mask left");
    Asm("          shl");
    Asm("          plo      rb");
    Asm("          ghi      rb");
    Asm("          shlc");
    Asm("          phi      rb");
    Asm("          glo      ra");
    Asm("          shlc");
    Asm("          plo      ra");
    Asm("          glo      r9           ; get exponent");
    Asm("          smi      1            ; decrement it");
    Asm("          plo      r9           ; and put it back");
    Asm("          lbr      atof_b       ; loop until high bit of mantissa set");
    Asm("atof_z:   ldi      080h         ; set initial mask");
    Asm("          plo      ra");
    Asm("          ldi      0");
    Asm("          phi      ra");
    Asm("          phi      rb");
    Asm("          plo      rb");
    Asm("          ldi      127          ; initial exponent");
    Asm("          plo      r9");
    /* ++++++++++++++++++++++++++++++++++++++++++++++++++ */
    /* +++++ Now convert number after decimal point +++++ */
    /* ++++++++++++++++++++++++++++++++++++++++++++++++++ */
    Asm("atof_2:   ldn      rf           ; get next byte from input");
    Asm("          smi      '.'          ; is it a decimal");
    Asm("          lbnz     atof_e       ; jump if not");
    Asm("          inc      rf           ; move past decimal");
    Asm("          ldi      99           ; need marker on stack");
    Asm("          stxd");
    Asm("atof_2a:  lda      rf           ; get next byte from input");
    Asm("          plo      re           ; keep a copy");
    Asm("          smi      '0'          ; see if below digits");
    Asm("          lbnf     atof_2b      ; jump if not valid digit");
    Asm("          smi      10           ; check for high of range");
    Asm("          lbdf     atof_2b      ; jump if not valid digit");
    Asm("          glo      re           ; recover number");
    Asm("          smi      '0'          ; convert to binary");
    Asm("          stxd                  ; and store on stack");
    Asm("          lbr      atof_2a      ; loop until all numerals copied");
    Asm("atof_2b:  dec      rf           ; move pointer back to non-numeral character");
    /* ------------------------------------ */
    /* ----- Main loop for fractional ----- */
    /* ------------------------------------ */
    Asm("atof_2c:  glo      rb           ; check mask for zero");
    Asm("          lbnz     atof_2d");
    Asm("          ghi      rb");
    Asm("          lbnz     atof_2d");
    Asm("          glo      ra");
    Asm("          lbnz     atof_2d");
    Asm("          lbr      atof_2z      ; done with fractional");
    Asm("atof_2d:  glo      r7           ; check mantissa for zero");
    Asm("          lbnz     atof_2e");
    Asm("          ghi      r8");
    Asm("          lbnz     atof_2e");
    Asm("          glo      r8");
    Asm("          lbnz     atof_2e");
    Asm("          glo      r9           ; zero result");
    Asm("          smi      1            ; so subtract 1 from exponent");
    Asm("          plo      r9           ; put it back");
    Asm("          lbr      atof_2f");
    Asm("atof_2e:  glo      ra           ; if result nonzero, shift mask right");
    Asm("          shr");
    Asm("          plo      ra");
    Asm("          ghi      rb");
    Asm("          shrc");
    Asm("          phi      rb");
    Asm("          glo      rb");
    Asm("          shrc");
    Asm("          plo      rb");
    Asm("atof_2f:  ldi      0            ; set carry to 0");
    Asm("          plo      re");
    Asm("          glo      r2           ; point to fractional data");
    Asm("          plo      rc");
    Asm("          ghi      r2");
    Asm("          phi      rc");
    Asm("          inc      rc");
    Asm("atof_2g:  ldn      rc           ; get next byte from fractional");
    Asm("          smi      99           ; check for end");
    Asm("          lbz      atof_2j      ; jump if end found");
    Asm("          glo      re           ; get carry");
    Asm("          shr                   ; shift into DF");
    Asm("          ldn      rc           ; get next fractional digit");
    Asm("          shlc                  ; add to itself plus carry");
    Asm("          str      rc           ; put it back");
    Asm("          smi      10           ; see if exceeded 10");
    Asm("          lbnf     atof_2h      ; jump if not");
    Asm("          str      rc           ; store corrected number");
    Asm("          ldi      1            ; set carry");
    Asm("atof_2i:  plo      re");
    Asm("          inc      rc           ; point to next character");
    Asm("          lbr      atof_2g      ; and loop back for more");
    Asm("atof_2h:  ldi      0            ; clear carry");
    Asm("          lbr      atof_2i");
    Asm("atof_2j:  glo      re           ; get carry");
    Asm("          shr                   ; shift into DF");
    Asm("          lbnf     atof_2c      ; loop until mask==0");
    Asm("          glo      rb           ; check mask for zero");
    Asm("          lbnz     atof_2k      ; jump if not zero");
    Asm("          ghi      rb");
    Asm("          lbnz     atof_2k      ; jump if not zero");
    Asm("          glo      ra");
    Asm("          lbnz     atof_2k      ; jump if not zero");
    Asm("          glo      r8           ; mask==0, add 1");
    Asm("          adi      1");
    Asm("          plo      r8");
    Asm("          ghi      r8");
    Asm("          adci     0");
    Asm("          phi      r8");
    Asm("          glo      r7");
    Asm("          adci     0");
    Asm("          plo      r7");
    Asm("          lbr      atof_2z      ; done with fractional");
    Asm("atof_2k:  glo      rb           ; combine mask with result");
    Asm("          str      r2");
    Asm("          glo      r8");
    Asm("          or");
    Asm("          plo      r8");
    Asm("          ghi      rb");
    Asm("          str      r2");
    Asm("          ghi      r8");
    Asm("          or");
    Asm("          phi      r8");
    Asm("          glo      ra");
    Asm("          str      r2");
    Asm("          glo      r7");
    Asm("          or");
    Asm("          plo      r7");
    Asm("          lbr      atof_2c      ; loop until mask == 0");
    Asm("atof_2z:  irx                   ; clean temp data from stack");
    Asm("atof_2z2: ldxa                  ; get next byte");
    Asm("          smi      99           ; look for end marker");
    Asm("          lbnz     atof_2z2     ; loop until marker found");
    Asm("          dec      r2           ; move stack pointer back");
    Asm("atof_e:   sep      scall        ; normalize number");
    Asm("          dw       fpnorm");
    Asm("          ldn      rf           ; get next character");
    Asm("          smi      'E'          ; check for exponent");
    Asm("          lbz      atof_ex      ; jump if so");
    Asm("          smi      32           ; check lowercase e as well");
    Asm("          lbz      atof_ex      ; jump if exponent");
    Asm("atof_dn:  irx                   ; recover destination");
    Asm("          ldxa");
    Asm("          plo      rd");
    Asm("          ldx");
    Asm("          phi      rd");
    Asm("          ghi      r7           ; store answer in destination");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          glo      r7");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          ghi      r8");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          glo      r8");
    Asm("          str      rd");
    Asm("          dec      rd           ; restore destination pointer");
    Asm("          dec      rd");
    Asm("          dec      rd");
    Asm("          irx                   ; recover expr stack");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          sep      sret         ; return to caller");
    /* ++++++++++++++++++++++++++++ */
    /* +++++ Process exponent +++++ */
    /* ++++++++++++++++++++++++++++ */
    Asm("atof_ex:  ldi      0            ; signal positive exponent");
    Asm("          phi      r9           ; put it here");
    Asm("          inc      rf           ; move past E");
    Asm("          ldn      rf           ; need to check for sign");
    Asm("          smi      '+'          ; check for positive");
    Asm("          lbz      atof_exp     ; jump if so");
    Asm("          smi      2            ; check for negative");
    Asm("          lbnz     atof_ex1     ; jump if not");
    Asm("          ldi      1            ; signal negative number");
    Asm("          phi      r9");
    Asm("atof_exp: inc      rf           ; move past sign");
    Asm("atof_ex1: ldi      0            ; set exponent count to zero");
    Asm("          plo      rc");
    Asm("atof_ex2: ldn      rf           ; get byte from input");
    Asm("          smi      '0'          ; see if below digits");
    Asm("          lbnf     atof_ex3     ; jump if not valid digit");
    Asm("          smi      10           ; check for high of range");
    Asm("          lbdf     atof_ex3     ; jump if not valid digit");
    Asm("          glo      rc           ; get count");
    Asm("          shl                   ; multiply by 2");
    Asm("          str      r2           ; save for add");
    Asm("          shl                   ; multiply by 4");
    Asm("          shl                   ; by 8");
    Asm("          add                   ; by 10");
    Asm("          str      r2           ; store for add");
    Asm("          lda      rf           ; get input byte");
    Asm("          smi      '0'          ; convert to binary");
    Asm("          add                   ; add in prior total");
    Asm("          plo      rc           ; put it back");
    Asm("          lbr      atof_ex2     ; loop until no more digits");
    Asm("atof_ex3: ghi      r7           ; put result on stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r8");
    Asm("          stxd");
    Asm("          glo      r8");
    Asm("          stxd");
    Asm("          ghi      r9           ; check sign of exponent");
    Asm("          shr");
    Asm("          lbdf     atof_exn     ; jump if negative");
    Asm("atof_ex4: glo      rc           ; see if done");
    Asm("          lbz      atof_exd     ; jump if done");
    Asm("          glo      r2           ; point to result");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          phi      rf");
    Asm("          inc      rf");
    Asm("          ldi      fp_10.1      ; point to 10.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_10.0");
    Asm("          plo      rd");
    Asm("          glo      rc           ; save count");
    Asm("          stxd");
    Asm("          sep      scall        ; multiply result by 10.0");
    Asm("          dw       mulfpi");
    Asm("          irx                   ; recover count");
    Asm("          ldx");
    Asm("          plo      rc           ; put back into count");
    Asm("          dec      rc           ; decrement count");
    Asm("          lbr      atof_ex4     ; loop until done");
    Asm("atof_exn: glo      rc           ; see if done");
    Asm("          lbz      atof_exd     ; jump if done");
    Asm("          glo      r2           ; point to result");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          phi      rf");
    Asm("          inc      rf");
    Asm("          ldi      fp_10.1      ; point to 10.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_10.0");
    Asm("          plo      rd");
    Asm("          glo      rc           ; save count");
    Asm("          stxd");
    Asm("          sep      scall        ; divide result by 10.0");
    Asm("          dw       divfpi");
    Asm("          irx                   ; recover count");
    Asm("          ldx");
    Asm("          plo      rc           ; put back into count");
    Asm("          dec      rc           ; decrement count");
    Asm("          lbr      atof_exn     ; loop until done");
    Asm("atof_exd: irx                   ; recover answer");
    Asm("          ldxa");
    Asm("          plo      r8");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          lbr      atof_dn      ; and return result");
    }

  if (useFtoA) {
    /* ************************************************* */
    /* ***** Convert floating point to ASCII       ***** */
    /* ***** RF - pointer to floating point number ***** */
    /* ***** RD - destination buffer               ***** */
    /* ***** Uses:                                 ***** */
    /* *****       R9.0  - exponent                ***** */
    /* *****       R9.1  - E                       ***** */
    /* *****       R7:R8 - number                  ***** */
    /* *****       RA:RB - fractional              ***** */
    /* *****       RC.0  - digit count             ***** */
    /* ************************************************* */
    Asm("ftoa:     ghi      r7           ; save expr stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          lda      rf           ; retrieve number into R7:R8");
    Asm("          plo      r8");
    Asm("          lda      rf");
    Asm("          phi      r8");
    Asm("          lda      rf");
    Asm("          plo      r7");
    Asm("          lda      rf");
    Asm("          phi      r7");
    Asm("          shl                   ; shift sign into DF");
    Asm("          lbnf     ftoa_1       ; jump if number is positive");
    Asm("          ldi      '-'          ; place minus sign into output");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("ftoa_1:   glo      r7           ; get low bit of exponent");
    Asm("          shl                   ; shift into DF");
    Asm("          ghi      r7           ; get high 7 bits of exponent");
    Asm("          shlc                  ; shift in the low bit");
    Asm("          plo      r9           ; store it");
    Asm("          lbnz     ftoa_2       ; jump if exponent is not zero");
    Asm("          ldi      '0'          ; write 0 digit to output");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("ftoa_t:   ldi      0            ; terminate output");
    Asm("          str      rf");
    Asm("          irx                   ; recover expr stack");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          sep      sret         ; and return to caller");
    Asm("ftoa_2:   smi      0ffh         ; check for infinity");
    Asm("          lbnz     ftoa_3       ; jump if not");
    Asm("          ldi      'i'          ; write inf to output");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          ldi      'n'");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          ldi      'f'");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          lbr      ftoa_t       ; terminate string and return");
    Asm("ftoa_3:   ghi      rd           ; save destination pointer");
    Asm("          stxd");
    Asm("          glo      rd");
    Asm("          stxd");
    Asm("          ldi      0            ; clear E");
    Asm("          phi      r9");
    Asm("          glo      r9           ; check exponent for greater than 150");
    Asm("          smi      151");
    Asm("          lbnf     ftoa_4       ; jump if <= 150");
    Asm("          ghi      r7           ; put number on the stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r8");
    Asm("          stxd");
    Asm("          glo      r8");
    Asm("          stxd");
    Asm("ftoa_3a:  glo      r9           ; get exponent");
    Asm("          smi      131          ; looking for below 131");
    Asm("          lbnf     ftoa_3z      ; jump if done scaling");
    Asm("          glo      r2           ; point to number");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          phi      rf");
    Asm("          inc      rf");
    Asm("          ghi      r9           ; get E");
    Asm("          stxd                  ; and save on stack");
    Asm("          ldi      fp_10.1      ; need to divide by 10");
    Asm("          phi      rd");
    Asm("          ldi      fp_10.0");
    Asm("          plo      rd");
    Asm("          sep      scall        ; perform the division");
    Asm("          dw       divfpi");
    Asm("          irx                   ; recover E");
    Asm("          ldx");
    Asm("          adi      1            ; increment E");
    Asm("          phi      r9           ; and put it back");
    Asm("          glo      r2           ; point to new exponent");
    Asm("          adi      3");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      rf");
    Asm("          lda      rf           ; get low bit");
    Asm("          shl                   ; shift into DF");
    Asm("          ldn      rf           ; get high 7 bites");
    Asm("          shlc                  ; shift in the low bit");
    Asm("          plo      r9           ; and store it");
    Asm("          lbr      ftoa_3a      ; loop until exponent in correct range");
    Asm("ftoa_3z:  irx                   ; retrieve the number from the stack");
    Asm("          ldxa");
    Asm("          plo      r8");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("ftoa_4:   glo      r9           ; check exponent for less than 114");
    Asm("          smi      114");
    Asm("          lbdf     ftoa_5       ; jump if > 114");
    Asm("          ghi      r7           ; put number on the stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r8");
    Asm("          stxd");
    Asm("          glo      r8");
    Asm("          stxd");
    Asm("ftoa_4a:  glo      r9           ; get exponent");
    Asm("          smi      127          ; looking for below 127");
    Asm("          lbdf     ftoa_4z      ; jump if done scaling");
    Asm("          glo      r2           ; point to number");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          phi      rf");
    Asm("          inc      rf");
    Asm("          ghi      r9           ; get E");
    Asm("          stxd                  ; and save on stack");
    Asm("          ldi      fp_10.1      ; need to multiply by 10");
    Asm("          phi      rd");
    Asm("          ldi      fp_10.0");
    Asm("          plo      rd");
    Asm("          sep      scall        ; perform the division");
    Asm("          dw       mulfpi");
    Asm("          irx                   ; recover E");
    Asm("          ldx");
    Asm("          smi      1            ; decrement E");
    Asm("          phi      r9           ; and put it back");
    Asm("          glo      r2           ; point to new exponent");
    Asm("          adi      3");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      rf");
    Asm("          lda      rf           ; get low bit");
    Asm("          shl                   ; shift into DF");
    Asm("          ldn      rf           ; get high 7 bites");
    Asm("          shlc                  ; shift in the low bit");
    Asm("          plo      r9           ; and store it");
    Asm("          lbr      ftoa_4a      ; loop until exponent in correct range");
    Asm("ftoa_4z:  irx                   ; retrieve the number from the stack");
    Asm("          ldxa");
    Asm("          plo      r8");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("ftoa_5:   ldi      0            ; clear high byte of number");
    Asm("          phi      r7");
    Asm("          glo      r7           ; set implied 1");
    Asm("          ori      080h");
    Asm("          plo      r7           ; and put it back");
    Asm("          ldi      0            ; clear fractional");
    Asm("          phi      ra");
    Asm("          plo      ra");
    Asm("          phi      rb");
    Asm("          plo      rb");
    Asm("ftoa_6:   glo      r9           ; get exponent");
    Asm("          smi      150          ; check for less than 150");
    Asm("          lbdf     ftoa_7       ; jump if not");
    Asm("          glo      r7           ; shift number right");
    Asm("          shr");
    Asm("          plo      r7");
    Asm("          ghi      r8");
    Asm("          shrc");
    Asm("          phi      r8");
    Asm("          glo      r8");
    Asm("          shrc");
    Asm("          plo      r8");
    Asm("          glo      ra");
    Asm("          shrc");
    Asm("          plo      ra");
    Asm("          ghi      rb");
    Asm("          shrc");
    Asm("          phi      rb");
    Asm("          glo      rb");
    Asm("          shrc");
    Asm("          plo      rb");
    Asm("          glo      r9           ; get exponent");
    Asm("          adi      1            ; increase it");
    Asm("          plo      r9           ; put it back");
    Asm("          lbr      ftoa_6       ; loop back until exponent >= 150");
    Asm("ftoa_7:   glo      r9           ; get exponent");
    Asm("          smi      151          ; check for greater than 150");
    Asm("          lbnf     ftoa_8       ; jump if not");
    Asm("          glo      r8           ; shift number left");
    Asm("          shl");
    Asm("          plo      r8");
    Asm("          ghi      r8");
    Asm("          shlc");
    Asm("          phi      r8");
    Asm("          glo      r7");
    Asm("          shlc");
    Asm("          plo      r7");
    Asm("          ghi      r7");
    Asm("          shlc");
    Asm("          phi      r7");
    Asm("          glo      r9           ; get exponent");
    Asm("          adi      1            ; increment it");
    Asm("          plo      r9           ; and put it back");
    Asm("          lbr      ftoa_7       ; loop until exponent in range");
    Asm("ftoa_8:   irx                   ; recover destination");
    Asm("          ldxa");
    Asm("          plo      rd");
    Asm("          ldx");
    Asm("          phi      rd");
    Asm("          ghi      r7           ; place integer portion on stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r8");
    Asm("          stxd");
    Asm("          glo      r8");
    Asm("          stxd");
    Asm("          glo      r2           ; point source to integer number");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          phi      rf");
    Asm("          inc      rf");
    Asm("          ghi      ra           ; save registers consumed by itoa");
    Asm("          stxd");
    Asm("          glo      ra");
    Asm("          stxd");
    Asm("          ghi      rb");
    Asm("          stxd");
    Asm("          glo      rb");
    Asm("          stxd");
    Asm("          ghi      r9");
    Asm("          stxd");
    Asm("          glo      r9");
    Asm("          stxd");
    Asm("          sep      scall        ; call itoa to convert integer portion of result");
    Asm("          dw       itoa32");
    Asm("          irx                   ; recover consumed registers");
    Asm("          ldxa");
    Asm("          plo      r9");
    Asm("          ldxa");
    Asm("          phi      r9");
    Asm("          ldxa");
    Asm("          plo      rb");
    Asm("          ldxa");
    Asm("          phi      rb");
    Asm("          ldxa");
    Asm("          plo      ra");
    Asm("          ldx");
    Asm("          phi      ra");
    Asm("          irx                   ; remove number from stack");
    Asm("          irx");
    Asm("          irx");
    Asm("          irx");
    Asm("          glo      ra           ; check for nonzero fractional");
    Asm("          lbnz     ftoa_9       ; jump if not zero");
    Asm("          ghi      rb");
    Asm("          lbnz     ftoa_9");
    Asm("          glo      rb");
    Asm("          lbnz     ftoa_9");
    Asm("          lbr      ftoa_e       ; no fractional digits, jump to E processing");
    Asm("ftoa_9:   ghi      r9           ; check if need E");
    Asm("          lbz      ftoa_9c2     ; jump if not");
    Asm("          dec      rd           ; get 2 characters back");
    Asm("          dec      rd");
    Asm("          lda      rd           ; get it");
    Asm("          smi      '1'          ; see if it was 1");
    Asm("          lbnz     ftoa_9c      ; jump if not");
    Asm("          ldn      rd           ; get 2nd number");
    Asm("          plo      re           ; save it");
    Asm("          ldi      '.'          ; replace it with a dot");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          glo      re           ; recover number");
    Asm("          str      rd           ; and store into destination");
    Asm("          inc      rd");
    Asm("          ghi      r9           ; get E");
    Asm("          adi      1            ; increment it");
    Asm("          phi      r9           ; and put it back");
    Asm("          lbr      ftoa_9d      ; then continue");
    Asm("ftoa_9c:  inc      rd           ; put RD back to original position");
    Asm("ftoa_9c2: ldi      '.'          ; need decimal point");
    Asm("          str      rd           ; store into destination");
    Asm("          inc      rd");
    Asm("ftoa_9d:  ldi      6            ; set digit count");
    Asm("          plo      rc");
    Asm("ftoa_9a:  glo      ra           ; check if fractional is still non-zero");
    Asm("          lbnz     ftoa_9b      ; jump if not");
    Asm("          ghi      rb");
    Asm("          lbnz     ftoa_9b");
    Asm("          glo      rb");
    Asm("          lbz      ftoa_e       ; on to E processing if no more fractional bits");
    Asm("ftoa_9b:  glo      rb           ; multiply fractional by 2");
    Asm("          shl");
    Asm("          plo      rb");
    Asm("          plo      r8           ; put copy in R7:R8 as well");
    Asm("          ghi      rb");
    Asm("          shlc");
    Asm("          phi      rb");
    Asm("          phi      r8");
    Asm("          glo      ra");
    Asm("          shlc");
    Asm("          plo      ra");
    Asm("          plo      r7");
    Asm("          ghi      ra");
    Asm("          shlc");
    Asm("          phi      ra");
    Asm("          phi      r7");
    Asm("          glo      r8           ; now multiply R7:R8 by 2");
    Asm("          shl");
    Asm("          plo      r8");
    Asm("          ghi      r8");
    Asm("          shlc");
    Asm("          phi      r8");
    Asm("          glo      r7");
    Asm("          shlc");
    Asm("          plo      r7");
    Asm("          ghi      r7");
    Asm("          shlc");
    Asm("          phi      r7");
    Asm("          glo      r8           ; now multiply R7:R8 by 4");
    Asm("          shl");
    Asm("          plo      r8");
    Asm("          ghi      r8");
    Asm("          shlc");
    Asm("          phi      r8");
    Asm("          glo      r7");
    Asm("          shlc");
    Asm("          plo      r7");
    Asm("          ghi      r7");
    Asm("          shlc");
    Asm("          phi      r7");
    Asm("          glo      rb           ; now add R7:R8 to RA:RB");
    Asm("          str      r2");
    Asm("          glo      r8");
    Asm("          add");
    Asm("          plo      rb");
    Asm("          ghi      rb");
    Asm("          str      r2");
    Asm("          ghi      r8");
    Asm("          adc");
    Asm("          phi      rb");
    Asm("          glo      ra");
    Asm("          str      r2");
    Asm("          glo      r7");
    Asm("          adc");
    Asm("          plo      ra");
    Asm("          ghi      ra");
    Asm("          str      r2");
    Asm("          ghi      r7");
    Asm("          adc");
    Asm("          phi      ra           ; D now has decimal byte");
    Asm("          adi      '0'          ; convert to ASCII");
    Asm("          str      rd           ; and write to destination");
    Asm("          inc      rd");
    Asm("          ldi      0            ; clear high byte of fractional");
    Asm("          phi      ra");
    Asm("          dec      rc           ; increment counter");
    Asm("          glo      rc           ; need to see if done");
    Asm("          lbnz     ftoa_9a      ; loop until done");
    Asm("ftoa_e:   ghi      r9           ; need to check for E");
    Asm("          lbz      ftoa_dn      ; jump if no E needed");
    Asm("          ldi      'E'          ; write E to output");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          ghi      r9           ; see if E was negative");
    Asm("          shl");
    Asm("          lbnf     ftoa_ep      ; jump if not");
    Asm("          ldi      '-'          ; write minus sign to output");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          ghi      r9           ; then 2s compliment E");
    Asm("          xri      0ffh");
    Asm("          adi      1");
    Asm("          phi      r9           ; and put it back");
    Asm("          lbr      ftoa_e1      ; then continue");
    Asm("ftoa_ep:  ldi      '+'          ; write plus to output");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("ftoa_e1:  ldi      0            ; place E as 32-bits onto stack");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          ghi      r9");
    Asm("          stxd");
    Asm("          glo      r2           ; point rf to number");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          phi      rf");
    Asm("          inc      rf");
    Asm("          sep      scall        ; call itoa to display E");
    Asm("          dw       itoa32");
    Asm("          irx                   ; remove number from stack");
    Asm("          irx");
    Asm("          irx");
    Asm("          irx");
    Asm("ftoa_dn:  ldi      0            ; terminate string");
    Asm("          str      rd");
    Asm("          irx                   ; recover expr stack");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          sep      sret         ; and return to caller");
    }

  if (useTrig) {
    Asm("fact:     db       000h, 000h, 000h, 000h");
    Asm("          db       000h, 000h, 080h, 03fh");
    Asm("          db       000h, 000h, 000h, 040h");
    Asm("          db       000h, 000h, 0c0h, 040h");
    Asm("          db       000h, 000h, 0c0h, 041h");
    Asm("          db       000h, 000h, 0f0h, 042h");
    Asm("          db       000h, 000h, 034h, 044h");
    Asm("          db       000h, 080h, 09dh, 045h");
    Asm("          db       000h, 080h, 01dh, 047h");
    Asm("          db       000h, 030h, 0b1h, 048h");
    Asm("          db       000h, 07ch, 05dh, 04ah");
    Asm("          db       040h, 045h, 018h, 04ch");
    Asm("          db       0e0h, 067h, 0e4h, 04dh");
    Asm("          db       066h, 094h, 0b9h, 04fh");
    Asm("          db       0d9h, 061h, 0a2h, 051h");
    Asm("          db       0bbh, 03bh, 098h, 053h");
    Asm("          db       0bbh, 03bh, 098h, 055h");
    Asm("          db       077h, 0bfh, 0a1h, 057h");
    Asm("          db       066h, 0f7h, 0b5h, 059h");
    Asm("          db       0c9h, 015h, 0d8h, 05bh");
    Asm("          db       09eh, 00dh, 007h, 05eh");
    Asm("          db       0dfh, 041h, 031h, 060h");
    Asm("          db       093h, 0bah, 073h, 062h");
    Asm("          db       01ah, 02eh, 0afh, 064h");
    Asm("          db       094h, 062h, 003h, 067h");
    Asm("          db       007h, 04ah, 04dh, 069h");
    Asm("          db       026h, 0cch, 0a6h, 06bh");
    Asm("          db       040h, 0bch, 00ch, 06eh");
    Asm("          db       070h, 049h, 076h, 070h");
    Asm("          db       08eh, 032h, 0dfh, 072h");
    Asm("          db       065h, 03fh, 051h, 075h");
    Asm("          db       06ah, 0b5h, 0cah, 077h");
    Asm("          db       06ah, 0b5h, 04ah, 07ah");
    Asm("          db       015h, 00bh, 0d1h, 07ch");
    Asm("          db       0c6h, 01bh, 05eh, 07fh");

    Asm("addtows:  irx                   ; retrieve return address");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldx");
    Asm("          plo      r8");
    Asm("          inc      rd           ; move to msb");
    Asm("          inc      rd");
    Asm("          inc      rd");
    Asm("          ldn      rd           ; retrieve");
    Asm("          stxd                  ; and place on stack");
    Asm("          dec      rd");
    Asm("          ldn      rd           ; retrieve next byte");
    Asm("          stxd                  ; and place on stack");
    Asm("          dec      rd");
    Asm("          ldn      rd           ; retrieve next byte");
    Asm("          stxd                  ; and place on stack");
    Asm("          dec      rd");
    Asm("          ldn      rd           ; retrieve next byte");
    Asm("          stxd                  ; and place on stack");
    Asm("          glo      r8           ; put return address back on stack");
    Asm("          stxd");
    Asm("          ghi      r8");
    Asm("          stxd");
    Asm("          sep      sret         ; return to caller");

    Asm("fpcopy:   lda      rd           ; copy source to destination");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          sep      sret         ; return to caller");

    Asm("getargs:  lda      r6           ; get passed argument");
    Asm("          str      r2           ; store for add");
    Asm("          glo      r2           ; add stack offset");
    Asm("          add");
    Asm("          plo      rf           ; put into first argument");
    Asm("          ghi      r2           ; high of stack");
    Asm("          adci     0            ; propagate carry");
    Asm("          phi      rf           ; rf now has argument address");
    Asm("          inc      rf           ; remove last call offset");
    Asm("          inc      rf");
    Asm("          lda      r6           ; get passed argument");
    Asm("          str      r2           ; store for add");
    Asm("          glo      r2           ; add stack offset");
    Asm("          add");
    Asm("          plo      rd           ; put into second argument");
    Asm("          ghi      r2           ; high of stack");
    Asm("          adci     0            ; propagate carry");
    Asm("          phi      rd           ; rd now has argument address");
    Asm("          inc      rd           ; remove last call offset");
    Asm("          inc      rd");
    Asm("          sep      sret         ; return to caller");
    }

  if (useSin) {
    /* ****************************************************** */
    /* ***** sin                                        ***** */
    /* ***** RF - Pointer to floating point number      ***** */
    /* ***** RD - Pointer to floating point destination ***** */
    /* ***** internal:                                  ***** */
    /* *****       R2+1  R7 - sum                       ***** */
    /* *****       R2+5  R8 - pwr                       ***** */
    /* *****       R2+9  R9 - last                      ***** */
    /* *****       R2+13 RA - fctPos                    ***** */
    /* *****       R2+17 RB - fct                       ***** */
    /* *****       R2+21 RC - tmp                       ***** */
    /* *****       R2+25 RD - sgn                       ***** */
    /* *****       R2+29    - angle                     ***** */
    /* ****************************************************** */
    Asm("fpsin:    ghi      r7           ; save expr stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r7           ; source is expr stack");
    Asm("          phi      rf");
    Asm("          glo      r7");
    Asm("          plo      rf");
    Asm("          inc      rf");
    Asm("          ghi      rf           ; angle = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          ldi      0            ; sign starts out positive");
    Asm("          stxd                  ; make space for sgn");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd                  ; make space for tmp");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd                  ; make space for fct");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd                  ; make space for fctPos");
    Asm("          stxd");
    Asm("          ldi      fact+12.1    ; position of 3!");
    Asm("          stxd");
    Asm("          ldi      fact+12.0");
    Asm("          stxd");
    Asm("          ldi      0");
    Asm("          stxd                  ; make space for last");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          ghi      rf           ; pwr = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          ghi      rf           ; sum = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("sincos:   sep      scall        ; angle = angle * angle");
    Asm("          dw       getargs");
    Asm("          db       29,29");
    Asm("          sep      scall        ; angle = angle * angle");
    Asm("          dw       mulfpi");
    Asm("sincos_l: sep      scall        ; need to see if sum == last");
    Asm("          dw       getargs");
    Asm("          db       9,1");
    Asm("          ldi      4            ; 4 bytes to check");
    Asm("          plo      rc");
    Asm("          ldi      0            ; clear comparison flag");
    Asm("          plo      re");
    Asm("sincos_1: ldn      rd           ; get byte from sum");
    Asm("          str      r2           ; save for comparison");
    Asm("          ldn      rf           ; get point from last");
    Asm("          sm                    ; compare them");
    Asm("          str      r2           ; store to combine with comparison flag");
    Asm("          glo      re           ; get comparison flag");
    Asm("          or                    ; combine");
    Asm("          plo      re           ; put back into comparison");
    Asm("          ldn      rd           ; get byte from sum");
    Asm("          str      rf           ; store into last");
    Asm("          inc      rd           ; increment pointers");
    Asm("          inc      rf");
    Asm("          dec      rc           ; decrement count");
    Asm("          glo      rc           ; see if done");
    Asm("          lbnz     sincos_1     ; jump if not");
    Asm("          glo      re           ; get comparison flag");
    Asm("          lbz      sincos_d     ; jump if done");
    Asm("          sep      scall        ; pwr = pwr * angle");
    Asm("          dw       getargs");
    Asm("          db       5,29");
    Asm("          sep      scall");
    Asm("          dw       mulfpi");
    Asm("          sep      scall        ; fct = facts[fctPos]");
    Asm("          dw       getargs");
    Asm("          db       17,13");
    Asm("          ldn      rd           ; get address of facts[fctPos]");
    Asm("          plo      r7");
    Asm("          adi      8            ; and then point two constants up");
    Asm("          str      rd");
    Asm("          inc      rd");
    Asm("          ldn      rd           ; get high byte of address");
    Asm("          phi      r7");
    Asm("          adci     0");
    Asm("          str      rd           ; fctPos now points at next one needed");
    Asm("          lda      r7           ; read factorial into destination");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      r7");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      r7");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          glo      r2           ; point to sgn");
    Asm("          adi      25");
    Asm("          plo      rd");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      rd");
    Asm("          ldn      rd           ; get sign");
    Asm("          xri      080h         ; flip it");
    Asm("          str      rd           ; and put it back");
    Asm("          str      r2           ; store to combine with fct");
    Asm("          lda      r7");
    Asm("          or                    ; set sign");
    Asm("          str      rf");
    Asm("          sep      scall        ; tmp = pwr");
    Asm("          dw       getargs");
    Asm("          db       21,5");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm(";          sep      scall        ; tmp = tmp * pwr");
    Asm(";          dw       getargs");
    Asm(";          db       21,29");
    Asm(";          sep      scall");
    Asm(";          dw       fpmul");
    Asm("          sep      scall        ; tmp = tmp / fct");
    Asm("          dw       getargs");
    Asm("          db       21,17");
    Asm("          sep      scall");
    Asm("          dw       divfpi");
    Asm("          sep      scall        ; sum = sum + tmp");
    Asm("          dw       getargs");
    Asm("          db       1,21");
    Asm("          sep      scall");
    Asm("          dw       addfpi");
    Asm("          lbr      sincos_l     ; loop until done");
    Asm("sincos_d: irx                   ; recover answer");
    Asm("          ldxa");
    Asm("          plo      r8");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldxa");
    Asm("          plo      ra");
    Asm("          ldx");
    Asm("          phi      ra");
    Asm("          glo      r2           ; clean workspace off stack");
    Asm("          adi      28");
    Asm("          plo      r2");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      r2");
    Asm("          irx                   ; recover expr stack");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          inc      r7");
    Asm("          glo      r8           ; store answer");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      r8");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          glo      ra");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      ra");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          sep      sret         ; and return to caller");
    }

  if (useCos) {
    /* ****************************************************** */
    /* ***** cos                                        ***** */
    /* ***** RF - Pointer to floating point number      ***** */
    /* ***** RD - Pointer to floating point destination ***** */
    /* ***** internal:                                  ***** */
    /* *****       R2+1  R7 - sum                       ***** */
    /* *****       R2+5  R8 - pwr                       ***** */
    /* *****       R2+9  R9 - last                      ***** */
    /* *****       R2+13 RA - fctPos                    ***** */
    /* *****       R2+17 RB - fct                       ***** */
    /* *****       R2+21 RC - tmp                       ***** */
    /* *****       R2+25 RD - sgn                       ***** */
    /* *****       R2+29    - angle                     ***** */
    /* ****************************************************** */
    Asm("fpcos:    ghi      r7           ; save expr stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r7           ; source is expr stack");
    Asm("          phi      rf");
    Asm("          glo      r7");
    Asm("          plo      rf");
    Asm("          inc      rf");
    Asm("          ghi      rf           ; angle = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          ldi      0            ; sign starts out positive");
    Asm("          stxd                  ; make space for sgn");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd                  ; make space for tmp");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd                  ; make space for fct");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd                  ; make space for fctPos");
    Asm("          stxd");
    Asm("          ldi      fact+8.1     ; position of 2!");
    Asm("          stxd");
    Asm("          ldi      fact+8.0");
    Asm("          stxd");
    Asm("          ldi      0");
    Asm("          stxd                  ; make space for last");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          ldi      fp_1.1       ; pwr = 1.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          ldi      fp_1.1       ; pwr = 1.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          lbr      sincos       ; now compute");
    }

  if (useTan) {
    /* ****************************************************** */
    /* ***** tan                                        ***** */
    /* ***** RF - Pointer to floating point number      ***** */
    /* ***** RD - Pointer to floating point destination ***** */
    /* ***** internal:                                  ***** */
    /* *****       R2+1     - s                         ***** */
    /* *****       R2+5     - c                         ***** */
    /* ****************************************************** */
    Asm("fptan:    ghi      r7           ; save expr stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r7           ; source is expr stack");
    Asm("          phi      rf");
    Asm("          glo      r7");
    Asm("          plo      rf");
    Asm("          inc      rf");
    Asm("          ghi      rf           ; s = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          ghi      rf           ; c = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          glo      r2           ; setup for computing sin");
    Asm("          plo      r7");
    Asm("          ghi      r2");
    Asm("          phi      r7");
    Asm("          sep      scall        ; compute sin");
    Asm("          dw       fpsin");
    Asm("          glo      r2           ; setup to compute cos");
    Asm("          adi      4");
    Asm("          plo      r7");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      r7");
    Asm("          sep      scall        ; compute cos");
    Asm("          dw       fpcos");
    Asm("          sep      scall        ; get arguments for division");
    Asm("          dw       getargs");
    Asm("          db       1,5");
    Asm("          sep      scall        ; s = s / c");
    Asm("          dw       divfpi");
    Asm("          irx                   ; recover answer");
    Asm("          ldxa");
    Asm("          plo      r8");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldxa");
    Asm("          plo      ra");
    Asm("          ldxa");
    Asm("          phi      ra");
    Asm("          irx                   ; move past c");
    Asm("          irx");
    Asm("          irx");
    Asm("          irx                   ; recover expr stack");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          inc      r7");
    Asm("          glo      r8           ; store answer");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      r8");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          glo      ra");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      ra");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          sep      sret         ; and return to caller");
    }

  if (useLn) {
    /* ****************************************************** */
    /* ***** Natural logarithm                          ***** */
    /* ***** RF - Pointer to floating point number      ***** */
    /* ***** RD - Pointer to floating point destination ***** */
    /* ***** internal:                                  ***** */
    /* *****       R2+1     - sum                       ***** */
    /* *****       R2+5     - last                      ***** */
    /* *****       R2+9     - k                         ***** */
    /* *****       R2+13    - pwr                       ***** */
    /* *****       R2+17    - tmp                       ***** */
    /* *****       R2+21    - n                         ***** */
    /* ****************************************************** */
    Asm("fpln:     ghi      r7           ; save expr stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r7           ; source is expr stack");
    Asm("          phi      rf");
    Asm("          glo      r7");
    Asm("          plo      rf");
    Asm("          inc      rf");
    Asm("          ghi      rf           ; n = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ghi      rf           ; tmp = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          stxd                  ; reserve space for pwr");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          ldi      fp_1.1       ; k = 1.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          ldi      fp_1.1       ; last = 1.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall        ; add to workspace");
    Asm("          dw       addtows");
    Asm("          ldi      0            ; sum = 0");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          glo      r2           ; point to tmp");
    Asm("          adi      17");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      rf");
    Asm("          ldi      fp_1.1       ; point to 1.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall        ; compute n+1");
    Asm("          dw       addfpi");
    Asm("          glo      r2           ; point to n");
    Asm("          adi      21");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      rf");
    Asm("          ldi      fp_1.1       ; point to 1.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall        ; compute n-1");
    Asm("          dw       subfpi");
    Asm("          sep      scall        ; compute (n-1)/(n+1)");
    Asm("          dw       getargs");
    Asm("          db       21,17");
    Asm("          sep      scall");
    Asm("          dw       divfpi");
    Asm("          sep      scall        ; pwr = n");
    Asm("          dw       getargs");
    Asm("          db       13,21");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          sep      scall        ; n = n * n");
    Asm("          dw       getargs");
    Asm("          db       21,21");
    Asm("          sep      scall");
    Asm("          dw       mulfpi");
    Asm("fplog_l:  sep      scall        ; need to see if sum == last");
    Asm("          dw       getargs");
    Asm("          db       5,1");
    Asm("          ldi      4            ; 4 bytes to check");
    Asm("          plo      rc");
    Asm("          ldi      0            ; clear comparison flag");
    Asm("          plo      re");
    Asm("fplog_1:  ldn      rd           ; get byte from sum");
    Asm("          str      r2           ; save for comparison");
    Asm("          ldn      rf           ; get point from last");
    Asm("          sm                    ; compare them");
    Asm("          str      r2           ; store to combine with comparison flag");
    Asm("          glo      re           ; get comparison flag");
    Asm("          or                    ; combine");
    Asm("          plo      re           ; put back into comparison");
    Asm("          ldn      rd           ; get byte from sum");
    Asm("          str      rf           ; store into last");
    Asm("          inc      rd           ; increment pointers");
    Asm("          inc      rf");
    Asm("          dec      rc           ; decrement count");
    Asm("          glo      rc           ; see if done");
    Asm("          lbnz     fplog_1      ; jump if not");
    Asm("          glo      re           ; get comparison flag");
    Asm("          lbz      fplog_d      ; jump if done");
    Asm("          sep      scall        ; tmp = pwr");
    Asm("          dw       getargs");
    Asm("          db       17,13");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          sep      scall        ; tmp = tmp / k");
    Asm("          dw       getargs");
    Asm("          db       17,9");
    Asm("          sep      scall");
    Asm("          dw       divfpi");
    Asm("          sep      scall        ; sum = sum + tmp");
    Asm("          dw       getargs");
    Asm("          db       1,17");
    Asm("          sep      scall");
    Asm("          dw       addfpi");
    Asm("          sep      scall        ; pwr = pwr * n");
    Asm("          dw       getargs");
    Asm("          db       13,21");
    Asm("          sep      scall");
    Asm("          dw       mulfpi");
    Asm("          glo      r2           ; k = k + 2");
    Asm("          adi      9");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      rf");
    Asm("          ldi      fp_2.1       ; point to 2.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_2.0");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addfpi");
    Asm("          lbr      fplog_l      ; loop until done");
    Asm("fplog_d:  sep      scall        ; sum = sum + sum");
    Asm("          dw       getargs");
    Asm("          db       1,1");
    Asm("          sep      scall");
    Asm("          dw       addfpi");
    Asm("          irx                   ; recover answer");
    Asm("          ldxa    ");
    Asm("          plo      r8");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldxa");
    Asm("          plo      ra");
    Asm("          ldx");
    Asm("          phi      ra");
    Asm("          glo      r2           ; clean up the stack");
    Asm("          adi      20");
    Asm("          plo      r2");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      r2");
    Asm("          irx                   ; recover expr stack");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          inc      r7");
    Asm("          glo      r8           ; store answer");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      r8");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          glo      ra");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      ra");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          sep      sret         ; and return to caller");
    }

  if (useExp) {
    /* ****************************************************** */
    /* ***** Natural exp                                ***** */
    /* ***** RF - Pointer to floating point number      ***** */
    /* ***** RD - Pointer to floating point destination ***** */
    /* ***** internal:                                  ***** */
    /* *****       R2+1     - sum                       ***** */
    /* *****       R2+5     - last                      ***** */
    /* *****       R2+9     - fct                       ***** */
    /* *****       R2+13    - fctCount                  ***** */
    /* *****       R2+17    - pwr                       ***** */
    /* *****       R2+21    - tmp                       ***** */
    /* *****       R2+25    - n                         ***** */
    /* ****************************************************** */
    Asm("fpexp:    ghi      r7           ; save expr stack");
    Asm("          stxd");
    Asm("          glo      r7");
    Asm("          stxd");
    Asm("          ghi      r7           ; source is expr stack");
    Asm("          phi      rf");
    Asm("          glo      r7");
    Asm("          plo      rf");
    Asm("          inc      rf");
    Asm("          ghi      rf           ; n = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          stxd                  ; space for tmp");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          stxd");
    Asm("          ghi      rf           ; pwr = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ldi      fp_2.1       ; fctCount = 2.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_2.0");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ldi      fp_1.1       ; fct = 1.0");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ldi      fp_0.1       ; last = 0");
    Asm("          phi      rd");
    Asm("          ldi      fp_0.0");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ghi      rf           ; sum = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ghi      r2           ; sum = sum + 1");
    Asm("          phi      rf");
    Asm("          glo      r2");
    Asm("          plo      rf");
    Asm("          inc      rf");
    Asm("          ldi      fp_1.1");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addfpi");
    Asm("fpexp_l:  sep      scall        ; need to see if sum == last");
    Asm("          dw       getargs");
    Asm("          db       5,1");
    Asm("          ldi      4            ; 4 bytes to check");
    Asm("          plo      rc");
    Asm("          ldi      0            ; clear comparison flag");
    Asm("          plo      re");
    Asm("fpexp_1:  ldn      rd           ; get byte from sum");
    Asm("          str      r2           ; save for comparison");
    Asm("          ldn      rf           ; get point from last");
    Asm("          sm                    ; compare them");
    Asm("          str      r2           ; store to combine with comparison flag");
    Asm("          glo      re           ; get comparison flag");
    Asm("          or                    ; combine");
    Asm("          plo      re           ; put back into comparison");
    Asm("          ldn      rd           ; get byte from sum");
    Asm("          str      rf           ; store into last");
    Asm("          inc      rd           ; increment pointers");
    Asm("          inc      rf");
    Asm("          dec      rc           ; decrement count");
    Asm("          glo      rc           ; see if done");
    Asm("          lbnz     fpexp_1      ; jump if not");
    Asm("          glo      re           ; get comparison flag");
    Asm("          lbz      fpexp_d      ; jump if done");
    Asm("          sep      scall        ; pwr = pwr * n");
    Asm("          dw       getargs");
    Asm("          db       17,25");
    Asm("          sep      scall");
    Asm("          dw       mulfpi");
    Asm("          sep      scall        ; fct = fct * fctCount");
    Asm("          dw       getargs");
    Asm("          db       9,13");
    Asm("          sep      scall");
    Asm("          dw       mulfpi");
    Asm("          glo      r2           ; fctCount = fctCount + 1");
    Asm("          adi      13");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      rf");
    Asm("          ldi      fp_1.1");
    Asm("          phi      rd");
    Asm("          ldi      fp_1.0");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addfpi");
    Asm("          sep      scall        ; tmp = pwr");
    Asm("          dw       getargs");
    Asm("          db       21,17");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          inc      rf");
    Asm("          lda      rd");
    Asm("          str      rf");
    Asm("          sep      scall        ; tmp = tmp / fct");
    Asm("          dw       getargs");
    Asm("          db       21,9");
    Asm("          sep      scall");
    Asm("          dw       divfpi");
    Asm("          sep      scall        ; sum = sum + tmp");
    Asm("          dw       getargs");
    Asm("          db       1,21");
    Asm("          sep      scall");
    Asm("          dw       addfpi");
    Asm("          lbr      fpexp_l      ; loop until done");
    Asm("fpexp_d:  irx                   ; recover answer");
    Asm("          ldxa");
    Asm("          plo      r8");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldxa");
    Asm("          plo      ra");
    Asm("          ldx");
    Asm("          phi      ra");
    Asm("          glo      r2           ; clean workspace off stack");
    Asm("          adi      24");
    Asm("          plo      r2");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      r2");
    Asm("          irx                   ; recover expr stack");
    Asm("          ldxa");
    Asm("          plo      r7");
    Asm("          ldx");
    Asm("          phi      r7");
    Asm("          inc      r7");
    Asm("          glo      r8           ; store answer");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      r8");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          glo      ra");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      ra");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          sep      sret         ; and return to caller");
    }

  if (usePow) {
    /* ****************************************************** */
    /* ***** Power x^y                                  ***** */
    /* ***** RF - Pointer to floating point number x    ***** */
    /* ***** RC - Pointer to floating point number y    ***** */
    /* ***** RD - Pointer to floating point destination ***** */
    /* ***** internal:                                  ***** */
    /* *****       R2+1     - x                         ***** */
    /* *****       R2+5     - y                         ***** */
    /* ****************************************************** */
    Asm("fppow:    inc      r7           ; x = log(x)");
    Asm("          inc      r7");
    Asm("          inc      r7");
    Asm("          inc      r7");
    Asm("          sep      scall");
    Asm("          dw       fpln");
    Asm("          dec      r7           ; now x = x * y");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          sep      scall");
    Asm("          dw       mulfp");
    Asm("          sep      scall        ; x = exp(x)");
    Asm("          dw       fpexp");
    Asm("          sep      sret         ; and return to caller");
    }

  if (useSqrt) {
    /* ****************************************************** */
    /* ***** Square root                                ***** */
    /* ***** RF - Pointer to floating point number x    ***** */
    /* *****       R2+1     - x                         ***** */
    /* *****       R2+5     - s                         ***** */
    /* *****       R2+9     - p                         ***** */
    /* *****       R2+13    - arg                       ***** */
    /* ****************************************************** */
    Asm("fpsqrt:   ghi      r7           ; argument is on expr stack");
    Asm("          phi      rf");
    Asm("          glo      r7");
    Asm("          plo      rf");
    Asm("          inc      rf");
    Asm("          ghi      rf           ; arg = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ghi      rf           ; p = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ghi      rf           ; s = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ghi      rf           ; x = argument");
    Asm("          phi      rd");
    Asm("          glo      rf");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       addtows");
    Asm("          ldi      255          ; set max iteration count");
    Asm("          plo      rc");
    Asm("fpsqrtlp: sep      scall        ; x = arg");
    Asm("          dw       getargs");
    Asm("          db       1,13");
    Asm("          sep      scall");
    Asm("          dw       fpcopy");
    Asm("          glo      rc           ; save iteration count");
    Asm("          stxd");
    Asm("          sep      scall        ; x = x / s");
    Asm("          dw       getargs");
    Asm("          db       2,6");
    Asm("          sep      scall");
    Asm("          dw       divfpi");
    Asm("          sep      scall        ; s = s + x");
    Asm("          dw       getargs");
    Asm("          db       6,2");
    Asm("          sep      scall");
    Asm("          dw       addfpi");
    Asm("          glo      r2           ; s = s * 0.5");
    Asm("          adi      6");
    Asm("          plo      rf");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      rf");
    Asm("          ldi      fpdot5.1");
    Asm("          phi      rd");
    Asm("          ldi      fpdot5.0");
    Asm("          plo      rd");
    Asm("          sep      scall");
    Asm("          dw       mulfpi");
    Asm("          irx                   ; recover iteration count");
    Asm("          ldx");
    Asm("          plo      rc");
    Asm("          sep      scall        ; check p=s");
    Asm("          dw       getargs");
    Asm("          db       9,5");
    Asm("          lda      rf");
    Asm("          ani      0fch");
    Asm("          str      r2");
    Asm("          lda      rd");
    Asm("          ani      0fch");
    Asm("          sm");
    Asm("          lbnz     fpsqrtn");
    Asm("          lda      rf");
    Asm("          str      r2");
    Asm("          lda      rd");
    Asm("          sm");
    Asm("          lbnz     fpsqrtn");
    Asm("          lda      rf");
    Asm("          str      r2");
    Asm("          lda      rd");
    Asm("          sm");
    Asm("          lbnz     fpsqrtn");
    Asm("          lda      rf");
    Asm("          str      r2");
    Asm("          lda      rd");
    Asm("          sm");
    Asm("          lbz      fpsqrtd");
    Asm("fpsqrtn:  dec      rc           ; decrement iteration count");
    Asm("          glo      rc");
    Asm("          lbz      fpsqrtd      ; jump if reached");
    Asm("          sep      scall        ; p = s");
    Asm("          dw       getargs");
    Asm("          db       9,5");
    Asm("          sep      scall");
    Asm("          dw       fpcopy");
    Asm("          lbr      fpsqrtlp     ; loop until convergence");
    Asm("fpsqrtd:  irx                   ; retrieve answer");
    Asm("          irx");
    Asm("          irx");
    Asm("          irx");
    Asm("          irx");
    Asm("          ldxa");
    Asm("          plo      r8");
    Asm("          ldxa");
    Asm("          phi      r8");
    Asm("          ldxa");
    Asm("          plo      r9");
    Asm("          ldx");
    Asm("          phi      r9");
    Asm("          glo      r2           ; remove remaining workspace");
    Asm("          adi      8");
    Asm("          plo      r2");
    Asm("          ghi      r2");
    Asm("          adci     0");
    Asm("          phi      r2");
    Asm("          inc      r7");
    Asm("          glo      r8           ; store answer");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      r8");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          glo      r9");
    Asm("          str      r7");
    Asm("          inc      r7");
    Asm("          ghi      r9");
    Asm("          str      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          dec      r7");
    Asm("          sep      sret         ; and return to caller");
    }

  if (useAtan) {
    /* ****************************************************** */
    /* ***** Compute arctangent                         ***** */
    /* ***** internal:                                  ***** */
    /* *****       R2+1     - ret                       ***** */
    /* *****       R2+5     - total                     ***** */
    /* *****       R2+9     - ydx                       ***** */
    /* *****       R2+13    - tmp                       ***** */
    /* ****************************************************** */
    Asm("atandata:  db      0abh,0aah,0aah,0beh"); //-1/3");
    Asm("           db      0cdh,0cch,04ch,03eh"); // 1/5");
    Asm("           db      025h,049h,012h,0beh"); //-1/7");
    Asm("           db      039h,08eh,0e3h,03dh"); // 1/9");
    Asm("           db      08ch,02eh,0bah,0bdh"); //-1/11");
    Asm("           db      0d9h,089h,09dh,03dh"); // 1/13");
    Asm("           db      089h,088h,088h,0bdh"); //-1/15");
    Asm("           db      0f1h,0f0h,070h,03dh"); // 1/17");
    Asm("           db      036h,094h,057h,0bdh"); //-1/19");
    Asm("           db      031h,00ch,043h,03dh"); // 1/21");
    Asm("fpatan:    inc     r7           ; retrieve x");
    Asm("           lda     r7");
    Asm("           plo     r8");
    Asm("           lda     r7");
    Asm("           phi     r8");
    Asm("           lda     r7");
    Asm("           plo     r9");
    Asm("           ldn     r7");
    Asm("           phi     r9");
    Asm("           dec     r7           ; keep x on the expr stack");
    Asm("           dec     r7");
    Asm("           dec     r7");
    Asm("           dec     r7");
    Asm("           sex     r7           ; Put x back on the stack twice");
    Asm("           ghi     r9");
    Asm("           stxd");
    Asm("           glo     r9");
    Asm("           stxd");
    Asm("           ghi     r8");
    Asm("           stxd");
    Asm("           glo     r8");
    Asm("           stxd");
    Asm("           ghi     r9");
    Asm("           stxd");
    Asm("           glo     r9");
    Asm("           stxd");
    Asm("           ghi     r8");
    Asm("           stxd");
    Asm("           glo     r8");
    Asm("           stxd");
    Asm("           sex     r2");
    Asm("           sep     scall        ; x*x");
    Asm("           dw      mulfp");
    Asm("           sex     r7           ; now add 1.0");
    Asm("           ldi     03fh");
    Asm("           stxd");
    Asm("           ldi     080h");
    Asm("           stxd");
    Asm("           ldi     000h");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           sex     r2");
    Asm("           sep     scall");
    Asm("           dw      addfp");
    Asm("           sep     scall        ; now sqrt");
    Asm("           dw      fpsqrt");
    Asm("           sex     r7           ; now add 1.0");
    Asm("           ldi     03fh");
    Asm("           stxd");
    Asm("           ldi     080h");
    Asm("           stxd");
    Asm("           ldi     000h");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           sex     r2");
    Asm("           sep     scall");
    Asm("           dw      addfp");
    Asm("           sep     scall       ; now have x/(1+sqrt(1+x*X))");
    Asm("           dw      divfp");
    Asm("           ghi      r7           ; save expr stack");
    Asm("           stxd");
    Asm("           glo      r7");
    Asm("           stxd");
    Asm("           stxd                  ; space on stack for tmp");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           ghi      r7           ; source is expr stack");
    Asm("           phi      rf");
    Asm("           glo      r7");
    Asm("           plo      rf");
    Asm("           inc      rf");
    Asm("           ghi      rf           ; ydx = argument");
    Asm("           phi      rd");
    Asm("           glo      rf");
    Asm("           plo      rd");
    Asm("           sep      scall        ; add to workspace");
    Asm("           dw       addtows");
    Asm("           ghi      rf           ; total = argument");
    Asm("           phi      rd");
    Asm("           glo      rf");
    Asm("           plo      rd");
    Asm("           sep      scall        ; add to workspace");
    Asm("           dw       addtows");
    Asm("           ghi      rf           ; ret = argument");
    Asm("           phi      rd");
    Asm("           glo      rf");
    Asm("           plo      rd");
    Asm("           sep      scall        ; add to workspace");
    Asm("           dw       addtows");
    Asm("           sep      scall        ; ydx = ydx * ydx");
    Asm("           dw       getargs");
    Asm("           db       9,9");
    Asm("           sep      scall");
    Asm("           dw       mulfpi");
    Asm("           ldi      atandata.1   ; point to -1/3");
    Asm("           phi      r9");
    Asm("           ldi      atandata.0");
    Asm("           plo      r9");
    Asm("           ldi      10           ; 10 loops");
    Asm("           plo      rc");
    Asm("atanlp:    sep      scall        ; total *= ydx");
    Asm("           dw       getargs");
    Asm("           db       5,9");
    Asm("           glo      rc           ; save needed registers");
    Asm("           stxd");
    Asm("           ghi      r9           ; save needed registers");
    Asm("           stxd");
    Asm("           glo      r9");
    Asm("           stxd");
    Asm("           sep      scall");
    Asm("           dw       mulfpi");
    Asm("           sep      scall        ; tmp = total");
    Asm("           dw       getargs");
    Asm("           db       16,8");
    Asm("           sep      scall");
    Asm("           dw       fpcopy");
    Asm("           irx                   ; tmp = tmp * fractional");
    Asm("           ldxa");
    Asm("           plo      rd");
    Asm("           ldx");
    Asm("           phi      rd");
    Asm("           dec      r2");
    Asm("           glo      r2");
    Asm("           adi      15");
    Asm("           plo      rf");
    Asm("           ghi      r2");
    Asm("           adci     0");
    Asm("           phi      rf");
    Asm("           dec      r2");
    Asm("           sep      scall");
    Asm("           dw       mulfpi");
    Asm("           sep      scall        ; ret = ret + tmp");
    Asm("           dw       getargs");
    Asm("           db       4,16");
    Asm("           sep      scall");
    Asm("           dw       addfpi");
    Asm("           irx                   ; recover registers");
    Asm("           ldxa");
    Asm("           plo      r9");
    Asm("           ldxa");
    Asm("           phi      r9");
    Asm("           ldx");
    Asm("           plo      rc");
    Asm("           inc      r9           ; move to next fractional");
    Asm("           inc      r9");
    Asm("           inc      r9");
    Asm("           inc      r9");
    Asm("           dec      rc           ; decrement loop count");
    Asm("           glo      rc           ; get remaining loops");
    Asm("           lbnz     atanlp       ; jump if more loops");
    Asm("           sep      scall        ; ret = ret + ret");
    Asm("           dw       getargs");
    Asm("           db       1,1");
    Asm("           sep      scall");
    Asm("           dw       addfpi");
    Asm("           irx                   ; recover answer");
    Asm("           ldxa");
    Asm("           plo      r8");
    Asm("           ldxa");
    Asm("           phi      r8");
    Asm("           ldxa");
    Asm("           plo      r9");
    Asm("           ldx");
    Asm("           phi      r9");
    Asm("           glo      r2           ; remove remaining workspace from stack");
    Asm("           adi      12");
    Asm("           plo      r2");
    Asm("           ghi      r2");
    Asm("           adci     0");
    Asm("           phi      r2");
    Asm("           irx                   ; recover expr stack");
    Asm("           ldxa");
    Asm("           plo      r7");
    Asm("           ldx");
    Asm("           phi      r7");
    Asm("           inc      r7");
    Asm("           glo      r8           ; store answer");
    Asm("           str      r7");
    Asm("           inc      r7");
    Asm("           ghi      r8");
    Asm("           str      r7");
    Asm("           inc      r7");
    Asm("           glo      r9");
    Asm("           str      r7");
    Asm("           inc      r7");
    Asm("           ghi      r9");
    Asm("           str      r7");
    Asm("           dec      r7");
    Asm("           dec      r7");
    Asm("           dec      r7");
    Asm("           dec      r7");
    Asm("           sep      sret         ; and return to caller");
    }

  if (useAsin) {
    /* ****************************************************** */
    /* ***** Compute arcsin                             ***** */
    /* ****************************************************** */
    Asm("fpasin:    inc     r7           ; retrieve x");
    Asm("           lda     r7");
    Asm("           plo     r8");
    Asm("           lda     r7");
    Asm("           phi     r8");
    Asm("           lda     r7");
    Asm("           plo     r9");
    Asm("           ldn     r7");
    Asm("           phi     r9");
    Asm("           dec     r7           ; keep x on the expr stack");
    Asm("           dec     r7");
    Asm("           dec     r7");
    Asm("           dec     r7");
    Asm("           sex     r7           ; now place 2 1.0s");
    Asm("           ldi     03fh");
    Asm("           stxd");
    Asm("           ldi     080h");
    Asm("           stxd");
    Asm("           ldi     000h");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           ldi     03fh");
    Asm("           stxd");
    Asm("           ldi     080h");
    Asm("           stxd");
    Asm("           ldi     000h");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           ghi     r9           ; Put x back on the stack twice");
    Asm("           stxd");
    Asm("           glo     r9");
    Asm("           stxd");
    Asm("           ghi     r8");
    Asm("           stxd");
    Asm("           glo     r8");
    Asm("           stxd");
    Asm("           ghi     r9");
    Asm("           stxd");
    Asm("           glo     r9");
    Asm("           stxd");
    Asm("           ghi     r8");
    Asm("           stxd");
    Asm("           glo     r8");
    Asm("           stxd");
    Asm("           sex     r2");
    Asm("           sep     scall        ; x * x");
    Asm("           dw      mulfp");
    Asm("           sep     scall        ; subtract from 1.0");
    Asm("           dw      subfp");
    Asm("           sep     scall        ; take square root");
    Asm("           dw      fpsqrt");
    Asm("           sep     scall        ; add 1.0");
    Asm("           dw      addfp");
    Asm("           sep     scall        ; divide into x");
    Asm("           dw      divfp");
    Asm("           sep     scall        ; and then atan");
    Asm("           dw      fpatan");
    Asm("           sex     r7           ; multiply result by 2.0");
    Asm("           ldi     040h");
    Asm("           stxd");
    Asm("           ldi     000h");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           sex     r2");
    Asm("           sep     scall");
    Asm("           dw      mulfp");
    Asm("           sep     sret");
    }

  if (useAcos) {
    /* ****************************************************** */
    /* ***** Compute arcsin                             ***** */
    /* ****************************************************** */
    Asm("fpacos:    inc     r7           ; retrieve x");
    Asm("           lda     r7");
    Asm("           plo     r8");
    Asm("           lda     r7");
    Asm("           phi     r8");
    Asm("           lda     r7");
    Asm("           plo     r9");
    Asm("           ldn     r7");
    Asm("           phi     r9");
    Asm("           sex     r7           ; now place 1.0");
    Asm("           ldi     03fh");
    Asm("           stxd");
    Asm("           ldi     080h");
    Asm("           stxd");
    Asm("           ldi     000h");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           ghi     r9           ; Put x back on the stack twice");
    Asm("           stxd");
    Asm("           glo     r9");
    Asm("           stxd");
    Asm("           ghi     r8");
    Asm("           stxd");
    Asm("           glo     r8");
    Asm("           stxd");
    Asm("           ghi     r9");
    Asm("           stxd");
    Asm("           glo     r9");
    Asm("           stxd");
    Asm("           ghi     r8");
    Asm("           stxd");
    Asm("           glo     r8");
    Asm("           stxd");
    Asm("           ldi     03fh         ; now place 1.0");
    Asm("           stxd");
    Asm("           ldi     080h");
    Asm("           stxd");
    Asm("           ldi     000h");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           ghi     r9           ; and 1 more x");
    Asm("           stxd");
    Asm("           glo     r9");
    Asm("           stxd");
    Asm("           ghi     r8");
    Asm("           stxd");
    Asm("           glo     r8");
    Asm("           stxd");
    Asm("           sex     r2");
    Asm("           sep     scall        ; add 1 to x");
    Asm("           dw      addfp");
    Asm("           inc     r7           ; transfer 1+x to stack for safe keeping");
    Asm("           lda     r7");
    Asm("           stxd");
    Asm("           lda     r7");
    Asm("           stxd");
    Asm("           lda     r7");
    Asm("           stxd");
    Asm("           ldn     r7");
    Asm("           stxd");
    Asm("           sep     scall        ; multiply the two xs");
    Asm("           dw      mulfp");
    Asm("           sep     scall        ; subtract from 1.0");
    Asm("           dw      subfp");
    Asm("           sep     scall        ; take the square root");
    Asm("           dw      fpsqrt");
    Asm("           irx                  ; transfer 1+x back to expr stack");
    Asm("           ldxa");
    Asm("           str     r7");
    Asm("           dec     r7");
    Asm("           ldxa");
    Asm("           str     r7");
    Asm("           dec     r7");
    Asm("           ldxa");
    Asm("           str     r7");
    Asm("           dec     r7");
    Asm("           ldx");
    Asm("           str     r7");
    Asm("           dec     r7");
    Asm("           sep     scall        ; now divide");
    Asm("           dw      divfp");
    Asm("           sep     scall        ; and then atan");
    Asm("           dw      fpatan");
    Asm("           sex     r7           ; multiply result by 2.0");
    Asm("           ldi     040h");
    Asm("           stxd");
    Asm("           ldi     000h");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           stxd");
    Asm("           sex     r2");
    Asm("           sep     scall");
    Asm("           dw      mulfp");
    Asm("           sep     sret");
    }

  if (useStrcpy) {
    /* *********************************** */
    /* ***** Copy string             ***** */
    /* ***** RD - destination string ***** */
    /* ***** RF - source string      ***** */
    /* *********************************** */
    Asm("strcpy:    lda     rf           ; get byte from source string");
    Asm("           str     rd           ; store into destination");
    Asm("           inc     rd");
    Asm("           lbnz    strcpy       ; loop back until terminator copied");
    Asm("           sep     sret         ; return to caller");
    }

  if (useStrcat) {
    /* *********************************** */
    /* ***** Concatenate string      ***** */
    /* ***** RD - destination string ***** */
    /* ***** RF - source string      ***** */
    /* *********************************** */
    Asm("strcat:    lda     rd           ; look for terminator");
    Asm("           lbnz    strcat       ; loop back until terminator found");
    Asm("           dec     rd           ; move back to terminator");
    Asm("           lbr     strcpy       ; and then copy source string to end");
    }

  if (useStrlen) {
    /* ********************************** */
    /* ***** String length          ***** */
    /* ***** RF - pointer to string ***** */
    /* ***** Returns: RC - length   ***** */
    /* ********************************** */
    Asm("strlen:    ldi     0            ; set count to zero");
    Asm("           plo     rc");
    Asm("           phi     rc");
    Asm("strlen_1:  lda     rf           ; get byte from string");
    Asm("           lbz     strlen_2     ; jump if terminator found");
    Asm("           inc     rc           ; otherwise increment count");
    Asm("           lbr     strlen_1     ; and keep looking");
    Asm("strlen_2:  sep     sret         ; return to caller");
    }

  if (useLeft) {
    /* ***************************************** */
    /* ***** Left portion of string        ***** */
    /* ***** RF - pointer to source string ***** */
    /* ***** RD - pointer to destination   ***** */
    /* ***** RC - Count of characters      ***** */
    /* ***************************************** */
    Asm("left:      glo     rc           ; see if characters left");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           or");
    Asm("           lbz     left_dn      ; jump if not");
    Asm("           dec     rc           ; decrement count");
    Asm("           lda     rf           ; get byte from source");
    Asm("           str     rd           ; write into destination");
    Asm("           inc     rd");
    Asm("           lbnz    left_1       ; jump if terminator not found");
    Asm("left_rt:   sep     sret         ; otherwise return to caller");
    Asm("left_dn:   ldi     0            ; write terminator to destination");
    Asm("           str     rd");
    Asm("           lbr     left_rt      ; then return");
    }

  if (useMid) {
    /* ***************************************** */
    /* ***** Middle portion of string      ***** */
    /* ***** RF - pointer to source string ***** */
    /* ***** RD - pointer to destination   ***** */
    /* ***** RB - Starting point           ***** */
    /* ***** RC - Count of characters      ***** */
    /* ***************************************** */
    Asm("mid:       glo     rb           ; see if starting position found");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           or");
    Asm("           lbz     mid_2        ; use left to copy characters");
    Asm("           dec     rb           ; decrement count");
    Asm("           lda     rf           ; get byte from source string");
    Asm("           lbz     mid_dn       ; jump if terminator found, will be empty destination");
    Asm("           lbr     mid_1        ; keep looping until start point");
    Asm("mid_dn:    ldi     0            ; write terminator to destination");
    Asm("           str     rd");
    Asm("           sep     sret         ; and return");
    Asm("mid_2:     sep     scall        ; call left to copy characters");
    Asm("           dw      left");
    Asm("           sep     sret         ; and return to caller");
    }

  if (useRight) {
    /* ***************************************** */
    /* ***** Right portion of string       ***** */
    /* ***** RF - pointer to source string ***** */
    /* ***** RD - pointer to destination   ***** */
    /* ***** RC - Count of characters      ***** */
    /* ***************************************** */
    Asm("right:     ldi     0            ; zero counter");
    Asm("           plo     rb");
    Asm("           phi     rb");
    Asm("right_1:   lda     rf           ; get byte from source");
    Asm("           lbz     right_2      ; jump if terminator found");
    Asm("           inc     rb           ; increment length");
    Asm("           lbr     right_1      ; keep looking for terminator");
    Asm("right_2:   dec     rf           ; point back to previous character");
    Asm("           glo     rb           ; check RB counter");
    Asm("           str     r2");
    Asm("           ghi     rb");
    Asm("           or");
    Asm("           lbz     right_dn     ; start found, so now just copy");
    Asm("           glo     rc           ; check rc counter");
    Asm("           str     r2");
    Asm("           ghi     rc");
    Asm("           or");
    Asm("           lbz     right_dn     ; start found, so now just copy");
    Asm("           dec     rb           ; decrement counters");
    Asm("           dec     rc");
    Asm("           lbr     right_2      ; keep looking for start point");
    Asm("right_dn:  sep     scall        ; call strcpy to copy the string");
    Asm("           dw      strcpy");
    Asm("           sep     sret         ; and return");
    }

  if (useLower) {
    /* *************************************** */
    /* ***** Convert string to lowercase ***** */
    /* ***** RF - Pointer to string      ***** */
    /* *************************************** */
    Asm("lower:     ldn     rf           ; get byte from buffer");
    Asm("           lbz     return       ; jump if terminator found");
    Asm("           smi     'A'          ; Check for lower range");
    Asm("           lbnf    lowernxt     ; jump if below range");
    Asm("           smi     26           ; check for above range");
    Asm("           lbdf    lowernxt     ; jump if above range");
    Asm("           ldn     rf           ; get character");
    Asm("           adi     32           ; convert to lowercvase");
    Asm("           str     rf           ; and put it back");
    Asm("lowernxt:  inc     rf           ; point to next character");
    Asm("           lbr     lower        ; process rest of string");
    }

  if (useUpper) {
    /* *************************************** */
    /* ***** Convert string to uppercase ***** */
    /* ***** RF - Pointer to string      ***** */
    /* *************************************** */
    Asm("upper:     ldn     rf           ; get byte from buffer");
    Asm("           lbz     return       ; jump if terminator found");
    Asm("           smi     'a'          ; Check for lower range");
    Asm("           lbnf    uppernxt     ; jump if below range");
    Asm("           smi     26           ; check for above range");
    Asm("           lbdf    uppernxt     ; jump if above range");
    Asm("           ldn     rf           ; get character");
    Asm("           smi     32           ; convert to lowercvase");
    Asm("           str     rf           ; and put it back");
    Asm("uppernxt:  inc     rf           ; point to next character");
    Asm("           lbr     upper_1      ; process rest of string");
    }

  if (useStrcmp) {
    /* ********************************************* */
    /* ***** String compare                    ***** */
    /* ***** RF - string1                      ***** */
    /* ***** RD - string2                      ***** */
    /* ***** Returns: DF=0 - strings unequal   ***** */
    /* *****          DF=1 - strings equal     ***** */
    /* *****          D=1  - string1 > string2 ***** */
    /* *****          D=0  - string1 < string2 ***** */
    /* ********************************************* */
    Asm("strcmp:    lda     rf           ; get byte from string1");
    Asm("           str     r2");
    Asm("           lbnz    strcmp_1     ; jump if terminator not found");
    Asm("           lda     rd           ; get byte from second string");
    Asm("           lbz     strcmp_eq    ; jump if strings are equal");
    Asm("           lbr     strcmp_lt    ; jump if string1 is smaller");
    Asm("strcmp_1:  lda     rd           ; get byte from second string");
    Asm("           lbz     strcmp_gt    ; jump if string2 is lower");
    Asm("           sd                   ; subtract from first string");
    Asm("           lbz     strcmp_2     ; loop to check remaining bytes");
    Asm("           lbdf    strcmp_gt    ; jump if");
    Asm("strcmp_lt: ldi     0            ; signal string 1 is lower");
    Asm("           lbr     strcmp_rt");
    Asm("strcmp_eq: ldi     1            ; signal strings equal");
    Asm("           lbr     strcmp_rt");
    Asm("strcmp_gt: ldi     2            ; signal string 2 is lower");
    Asm("strcmp_rt: shr");
    Asm("           sep     sret");
    }

  if (passNumber == 1) lblStart = address;
  if (useStg) {
    Asm("start:      ghi  r6");
    Asm("            stxd");
    Asm("            glo  r6");
    Asm("            stxd");
    Asm("            ldi  [STG_].1");
    Asm("            phi  rf");
    Asm("            ldi  [STG_].0");
    Asm("            plo  rf");
    Asm("            ghi  r2");
    Asm("            str  rf");
    Asm("            inc  rf");
    Asm("            glo  r2");
    Asm("            str  rf");
    }
  else {
    Asm("start:      ldi  [stack].1");
    Asm("            phi  r2");
    Asm("            ldi  [stack].0");
    Asm("            plo  r2");
    }
  Asm("            ldi  [estack].1");
  Asm("            phi  r7");
  Asm("            ldi  [estack].0");
  Asm("            plo  r7");
  if (useElfos == 0 && useStg == 0) {
    Asm("          ldi  call.1");
    Asm("          phi  r4      ");
    Asm("          ldi  call.0");
    Asm("          plo  r4");
    Asm("          ldi  ret.1");
    Asm("          phi  r5      ");
    Asm("          ldi  ret.0");
    Asm("          plo  r5");
    }
  t1 = variableRAM + (2 * numberOfVariables);
  t2 = getVariable("FREE_");
  Asm("          ldi  [free_].1");
  Asm("          phi  rf");
  Asm("          ldi  [free_].0");
  Asm("          plo  rf");
  if (use32Bits) {
    Asm("          ldi  0");
    Asm("          str  rf");
    Asm("          inc  rf");
    Asm("          str  rf");
    Asm("          inc  rf");
    }
  sprintf(buffer,"          ldi  %d",t1/256); Asm(buffer);
  Asm("          str  rf");
  Asm("          inc  rf");
  sprintf(buffer,"          ldi  %d",t1%256); Asm(buffer);
  Asm("          str  rf");
  if (useData) {
    a = getVariable("DATA_");
    output(LDI); output(a/256); output(PHI+RF);
    output(LDI); output(a%256); output(PLO+RF);
    output(LDI); output(dataAddress/256); output(STR+RF); output(INC+RF);
    output(LDI); output(dataAddress%256); output(STR+RF);
    }
  if (useHeap) {
    a = getVariable("HEAP_");
    output(LDI); output(a/256); output(PHI+RF);
    output(LDI); output(a%256); output(PLO+RF);
    output(LDI); output(heap/256); output(STR+RF); output(INC+RF);
    output(LDI); output(heap%256); output(STR+RF);
    }
  if ((useItoA || useAtoI || useItoA32 || useAtoI32) && useElfos == 0) {
    Asm("          sep  scall");
    Asm("          dw   f_setbd");
    }
  showCompiler = ctmp;
  if (passNumber == 1) runtime = address;
  }

