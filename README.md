# Synther
# Description
Welcome to _Synther_, an interactive, intuitive, virtual keyboard. Offering support for over 15 instruments, _Synther_ emulates a synthesizer and brings music production and experimentation to your computer! The goal of _Synther_ is provide a musical experience that looks and feels like a real piano, through C++ and the Cinder library.

# Installation
This project is currently stable for MacOS. Other platforms have yet to be tested.

This installation requires the [CLion IDE](https://www.jetbrains.com/clion/)
### Setting up Cinder
This project requires the Cinder framework. First, we need to set up Cinder. These instructions are modified from [UIUC Fall 2020 NaiveBayes](https://courses.grainger.illinois.edu/cs126/fa2020/assignments/naive-bayes/)
* Download [Cinder](https://libcinder.org/download) (v0.9.2) for you platform
* Extract the downloaded item into a folder. We will call this folder `~/Cinder`
* Follow the [Instructions](https://www.libcinder.org/docs/guides/cmake/cmake.html#building-libcinder-with-cmake) for building LibCinder with CMake
* * Alternatively, if using the CLion IDE, navigate to ~/Cinder and select `Run` -> `Build`
### Running the Project
* Create a directory caled `my-projects` in `~/Cinder`. Navigate to `my-projects` and clone this repository inside.
* From here, you can run the cloned project in CLion

# Gameplay
The core controls are displayed directly on the _Synther_ keyboard. Every piano key is labelled with its corresponding control key. Every note is played for as long
its corresponding key is held down.
### Controls
_Synther_ allows you to move the keyboard view to play all 88 keys of the keyboard.
| Key        | Action                                                                 |
| ---------- | -----------------------------------------------------------------------|
| `QWERTY...`| Play black notes on the keyboard                                       |
| `ASDF...`  | Play white notes on the keyboard                                       |
| `Up`       | Move the keyboard up a white key                                       |
| `Down`     | Move the keyboard down a white key                                     |
| `Right`    | Move the keyboard up an octave                                         |
| `Up`       | Move the keyboard up down an octave                                    |
| `Space`    | Toggle the sustain pedal on/off, altering the resonation of the piano  |
| `n`        | Opens File Explorer, allowing you to change the musical instrument |

### Changing Instruments
Pressing `n` on the keyboard opens up the File Explorer/Finder with a list of directories containing instrument sound files. To change instruments, simply select the instrument's folder and press `open` in File Explorer. Note that many instruments have a smaller range than the Acoustic Piano. Therefore, not all keys on the keyboard will be visible for all instruments.

# Credits
## Sound Files
* Philharmonia Orchestra
* Ivy Audio
