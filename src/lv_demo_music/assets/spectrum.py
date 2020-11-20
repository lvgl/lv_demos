import numpy as np
import librosa
import math

print("Start loading")
audio, sample_rate = librosa.load('a.mp3', duration=60, offset=0, sr=15360)
print("Loaded")

spectrum = librosa.stft(audio)
print("Spectrum")
S = np.abs(spectrum)
print(len(spectrum))
print(len(spectrum[0]))

fout = open("spectrum.h", "w")

#for f in np.logspace(0,3,num=5, endpoint=True):
 #   print(f)
    
fn = 36
fs = int(len(S) / fn)
fout.write("uint16_t spectrum[][4] = {\n")
for t in range(0,len(S[0]-1)):
  fout.write("{ ")
  f_prev = 0 
#  for f in [10, 50, 300, 600]:
  for f in [8, 45, 300, 600]:
    v = 0
    for i in range(f_prev, f):
      v += S[i][t]
    #v = v / (f - f_prev)
    if v != 0:
      #v = int(math.log(v, 2) * 5)
      v = int(v/30)
    if v < 0:
      v = 0
      
    f_prev = f
    fout.write(str(int(v)) + ", ")
  fout.write("},\n")
fout.write("};\n")
fout.close()
