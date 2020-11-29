#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
uint8_t* create_buffer(int h, int w)
{
    return malloc(h * w * 4 * sizeof(uint8_t));
}

EMSCRIPTEN_KEEPALIVE
void destroy_buffer(uint8_t* p)
{
    free(p);
}

int mandelbrot(double cr, double ci)
{
    double zr, zi, _zr, _zi;
    zr = 0.0;
    zi = 0.0;
    for(int i=0;i<255;i++){
        _zr = zr*zr - zi*zi + cr;
        _zi = 2.0*zr*zi + ci;
        zr = _zr;
        zi = _zi;
        if(zr*zr + zi*zi > 4.0){
            return i;
        }
    }
    return 255;
}

EMSCRIPTEN_KEEPALIVE
void draw_mandelbrot(uint8_t* p, int h, int w)
{
    double xmin = -1.5;
    double ymin = -1.0;
    double xmax = 0.5;
    double ymax = 1.0;
    double dx = (xmax - xmin)/(double)w;
    double dy = (ymax - ymin)/(double)h;

    for(int iy=0;iy<h;iy++){
        for(int ix=0;ix<w;ix++){
            double x = xmin + dx*(double)ix;
            double y = ymin + dy*(double)iy;
            int ret = mandelbrot(x, y);
            p[iy*w*4+ix*4+0] = ret;
            p[iy*w*4+ix*4+1] = ret;
            p[iy*w*4+ix*4+2] = ret;
            p[iy*w*4+ix*4+3] = 255;
        }
    }
}

int main(void)
{
    printf("Hello, wasm!\n");
    return 0;
}