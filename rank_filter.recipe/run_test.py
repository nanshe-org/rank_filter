#!/usr/bin/env python


import os
import subprocess
import sys


def main(*argv):
    argv = list(argv)

    os.environ["PYTHONPATH"] = os.environ["SRC_DIR"] + ":" + os.environ.get("PYTHONPATH", "")

    return(subprocess.check_call(["python", "-m", "unittest", "test"] + argv[1:],
                                 stdin=sys.stdin,
                                 stdout=sys.stdout,
                                 stderr=sys.stderr))


if __name__ == "__main__":
    sys.exit(main(*sys.argv))
