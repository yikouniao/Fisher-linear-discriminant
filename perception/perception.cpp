#include "perception.h"
#include <iostream>
#include <fstream>

namespace Percp {
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
    } else if (c[0] == 'c') {
      dat_type = TYPE_C;
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
  w_.fill(Vector3d(0,0,0));
  p_ = 10;
}

D_F::~D_F() {}

void D_F::SetP(double p) {
  p_ = p;
}

void D_F::Train(DatSet& ds) {
  array<double, TYPE_ALL> d; // discriminant function
  unsigned int k = 0; // step counter
  int i{ 0 }; // pointer to current element of ds
  while (k < ds.size()) {
    int d_max = TYPE_MINUS_1 + 1; // d[d_max] is max in d[...]
    for (int j = 0; j < TYPE_ALL; ++j) {
      // calculate discriminant function
      d[j] = w_[j].transpose() * ds[i].xy_;
      d_max = (d[j] > d[d_max]) ? j : d_max;
    }
    if (ds[i].type_ == d_max) { // right type
      ++k;
    } else { // wrong type
      k = 0;
      for (int j = 0; j < TYPE_ALL; ++j) { // modify weight vector
        if (ds[i].type_ == j) {
          w_[j] += p_ * ds[i].xy_;
        } else {
          w_[j] -= p_ * ds[i].xy_;
        }
      } // for (int j = 0; j < TYPE_ALL; ++j)
    } // if (ds[i].type_ == d_max) else
    i = (++i == ds.size()) ? 0 : i;
  } // while (k < ds.size())
}

void D_F::Test(DatSet& ds) {
  for (auto& e : ds) {
    array<double, TYPE_ALL> d; // discriminant function
    int d_max = TYPE_MINUS_1 + 1; // d[d_max] is max in d[...]
    for (int i = 0; i < TYPE_ALL; ++i) {
      d[i] = w_[i].transpose() * e.xy_;
      d_max = (d[i] > d[d_max]) ? i : d_max;
    }
    e.type_ = static_cast<DatType>(d_max);
  }
}

void D_F::Out() {
  cout << "\nperception's discriminant parameter:\n";
  for (int i = 0; i < TYPE_ALL; ++i) {
      cout << "Type" << i + 1 << ": ";
      cout << "w: [" << w_[i].transpose() << "]'\n";
  }
}

void D_F::ErrRate(DatSet& standard, DatSet& comparison) {
  cout << "\nperception approach error rate:\n";
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
} // namespace Percp