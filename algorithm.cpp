void BresenhamLine(int x0, int y0, int x1, int y1)
{
  int dx=x1-x0;
  int dy=y1-y0;
  int e = (dy<<1) - dx;
  plot(x0,y0);

  int y=y0;
  int x=x0;

  while(x<=x1)
  {
    if( D > 0)
    {
      y = y+1;
      plot(x,y);
      D = D + ((dy<<1)-(dx<<1));
    }
  else
    {
      plot(x,y);
      D = D + (dy<<1);
    }
}
}

void BresenhamCircle(int x0, int y0, int radius)
{
  int x = radius;
  int y = 0;
  int switchFlag = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0
 
  while(x >= y)
  {
    DrawPixel( x + x0,  y + y0);
    DrawPixel( y + x0,  x + y0);
    DrawPixel(-x + x0,  y + y0);
    DrawPixel(-y + x0,  x + y0);
    DrawPixel(-x + x0, -y + y0);
    DrawPixel(-y + x0, -x + y0);
    DrawPixel( x + x0, -y + y0);
    DrawPixel( y + x0, -x + y0);
    y++;
    if (switchFlag<=0)
    {
      switchFlag+= (y + 1)<<1;   // Change in decision criterion for y -> y+1
    }
    else
    {
      x--;
      switchFlag += ((y - x)<<1) + 1;   // Change for y -> y+1, x -> x-1
    }
  }
}
