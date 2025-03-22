#include <cmath>
#include <iostream>

class Vector3 {
public:
  /*
   * STATIC PROPERTIES
   */
  static Vector3 back() { return Vector3(0, 0, -1); }
  static Vector3 down() { return Vector3(0, -1, 0); }
  static Vector3 forward() { return Vector3(0, 0, 1); }
  static Vector3 left() { return Vector3(-1, 0, 0); }
  static Vector3 one() { return Vector3(1, 1, 1); }
  static Vector3 right() { return Vector3(1, 0, 0); }
  static Vector3 up() { return Vector3(0, 1, 0); }
  static Vector3 zero() { return Vector3(0, 0, 0); }

  /*
   * CONSTUCTOR
   */
  Vector3(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;
  }
  ~Vector3();

  /*
   * PROPERTIES
   */
  double magnitude() { return _x * _x + _y * _y + _z * _z; }
  Vector3 normalized() {
    double x, y, z;
    if (_x > 0)
      x = 1;
    if (_y > 0)
      y = 1;
    if (_z > 0)
      z = 1;

    return Vector3(x, y, z);
  }
  double sqrMagnitude() { return sqrt(magnitude()); }
  double x() { return _x; }
  double y() { return _y; }
  double z() { return _z; }

  /*
   * PUBLIC METHODS
   */
  void Set(Vector3 vec) {
    _x = vec.x();
    _y = vec.y();
    _z = vec.z();
  }
  void ToString() { std::cout << "[" << _x << ", " << _y << ", " << _z << "]"; }
  bool Equals(Vector3 vec) {
    bool flag = true;
    if (_x != vec._x)
      flag = false;
    if (_y != vec._y)
      flag = false;
    if (_z != vec._z)
      flag = false;
    return flag;
  }

  /*
   * STATIC METHODS
   */
  static float Angle(Vector3 from, Vector3 to);
  static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
  static Vector3 Cross(Vector3 lhs, Vector3 rhs);
  static float Distance(Vector3 a, Vector3 b);
  static float Dot(Vector3 lhs, Vector3 rhs) {
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
  }
  static Vector3 Max(Vector3 lhs, Vector3 rhs);
  static Vector3 Min(Vector3 lhs, Vector3 rhs);
  static Vector3 MoveTowards(Vector3 current, Vector3 target,
                             float maxDistanceDelta);
  void Normalize();
  static void OrthoNormalize(Vector3 normal, Vector3 tangent);
  static void OrthoNormalize(Vector3 normal, Vector3 tangent, Vector3 binormal);
  static Vector3 Project(Vector3 vector, Vector3 onNormal);
  static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);
  static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);
  static Vector3 RotateTowards(Vector3 current, Vector3 target,
                               float maxRadiansDelta, float maxMagnitudeDelta);
  static Vector3 Scale(Vector3 a, Vector3 b);
  static float SignedAngle(Vector3 from, Vector3 to, Vector3 axis);
  static Vector3 Slerp(Vector3 a, Vector3 b, float t);
  static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);
  // TODO: Implement Time.deltatime library
  static Vector3 SmoothDamp(Vector3 current, Vector3 target,
                            Vector3 currentVelocity, float smoothTime,
                            float maxSpeed = INFINITY, float deltaTime = 0.1f);
  static Vector3 Lerp(Vector3 a, Vector3 b, float t);
  static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);

  /*
   * OPERATORS
   */
  // TODO: Remake those operators in future (maybe)
  Vector3 operator-(Vector3 const &obj) {
    return Vector3(_x - obj._x, _y + obj._y, _z + obj._z);
  }
  Vector3 operator+(Vector3 const &obj) {
    return Vector3(_x + obj._x, _y + obj._y, _z + obj._z);
  }
  Vector3 operator*(Vector3 const &obj) {
    return Vector3(_x * obj._x, _y * obj._y, _z * obj._z);
  }
  Vector3 operator/(Vector3 const &obj) {
    return Vector3(_x / obj._x, _y / obj._y, _z * obj._z);
  }

private:
  double _x, _y, _z;
};
