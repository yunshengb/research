from config import *
from os import system
from glob import glob

cmd = ''
if APP_TYPE == 'qa':
  file = open(FILE_PATH, 'r')
  lines = file.readlines()
  file.close()
  for line in lines:
    cmd += 'tq\n'
    cmd += line.split(',')[FIELD_ID].replace('"', '').strip()
    cmd += '\n'
elif APP_TYPE == 'asr':
  files = glob('../asr_qa/speech/*.wav')
  for file_path in files:
    cmd += 'ta\n'
    cmd += file_path
    cmd += '\n'
else:
  raise RuntimeError('Unrecognized app type')
cmd += 'qq'
print(cmd)

system('echo "{}" | ./X'.format(cmd));
