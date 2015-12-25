#include "H-K.h"
#include <iostream>
#include <fstream>

namespace HK {
using namespace std;
using namespace Eigen;

void InitDatSet(DatSet& ds, char* f_name) {
  ifstream f(f_name);
  if (!f)
  {
    cerr << f_name << " could not be opened!\n" << endl;
    exit(1);
  }
  array<double, 2> xy;
  array<char, 5> c;
  while (1) {
    f.getline(&c[0], 65532, '\t');  // read x_
    if (c[0] == '#')
      break;
    xy[0] = char2double(&c[0]);
    f.getline(&c[0], 65532, '\t');  // read y_
    xy[1] = char2double(&c[0]);
    f.getline(&c[0], 65532, '\n');  // read type_
    DatType dat_type;
    if (c[0] == 'a') {
      dat_type = TYPE_A;
    } else if (c[0] == 'b') {
      dat_type = TYPE_B;
    } else {
      dat_type = TYPE_ALL;
    }
    ds.push_back(Dat{ xy, dat_type });
  }  // while (1)
}

static double char2double(char* s) {
  char* p{ s };  // save the start position of the string
  double a{ 0 };
  while (*s) {  // let s point to '\0'
    ++s;
  }
  int i{ 0 };
  while (!(--s < p)) {
    a += (*s - 48) * pow(10, i++);
  }
  return a;
}

D_F::D_F()
{
  w_ = Vector3d(0,0,0);
  p_ = 1;
  threshold_ = 0.1;
}

D_F::~D_F() {}

void D_F::SetP(double p) {
  p_ = p;
}

void D_F::SetThreshold(double threshold) {
  threshold_ = threshold;
}

void D_F::Train(DatSet& ds) {
  MatrixXd X(ds.size(), 3); // data
  VectorXd b(ds.size()); // margin vector
  for (unsigned int i = 0; i < ds.size(); ++i) {
    X.row(i) = (ds[i].type_ == TYPE_A) ? ds[i].xy_ : -ds[i].xy_;
    b(i) = 1;
  }
  std::cout << "X\n" << X << '\n';
  std::cout << "b\n" << b << '\n';
  // pseudo-inverse matrix
  MatrixXd X_pi = (X.transpose() * X).inverse() * X.transpose();
  std::cout << "X+\n" << X_pi<< '\n';
  MatrixXd e(ds.size(), 1); // error vector
  w_ = X_pi * b;
  e = X * w_ - b;
  std::cout << "w\n" << w_ << '\n';
  std::cout << "e\n" << e << '\n';
  while (!IsLittle(e, threshold_)) {
    w_ += p_ * X_pi * (e + e.cwiseAbs());
    b += p_ * (e + e.cwiseAbs());
    w_ = X_pi * b;
    e = X * w_ - b;
  }
}

void D_F::Test(DatSet& ds) {
  for (auto& e : ds) {
    double d; // discriminant function
    d = w_.transpose() * e.xy_;
    e.type_ = (d > 0) ? TYPE_A : TYPE_B;
  }
}

void D_F::Out() {
  cout << "\nH-K algorithm's discriminant parameter:\n";
  cout << "w: [" << w_.transpose() << "]'\n";
}

void D_F::ErrRate(DatSet& standard, DatSet& comparison) {
  cout << "\nH-K algorithm error rate:\n";
  array<int, TYPE_ALL_PLUS_1> n;
  array<int, TYPE_ALL_PLUS_1> n_err;
  array<double, TYPE_ALL_PLUS_1> rate_err;
  n.fill(0);
  n_err.fill(0);
  rate_err.fill(0);
  for (unsigned int i = 0; i < standard.size(); ++i) {
    if (standard[i].type_ != comparison[i].type_) {
      ++(n_err[standard[i].type_]);
      ++(n_err[TYPE_ALL]);
    }
    ++(n[standard[i].type_]);
    ++(n[TYPE_ALL]);
  }
  cout << "\nType\tError/Total num\tError rate\n";
  for (int i = 0; i < TYPE_ALL_PLUS_1; ++i) {
    rate_err[i] = static_cast<double>(n_err[i]) / n[i];
    (i == TYPE_ALL) ? cout << "all:\t" : cout << i + 1 << ":\t";
    cout << n_err[i] << "/" << n[i] << "\t\t";
    cout << rate_err[i] * 100 << "%\n";
  }
}
} // namespace HK