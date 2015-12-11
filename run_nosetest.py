import os
import subprocess
import sys

import nose


def main(argv):
    argv = list(argv)

    os.environ["PYTHONPATH"] = argv[1] + ":" + os.environ.get("PYTHONPATH", "")

    return(subprocess.check_call([sys.executable, nose.core.__file__] + argv[2:],
                                 stdin=sys.stdin,
                                 stdout=sys.stdout,
                                 stderr=sys.stderr)
    )


if __name__ == "__main__":
    sys.exit(main(sys.argv))
