#include "rt.h"

int		greyscaler(int color)
{
	return (int)(MIN(MIN(color & 0xFF, (color >> 8) & 0xFF), (color >> 16) & 0xFF) +
		MAX(MAX(color & 0xFF, (color >> 8) & 0xFF), (color >> 16) & 0xFF)) / 2 * (1 + 256 + 256 * 256);
}

void	greyscale(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], greyscaler(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

int		sepiacer(int color)
{

	return (
		(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.393 + (float)((color >> 8) & 0xFF) * 0.769 + (float)((color) & 0xFF) * 0.189)) << 16) |
		(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.349 + (float)((color >> 8) & 0xFF) * 0.686 + (float)((color) & 0xFF) * 0.168)) << 8) |
		(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.272 + (float)((color >> 8) & 0xFF) * 0.534 + (float)((color) & 0xFF) * 0.131)))
	);
}

void	sepia(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], sepiacer(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

int		cartooner(int color)
{
	return (((int)((color & 0xFF) / CARTOON_FACTOR) * CARTOON_FACTOR) |
		((int)(((color >> 8) & 0xFF) / CARTOON_FACTOR) * CARTOON_FACTOR << 8) |
		((int)(((color >> 16) & 0xFF) / CARTOON_FACTOR) * CARTOON_FACTOR << 16));
}

void	cartoon(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], cartooner(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}


int 	*boxes_for_gauss(double sigma, int n)
{
	int wl;
	int m;
	int *sizes;
	int i;

  wl = floor(sqrt((12 * sigma * sigma / (double)n) + 1));
  if (wl % 2 == 0)
  	wl--;
  m = (12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4.0 * (double)wl - 4.0);
  if (m - floor(m) >= 0.5)
  	m = ceil(m);
  else
  	m = floor(m);
  if (!(sizes = (int*)malloc(sizeof(int) * n)))
  	return NULL;
  i = 0;
  while (i < n)
  {
  	if (i < m)
			sizes[i] = wl;
		else
			sizes[i] = wl + 2;
		i++;
  }
  return sizes;
}

// scl, tcl, w, h, r
void boxBlurH_4(t_param *param, float r)
{
	// iarr;
	// ti;
	// fv;
	if (!param && !r)
		mprintf(1, "boxblurH");
 //  var iarr = 1 / (r+r+1);
 //  for(var i=0; i<h; i++) {
 //      var ti = i*w, li = ti, ri = ti+r;
 //      var fv = scl[ti], lv = scl[ti+w-1], val = (r+1)*fv;
 //      for(var j=0; j<r; j++) val += scl[ti+j];
 //      for(var j=0  ; j<=r ; j++) { val += scl[ri++] - fv       ;   tcl[ti++] = Math.round(val*iarr); }
 //      for(var j=r+1; j<w-r; j++) { val += scl[ri++] - scl[li++];   tcl[ti++] = Math.round(val*iarr); }
 //      for(var j=w-r; j<w  ; j++) { val += lv        - scl[li++];   tcl[ti++] = Math.round(val*iarr); }
 //  }
}

// scl, tcl, w, h, r
void boxBlurT_4(t_param *param, float r)
{
	if (!param && !r)
		mprintf(1, "boxBlurT");
    // var iarr = 1 / (r+r+1);
    // for(var i=0; i<w; i++) {
    //     var ti = i, li = ti, ri = ti+r*w;
    //     var fv = scl[ti], lv = scl[ti+w*(h-1)], val = (r+1)*fv;
    //     for(var j=0; j<r; j++) val += scl[ti+j*w];
    //     for(var j=0  ; j<=r ; j++) { val += scl[ri] - fv     ;  tcl[ti] = Math.round(val*iarr);  ri+=w; ti+=w; }
    //     for(var j=r+1; j<h-r; j++) { val += scl[ri] - scl[li];  tcl[ti] = Math.round(val*iarr);  li+=w; ri+=w; ti+=w; }
    //     for(var j=h-r; j<h  ; j++) { val += lv      - scl[li];  tcl[ti] = Math.round(val*iarr);  li+=w; ti+=w; }
    // }
}

// scl, tcl, w, h, r
void	box_blur(t_param *param, float r)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			param->pxl_infos[param->i[1]][param->i[0]]->calc_col = param->pxl_infos[param->i[1]][param->i[0]]->col;
			param->i[1]++;
		}
		param->i[0]++;
	}

  // boxBlurH_4(tcl, scl, w, h, r);
  // boxBlurT_4(scl, tcl, w, h, r);
  boxBlurH_4(param, r);
  boxBlurT_4(param, r);
}

// scl, tcl, w, h, double r
void	blur(t_param *param)
{
	int	*bxs;

  bxs = boxes_for_gauss(BLUR_RADIUS, 3);
  // boxBlur_4(scl, tcl, w, h, (bxs[0] - 1) / 2);
  // boxBlur_4(tcl, scl, w, h, (bxs[1] - 1) / 2);
  // boxBlur_4(scl, tcl, w, h, (bxs[2] - 1) / 2);
  box_blur(param, (float)(bxs[0] - 1) / 2);
  // box_blur(param, (float)(bxs[1] - 1) / 2);
  // box_blur(param, (float)(bxs[2] - 1) / 2);
}
