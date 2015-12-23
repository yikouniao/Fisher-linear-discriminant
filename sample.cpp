#include "sample.h"
#include "pic.h"
#include "Fisher.h"

void SamFisher(DatSet& train, DatSet& test, DatSet& result) {
  Dat2Pic(train, "train");
  Fisher fisher;
  fisher.Train(train);
  fisher.Out();
  fisher.TrainErrRate(train);
  Dat2Pic(test, "test");
  fisher.Discri(result);
  Dat2Pic(result, "result");
  fisher.TestErrRate(test, result);
}