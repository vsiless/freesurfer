import sys
import os
import shutil
import select
import subprocess as sp
from .log import error


# run a shell command and return the exit code
def run(cmd, silent=False, executable='/bin/bash'):
  if silent:
    return sp.call(cmd, stdout=sp.DEVNULL, stderr=sp.DEVNULL, shell=True, executable=executable)
  else:
    return sp.call(cmd, shell=True, executable=executable)


# returns the output of a subprocess along with the exit code
def getoutput(cmd):
  result = sp.run(cmd, stdout=sp.PIPE, stderr=sp.STDOUT, shell=True, executable='/bin/bash')
  return result.stdout.decode('utf-8'), result.returncode


# removes a directory if it exists
def rmdir(dirpath):
  if os.path.exists(dirpath) and os.path.isdir(dirpath):
    shutil.rmtree(dirpath)


# remove extensions from a volume filename
def rmext(filename):
  for ext in ('.mgh', '.mgz', '.nii', '.nii.gz'):
    if filename.endswith(ext): return filename[:-len(ext)]


# custom pythonic source function
def source(filename):
  # source the file and return the resulting env
  output, ret = getoutput('. {0} 2>&1 /dev/null ; env'.format(filename))
  # parse the env output to a dict of env variables
  varlist = []
  for line in output.splitlines():
    pair = line.split('=', 1)
    if len(pair) == 1: varlist[-1][1] += '\n' + line
    else: varlist.append(pair)
  # update the python environ
  os.environ.update(dict(varlist))


# source a freesurfer environment
def sourceFS(fspath):
  os.environ['FREESURFER_HOME'] = fspath
  setup_script = os.path.join(fspath, 'SetUpFreeSurfer.sh')
  if not os.path.isfile(setup_script): return False
  source(setup_script)
  return True


def errorExit(message, ret=1):
  error(message)
  exit(ret)
