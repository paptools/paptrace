# paptrace

Platform-agnostic performance trace library.

## Building

To build the project, run:

```bash
cmake -S . -B build --install-prefix=$PWD/install
cmake --build build -j 8
```

## Installing

To install the project, run:

```bash
cmake --install build
```

## Tools

### Build/Install

A script has been provided to build and locally install the project at
`<repo root>/install`:

```bash
./tools/build
```

### Formatting

To keep the style of the code consistent, you can run a repository wide format
with:

```bash
./tools/format
```
