# Huffman Coding in C++ (binary tree)

## Project Description
This project implements **Huffman Coding**, a lossless compression algorithm that reduces file size based on character frequency. The algorithm builds a binary tree to generate variable-length codes, assigning shorter codes to more frequent characters and longer codes to less frequent ones.

## Features
- **Encoder and Decoder**: The application includes both encoding and decoding functionality for files.
- **Priority Queue**: Implemented using a Min-Heap to manage character frequencies during tree construction.
- **Input and Output Format**: The program reads any file type in binary mode, allowing flexibility across various file formats (e.g., `.txt`, `.bmp`, etc.). Encoded files are saved with a `.huff` extension.
- **Compression Rate Calculation**: Calculates the compression rate by comparing the original and compressed file sizes.

## Implementation Details
- **Node Class**: Represents each node in the Huffman tree, storing character frequencies and left and right child pointers.
- **Min Priority Queue**: A priority queue structure to manage nodes, supporting operations like extracting the minimum frequency node.
- **Encoding Table**: Stores prefix codes for each character in the file.
- **Huffman Class**: Builds the Huffman tree and handles encoding and decoding processes.

## Usage
### Compilation
To compile the project, ensure that all `.h` and `.cpp` files are in the same directory, then run:

```bash
g++ main.cpp Huffman.cpp -o huffman_program
```
## Running the Program
After compiling, you can encode or decode files:

1. **Encoding**:
   ```bash
   ./huffman_program
   ```

2. **Decoding**
- Choose the decoding option and provide the `.huff` file for decompression.

### Example
- **Input**: `example.txt`
- **Encoded Output**: `example.huff`
- **Decoded Output**: Restored `example.txt`
- 
## Implementation Notes.
- **Encoding buffer**: The encoding process uses an 8-bit buffer, so it is slow for encoding large files.

## Class Diagram
The primary classes include:
- `Node`: Represents each character and frequency in the tree.
- `MinPriorityQueue`: Manages nodes during tree construction.
- `TableCode`: Stores prefix codes.
- `Huffman`: Main class handling file I/O, tree construction, encoding, and decoding.

## License
This project is licensed under the MIT License.
