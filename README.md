# Runtag Preprocessor

Preprocessor of the Runtag detector. Basically just a wrapper around runtag detector (`lib-runtagdetector`) routines.

# Dependencies

`OpenCV` and `lib-runtagdetectar` headers and libs are required for compile and run. 
On ubuntu you can install `OpenCV` via `apt-get`. 
Runtag headers and libs are not yet published, request them by creating an issue here.

# Build
You should specify runtag headers and library dirs in `CMakeList.txt`.
Then to compile binary code, run

```bash
cd ~/.../runtag-preprocessor
mkdir build
cd ./build
cmake ..
make
```

This will prepare `setup.py` and build `preprocessor.so`

#Install

In `build` dir run `sudo ./setup.py install` this will copy `.so` and `.py` files to your python dist-packages


#Use

```python
import cv2
import runtag.preprocessor as p

i = cv2.imread('./image.jpg', 0)
c = p.candidates(i)
```

This will select marker-like shapes form image. Here `c` will be a list of tuples, each tuple is a pair of marker candidate bounding box and its image (as ND array). Bounding box is a 4-tuple of points. Each point is a 2-tuple of floats, (x,y)
