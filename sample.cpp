#include "sample.h"
#include "pic.h"
#include "Fisher/Fisher.h"
#include "perception/perception-dat.h"
#include "h-k/H-K.h"

void SamFisher(char* f_train, char* f_test) {
  using namespace Fisher;
  DatSet train(f_train);
  Dat2Pic(train, "Fisher train");
  D_F fisher;
  fisher.Train(train);
  fisher.Out();
  fisher.TrainErrRate(train);
  DatSet test(f_test);
  Dat2Pic(test, "Fisher test");
  DatSet result = test;
  fisher.Discri(result);
  Dat2Pic(result, "Fisher result");
  fisher.TestErrRate(test, result);
}

void SamPercp(char* f_train, char* f_test) {
  using namespace Percp;
  DatSet train;
  InitDatSet(train, f_train);
  Dat2Pic(train, "perception train");
  D_F perception;
  perception.SetP(2000);
  perception.Train(train);
  perception.Out();
  DatSet test;
  InitDatSet(test, f_test);
  Dat2Pic(test, "perception test");
  DatSet result = test;
  perception.Test(result);
  Dat2Pic(result, "perception result");
  perception.ErrRate(test, result);
}

void SamHK(char* f_train, char* f_test) {
  using namespace HK;
  DatSet train;
  InitDatSet(train, f_train);
  Dat2Pic(train, "HK train");
  D_F hk;
  hk.SetP(1);
  hk.SetThreshold(0.1);
  hk.Train(train);
  hk.Out();
  DatSet test;
  InitDatSet(test, f_test);
  Dat2Pic(test, "HK test");
  DatSet result = test;
  hk.Test(result);
  Dat2Pic(result, "HK result");
  hk.ErrRate(test, result);
}