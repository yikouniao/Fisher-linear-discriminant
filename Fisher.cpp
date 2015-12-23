#include "Fisher.h"
#include <iostream>

using namespace std;
using namespace Eigen;

void Fisher::Train(DatSet& ds) {
  Matrix2d Sw_inv;
  ds.CalSwSumInv(Sw_inv);
  array<Vector2d, n_df> u;
  int n{ 0 };
  for (int i = TYPE_MINUS_1 + 1; i < TYPE_ALL - 1; ++i) {
    u_trans[i][i] = RowVector2d(0, 0);
    yt[i][i] = 0;
    for (int j = i + 1; j < TYPE_ALL; ++j) {
      u[n] = Sw_inv * static_cast<Vector2d>(ds.m[i] - ds.m[j]);
      Vector2d mm = static_cast<Vector2d>(ds.m[i] + ds.m[j]) / 2;
      u_trans[i][j] = u[n].transpose();
      u_trans[j][i] = -u_trans[i][j];
      yt[i][j] = u_trans[i][j] * mm;
      yt[j][i] = -yt[i][j];
      ++n;
    }
  }
}

void Fisher::Out() {
  cout << "\nFisher's discriminant parameter:\n";
  for (int i = 0; i < TYPE_ALL; ++i) {
    for (int j = i + 1; j < TYPE_ALL; ++j) {
      cout << "Type" << i + 1 << "-" << j + 1 << ": ";
      cout << "u_trans: [" << u_trans[i][j] << "]\t";
      cout << "yt: " << yt[i][j] << "\n";
    }
  }
}

void Fisher::DiscriDat(Dat& x) {
  bool is_type = false;
  for (int i = 0; i < TYPE_ALL; ++i) {
    for (int j = 0; j < TYPE_ALL; ++j) {
      if (i != j) {  // avoid yt[i][i]
        if (u_trans[i][j] * Vector2d(x) < yt[i][j]) {
          is_type = false;
          break;
        } else {
          is_type = true;
        }
      }  // if (i != j)
    }  // for (int j = 0; j < TYPE_ALL; ++j)
    if (is_type) {
      x.type_ = static_cast<DatType>(i);
      return;
    }
  }  // for (int i = 0; i < TYPE_ALL; ++i)
  if (!is_type) {
    x.type_ = TYPE_ALL;
  }
}

void Fisher::Discri(DatSet& ds) {
  for (auto& e : ds.datset_) {
    DiscriDat(e);
  }
}

void Fisher::TrainErrRate(DatSet& train) {
  cout << "\nError rate of train data:\n";
  DatSet result = train;
  Discri(result);
  ErrRate(train, result);
}

void Fisher::TestErrRate(DatSet& test, DatSet& result) {
  cout << "\nError rate of test data:\n";
  ErrRate(test, result);
}

void Fisher::ErrRate(DatSet& standard, DatSet& comparison) {
  array<int, TYPE_ALL_PLUS_1> n_err;
  array<double, TYPE_ALL_PLUS_1> rate_err;
  n_err.fill(0);
  rate_err.fill(0);
  for (int i = 0; i < standard.n[TYPE_ALL]; ++i) {
    if (standard.datset_[i].type_ != comparison.datset_[i].type_) {
      ++(n_err[standard.datset_[i].type_]);
      ++(n_err[TYPE_ALL]);
    }
  }
  cout << "\nType\tError/Total num\tError rate\n";
  for (int i = 0; i < TYPE_ALL_PLUS_1; ++i) {
    rate_err[i] = static_cast<double>(n_err[i]) / standard.n[i];
    (i == TYPE_ALL) ? cout << "all:\t" : cout << i + 1 << ":\t";
    cout << n_err[i] << "/" << standard.n[i] << "\t\t" << rate_err[i] << "\n";
  }
}