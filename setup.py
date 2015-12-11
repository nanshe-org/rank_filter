import os
import sys
from glob import glob
from distutils.sysconfig import get_config_var, get_python_inc
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as _build_ext

import versioneer


class build_ext(_build_ext):
    def finalize_options(self):
        _build_ext.finalize_options(self)
        # Prevent numpy from thinking it is still in its setup process:
        __builtins__.__NUMPY_SETUP__ = False
        import numpy
        self.include_dirs.append(numpy.get_include())

def readme():
    with open("README.rst", "r") as f:
        return(f.read())


version=versioneer.get_version()

cython_dep = ["Cython >= 0.23"]
numpy_dep = ["numpy >= 1.7"]
boost_dep = ["boost >= 1.56"]
boost_dep = (boost_dep if sys.argv[1] == "bdist_conda" else [])

setup_requires = cython_dep + numpy_dep
setup_requires = [] if sys.argv[1] == "bdist_conda" else setup_requires
build_requires = setup_requires + boost_dep
install_requires = numpy_dep + boost_dep
tests_require = cython_dep + numpy_dep

include_dirs = [
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "include"),
    os.path.dirname(get_python_inc()),
    get_python_inc()
]
library_dirs = [get_config_var("LIBDIR")]
sources = glob("src/*.pxd") + glob("src/*.pyx") + glob("src/*.cpp")
libraries = ["boost_container"]
extra_compile_args = ["-std=c++11"]
extra_compile_args += ["-mmacosx-version-min=10.7", "-stdlib=libc++"] if sys.platform == "darwin" else []


setup(
    name="rank_filter",
    version=version,
    description = "A simple python module containing an in-place linear rank filter optimized in C++.",
    long_description=readme(),
    platforms=['Linux'],
    classifiers=[
        'Intended Audience :: Developers',
        'License :: OSI Approved :: BSD License',
        'Operating System :: POSIX :: Linux',
        'Programming Language :: C++',
        'Programming Language :: Cython',
        'Programming Language :: Python',
        'Topic :: Software Development :: Libraries'
    ],
    author="John Kirkham",
    author_email="kirkhamj@janelia.hhmi.org",
    url="https://github.com/nanshe-org/rank_filter",
    download_url="https://github.com/nanshe-org/rank_filter/archive/v%s.tar.gz" % version,
    cmdclass=dict(
        versioneer.get_cmdclass().items() +
        [
            ('build_ext', build_ext)
        ]
    ),
    setup_requires=setup_requires,
    build_requires=build_requires,
    install_requires=install_requires,
    tests_require=tests_require,
    test_suite="test",
    headers=glob("include/*.hxx"),
    ext_modules=[Extension("rank_filter",
                            sources,
                            include_dirs=include_dirs,
                            library_dirs=library_dirs,
                            libraries=libraries,
                            extra_compile_args=extra_compile_args,
                            language="c++")],
    zip_safe=False
)
