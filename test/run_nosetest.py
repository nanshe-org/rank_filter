import os
import subprocess
import sys

import nose


def main(argv):
    argv = list(argv)

    os.environ["PYTHONPATH"] = os.getcwd() + "/slib" + ":" + os.environ["PYTHONPATH"]

    return(subprocess.check_call([sys.executable, nose.core.__file__] + argv[1:],
                                 stdin=sys.stdin,
                                 stdout=sys.stdout,
                                 stderr=sys.stderr)
    )


if __name__ == "__main__":
    sys.exit(main(sys.argv))
