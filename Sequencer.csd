<Cabbage>
form caption("Untitled") size(400, 300), colour(58, 110, 182), pluginid("def1")
rslider bounds(296, 162, 100, 100), channel("gain"), range(0, 1, 0, 1, .01), text("Gain"), trackercolour("lime"), outlinecolour(0, 0, 0, 50), textcolour("black")

button bounds(16, 14, 80, 40), text("Update Notes"), channel("updateNotes")
button bounds(100, 14, 80, 40), text("Add delay", "Remove delay"), channel("addDelay")
</Cabbage>
<CsoundSynthesizer>
<CsOptions>
-n -d -+rtmidi=NULL -M0 -m0d 
</CsOptions>
<CsInstruments>
; Initialize the global variables. 
ksmps = 32
nchnls = 2
0dbfs = 1

gkNotes[] init 32
gkNoteCnt init 8


instr SEQUENCER

   
    kCnt init 0
    kNoteIndex init 0
     
    if changed:k(chnget:k("updateNotes")) == 1 then
        kCnt = 0
        while kCnt < gkNoteCnt do
            gkNotes[kCnt] = 60+int(random:k(0, 12))
            kCnt+=1
        od 
    endif
    



    while kCnt < gkNoteCnt do
        gkNotes[kCnt] = 60+kCnt
        kCnt+=1
    od

    if metro(4) == 1 then
        event "i", "SYNTH", 0, .5, gkNotes[kNoteIndex]
        
        if chnget:k("addDelay") == 1 then
            event "i", "SYNTH", .50, .5, gkNotes[kNoteIndex]
        endif
        
        kNoteIndex = kNoteIndex<6 ? kNoteIndex+1 : 0
    endif
endin


instr SYNTH
    a1 expon 1, p3, 0.01
    aOut oscili a1, cpsmidinn(p4)
    out aOut*chnget:k("gain"), aOut*chnget:k("gain")
endin

</CsInstruments>
<CsScore>
;causes Csound to run for about 7000 years...
f0 z
;starts instrument 1 and runs it for a week
i"SEQUENCER" 0 [60*60*24*7] 
</CsScore>
</CsoundSynthesizer>
