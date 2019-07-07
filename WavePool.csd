<Cabbage> bounds(0, 0, 0, 0)
form caption("WavePool") size(600, 400), colour(128, 197, 242), pluginid("def1")
keyboard bounds(12, 267, 576, 121)
rslider bounds(12, 12, 70, 70), channel("att"), range(0, 1, 0.01, 1, 0.01), text("Attack") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(90, 12, 70, 70), channel("dec"), range(0, 1, 0.5, 1, 0.01), text("Decay") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(168, 12, 70, 70), channel("sus"), range(0, 1, 0.5, 1, 0.01), text("Sustain") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(246, 12, 70, 70), channel("rel"), range(0, 1, 0.7, 1, 0.01), text("Release") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(12, 90, 70, 70), channel("cutoff"), range(0, 22000, 2000, 0.5, 0.01), text("Cut-Off") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(90, 90, 70, 70), channel("res"), range(0, 1, 0.7, 1, 0.01), text("Resonance") colour(255, 255, 255, 255) textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(168, 90, 70, 70), channel("LFOFreq"), range(0, 10, 0, 1, 0.01), text("LFO Freq") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
rslider bounds(246, 90, 70, 70), channel("amp"), range(0, 1, 0.7, 1, 0.01), text("Amp") textcolour(255, 255, 255, 255) trackercolour(19, 161, 255, 255)
csoundoutput bounds(12, 170, 483, 85)

button bounds(498, 215, 91, 40) text("Write Data")
filebutton bounds(498, 170, 90, 40)


csoundoutput bounds(452, 76, 400, 200)
signaldisplay bounds(324, 12, 264, 148)
</Cabbage>
<CsoundSynthesizer>
<CsOptions>
-n -d -+rtmidi=NULL -M0 -m0d --midi-key-cps=4 --midi-velocity-amp=5
</CsOptions>
<CsInstruments>
; Initialize the global variables. 
ksmps = 32
nchnls = 2
0dbfs = 1

;instrument will be triggered by keyboard widget
instr 1
kEnv madsr .1, .2, .6, .4
aOut vco2 p5, p4
outs aOut*kEnv, aOut*kEnv
endin

</CsInstruments>
<CsScore>
;causes Csound to run for about 7000 years...
f0 z
</CsScore>
</CsoundSynthesizer>
