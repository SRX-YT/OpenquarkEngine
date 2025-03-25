#include <cmath>
#include <iostream>
#include <math.h>
#include <string>

class Vector3 {
public:
  /*
   * STATIC PROPERTIES
   */
  static Vector3 back()    { return Vector3( 0,  0, -1); }
  static Vector3 down()    { return Vector3( 0, -1,  0); }
  static Vector3 forward() { return Vector3( 0,  0,  1); }
  static Vector3 left()    { return Vector3(-1,  0,  0); }
  static Vector3 one()     { return Vector3( 1,  1,  1); }
  static Vector3 right()   { return Vector3( 1,  0,  0); }
  static Vector3 up()      { return Vector3( 0,  1,  0); }
  static Vector3 zero()    { return Vector3( 0,  0,  0); }

  /*
   * CONSTRUCTOR
   */
  Vector3(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;
  }

  /*
   * PROPERTIES
   */
  double magnitude() { return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2)); }
  Vector3 normalized() {
    if (_x == 0 && _y == 0 && _z == 0) {
      return this->zero();
    }
    double magnitude_value = magnitude();
    double x = _x / magnitude_value;
    double y = _y / magnitude_value;
    double z = _z / magnitude_value;
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
  std::string ToString() {
    std::string res;
    res.append("[");
    res.append(std::to_string(_x));
    res.append(", ");
    res.append(std::to_string(_y));
    res.append(", ");
    res.append(std::to_string(_z));
    res.append("]");
    return res;
  }
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
  static float Angle(Vector3 from, Vector3 to) {
    float angle = (Dot(from, to)) / (from.magnitude() * to.magnitude());
    // Inverse cosine for the angle
    return acos(angle);
  }
  // static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
  static Vector3 Cross(Vector3 lhs, Vector3 rhs) {
    return Vector3(
                   lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                   lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                   lhs.x() * rhs.y() - lhs.y() * rhs.x()
                  );
  }
  static float Distance(Vector3 a, Vector3 b) {
    return sqrt(pow(b.x() - a.x(), 2) + pow(b.y() - a.y(), 2) + pow(b.z() - a.z(), 2));
  }
  static float Dot(Vector3 lhs, Vector3 rhs) {
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
  }
  static Vector3 Max(Vector3 lhs, Vector3 rhs) {
    double max_x = lhs.x() > rhs.x() ? lhs.x() : rhs.x();
    double max_y = lhs.y() > rhs.y() ? lhs.y() : rhs.y();
    double max_z = lhs.z() > rhs.z() ? lhs.z() : rhs.z();
    return Vector3(max_x, max_y, max_z);
  }
  static Vector3 Min(Vector3 lhs, Vector3 rhs) {
    double min_x = lhs.x() < rhs.x() ? lhs.x() : rhs.x();
    double min_y = lhs.y() < rhs.y() ? lhs.y() : rhs.y();
    double min_z = lhs.z() < rhs.z() ? lhs.z() : rhs.z();
    return Vector3(min_x, min_y, min_z);
  }
  // static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);
  void Normalize() {
    if (_x == 0 && _y == 0 && _z == 0) {
      return;
    }
    double magnitude_value = magnitude();
    _x /= magnitude_value;
    _y /= magnitude_value;
    _z /= magnitude_value;
  }
  // static void OrthoNormalize(Vector3 normal, Vector3 tangent);
  // static void OrthoNormalize(Vector3 normal, Vector3 tangent, Vector3 binormal);
  static Vector3 Project(Vector3 vector, Vector3 onNormal) {
    float aDot = Dot(vector, onNormal);
    float bDot = Dot(onNormal, onNormal);
    float value = aDot / bDot;
    return Vector3(onNormal._x * value, onNormal._y * value, onNormal._z * value);
  }
  static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal) {
    float dot = Dot(vector, planeNormal);
    Vector3 multiplyedVector = Vector3(planeNormal._x * dot, planeNormal._y * dot, planeNormal._z * dot);
    return vector - multiplyedVector;
  }
  static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal) {
    float dot = Dot(inDirection, inNormal);
    Vector3 multiplyedVector = Vector3(inNormal * 2 * dot);
    return inDirection - multiplyedVector;
  }
  // static Vector3 RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta);
  // static Vector3 Scale(Vector3 a, Vector3 b) { return a * b; }
  // static float SignedAngle(Vector3 from, Vector3 to, Vector3 axis);
  // static Vector3 Slerp(Vector3 a, Vector3 b, float t);
  // static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);
  // TODO: Implement Time.deltatime library
  // static Vector3 SmoothDamp(Vector3 current, Vector3 target, Vector3
  // currentVelocity, float smoothTime, float maxSpeed = INFINITY, float
  // deltaTime = 0.1f); static Vector3 Lerp(Vector3 a, Vector3 b, float t);
  // static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);

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
  Vector3 operator*(float value) {
    return Vector3(_x * value, _y * value, _z * value);
  }
  Vector3 operator/(Vector3 const &obj) {
    return Vector3(_x / obj._x, _y / obj._y, _z * obj._z);
  }

  /*
   *  TEST
   */
  static void Test() {
    Vector3 a = Vector3(3, 4, 0);
    Vector3 b = Vector3(0, 5, 12);
    Vector3 n = Vector3(0, 1, 0);

    std::cout << "Vector A: " << a.ToString() << std::endl;
    std::cout << "Vector B: " << b.ToString() << std::endl;
    std::cout << "Vector N: " << n.ToString() << std::endl;

    std::cout << std::endl;

    std::cout << "Magnitude A: " << a.magnitude() << std::endl;
    std::cout << "Expected 5" << std::endl;
    std::cout << "Magnitude B: " << b.magnitude() << std::endl;
    std::cout << "Expected 13" << std::endl;

    std::cout << std::endl;

    std::cout << "Normalized A: " << a.normalized().ToString() << std::endl;
    std::cout << "Expected (0.6, 0.8, 0)" << std::endl;
    std::cout << "Normalized B: " << b.normalized().ToString() << std::endl;
    std::cout << "Expected (0, 0.3846, 0.9231)" << std::endl;

    std::cout << std::endl;

    std::cout << "SqrMagnitude A: " << a.sqrMagnitude() << std::endl;
    std::cout << "Expected 25" << std::endl;
    std::cout << "SqrMagnitude B: " << b.sqrMagnitude() << std::endl;
    std::cout << "Expected 169" << std::endl;

    std::cout << std::endl;

    std::cout << "Angle: " << Vector3::Angle(a, b) << std::endl;
    std::cout << "Expected: 72.25" << std::endl;

    std::cout << std::endl;

    std::cout << "Cross: " << Vector3::Cross(a, b).ToString() << std::endl;
    std::cout << "Expected (48, -36, 15)" << std::endl;

    std::cout << std::endl;

    std::cout << "Distance: " << Vector3::Distance(a, b) << std::endl;
    std::cout << "Expected 12.41" << std::endl;

    std::cout << std::endl;

    std::cout << "Dot: " << Vector3::Dot(a, b) << std::endl;
    std::cout << "Expected 20" << std::endl;

    std::cout << std::endl;

    std::cout << "Max: " << Vector3::Max(a, b).ToString() << std::endl;
    std::cout << "Expected (3, 5, 12)" << std::endl;

    std::cout << std::endl;

    std::cout << "Min: " << Vector3::Min(a, b).ToString() << std::endl;
    std::cout << "Expected (0, 4, 0)" << std::endl;

    std::cout << std::endl;

    std::cout << "Project: " << Vector3::Project(a, b).ToString() << std::endl;
    std::cout << "Expected (0, 0.5917, 1.4201)" << std::endl;

    std::cout << std::endl;

    std::cout << "Project On Plane: " << Vector3::ProjectOnPlane(a, n).ToString()
              << std::endl;
    std::cout << "Expected (3, 0, 0)" << std::endl;

    std::cout << "Reflect: " << Vector3::Reflect(a, n).ToString() << std::endl;
    std::cout << "Expected (3, -4, 0)" << std::endl;
  }

private:
  double _x, _y, _z;
};
