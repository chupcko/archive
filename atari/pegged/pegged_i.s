.export      errno,exit
.import      main,_FreeAll

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
start:
  lea.l      start-BasePageSize,a0
  movea.l    TextSegSize(a0),a1
  adda.l     DataSegSize(a0),a1
  adda.l     BssSegSize(a0),a1
  adda.w     #BasePageSize,a1

  move.l     a0,d0
  add.l      a1,d0
  and.b      #0xfc,d0
  movea.l    d0,sp

  move.l     a1,-(sp)
  move.l     a0,-(sp)
  clr.w      -(sp)
  move.w     #74,-(sp)
  trap       #1
  adda.w     #12,sp

  jsr        main
exit:
  jsr        _FreeAll
  clr.w      -(sp)
  trap       #1

.data
errno:
  .dc.w      0
