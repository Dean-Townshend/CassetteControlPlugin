# CassetteControlPlugin
![image](https://user-images.githubusercontent.com/38728500/129430722-c31fdc27-cd7e-4fee-9fb3-c116b7a4cc07.png)

This plugin is used in tandem with my Cassette motor controller Arduino sketch to turn a cassette player into a quasi synthesiser. Each note dial sets the speed at which the cassette motor will run when the corresponding note is played. The Glide dial sets how quickly the cassette motor will speed up/slow down between changing notes. The Min Speed dial sets the base for how slow the cassette motor can be set, this stops the motor from stalling. All of this control data is sent to the Arduino via MIDI.

All of these feature are all implemented and working. However the ADSR still needs to be implemented.


