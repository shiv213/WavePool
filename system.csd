<Cabbage> bounds(0, 0, 0, 0)
form caption("WavePool") size(600, 400), colour(128, 197, 242), pluginid("def1")
button bounds(11, 168, 305, 40) text("Write to table", "Write to table"), channel("write") value(1)
</Cabbage>
<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
; Audio out   Audio in
-odac          ; -iadc    ;;;RT audio I/O
; For Non-realtime ouput leave only the line below:
; -o system.wav -W ;;; for file output any platform
</CsOptions>
<CsInstruments>

; Initialize the global variables.
sr = 44100
kr = 4410
ksmps = 10
nchnls = 1

instr 1
; Waits for command to execute before continuing
ires system_i 1,{{start "" getData.exe}},1
;        }}
;ires system 1, {{.\test.cmd}}, 1

print ires
prints "yes"
turnoff
endin

;instr 2
;; Runs command in a separate thread
;
;print ires
;prints "second"
;turnoff
;endin

</CsInstruments>
<CsScore>

; Play Instrument #1 for thirty seconds.
i 1 0 1
e


</CsScore>
</CsoundSynthesizer>