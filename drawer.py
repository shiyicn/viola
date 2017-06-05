#---import some packages
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches

def draw(x, y, w, h, fig, color):
    ax1 = fig.add_subplot(111, aspect='equal')
    ax1.add_patch(
        patches.Rectangle(
            (x, 1-y-h),   # (x,y)
            w,          # width
            h,          # height
            facecolor = color,
            edgecolor = "black"
        )
    )

def draw_scaled(x, y, w, h, wi, hi, fig, color):
    wf = wi * 1.0
    hf = hi * 1.0
    draw(x/wf, y/hf, w/wf, h/hf, fig, color)

def draw_rectA(x, y, w, h, wi, hi, path):
    fig = plt.figure()
    draw_scaled(x, y, w/2.0, h, wi, hi, fig, "none")
    draw_scaled(x+w/2.0, y, w/2.0, h, wi, hi, fig, "black")
    fig.savefig(path, dpi=90, bbox_inches='tight')

def draw_rectB(x, y, w, h, wi, hi, path):
    fig = plt.figure()
    draw_scaled(x, y, w, h/2.0, wi, hi, fig, "black")
    draw_scaled(x, y+h/2.0, w, h/2.0, wi, hi, fig, "none")
    fig.savefig(path, dpi=90, bbox_inches='tight')

def draw_rectC(x, y, w, h, wi, hi, path):
    fig = plt.figure()
    draw_scaled(x, y, w/4.0, h, wi, hi, fig, "none")
    draw_scaled(x+w/4.0, y, w/2.0, h, wi, hi, fig, "black")
    draw_scaled(x+w*3/4.0, y, w/4.0, h, wi, hi, fig, "none")
    fig.savefig(path, dpi=90, bbox_inches='tight')

def draw_rectD(x, y, w, h, wi, hi, path):
    fig = plt.figure()
    draw_scaled(x, y, w/2.0, h/2.0, wi, hi, fig, "none")
    draw_scaled(x+w/2.0, y, w/2.0, h/2.0, wi, hi, fig, "black")
    draw_scaled(x, y+h/2.0, w/2.0, h/2.0, wi, hi, fig, "black")
    draw_scaled(x+w/2.0, y+h/2.0, w/2.0, h/2.0, wi, hi, fig, "none")
    fig.savefig(path, dpi=90, bbox_inches='tight')

def draw_rect_by_type(x, y, w, h, wi, hi, t, path):
    x = int(x)
    y = int(y)
    w = int(w)
    h = int(h)
    if t == '0' :
        draw_rectA(x, y, w, h, wi, hi, path)
    elif t == '1' :
        draw_rectB(x, y, w, h, wi, hi, path)
    elif t == '2' :
        draw_rectC(x, y, w, h, wi, hi, path)
    elif t == '3' :
        draw_rectD(x, y, w, h, wi, hi, path)
    else :
        print(t)

#open files
with open("result/strongInfo.txt") as f:
    data = f.read()

data = data.split('\n')

x = [row.split(' ')[0] for row in data]
y = [row.split(' ')[1] for row in data]
w = [row.split(' ')[2] for row in data]
h = [row.split(' ')[3] for row in data]
t = [row.split(' ')[4] for row in data]

wi = 112
hi = 92

for i in range(0, len(x)):
    draw_rect_by_type(x[i], y[i], w[i], h[i], wi, hi, t[i], "result/"+str(i)+".png")