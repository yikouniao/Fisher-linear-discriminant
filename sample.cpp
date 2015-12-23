#include "sample.h"
#include "pic.h"
#include "Fisher/Fisher.h"

void SamFisher(char* f_train, char* f_test) {
  FisherDatSet train(f_train);
  Dat2Pic(train, "Fisher train");
  Fisher fisher;
  fisher.Train(train);
  fisher.Out();
  fisher.TrainErrRate(train);
  FisherDatSet test(f_test);
  Dat2Pic(test, "Fisher test");
  FisherDatSet result = test;
  fisher.Discri(result);
  Dat2Pic(result, "Fisher result");
  fisher.TestErrRate(test, result);
}