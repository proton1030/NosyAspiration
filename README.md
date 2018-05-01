# NosyAspiration
An audio effect plugin sings with an audio input's pitch. 

### Functionality

A syllable pronunciation macro editor interface which allows user to form their own words/sentences and accepts MIDI input controlling in real-time.

A pitch tracker that can analyze monophonic audio input and map the extracted pitch to articulatory synthesis.

### The speech sythnesis

Referencing Neil Thapen's (https://dood.al/pinktrombone/) web audio implementation of procedural speech synthesis, and we translate javascript code into c++ code in an API fashion.

### Build Instruction

Open NosyAspiration.jucer project file, then open IDE from projucer to build it.

### Folder Structure

Assets //GUI related resources (background, fonts, etc)

Source // Source files

- JuceTemplate // processer & editor
- Sequencer // step sequencer API 
- OnsetDetection // onset detection API (rms, ppm)
- PitchTrack // pitch track API (acf)
- Tract // tract filter simulation API
- Glottis // Glottis source generation API
- SimplexNoise // 3rd party simplex noise API
- GUIComponents // GUI components
- AudioFilesIO // 3rd party IO lib for protential wavfile testing
- Test // wav file test for glottis

