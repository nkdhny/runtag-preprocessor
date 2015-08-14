import base64
import numpy as np

def unpack_shape(shape_serial):
    shape_bytes = bytearray(base64.b64decode(shape_serial))

    s = shape_bytes[::-1]

    rows_h = s.pop()
    rows_l = s.pop()
    rows = rows_h * 256 + rows_l

    cols_h = s.pop()
    cols_l = s.pop()
    cols = cols_h * 256 + cols_l

    bit = 0

    portion = 0

    shape = np.zeros((rows, cols), dtype='uint8')

    try:
        for row in range(0, rows):
            for col in range(0, cols):
                if bit % 8 == 0:
                    portion = s.pop()
                    bit = 0

                if portion & 0x80 > 0:
                    shape[row, col] = 255

                portion <<= 1

                bit += 1
    except Exception as e:
        print e

    return shape

def pack_shape(shape_img):
    builder = bytearray()
    rows, cols, _ = img.shape

    rows_l = rows%256
    rows_h = rows>>8
    assert rows_h <= 256

    cols_l = cols%256
    cols_h = cols>>8
    assert cols_h <=256

    builder.append(rows_h)
    builder.append(rows_l)
    builder.append(cols_h)
    builder.append(cols_l)

    bit = 0
    portion = 0

    for row in range(0, rows):
        for col in range(0, cols):
            if bit == 8:
                builder.append(portion)
                portion = 0
                bit = 0
            portion <<= 1
            bit+=1

            if shape_img[row, col] > 120:
                portion |= 1
    if bit != 0:
        portion <<= (8-bit)
        builder.append(portion)

    return base64.b64encode(builder)




