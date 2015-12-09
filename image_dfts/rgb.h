#ifndef rgb
#define rgb
#include <cmath>

class RGB {
public:
    RGB()
    {
      v_[0] = 0.0;
      v_[1] = 0.0;
      v_[2] = 0.0;
    }
    RGB(double R, double G, double B)
    {
      v_[0] = R;
      v_[1] = G;
      v_[2] = B;
    }
    RGB(const RGB& other)
    {
      v_[0] = other.v_[0];
      v_[1] = other.v_[1];
      v_[2] = other.v_[2];
    }

    RGB& operator =(const RGB& other)
    {
      v_[0] = other.v_[0];
      v_[1] = other.v_[1];
      v_[2] = other.v_[2];
      return *this;
    }

    void power(double exp) {
        v_[0] = pow(v_[0], exp);
        v_[1] = pow(v_[1], exp);
        v_[2] = pow(v_[2], exp);
    }

    double& operator[](size_t idx)
    {
      return v_[ idx ];
    }
    double operator[](size_t idx) const
    {
      return v_[ idx ];
    }
    void setCol(double R, double G, double B);
    double getR();
    double getG();
    double getB();

    void clamp();
private:
    double v_[3];
};

inline RGB operator *(const RGB& c1, const RGB& c2)
{
  return RGB(c1[0]* c2[0], c1[1] * c2[1], c1[2] * c2[2]);
}

inline RGB operator *(double s, const RGB& v)
{
  return RGB(s*v[0], s*v[1], s*v[2]);
}

inline RGB operator +(const RGB& a, const RGB& b)
{
  return RGB(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}


#endif // RGB

