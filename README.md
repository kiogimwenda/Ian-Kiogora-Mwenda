# DSP Toolbox in C

DSP Toolbox in C is a modular digital signal processing (DSP) library implemented in C. It provides a set of tools for signal generation, filtering, spectral analysis, convolution, modulation, and I/O operations. This project is designed to be educational, extensible, and suitable for both research and real-world DSP applications.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Building the Project](#building-the-project)
- [Running the Demo](#running-the-demo)
- [Running Unit Tests](#running-unit-tests)
- [License](#license)
- [Acknowledgements](#acknowledgements)
- [Contact](#contact)

## Overview

This DSP toolbox is organized into several modules:

- **Signal Generation:** Functions to generate sine, cosine, square, sawtooth, triangle, impulse, step, chirp, white noise, and pink noise signals.
- **Filtering:** Implementation of FIR filtering (with filter design using a windowed-sinc method and Hamming window) and IIR filtering (using Direct Form I and Direct Form II transposed).
- **FFT/IFFT:** A Fast Fourier Transform and its inverse based on an iterative Cooley-Tukey algorithm.
- **Window Functions:** Generation of common windows (Hamming, Hanning, Blackman, Rectangular).
- **Spectral Analysis:** Compute magnitude, phase, and power spectral density from FFT output.
- **Convolution:** Linear convolution of signals.
- **Modulation:** Basic Amplitude Modulation (AM) and Frequency Modulation (FM) schemes.
- **I/O Operations:** Read and write signal data to CSV files.
- **Utility Functions:** Helper functions for common tasks (e.g., printing vectors, checking power-of-two).

## Features

- **Modular Design:** Each functionality is implemented in separate modules (headers and source files), facilitating ease of testing and extension.
- **CMake Build System:** Uses CMake to support cross-platform builds with the final executable stored in the `bin` folder.
- **Dynamic Memory Management:** Uses dynamic allocation where necessary (e.g., convolution output).
- **Extensive Test Suite:** Unit tests for each module are provided under the `tests/` directory.
- **Educational & Extensible:** Ideal for learning DSP concepts and for further extension into more advanced applications.

## Project Structure


## Requirements

- **Compiler:** A C compiler that supports C99 (GCC, Clang, or MSVC).
- **CMake:** Version 3.10 or later.
- **Operating System:** Cross-platform (tested on Windows and Linux).

## Building the Project

1. **Clone the repository:**
   ```bash
   git clone https://github.com/kiogimwenda/Ian-Kiogora-Mwenda.git
   cd DSP_Toolbox
   ```

2. **Build the project:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the demo:**
   ```bash
   cd ../bin/Debug
   ./dsp_demo
   ```



