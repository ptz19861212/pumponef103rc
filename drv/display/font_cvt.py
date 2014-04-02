#!/usr/bin/python2
#encoding:gb2312

file_object = open('font_ascii.c')
file_w = open('font_ascii.fi', 'w')

size_xy = [0, 0]
font = []
font_all = []
# 一个字占有的字节长度
length = 0

try:
    for line in file_object:
        line_lstrip = line.lstrip()
        if (line_lstrip.startswith('/')):
            file_w.write(line)
            font_all = []
            length = size_xy[0] * size_xy[1]
        elif (line_lstrip.startswith('*')):
            file_w.write(line)
        elif (line_lstrip.startswith('{')):
            file_w.write(line)
        elif (line_lstrip.startswith('}')):
            file_w.write(line)
        elif (line_lstrip.startswith('const')):
            file_w.write(line)
            size_all = line_lstrip.split(' ')
            for size in size_all:
                if (size.startswith('cFont')):
                    size_rep = size.replace('cFontAscii', ' ')
                    size_rep = size_rep.replace('x', ' ')
                    size_rep = size_rep.replace('[]', ' ')
                    size_rep = size_rep.strip()
                    size_xy = size_rep.split(' ')
            size_xy[0] = int(size_xy[0])
            if (int(size_xy[1]) % 8):
                size_xy[1] = (int(size_xy[1]) / 8) + 1
            else:
                size_xy[1] = (int(size_xy[1]) / 8)
            length = size_xy[0] * size_xy[1]
        elif (line_lstrip.startswith('0x')):
            font = line_lstrip.split(',')
            # 最后一个逗号会带来额外的一个数字
            font.pop()
            font_all.extend(font)
            if ((size_xy[0] * size_xy[1]) == len(font_all)):
                font = []
                offset = size_xy[1] & 0x07
                for ly in reversed(range(size_xy[1])):
                    for lx in range(size_xy[0]):
                        if (ly == 0):
                            font_each = (hex(font_all[ly * size_xy[0] + lx])
                                            >> (8 - offset))
                        else:
                            font_each = (hex(font_all[ly * size_xy[0] + lx])
                                            >> (8 - offset)) \
                                            | (hex(font_all[(ly - 1) 
                                            * size_xy[0] + lx]) << offset)
                        #font.append(font_all[ly * size_xy[0] + lx])
                        font.append(font_eah)
                    font_write = ', '.join(font)
                    font = []
                    file_w.write(font_write + ',\n')
                
                #while (length):
                    #if (length < size_xy[0]):
                        #font_write = ', '.join(font_all)
                        #file_w.write(font_write + ',\n')
                        #length = 0
                    #else:
                        #font = font_all[0:(size_xy[0])]
                        #font_all = font_all[(size_xy[0]):]
                        #font_write = ', '.join(font)
                        #file_w.write(font_write + ',\n')
                        #length -= size_xy[0]

        print(line_lstrip)
finally:
    file_object.close()
    file_w.close()
