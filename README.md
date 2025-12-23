# 📦 Huffman Image Compressor (C++ & Qt)

![Language](https://img.shields.io/badge/C++-17-00599C)
![GUI](https://img.shields.io/badge/GUI-Qt%205-green)
![Algorithm](https://img.shields.io/badge/Algorithm-Huffman%20Coding-orange)

## 📌 Project Overview
This project is a **Lossless Image Compression Tool** capable of shrinking file sizes by 40-50% without losing any visual data. It implements the **Huffman Coding Algorithm** from scratch using **C++**.

The tool is specifically optimized for **PGM (Portable Gray Map)** images, commonly used in medical imaging (DICOM), and features a user-friendly **Qt GUI** for easy encoding/decoding operations.

## ⚙️ Key Features
* **Core Algorithm:**
    * Implements **Greedy Strategy** using **Min-Heap (Priority Queue)** to build the Optimal Huffman Tree.
    * Generates variable-length binary codes based on pixel frequency (frequent pixels = shorter codes).
* **Serialization:** Saves the compressed data along with the Huffman Tree structure (Header) to allow perfect reconstruction.
* **Qt GUI:**
    * Visualize compression ratio.
    * Toggle between Compress/Decompress modes easily.
* **Performance:** Optimized C++ file I/O for handling large raw image binaries.

## 🛠️ Technical Implementation
The system relies on advanced Data Structures:
1.  **Frequency Map:** Hash map to count pixel occurrences.
2.  **Priority Queue:** To select the two smallest probability nodes iteratively.
3.  **Binary Tree:** To generate unique prefix codes (0/1 paths).
4.  **Bit Manipulation:** Packing bits into bytes for physical storage.

## 🚀 How to Build & Run
### Prerequisites
* C++ Compiler (GCC/Clang)
* Qt Creator (or Qt 5.x Libraries)

### Steps
1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/mariamashraf731/Huffman-Image-Compressor.git](https://github.com/mariamashraf731/Huffman-Image-Compressor.git)
    ```
2.  **Open in Qt Creator:**
    * Open `src/gui/GUI.pro`.
    * Configure Project & Build.
3.  **Run:**
    * Load a `.pgm` image to compress.
    * Or load a `.enc` file to decompress.

## 📄 Documentation
For the mathematical proof and algorithmic details, check the [Final Report](docs/Project_Report.pdf).