# Change Log

All notable changes to imquery will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## Unreleased
### Added
- Added `getIndex` and `setIndex` to `QValue`. Strings can now be indexed.
- `compile` function: Parses a string into a function object that can be called from within imquery.
- `version` function: Get the version of imquery.
- `char` function: Get a string from a character code.
- `find` function: find the position of a string

### Changed
- Lambda block syntax now does away with the `=>`, while blockless syntax keeps it.
- Updated ANTLR to 4.7

## [0.5.0] - 2017-4-18
### Added
- Shorthand math operators (`+=`, `-=`, `*=`, `/=`, `%=`)
- This changelog
- `error` function
- `hash` function
- `try` function
- `QColor.mag` function
- import chaining/io rewriting
- removed restriction on setting outputs multiple times

### Changed
- Fixed function subcontexts setting the wrong variables as arguments due to a parent context having another variable named the same way.

## [0.4.2] - 2017-3-31
### Changed
- Image selections didn't throw errors on certain coordinate ranges despite them being out of bounds.

## [0.4.1] - 2017-3-6
### Changed
- Fixed crash due to contexts not marking return values for the GC
- Fixed incorrect help text in iqc that showed `NoBarriers` as the default GC mode

## [0.4.0] - 2017-3-6
### Added
- Import and export statements
- cimq - basic bindings of imq to C

### Changed
- imq is now a shared library
- Garbage collection now uses the `Barriers` mode by default

## [0.3.1] - 2017-1-25
### Changed
- Fixed crash due to GC cleanup of VBlock::lastResult in iqc

## [0.3.0] - 2017-1-25
### Added
- String type
- Image loading + saving from within the standard library
- Expression support for command-line inputs in iqc
- GC memory tracking

### Changed
- Upgraded to ANTLR 4.6

## [0.2.0] - 2016-12-21
### Added
- Garbage collection
- Iterator support for QObject types
- For-each loop
- NaN value for floats
- Additional math functionality (sin, cos, abs, min, max, clamp, pow, sqrt)

### Changed
- valgrind is now used on CI builds
- Reference counting has been dropped in favor of garbage collection where possible
- Removed ContextPtr type
- Memory leak of VBlock objects due to parser errors has been fixed
- Allow fieldExpr on the left side of set_field_stm and set_index_stm

## 0.1.0 - 2016-12-11
### Added
- Initial release

[Unreleased]: https://github.com/redxdev/imquery/compare/v0.5.0...HEAD
[0.5.0]: https://github.com/redxdev/imquery/compare/v0.4.2...v0.5.0
[0.4.2]: https://github.com/redxdev/imquery/compare/v0.4.1...v0.4.2
[0.4.1]: https://github.com/redxdev/imquery/compare/v0.4...v0.4.1
[0.4.0]: https://github.com/redxdev/imquery/compare/v0.3.1...v0.4
[0.3.1]: https://github.com/redxdev/imquery/compare/v0.3...v0.3.1
[0.3.0]: https://github.com/redxdev/imquery/compare/v0.2...v0.3
[0.2.0]: https://github.com/redxdev/imquery/compare/v0.1...v0.2