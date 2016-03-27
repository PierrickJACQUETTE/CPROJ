#include "conversionGraphic.h"

float miseAEchelleX(float x, float y,int size){
  return x*size/y;
}

float miseAEchelleY(float x, float y,int size){
  return size-(x*size/y);
}
