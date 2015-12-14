#!/usr/bin/env python


import os
import subprocess
import sys


def main(*argv):
    argv = list(argv)

    return(subprocess.check_call([sys.executable, "-m", "unittest", "discover", "-s", os.environ["SRC_DIR"]] + argv[1:],
                                 stdin=sys.stdin,
                                 stdout=sys.stdout,
                                 stderr=sys.stderr))


if __name__ == "__main__":
    sys.exit(main(*sys.argv))
