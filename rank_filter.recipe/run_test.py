#!/usr/bin/env python
    
import os
import subprocess
import sys
import unittest


if __name__ == "__main__":
    test = os.path.join(os.environ["SRC_DIR"], "test")
    print(test)
    sys.argv = [test] + sys.argv

    unittest.main()
