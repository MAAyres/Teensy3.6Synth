# Teensy3.6Synth

Monophonic subtrative synthesiser with stereo output.

The synth is formed of two oscillators with adjustable waveforms which are then filtered and amplified in stereo.

The synth features 3 Analog potentiometers for parameter control and 4 pushbuttons (Shift, Edit, Left, Right) for menu selection and enabling parameter editing. Use of a Nokia 5110 LCD allows for visual feedback of parameter adjustments and a visual representation of envelopes etc.

Though currently monophonic, the code has been structured for a future expansion to polyphony.

Signal Flow Diagram.  
<img width="766" alt="Screenshot 2022-04-04 at 08 43 40" src="https://user-images.githubusercontent.com/102936196/161497100-c55dffa6-b6ce-432c-a7d4-139e3b1b27e4.png">

Synthesiser Hardware.
![20220404_084655](https://user-images.githubusercontent.com/102936196/161497942-70ba81ac-b008-429b-865b-b56c2d7926da.jpeg)

File structure:

teensy3.6synth.ino - Main. <br />
ui.cpp - User interface and Parameter editing. <br />
ui.h - User interface header file. <br />
voice.cpp - Audio Engine control, signal processing. <br /> 
voice.h - Audio Engine header file. <br />
