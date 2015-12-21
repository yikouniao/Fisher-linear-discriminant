# basic-surpervised-classifications
Basic surpervised classifications in C++, including Fisher's linear discriminant, perceptron algorithm, W-H algorithm and H-K algorithm.  

Author: [yikouniao](https://github.com/yikouniao)  
Project link: https://github.com/yikouniao/basic-surpervised-classifications  

### Notes

 * The data for training and testing is generated by Matlab. Both data in two classes are normally distributed.
 * The data is two-dimensional.
 * The data is divided into two classes as an example.
 * Edit `enum DatType` in `dat.h` to modify the names and quantities of the classes.
 * The arguments for `int main(int argc, char** argv)` are:
```cpp
basic-surpervised-classifications.exe dat/train.txt dat/test.txt
```