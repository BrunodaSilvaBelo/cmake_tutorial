#ifndef TEMPLATED_H
#define TEMPLATED_H

namespace teste {
template <typename T> class X {
  template <typename U> class Y {
  public:
    Y();
    U& value();
    void print();
    ~Y();

  private:
    U* u;
  } Y<int> y;

public:
  X(T t) { y.value() = t }
  void print() { y.print() }
}
} // namespace teste

#endif /* TEMPLATED_H */
