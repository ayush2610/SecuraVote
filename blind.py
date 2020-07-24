import serial 
import time
import pyglet
import speech_recognition as sr
import pyaudio

ser = serial.Serial('COM4', 9600, timeout=0)
pyglet.lib.load_library('avbin')
pyglet.have_avbin=True

engDir = 'E:\\Recordings_eng'


choices = pyglet.media.load(engDir+'\\choices.mp3',streaming=False)
enter = pyglet.media.load(engDir+'\\enter_your_choice.mp3',streaming=False)
invalid = pyglet.media.load(engDir+'\\Invalid_Choice.mp3',streaming=False)
notElig = pyglet.media.load(engDir+'\\Not_eligible_to_vote.mp3',streaming=False)
place = pyglet.media.load(engDir+'\\Place_Finger.mp3',streaming=False)
retries = pyglet.media.load(engDir+'\\Retries_Exceeded.mp3',streaming=False)
tryag = pyglet.media.load(engDir+'\\Try_Again.mp3',streaming=False)
vote = pyglet.media.load(engDir+'\\Vote_registered.mp3',streaming=False)
welcom = pyglet.media.load(engDir+'\\Welcom.mp3',streaming=False)
youcan = pyglet.media.load(engDir+'\\You_can_now_vote.mp3',streaming=False)

done = [0,0,0,0,0,0,0,0,0,0,0]
plenter = pyglet.media.Player()
plenter.queue(enter)
plenter.queue(choices)

plchoices = pyglet.media.Player()
plchoices.queue(choices)

plinvalid = pyglet.media.Player()
plinvalid.queue(invalid)

plnotElig = pyglet.media.Player()
plnotElig.queue(notElig)

plplace = pyglet.media.Player()
plplace.queue(place)

plretries = pyglet.media.Player()
plretries.queue(retries)

pltryag = pyglet.media.Player()
pltryag.queue(tryag)

plvote = pyglet.media.Player()
plvote.queue(vote)

plwelcom = pyglet.media.Player()
plwelcom.queue(welcom)


plyoucan = pyglet.media.Player()
plyoucan.queue(youcan)

####################
hindiDir = 'E:\\Recordings_hind'
aapvote = pyglet.media.load(hindiDir+'\\vote_yogya.mp3',streaming=False)
amanya = pyglet.media.load(hindiDir+'\\amaanya.mp3',streaming=False)
vikalp = pyglet.media.load(hindiDir+'\\vikalp.mp3',streaming=False)
lis = pyglet.media.load(hindiDir+'\\ballot.mp3',streaming=False)
prayas = pyglet.media.load(hindiDir+'\\prayas.mp3',streaming=False)
ungli = pyglet.media.load(hindiDir+'\\ungli_sensor.mp3',streaming=False)
matdan = pyglet.media.load(hindiDir+'\\matdaan_ankit.mp3',streaming=False)
votekar = pyglet.media.load(hindiDir+'\\vote_karein.mp3',streaming=False)
swagat = pyglet.media.load(hindiDir+'\\swagat.mp3',streaming=False)
punarpryaas = pyglet.media.load(hindiDir+'\\punarpryaas.mp3',streaming=False)


plaapvote = pyglet.media.Player()
plaapvote.queue(aapvote)


plamanya = pyglet.media.Player()
plamanya.queue(amanya)

plvikalp = pyglet.media.Player()
plvikalp.queue(vikalp)
plvikalp.queue(lis)



plprayas = pyglet.media.Player()
plprayas.queue(prayas)

plungli = pyglet.media.Player()
plungli.queue(ungli)

plmatdan = pyglet.media.Player()
plmatdan.queue(matdan)

plvotekar = pyglet.media.Player()
plvotekar.queue(votekar)

plswagat = pyglet.media.Player()
plswagat.queue(swagat)

plpunarpryaas = pyglet.media.Player()
plpunarpryaas.queue(punarpryaas)




while 1:
        pl=0
        vote =0
        vr = ser.readline()
        msg= vr.decode('utf-8')
        
        if msg=='a':
                
                        plwelcom.play()
                        plwelcom.seek(0.0)
                        
                        
                        
                        
        
        elif msg=='b':
                        plplace.play()
                        plplace.seek(0.0)
                        
                        
                        
               
                
       
                        
        elif msg =='l':
                
                        plvote.play()
                        plvote.seek(0.0)
                        
                        
                                              
                        
                       
                        
                        
                
        elif msg == 'd':
                
                        pltryag.play()
                        pltryag.seek(0.0)
                        
                        
                        
                        
                
        elif msg == 'e':
                
                        plretries.play()
                        plretries.seek(0.0)
                     
                        
                       
                
        elif msg == 'f':
               
                        plvote.play()
                        plvote.seek(0.0)
                    
                        
               
        elif msg =='g':
              
                        plnotElig.play()
                        plnotElig.seek(0.0)
               
                        
                       
        elif msg == 'h':
              
                        plyoucan.play()
                        plyoucan.seek(0.0)
                 
                        
                        
                        
                
        elif msg =='j':
               
                        plenter.play()
                        plenter.seek(0.0)
                        r = sr.Recognizer()
                        with sr.Microphone() as source:
                                audio = r.listen(source)
            
                        try:
   
                                print("Casting vote to choice # " + r.recognize_google(audio))
                                vote=(str(r.recognize_google(audio)))
                                ser.write((vote+'**\r').encode())
                                print(vote)
                        except sr.UnknownValueError:
                                vote='0'
                                ser.write((vote+'**\r').encode())
                        except sr.RequestError as e:
                                vote='0'
                                ser.write((vote+'**\r').encode())


                                
                        
                     
         
        elif msg =='k':
                
                        plinvalid.play()
                        plinvalid.seek(0.0)
        elif msg == 'o':
                        plungli.play()
                        plungli.seek(0.0)

        elif msg =='p':
                        plprayas.play()
                        plprayas.seek(0.0)

        elif msg == 'q':
                        plprayas.play()
                        plprayas.seek(0.0)
                        

        elif msg =='r':
                        plpunarpryaas.play()
                        plpunarpryaas.seek(0.0)


                        

        elif msg =='t':
                        plaapvote.play()
                        plaapvote.seek(0.0)

        elif msg =='u':
                        plvotekar.play()
                        plvotekar.seek(0.0)

        elif msg =='v':
                        plvikalp.play()
                        plvikalp.seek(0.0)
                        
                        

        elif msg =='w':
                        plamanya.play()
                        plamanya.seek(0.0)

        elif msg == 'x':
                        plmatdan.play()
                        plmatdan.seek(0.0)

        elif msg =='y':
                        plprayas.play()
                        plprayas.seek(0.0)

       
    
                        
        
                       
                        
      
                
        
        
    
        
        
                
                
        

