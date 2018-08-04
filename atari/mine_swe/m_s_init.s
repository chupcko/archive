.export      errno,exit,str_copy,new_msvc
.import      main,_FreeAll,old_msvc

.offset      0
  .ds.l      1
  .ds.l      1
  .ds.l      1
TextSegSize:
  .ds.l      1
  .ds.l      1
DataSegSize:
  .ds.l      1
  .ds.l      1
BssSegSize:
  .ds.l      1
  .ds.l      1
  .ds.l      1
  .ds.l      1
EnvStrPtr:
  .ds.l      1
  .ds.b      7
  .ds.b      1
  .ds.l      18
  .ds.b      128
BasePageSize:
  .ds.w      0

.code
  movea.l    4(sp),a1

  movea.l    TextSegSize(a1),a0
  adda.l     DataSegSize(a1),a0
  adda.l     BssSegSize(a1),a0
  adda.w     #BasePageSize,a0

  move.l     a1,d0
  add.l      a0,d0
  and.b      #0xfc,d0
  movea.l    d0,sp

  move.l     a0,-(sp)
  move.l     a1,-(sp)
  clr.w      -(sp)
  move.w     #74,-(sp)
  trap       #1
  adda.w     #12,sp

  jsr        main
exit:
  jsr        _FreeAll
  clr.w      -(sp)
  trap       #1

str_copy:
  move.b     (a1)+,(a0)+
  bne.b      str_copy
  rts

new_msvc:
  btst.b     #0,(a0)
  beq.b      quit

  bchg.b     #1,(a0)

quit:
  movea.l    old_msvc,a2
  jmp        (a2)

.data
errno:
  .dc.w      0
