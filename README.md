# Synchronization Protocol

This repository provides files associated with our protocol paper about signal synchronization.

Dagher & Ishiyama (2023) STAR Protocols.



Example data are available:

Dagher, Sarah; Ishiyama, Shimpei (2023), “Signal synchronization in systems neuroscience (example data)”, Mendeley Data, V1, doi: 10.17632/98rzkwy8s6.1



## Pulse generator PCB

Printed circuit board (PCB) of the pulse generator is provided as KiCad files in the Pulse_Generator_PCB folder.



Printing the PCB can be outsourced to companies such as Aisler. Aisler accepts KiCad files directly.



## Pulse generator software

Codes necessary for the pulse generator are under the Pulse_Generator_software folder.



MATLAB files are necessary to trigger the pulse generator from MATLAB.

**exampleTimer.m** demonstrates an example use of triggering the pulse generator from MATLAB.



ArduinoLibrary\pulseGen folder contains Arduino files to setup the main Teensy board of the pulse generator.



myPulses folder contains an Arduino file to configure custom settings for each channel of the pulse generator.



## Sync TTL analysis

syncTTL folder contains MATLAB functions to extract TTL times from each signal.

**getAudioTTL_demo.m** extracts TTL rise times [s] from the least significant bit of a .wav file recorded by Avisoft devices. Times are based on the sample positions in the .wav file.



**getNlxTTL_demo.m**  extracts TTL rise times [s] from a Events.nev file created by Neuralynx Cheetah software. Users may need to adjust `TTLeventID` and `bitpos` dependent on the Neuralynx device used. Times are based on the timestamps of the Neuralynx device.



**getVideoTTL_demo.m** extracts TTL rise times [s] from a .csv file created by Bonsai with our configuration for the FLIR cameras. Times are based on the timestamps of the FLIR camera.



**sync_pulse_analysis.mlx** demonstrates sync pulse analysis to verify the validity of a recording. Example data are provided in Example_data folder.



## Bonsai file

**TwoCam.bonsai** demonstrates an example setting for video recording with two FLIR cameras, monitoring real-time TTL status and drop frames, embedding frame ID in the video frames, and exporting timestamp and TTL status of each frame as .csv files.
