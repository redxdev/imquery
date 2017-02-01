# imquery

[![Build Status](https://travis-ci.org/redxdev/imquery.svg?branch=master)](https://travis-ci.org/redxdev/imquery)

imquery is a simple scripting language designed around image manipulation.

Quick example:

    in input = image();
    out output = image(input.w, input.h);
    output: ((color.each((v) => sin(v * 2 * pi)) + 1) / 2 + {0.,1.}).clamp() from input;

Turns this
![flowers](https://github.com/redxdev/imquery/raw/master/images/flowers.png)

into this

![filtered flowers](https://github.com/redxdev/imquery/raw/master/images/readme-output.png)

## Editor

An editor is in development and can be found [here](https://github.com/redxdev/iqed).

## Dependencies

imquery depends on [ANTLR](http://www.antlr.org/) for parsing. Download or build the ANTLR 4.6
jar and install the 4.6 Cpp runtime. ANTLR's source code is available [here](https://github.com/antlr/antlr4)

Additionally, you will have to build the cpp runtime for antlr.

imquery also depends on [google test](https://github.com/google/googletest) for unit testing.

Finally, imquery heavily relies on C++11 features, so your compiler must support C++11. In
practice, VS2015 and any recentish versions of GCC and clang should work.

## Building

imquery uses [premake5](https://premake.github.io/) as the build system. Install premake5,
then copy `environment.lua.dist` to `environment.lua` and edit to your liking.

Once all dependencies are installed and `environment.lua` is setup correctly, run the following
command to generate a project for your preferred build system:

    premake5 <project-type>

premake5 supports a number of build systems. Some common ones are `vs2015`, `gmake`, and `xcode4`.
Once the projects have generated without errors, you may use them to build imquery.

## Projects

imquery is made up of three projects:

* imq - this is a shared library that provides the imquery interpreter and standard
libraries.
* testimq - gtest unit testing.
* iqc - the imquery command prompt.
* cimq - a binding of imq to C, for integration into other languages. This is not meant to be a
full set of bindings, just enough to cover the basics.

### iqc

Unless you are embedding imquery inside another application, iqc is primarily how you will
interact with imquery. It provides an interactive command console and a way to run imquery scripts
(*.imq).

## Tutorials

* [Getting Started](https://github.com/redxdev/imquery/blob/master/docs/GettingStarted.md)
