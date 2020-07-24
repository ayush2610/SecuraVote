# SecuraVote
A Biometric Authentication based secure and user-friendly Electronic Voting Machine with Speech Recognition and Audio Processing for blind and illiterate people


# 1. Folder Structure

nowVoiceandspee : contains Arduino .ino script 
Recordings_eng and Recordings_hind : contain the audio recording for voice assistance. Can be replaced with any local language
EVM.py : python script to interface arduino peripherals with speech recognition and audio features.

# 2. Usage

1. Upload the nowVoiceandspee.ino on the arduino microcontroller.
2. Run the EVM.py python script
3. Now according to the Key pressed on Arduino corresponding actions will take place. Arduino also Serially transmits the data to its COM port.

# 3. Working

1. Arduino Uno microcontroller is connected to a LCD, a Keypad and a Fingerprint sensor. the script allows arduino to take input from the keypad and perform the corresponding
   action.Arduino also transmits data to COM Port using serial communication. After the voting process is complete the Arduino triggers the fingerprint sensor to take input and
   thus authenticates the identity of the user by verifying with the fingerprint samples of the user already in the database.
2. The python script takes the input serial data from arduino and performs either audio playback in the chosen language or takes input by recognising speech commands.


