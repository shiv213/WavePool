<Cabbage> bounds(0, 0, 0, 0)
form caption("WavePool") size(600, 400), colour(128, 197, 242), pluginid("def1")
keyboard bounds(12, 266, 576, 121)
rslider bounds(12, 12, 70, 70), channel("att"), range(0, 1, 0.01, 1, 0.01), text("Attack") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(90, 12, 70, 70), channel("dec"), range(0, 1, 0.5, 1, 0.01), text("Decay") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(168, 12, 70, 70), channel("sus"), range(0, 1, 0.5, 1, 0.01), text("Sustain") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(246, 12, 70, 70), channel("rel"), range(0, 1, 0.7, 1, 0.01), text("Release") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(12, 90, 70, 70), channel("cutoff"), range(0, 22000, 2000, 0.5, 0.01), text("Cut-Off") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(90, 90, 70, 70), channel("res"), range(0, 1, 0.7, 1, 0.01), text("Resonance") colour(255, 255, 255, 255) textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(168, 90, 70, 70), channel("LFOFreq"), range(0, 10, 0, 1, 0.01), text("LFO Freq") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(246, 90, 70, 70), channel("amp"), range(0, 1, 0.7, 1, 0.01), text("Amp") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)

button bounds(11, 168, 305, 40) text("Write to table", "Write to table"), channel("write") value(1)
gentable bounds(324, 12, 264, 196), identchannel("widgetIdent"), tablenumber(4)  samplerange(0, 4096) fill(0) tablecolour:0(0, 82, 255, 255)
hslider bounds(12, 212, 576, 50) range(0, 1, 0.473, 1, 0.001), channel("traverse") trackercolour(19, 161, 255, 255)
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

;    iindex = 0
;    begin_loop:
;        ivalue tab_i iindex, giRaw
;        prints "%d:\t%f\n", iindex, ivalue
;        iindex = iindex + 1
;    if (iindex < ftlen(giRaw)) igoto begin_loop

instr 200
    p3 = 4096
    
;    printks "Sampling again", 0
    giRaw ftgen 2, 0, 4096, -23, "raw.txt"
    giPost ftgen 4, 0, -4096, 2, 0
    indx init 0
    loop:
        ivalue tab_i indx, 2
        tabw_i ivalue-200, indx, 4
    loop_lt indx, 1, 4096, loop
    
    chnset	"tablenumber(4)", "widgetIdent"
endin

;instrument will be triggered by keyboard widget
instr 1
    iTraverse chnget "traverse"
    SIdentifier init ""
    SIdent sprintf "samplerange(%f, %d) ", iTraverse*4096-128, iTraverse*4096+128
    SIdentifier strcat SIdentifier, SIdent
    SIdentifier strcat SIdentifier, "tablenumber(3)"

    ;send identifier string to Cabbage
    chnset SIdentifier, "widgetIdent"
    indx init 0
    loop:
        ivalue tab_i iTraverse*3840+indx, 4
        tabw_i ivalue, indx, 3
    loop_lt indx, 1, 256, loop
    chnset "tablenumber(3)", "widgetIdent"
    
    iindex = 0
    begin_loop:
        ivalue tab_i iindex, 3
        prints "%d:\t%f\n", iindex, ivalue
        iindex = iindex + 1
    if (iindex < ftlen(3)) igoto begin_loop

    prints "%d", iTraverse*100
    
;    prints "Index %d = %f%n", iTraverse*4096, ival
    
;    printk2 kfreq
;    a1 loscil p5, p4, 1
;    a1 loscil p5, p4, 3
    a1 poscil p5, p4, 3
    iAtt chnget "att"
    iDec chnget "dec"
    iSus chnget "sus"
    iRel chnget "rel"
    kRes chnget "res"
    kCutOff chnget "cutoff"
    kLFOFreq chnget "LFOFreq"
    kAmp chnget "amp"
    
    kEnv madsr iAtt, iDec, iSus, iRel 
    aLP moogladder a1, kLFOFreq*kCutOff, kRes
    
    outs kAmp*(aLP*kEnv), kAmp*(aLP*kEnv)


endin


</CsInstruments>
<CsScore>
; table that samples are written to..
f1 0 4096 7 0
;f 111 0 16 10 1 

; table to apply fade to samples
f99 0 4096 7 0 48 1 4000 1 48 0 
;f99 0 4096 7 0

i200 0 z
f0 z
</CsScore>
</CsoundSynthesizer>

</CsScore>
</CsoundSynthesizer>
