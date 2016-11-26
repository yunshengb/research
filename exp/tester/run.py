from config import *
from os import system
from glob import glob
import pandas as pd

cmd = ''
if APP_TYPE == 'qa':
  data = pd.read_csv(FILE_PATH)
  for line in data[FIELD_NAME]:
    cmd += 'tq\n'
    cmd += line.replace('"', '').strip()
    cmd += '\n'
elif APP_TYPE == 'asr':
  files = glob(DIR_PATH + '/*.wav')
  for i, file_path in enumerate(files):
    cmd += 'ta\n'
    cmd += file_path
    cmd += '\n'
elif APP_TYPE == 'cl':
  data = pd.read_csv(FILE_PATH)
  for line in data[FIELD_NAME]:
    cmd += 'tcl\n'
    cmd += line.replace('"', '').strip()
    cmd += '\n\n' # no image at this point
else:
  raise RuntimeError('Unrecognized app type')
cmd += 'qq'
print(cmd)

system('echo "{}" | ./X'.format(cmd))
