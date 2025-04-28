import argparse
import pathlib
import subprocess
import sys

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument('--out', type=pathlib.Path)
  parser.add_argument('input', type=pathlib.Path)
  parser.add_argument('--var-name')
  args = parser.parse_args()
  ir_file = args.out / (args.input.stem + '.ir')
  lib_file = args.out / (args.input.stem + '.metallib')
  header_file = args.out / (args.input.stem + '.h')
  subprocess.run([
    'xcrun', 'metal', '-o', ir_file, '-c', args.input
  ])
  subprocess.run([
    'xcrun', 'metallib', '-o', lib_file, ir_file
  ])
  subprocess.run([
    'xxd', '-i', '-n', args.var_name, lib_file, header_file
  ])
  return 0

if __name__ == '__main__':
  sys.exit(main())
