#!/usr/bin/env python


import subprocess
import sys


def main(*argv):
    argv = list(argv)

    sys.path.insert(0, argv[1])

    return(subprocess.check_call([sys.executable, "-m", "unittest", "discover", "-s"] + argv[2:],
                                 stdin=sys.stdin,
                                 stdout=sys.stdout,
                                 stderr=sys.stderr))


if __name__ == "__main__":
    sys.exit(main(*sys.argv))
