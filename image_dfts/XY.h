#ifndef XY_H
#define XY_H
#include <QImage>
#include <cmath>

class XY {
public:
    XY()
    {
      v_[0] = 0.0;
      v_[1] = 0.0;
    }
    XY(double X, double Y)
    {
      v_[0] = X;
      v_[1] = Y;
    }
    XY(const XY& other)
    {
      v_[0] = other.v_[0];
      v_[1] = other.v_[1];
    }

    XY& operator =(const XY& other)
    {
      v_[0] = other.v_[0];
      v_[1] = other.v_[1];
      return *this;
    }

    void power(double exp) {
        v_[0] = pow(v_[0], exp);
        v_[1] = pow(v_[1], exp);
    }

    double& operator[](size_t idx)
    {
      return v_[ idx ];
    }
    double operator[](size_t idx) const
    {
      return v_[ idx ];
    }

    void setXY(double X, double Y) {
        v_[0] = X;
        v_[1] = Y;
    }

    double getX() { return v_[0]; }
    double getY() { return v_[1]; }

    // Return the cartesian (I think?) distance between a given point and
    // a point "other"
    double getDistance(XY other) {
        double Xdist = pow(v_[0] - other[0], 2.0);
        double Ydist = pow(v_[1] - other[1], 2.0);
        return sqrt(Xdist + Ydist);
    }

private:
    double v_[2];
};

inline XY operator *(const XY& c1, const XY& c2)
{
  return XY(c1[0]* c2[0], c1[1] * c2[1]);
}

inline XY operator *(double s, const XY& v)
{
  return XY(s*v[0], s*v[1]);
}

inline XY operator +(const XY& a, const XY& b)
{
  return XY(a[0]+b[0], a[1]+b[1]);
}

inline XY operator -(const XY&a, const XY& b)
{
    return XY(a[0]-b[0], a[1]-b[1]);
}




#endif // XY_H

