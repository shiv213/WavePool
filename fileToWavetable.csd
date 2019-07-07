<Cabbage>
form caption("WavePool") size(400, 400), colour(58, 110, 182), pluginid("def1")
keyboard bounds(10, 296, 381, 95)
button bounds(12, 196, 379, 40), text("Write to table", "Write to table"), channel("write") value(1)
hslider bounds(10, 242, 380, 50) range(0, 1, 0.5, 1, 0.001), channel("traverse") trackercolour(0, 82, 255, 255)
gentable bounds(12, 10, 380, 180), identchannel("widgetIdent"), tablenumber(1) fill(0) tablecolour:0(0, 82, 255, 255)
</Cabbage>
<CsoundSynthesizer>
<CsOptions>
-n -d -+rtmidi=NULL -M0 -m0d --midi-key-cps=4 --midi-velocity-amp=5 -odac
</CsOptions>
<CsInstruments>
; Initialize the global variables. 
ksmps = 32
nchnls = 2
0dbfs = 1

giEmpty ftgen 3, 0, -256, 2, 0

; simple UDO that will write the incoming audio stream
; to a function table when triggered..
opcode TableWrite, 0, akii
   aSig, kTrig, iTableSize, iTableNum xin
   
   kCnt init 0
   setksmps 1
   kSig = aSig

   
   if changed(kTrig) == 1 then
      printks "Sampling again", 0
      kCnt = 0
   endif
   
   if kCnt < iTableSize then
      tablew kSig, kCnt, iTableNum
      printk2 kSig
      kCnt +=1
   endif
endop 

; always playing instrument. Pressing the "Write to table" button
; will write 4096 samples to function table 1
instr 200
    p3 = filelen("pianoMood.wav")
    a1, a2 diskin2 "pianoMood.wav", 1, 0, 1
    TableWrite a1, chnget:k("write"), 4096, 1
    chnset	"tablenumber(1)", "widgetIdent"
endin

;instrument will be triggered by keyboard widget
instr 1
    iTraverse chnget "traverse"
    SIdentifier init ""
    SIdent sprintf "samplerange(%f, %d) ", iTraverse*4096-256, iTraverse*4096+256
    SIdentifier strcat SIdentifier, SIdent
    SIdentifier strcat SIdentifier, "tablenumber(1)"

    ;send identifier string to Cabbage
    chnset SIdentifier, "widgetIdent"
    kEnv madsr .1, .2, .6, .4

;    kndx line 0, p3, 1
;    kfreq table iTraverse, 1, 1
;    ares tablera 1, iTraverse*4096-8, 16

    indx table iTraverse*4096, 1
    loop:
        ivalue tab_i indx, 1
        tabw_i ivalue, indx, 3
    loop_lt indx, 1, 256, loop

    iindex = 0
    begin_loop:
        ivalue tab_i iindex, 3
        prints "%d:\t%f\n", iindex, ivalue
        iindex = iindex + 1
    if (iindex < ftlen(3)) igoto begin_loop

;    prints "Index %d = %f%n", iTraverse*4096, ival
    
;    printk2 kfreq
;    a1 loscil p5, p4, 1
;    a1 oscil 1, p4, 1
    a1 poscil 1, p4, 3
;    prints "%d", p4
;    al osciln 1, 
    outs a1, a1
endin


</CsInstruments>
<CsScore>
; table that samples are written to..
f1 0 4096 7 0
f 2 0 128 -23 "spectrum.txt"
;f 111 0 16 10 1 

; table to apply fade to samples
f99 0 4096 7 0 48 1 4000 1 48 0 
;f99 0 4096 7 0

i200 0 z
f0 z
</CsScore>
</CsoundSynthesizer>
