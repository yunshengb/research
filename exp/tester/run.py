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
  files = glob(DIR_PATH + '/*.wav')
  for i, file_path in enumerate(files):
    cmd += 'ta\n'
    cmd += file_path
    cmd += '\n'
elif APP_TYPE == 'cl':
  file = open(FILE_PATH, 'r')
  lines = file.readlines()
  file.close()
  for line in lines:
    cmd += 'tcl\n'
    cmd += line.split(',')[FIELD_ID].replace('"', '').strip()
    cmd += '\n\n' # no image at this point
else:
  raise RuntimeError('Unrecognized app type')
cmd += 'qq'
print(cmd)

system('echo "{}" | ./X'.format(cmd))
