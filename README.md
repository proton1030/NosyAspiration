# NosyAspiration
An audio effect plugin sings with an audio input's pitch. 

### Link to Introduction Vid:

[![pic](https://i.vimeocdn.com/video/698111777_1280x720.jpg)](https://vimeo.com/267555841)

### Functionality

To add pronuciation to the step sequencer, drag pronunciation on the right to the middle drop box, dropped pronounciation will be added to step sequencer on the left. 

To delete pronunciation from the step sequencer, drag pronunciation on the left to the middle drop box.

Three knobs availble to adjust: Gain, Vibrato freq, Reverb amount

*"**note that the plug-in params are tweaked for real electric guitar, the power of the guitar pick up may also affect the playing effect.**"*

### The speech sythnesis

Referencing Neil Thapen's (https://dood.al/pinktrombone/) web audio implementation of procedural speech synthesis, and we translate javascript code into c++ code in an API fashion.

### The Real-Time pitch tracking

Using ACF to detect monophonic pitch, due to the nature of ACF algorithm, preferably 1024 blocksize should be used.

### The Onset Detection

A mixed measurements of RMS and PPM are used.

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

